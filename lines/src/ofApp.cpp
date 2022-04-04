#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	x = 0;
	y = ofRandomHeight();
	line.addVertex(x, y);
	ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update(){
	x += 1;
	line.lineTo(x, y);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofColor mainColor;
	mainColor.setHex(0x4169E1);
	ofSetColor(mainColor);
	ofSetLineWidth(3);
	line.draw();
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
