#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	pos = ofVec2f(0, ofRandomHeight());
	x = 0;
	y = ofRandomHeight();
	xChange = 1;
	yChange = 0;
	line.addVertex(pos.x, pos.y);
	ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update(){
	pos.x += xChange;
	pos.y += yChange;
	line.lineTo(pos.x, pos.y);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofColor mainColor;
	mainColor.setHex(0x4169E1);
	ofSetColor(mainColor);
	ofSetLineWidth(3);
	line.draw();
	line.simplify();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
		if (xChange != 0) {
			xChange = 0;
			yChange = (int)ofRandom(2);
			if (yChange == 0) {
				yChange = -1;
			}
		}
		else {
			yChange = 0;
			xChange = (int)ofRandom(2);
			if (xChange == 0) {
				xChange = -1;
			}
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
