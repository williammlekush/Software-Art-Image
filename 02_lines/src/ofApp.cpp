#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// set up the gui
	gui.setup()->setWidthElements(160);
	// have a slider for the thickness
	gui.add(thickSlider.setup("thickness", 1.0, 1.0, 20.0,160, 16));
	// a label describing the rotation function
	// opted for this over a button because buttons can be pressed and held
	gui.add(rotateLabel.setup("rotate", "press 'r' to rotate", 160, 16));
	// color for the line to change
	gui.add(colorSlider.setup("color", 0x000000, 0x000000, 0xFFFFFf0, 160, 16));

	// chose a random point on the left to start
	pos = ofVec2f(0, ofRandomHeight());

	// set the speed, 5 is good
	speed = 5;

	// start moving to the right
	xChange = speed;
	yChange = 0;

	// add a vertix on the position
	activeLine.addVertex(pos.x, pos.y);

	// set background to white
	ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update() {
	// increase the position by the coordinate changes
	pos.x += xChange;
	pos.y += yChange;

	// if outside the window, make a new line without loosing the old one
	// to create an effect of wrapping around to the other side
	if (pos.x < 0 || pos.x > ofGetWindowWidth() || pos.y < 0 || pos.y > ofGetWindowHeight()) {
		// store the current line data
		lines.push_back(activeLine);
		// clear the current line
		activeLine.clear();
		// determine new corrdinates based on how peole are out
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

		// add the starting vertix
		activeLine.addVertex(pos.x, pos.y);
	}

	// add a line to the new position
	activeLine.lineTo(pos.x, pos.y);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// set the color to the color slider
	ofSetColor(colorSlider);
	// set line thickness to the thickness slider
	ofSetLineWidth(thickSlider);

	// draw all the lines
	for (auto line : lines) {
		line.draw();
	}

	// draw the active line
	activeLine.draw();
	// minimize the nubmer of points
	activeLine.simplify();
	// draw the gui on top
	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// if r is pressed, make a random turn left or right
	if (key == 'r') {
		// if moving horizontally
		if (xChange != 0) {
			// stop moving horizontally
			xChange = 0;
			// start moving vertically
			yChange = (int)ofRandom(2);
			if (yChange == 0) {
				yChange = -speed;
			}
			else {
				yChange = speed;
			}
		}
		// otherwise,
		else {
			// stop moving vertically
			yChange = 0;
			// start moving horizontally
			xChange = (int)ofRandom(2);
			if (xChange == 0) {
				xChange = -speed;
			}
			else {
				xChange = speed;
			}
		}
	}

	// save the window to a png when the 's' key is pressed
	if (key == 's') {
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshot.save("screenshot_002.png"); // adjust this with each canvas
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
