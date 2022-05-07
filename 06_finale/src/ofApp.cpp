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
	circle.z = ofGetWindowHeight() / 4 * pow(1.618, id);
	return circle;
}

ofPolyline ofApp::getPoly(ofVec3f circle, float fft, float playback) {
	ofPolyline poly;
	float radius = ofMap(fft, 0.0f, 1.0f, 0.0f, circle.z) / playback;
	radius = upperLowerGuard(radius, radius, 5);
	poly.arc(circle.x, circle.y, radius, radius, 0, 360, 100);	
	return poly;
}

ofPath ofApp::getPath(ofPolyline circlePoly) {
	ofPath path;
	for (int i = 0; i < circlePoly.getVertices().size(); i++) {
		if (i == 0) {
			path.newSubPath();
			path.moveTo(circlePoly.getVertices()[i]);
		}
		else {
			path.lineTo(circlePoly.getVertices()[i]);
		}
	}

	path.close();
	path.simplify();

	return path;
}

ofPolyline ofApp::glitchCircles(ofPolyline poly, float xVary, float yVary) {
	for (auto &point : poly.getVertices()) {
		point.x += ofMap(sin(ofRandom(ofGetElapsedTimef())), 0.0f, 1.0f, -xVary, xVary);
		point.y += ofMap(cos(ofRandom(ofGetElapsedTimef())), 0.0f, 1.0f, -yVary, yVary);
	}
	return poly;
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
		100);
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

float ofApp::getFftSize(int bands, float playMin, float playMax, float playback) {
	return ofMap(bands / playback, bands / playMax, bands / playMin, bands, bands * 3);
}


void ofApp::setup() {
	// number of circles to represent the sound
	bands = 0;
	bandsMax = 32;
	
	// adjust these to control size and speed of circles
	volMin = 0.0f;
	volMax = 0.7f;

	volume = volMin;

	playMax = 1.0f;
	playMin = 0.2f;

	playback = playMin;


	decay = getDecay(playback);

	isGlitch = false;

	// resize for efficiency's sake
	circles.resize(bandsMax);
	circlePolys.resize(bandsMax);
	circlePaths.resize(bandsMax);
	keyColors.resize(bandsMax + 1); // need an extra key color for the lerping!
	colors.resize(bandsMax);
	targetCircles.resize(bandsMax);
	targetColors.resize(bandsMax);

	// play the audio on loop
	chordsLoop.load("chords.mp3");
	chordsLoop.play();
	chordsLoop.setLoop(true);
	chordsLoop.setVolume(volume);
	chordsLoop.setSpeed(playback);

	// cut the audio into pieces and populate the fft array
	fft.resize(getFftSize(bands, playMin, playMax, playback));

	// set key colors for color harmony
	for (int i = 0; i < bandsMax + 1; i++) {
		keyColors[i] = getKeyColor();
	}

	// generate circle parameters
	for (int i = 0; i < bandsMax; i++) {
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

	// make decay dependent on playback
	decay = getDecay(playback);

	// update the volume
	chordsLoop.setVolume(volume);

	// cut the audio into pieces and populate the fft array
	fft.resize(getFftSize(bands, playMin, playMax, playback));

	// grab the sound spectrum for the bands
	soundSpectrum = ofSoundGetSpectrum(fft.size());

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
		
		circlePolys[i] = getPoly(circles[i], fft[i], playback);

		// move the colors toward the target colors using lerping
		colors[i] = colors[i].getLerped(targetColors[i], speed);
	}

	if (isGlitch) {
		for (auto& poly : circlePolys) {
			poly = glitchCircles(poly, 10 / playback, 2 / playback);
		}

		float noise = ofNoise(ofGetElapsedTimef());
		float soundPos = chordsLoop.getPosition();
		float noiseVary = 0.9;
		float min = ofMap(soundPos - noise, 0.0f, 1.0f, 0.0f, -noiseVary);
		float max = ofMap(soundPos + noise, 0.0f, 1.0f, 0.0f, noiseVary);

		// chordsLoop.setPosition(soundPos += noise); // subtle glitch, start here
		// chordsLoop.setPosition(ofRandom(min, max)); // gradually increase min / max to move from paused to moving glitch
	}

	for (int i = 0; i < circlePolys.size(); i++) {
		circlePaths[i] = getPath(circlePolys[i]);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// set the background color to transition cleanly
	ofColor bgColor = keyColors[0];
	bgColor.setBrightness(200);
	bgColor.setSaturation(100);
	ofBackground(bgColor);
	ofEnableAlphaBlending();

	// draw the circles with a high resolution
	ofSetCircleResolution(100);
	for (int i = bands - 1; i > -1; i--) {
		ofPath path = circlePaths[i];
		path.setFillColor(colors[i]);
		path.draw();
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
		// constratin the playback to between 0.2-0.7
		playback = upperLowerGuard(playback + 0.01, playMax, playMin);
		// update the playback speed
		chordsLoop.setSpeed(playback);
		break;
	case OF_KEY_DOWN:
		// constratin the playback to between 0.2-0.7
		playback = upperLowerGuard(playback - 0.01, playMax, playMin);
		// update the playback speed
		chordsLoop.setSpeed(playback);
		break;
	case OF_KEY_LEFT:
		volume = upperLowerGuard(volume - 0.01, volMax, volMin);
		chordsLoop.setVolume(volume);
		break;
	case OF_KEY_RIGHT:
		volume = upperLowerGuard(volume + 0.01, volMax, volMin);
		chordsLoop.setVolume(volume);
		break;
	case 'g':
		isGlitch = !isGlitch;
		break;
	case 'd':
		if (bands >= 1) {
			bands -= 1;
		}
		break;
	case 'a':
		if (bands < 32) {
			bands += 1;
		}
		break;
	case OF_KEY_ESC:
		OF_EXIT_APP(0);
		break;
	}
}