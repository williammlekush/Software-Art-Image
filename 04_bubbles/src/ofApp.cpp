#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// constrain heights to narrower bins than widths
	// largest circle has smallest range --> circles remain inside each other
	circles[0] = ofVec3f(
		ofRandom(ofGetWindowWidth() * 2 / 12, ofGetWindowWidth() * 10 / 12),
		ofRandom(ofGetWindowHeight() * 3 / 12, ofGetWindowHeight() * 9 / 12),
		ofGetWindowHeight() / 9
	);
	circles[1] = ofVec3f(
		ofRandom(ofGetWindowWidth() * 3 / 12, ofGetWindowWidth() * 9 / 12),
		ofRandom(ofGetWindowHeight() * 4 / 12, ofGetWindowHeight() * 8 / 12),
		circles[0].z * 2.56
	);
	circles[2] = ofVec3f(
		ofRandom(ofGetWindowWidth() * 5 / 12, ofGetWindowWidth() * 7 / 12),
		ofRandom(ofGetWindowHeight() * 5 / 12, ofGetWindowHeight() * 7 / 12),
		circles[1].z * 2.56
	);

	// declare key colors for lerping
	for (int i = 0; i < 4; i++) {
		keyColors[i] = ofColor(
			ofMap(ofNoise(ofRandom(255)),0, 1, 0, 255),
			ofMap(sin(ofRandom(255)), 0, 1, 0, 255),
			ofMap(cos(ofRandom(255)),0,1,0,255));
	}

	// use lerping to create color harmonies
	for (int i = 0; i < 3; i++) {
		colors[i] = keyColors[i].lerp(keyColors[i + 1], ofRandom(1.0));
		targetCircles[i] = circles[i];
		targetColors[i] = colors[i];
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	float speed = 0.1;

	for (int i = 0; i < 3; i ++) {
		ofVec3f circle = circles[i];
		ofVec3f target = targetCircles[i];



		circles[i] = ofVec3f(
			speed * target.x + (1 - speed) * circle.x,
			speed * target.y + (1 - speed) * circle.y,
			ofMap(sin(ofGetElapsedTimef() + 2.56 * i), 0, 1, targetCircles[i].z / 1.6, targetCircles[i].z)
		);


		colors[i] = colors[i].getLerped(targetColors[i], speed);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofColor bgColor = keyColors[0];
	bgColor.setBrightness(200);
	bgColor.setSaturation(100);
	ofBackground(bgColor);

	ofSetCircleResolution(100);
	for (int i = 2; i > -1; i --) {
		ofVec3f circle = circles[i];
		ofSetColor(colors[i]);
		ofDrawCircle(circle.x, circle.y, circle.z);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
		targetCircles[0] = ofVec3f(
			ofRandom(ofGetWindowWidth() * 2 / 12, ofGetWindowWidth() * 10 / 12),
			ofRandom(ofGetWindowHeight() * 3 / 12, ofGetWindowHeight() * 9 / 12),
			ofGetWindowHeight() / 9
		);
		targetCircles[1] = ofVec3f(
			ofRandom(ofGetWindowWidth() * 3 / 12, ofGetWindowWidth() * 9 / 12),
			ofRandom(ofGetWindowHeight() * 4 / 12, ofGetWindowHeight() * 8 / 12),
			targetCircles[0].z * 2.56
		);
		targetCircles[2] = ofVec3f(
			ofRandom(ofGetWindowWidth() * 5 / 12, ofGetWindowWidth() * 7 / 12),
			ofRandom(ofGetWindowHeight() * 5 / 12, ofGetWindowHeight() * 7 / 12),
			targetCircles[1].z * 2.56
		);

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
