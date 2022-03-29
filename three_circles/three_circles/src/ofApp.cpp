#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	y1 = ofGetWindowHeight() / 2;
	y2 = y1;
	y3 = y2;

	x1 = ofRandom(ofGetWindowWidth() * 5 / 12, ofGetWindowWidth() * 7 / 12);
	x2 = ofRandom(ofGetWindowWidth() * 4 / 12, ofGetWindowWidth() * 8 / 12);
	x3 = ofRandom(ofGetWindowWidth() * 3 / 12, ofGetWindowWidth() * 9 / 12);

	r1 = 80;
	r2 = r1 * 1.6 * 1.6;
	r3 = r2 * 1.6 *1.6;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 50);
	ofDrawCircle(x1, y1, r1);
	ofSetColor(255, 100);
	ofDrawCircle(x2, y2, r2);
	ofSetColor(255, 150);
	ofDrawCircle(x3, y3, r3);
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
