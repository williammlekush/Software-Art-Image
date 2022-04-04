#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup()->setWidthElements(160);
	gui.add(thickSlider.setup("thickness", 1.0, 1.0, 20.0,160, 16));
	gui.add(rotateLabel.setup("rotate", "press 'r' to rotate", 160, 16));
	gui.add(colorSlider.setup("color", 0x000000, 0x000000, 0xFFFFFf0, 160, 16));

	pos = ofVec2f(0, ofRandomHeight());

	xChange = 1;
	yChange = 0;

	activeLine.addVertex(pos.x, pos.y);

	ofBackground(255);


}

//--------------------------------------------------------------
void ofApp::update() {
	pos.x += xChange;
	pos.y += yChange;

	if (pos.x < 0 || pos.x > ofGetWindowWidth() || pos.y < 0 || pos.y > ofGetWindowHeight()) {
		lines.push_back(activeLine);
		activeLine.clear();

		if (pos.x < 0) {
			pos.x = ofGetWindowWidth();
		}
		else if (pos.x > ofGetWindowWidth()) {
			pos.x = 0;
		}
		else if (pos.y < 0) {
			pos.y = ofGetWindowHeight();
		}
		else if (pos.y > ofGetWindowHeight()) {
			pos.y = 0;
		}

		activeLine.addVertex(pos.x, pos.y);
	}

	activeLine.lineTo(pos.x, pos.y);
}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.draw();
	ofSetColor(colorSlider);
	ofSetLineWidth(thickSlider);

	for (auto line : lines) {
		line.draw();
	}

	activeLine.draw();
	activeLine.simplify();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = 'r') {
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
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
