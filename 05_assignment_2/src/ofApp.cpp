#include "ofApp.h"

//-------------------------------------------------------------
ofVec3f ofApp::setCirclePos(ofVec3f circle, int id, float offset) {
	circle.x = ofMap(ofNoise(offset * pow(id, id) + sin(id)), 0.0f, 1.0f, 0.0f, ofGetWindowWidth());
	circle.y = ofMap(ofNoise(offset * pow(id, id) + cos(id)), 0.0f, 1.0f, 0.0f, ofGetWindowHeight());
	return circle;
}

ofVec3f ofApp::setCircleR(ofVec3f circle, int id) {
	circle.z = ofGetWindowHeight() / 4.5 * pow(2.618, id);
	return circle;
}

ofColor ofApp::getKeyColor() {
	return ofColor(
		ofMap(ofNoise(ofRandom(255)), 0, 1, 0, 255),
		ofMap(sin(ofRandom(255)), 0, 1, 0, 255),
		ofMap(cos(ofRandom(255)), 0, 1, 0, 255)
		);
}

ofColor ofApp::lerpColor(ofColor keyColor, ofColor targetColor) {
	return keyColor.lerp(targetColor, ofRandom(1.0));
}
void ofApp::setup(){

	chordsLoop.load("chords.mp3");
	chordsLoop.play();
	chordsLoop.setLoop(true);

	volume = 0.7f;
	decay = 0.999f;
	playback = 0.3f;

	fft = new float[128];
	for (int i = 0; i < 128; i++) {
		fft[i] = 0.0f;
	}

	bands = 128;

	// set key colors for color harmony
	for (int i = 0; i < 4; i++) {
		keyColors[i] = getKeyColor();
	}

	// constrain heights to narrower bins than widths
	// largest circle has smallest range --> circles remain inside each other
	for (int i = 0; i < 3; i++) {
		targetCircles[i] = circles[i] = setCirclePos(setCircleR(circles[i], i), i, 1);
		targetColors[i] = colors[i] = lerpColor(keyColors[i], keyColors[i + 1]);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	float speed = 0.1f;

	// update sond engine
	ofSoundUpdate();

	chordsLoop.setVolume(volume);

	if (playback > 0.7) {
		playback = 0.7;
	}
	else if (playback < 0.2) {
		playback = 0.2;
	}

	chordsLoop.setSpeed(playback);

	soundSpectrum = ofSoundGetSpectrum(bands);

	for (int i = 0; i < bands; i++) {
		fft[i] *= decay;
		if (fft[i] < soundSpectrum[i]) {
			fft[i] = soundSpectrum[i];
		}
	}

	for (int i = 0; i < 3; i++) {
		ofVec3f circle = circles[i];
		ofVec3f target = targetCircles[i];

		circles[i] = ofVec3f(
			speed * target.x + (1 - speed) * circle.x,
			speed * target.y + (1 - speed) * circle.y,
			circle.z
		);


		// move the colors toward the target colors using lerping
		colors[i] = colors[i].getLerped(targetColors[i], speed);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	// set the background color to transition cleanly
	ofColor bgColor = keyColors[0];
	bgColor.setBrightness(200);
	bgColor.setSaturation(100);
	ofBackground(bgColor);

	// draw the circles with a high resolution
	ofSetCircleResolution(100);
	for (int i = 2; i > -1; i--) {
		ofVec3f circle = circles[i];
		ofSetColor(colors[i]);

		for (int j = (i + 1) * bands / 32; j > i * bands / 32; j--) {
			ofDrawCircle(circle.x, circle.y, ofMap(fft[j], 0.0f, 1.0f, 0.0f, circle.z) * 0.5/playback);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// when r is pressed, reset to a new position and color scheme
	switch (key) {
		case'r': 
			for (int i = 0; i < 4; i++) {
				keyColors[i] = getKeyColor();
			}
			for (int i = 0; i < 3; i++) {
				targetCircles[i] = setCirclePos(targetCircles[i], i, ofGetElapsedTimef());
				targetColors[i] = lerpColor(keyColors[i], keyColors[i + 1]);
			}
			break;
		case 's':
			screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			screenshot.save("screenshot" + ofToString(ofGetElapsedTimeMillis()) + ".png"); // use time to differentiate
			break;
		case OF_KEY_UP:
			playback += 0.01;
			break;
		case OF_KEY_DOWN:
			playback -= 0.01;
			break;		
	}
}