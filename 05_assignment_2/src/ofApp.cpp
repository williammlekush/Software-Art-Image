#include "ofApp.h"

//-------------------------------------------------------------
ofVec3f ofApp::setCirclePos(ofVec3f circle, int id, float offset) {
	circle.x = ofMap(ofNoise(offset * pow(id, id) + sin(id)), 0.0f, 1.0f, 0.0f, ofGetWindowWidth());
	circle.y = ofMap(ofNoise(offset * pow(id, id) + cos(id)), 0.0f, 1.0f, 0.0f, ofGetWindowHeight());
	return circle;
}

ofVec3f ofApp::setCircleR(ofVec3f circle, int id) {
	circle.z = ofGetWindowHeight() / 9 * pow(1.618, id);
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
	chordsLoop.setSpeed(0.3);

	volume = 0.5f;
	decay = 0.9f;

	fft = new float[128];
	for (int i = 0; i < 128; i++) {
		fft[i] = 0.0f;
	}

	bands = 64;

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

		for (int i = 0; i < bands; i++) {
			ofDrawCircle(circle.x, circle.y, fft[i] * 256);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// when r is pressed, reset to a new position and color scheme
	if (key == 'r') {
		for (int i = 0; i < 4; i++) {
			keyColors[i] = getKeyColor();
		}

		for (int i = 0; i < 3; i++) {
			targetCircles[i] = setCirclePos(targetCircles[i], i, ofGetElapsedTimef());
			targetColors[i] = lerpColor(keyColors[i], keyColors[i + 1]);
		}
	}

	if (key == 's') {
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshot.save("screenshot" + ofToString(ofGetElapsedTimeMillis()) + ".png"); // use time to differentiate
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
