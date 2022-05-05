#include "ofApp.h"

//-------------------------------------------------------------

/**
* func:		setCirclePos
* input:	circle parameters (ofVec3f),
*			circle id (int)
*			position seed offset (float)
* process:	calculates slightly random position coordinates
* output:	circle paramters (ofVec3f)
*/
ofVec3f ofApp::setCirclePos(ofVec3f circle, int id, float offset) {
	circle.x = ofMap(ofNoise(offset * pow(id, id) * sin(ofRandom(id))), 0.0f, 1.0f, 0.0f, ofGetWindowWidth());
	circle.y = ofMap(ofNoise(offset * pow(id, id) * cos(ofRandom(id))), 0.0f, 1.0f, 0.0f, ofGetWindowHeight());
	return circle;
}

/**
* func:		setCircleR
* input:	circle parameters (ofVec3f),
*			circle id (int)
* process:	calculates circle radius based on id
* output:	circle paramters (ofVec3f)
*/
ofVec3f ofApp::setCircleR(ofVec3f circle, int id) {
	circle.z = ofGetWindowHeight() / 3 * pow(1.618, id);
	return circle;
}

/**
* func:		getKeyColor
* input:	none
* process:	generates a random color
* output:	color (ofColor)
*/
ofColor ofApp::getKeyColor() {
	return ofColor(
		ofMap(ofNoise(ofRandom(255)), 0, 1, 0, 255),
		ofMap(sin(ofRandom(255)), 0, 1, 0, 255),
		ofMap(cos(ofRandom(255)), 0, 1, 0, 255),
		100
	);
}

/**
* func:		lerpColor
* input:	two colors to lerp between (ofColor),
* process:	lerps a random distance across the color space
*			between two colors
* output:	lerped color (ofColor)
*/
ofColor ofApp::lerpColor(ofColor keyColor, ofColor targetColor) {
	return keyColor.lerp(targetColor, ofRandom(1.0));
}

float ofApp::getDecay(float playback) {
	return 1 - playback / 100;
}

float ofApp::upperLowerGuard(float num, float max, float min) {
	if (num > max) {
		return max;
	}
	else if (num < min) {
		return min;
	}
	else {
		return num;
	}
}

void ofApp::setup() {
	// number of circles to represent the sound
	bands = 32;

	// resize for efficiency's sake
	circles.resize(bands);
	keyColors.resize(bands + 1); // need an extra key color for the lerping!
	colors.resize(bands);
	targetCircles.resize(bands);
	targetColors.resize(bands);

	// play the audio on loop
	chordsLoop.load("chords.mp3");
	chordsLoop.play();
	chordsLoop.setLoop(true);
	chordsLoop.setVolume(0.7f);

	// adjust these to control size and speed of circles
	playback = 0.3f;
	playMax = 1.0f;
	playMin = 0.2f;
	decay = getDecay(playback);

	// cut the audio into pieces and populate the fft array
	fft.resize(bands * (playMax + 1.0 - playback));
	for (auto band:fft) {
		band = 0.0f;
	}

	// set key colors for color harmony
	for (int i = 0; i < bands + 1; i++) {
		keyColors[i] = getKeyColor();
	}

	// generate circle parameters
	for (int i = 0; i < bands; i++) {
		// make sure to set targets to initial circles and colors
		targetCircles[i] = circles[i] = setCirclePos(setCircleR(circles[i], i), i, 1);
		targetColors[i] = colors[i] = lerpColor(keyColors[i], keyColors[i + 1]);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	// speed of animation on reset
	float speed = 0.1f;

	// update sound every frame
	ofSoundUpdate();

	// constratin the playback to between 0.2-0.7
	playback = upperLowerGuard(playback, playMax, playMin);

	// make decay dependent on playback
	decay = getDecay(playback);

	// update the playback speed
	chordsLoop.setSpeed(playback);

	// grab the sound spectrum for the bands
	soundSpectrum = ofSoundGetSpectrum(bands);

	// cut the audio into pieces and populate the fft array
	fft.resize(bands * (playMax + 1.0 - playback));

	for (int i = 0; i < bands; i++) {
		// decrease the bands using decay
		fft[i] *= decay;
		// don't let it go below zero
		if (fft[i] < soundSpectrum[i]) {
			fft[i] = soundSpectrum[i];
		}
	}

	// update the positions and colors with each frame
	for (int i = 0; i < bands; i++) {
		ofVec3f circle = circles[i];
		ofVec3f target = targetCircles[i];

		// always be approaching the target destiatnion
		circles[i] = ofVec3f(
			speed * target.x + (1 - speed) * circle.x,
			speed * target.y + (1 - speed) * circle.y,
			setCircleR(circle, i).z
		);


		// move the colors toward the target colors using lerping
		colors[i] = colors[i].getLerped(targetColors[i], speed);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	// set the background color to transition cleanly
	ofColor bgColor = keyColors[0];
	bgColor.setBrightness(200);
	bgColor.setSaturation(100);
	ofBackground(bgColor);
	//ofNoFill();

	// draw the circles with a high resolution
	ofSetCircleResolution(100);
	for (int i = bands - 1; i > -1; i--) {
		ofVec3f circle = circles[i];
		ofSetColor(colors[i]);

		// and draw a circle with a radius dependent on the frequency and playback speed
		// slower = bigger, faster = smaller
		
		float radius = ofMap(fft[i], 0.0f, 1.0f, 0.0f, circle.z) / playback;
		//ofSetLineWidth(radius / 25.6);
		ofDrawCircle(circle.x, circle.y, radius);
		
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
		// when r is pressed, reset to a new position and color scheme
	case'r':
		for (int i = 0; i < bands + 1; i++) {
			keyColors[i] = getKeyColor();
		}
		for (int i = 0; i < bands; i++) {
			targetCircles[i] = setCirclePos(targetCircles[i], i, ofGetElapsedTimef()); // use elapsed time to offset the noise seed
			targetColors[i] = lerpColor(keyColors[i], keyColors[i + 1]);
		}
		break;
		// when s is pressed, save the screen
	case 's':
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshot.save("screenshot" + ofToString(ofGetElapsedTimeMillis()) + ".png"); // use time to differentiate
		break;
		// use arrow keys to change the playback
	case OF_KEY_UP:
		playback += 0.01;
		// cut the audio into pieces and populate the fft array
		break;
	case OF_KEY_DOWN:
		playback -= 0.01;
		// cut the audio into pieces and populate the fft array
		break;
	}
}