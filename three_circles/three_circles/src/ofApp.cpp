#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(50);
	y3 = ofRandom(ofGetWindowHeight() * 5 / 12, ofGetWindowHeight() * 7 / 12);
	y2 = ofRandom(ofGetWindowHeight() * 4 / 12, ofGetWindowHeight() * 8 / 12);
	y1 = ofRandom(ofGetWindowHeight() * 3 / 12, ofGetWindowHeight() * 9 / 12);

	x3 = ofRandom(ofGetWindowWidth() * 5 / 12, ofGetWindowWidth() * 7 / 12);
	x2 = ofRandom(ofGetWindowWidth() * 3 / 12, ofGetWindowWidth() * 9 / 12);
	x1 = ofRandom(ofGetWindowWidth() * 2 / 12, ofGetWindowWidth() * 10 / 12);

	r1 = ofGetWindowHeight() / 9;
	r2 = r1 * 1.6 * 1.6;
	r3 = r2 * 1.6 *1.6;

	ofColor keyColor1(58, 134, 255);
	ofColor keyColor2(255, 190, 11);
	ofColor keyColor3(255, 0, 110);
	ofColor keyColor4(131, 56, 236);

	color1 = keyColor1.lerp(keyColor2, ofRandom(1.0));
	color2 = color1.lerp(keyColor3, ofRandom(1.0));
	color3 = color1.lerp(keyColor4, ofRandom(1.0));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(color3, 200);
	ofDrawCircle(x3, y3, r3);
	ofSetColor(color2, 200);
	ofDrawCircle(x2, y2, r2);
	ofSetColor(color1, 200);
	ofDrawCircle(x1, y1, r1);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
