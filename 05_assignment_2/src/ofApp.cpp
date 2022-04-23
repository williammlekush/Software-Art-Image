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

void ofApp::setup(){
	// constrain heights to narrower bins than widths
	// largest circle has smallest range --> circles remain inside each other
	for (int i = 0; i < 3; i++) {
		circles[i] = setCirclePos(setCircleR(circles[i], i), i, 1);
	}

	// set key colors for color harmony
	for (int i = 0; i < 4; i++) {
		keyColors[i] = ofColor(
			ofMap(ofNoise(ofRandom(255)), 0, 1, 0, 255),
			ofMap(sin(ofRandom(255)), 0, 1, 0, 255),
			ofMap(cos(ofRandom(255)), 0, 1, 0, 255));
	}

	// use lerping to generate color harmonies
	for (int i = 0; i < 3; i++) {
		colors[i] = keyColors[i].lerp(keyColors[i + 1], ofRandom(1.0));
		targetCircles[i] = circles[i];
		targetColors[i] = colors[i];
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	float speed = 0.1;

	for (int i = 0; i < 3; i++) {
		ofVec3f circle = circles[i];
		ofVec3f target = targetCircles[i];

		circles[i] = ofVec3f(
			// constantly move the circles toward the target cirlces
			speed * target.x + (1 - speed) * circle.x,
			speed * target.y + (1 - speed) * circle.y,
			// have the size oscilate between bounds
			// use the squard golden ratio (~2.56) to set the oscillation bounds
			ofMap(sin(ofGetElapsedTimef() + 2.56 * i), 0, 1, targetCircles[i].z / 1.6, targetCircles[i].z)
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

		ofPushMatrix();
		//ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		ofDrawCircle(circle.x, circle.y, circle.z);
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// when r is pressed, reset to a new position and color scheme
	if (key == 'r') {
		for (int i = 0; i < 3; i++) {
			targetCircles[i] = setCirclePos(setCircleR(circles[i], i), i, ofGetElapsedTimef());
		}

		for (int i = 0; i < 4; i++) {
			keyColors[i] = ofColor(
				ofMap(ofNoise(ofRandom(255)), 0, 1, 0, 255),
				ofMap(sin(ofRandom(255)), 0, 1, 0, 255),
				ofMap(cos(ofRandom(255)), 0, 1, 0, 255));
		}

		for (int i = 0; i < 3; i++) {
			targetColors[i] = keyColors[i].lerp(keyColors[i + 1], ofRandom(1.0));
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
