#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// change this for more/less lines, 20 is nice on 1080p
	lineCount = 20;

	// resize all the vectors up front, more efficient than push_back()
	positions.resize(lineCount);
	lines.resize(lineCount);
	xChanges.resize(lineCount);
	yChanges.resize(lineCount);
	delay.resize(lineCount);
	thicks.resize(lineCount);
	speeds.resize(lineCount);
	keyColors.resize(lineCount);
	lerpColors.resize(lineCount);


	// for every line
	for (int i = 0; i < lineCount; i++) {
		// give it a random speed
		speeds[i] = (int)ofRandom(1, 10);
		
		// start it moving to the right
		xChanges[i] = speeds[i];
		yChanges[i] = 0;

		// give it a random time between turns
		int delayf = ofNoise(ofRandom(5)) * 1000;
		delay[i] = (int)delayf;

		// random thickness
		thicks[i] = ofRandom(1, 10);

		// generate its key color
		keyColors[i] = ofColor(
			ofMap(ofRandom(i), 0.0, i, 0.0, 255.0),
			ofMap(ofRandom(i), 0.0, i, 0.0, 255.0),
			ofMap(ofRandom(i), 0.0, i, 0.0, 255.0)
			);

		// a random position
		positions[i] = (ofVec2f(ofRandomWidth(), ofRandomHeight()));
		
		// instantiate a Polyline with the position
		tempL.clear();
		tempL.addVertex(positions[i].x, positions[i].y);

		// instantiate a line with that Polyline
		tempLine.clear();
		tempLine.push_back(tempL);

		// stash the line
		lines[i] = tempLine;
	}

	// first color is the first key color
	lerpColors[0] = keyColors[0];

	// use a controlled random lerping method for the rest
	for (int i = 1; i < lineCount; i++) {
		lerpColors[i] = keyColors[0].lerp(keyColors[i], ofRandom(1.0));
	}

	// set to a midtone from the first key color to white
	// drop opacity to reduce visual noise
	ofBackground(ofColor(keyColors[0].lerp(0xFFFFFF, 0.2), 127));
}

//--------------------------------------------------------------
void ofApp::update() {

	// grab the time, used throughout
	int time = ofGetElapsedTimeMillis();

	// for all the lines
	for (int i = 0; i < lineCount; i ++) {
		// grab their positions
		float posX = positions[i].x;
		float posY = positions[i].y;
		
		// increase the position by the coordinate changes
		posX += xChanges[i];
		posY += yChanges[i];

		// if the position is outside the window, we need to make a new line
		// to create an effect of wrapping around to the other side
		if (posX < 0 || posX > ofGetWindowWidth() || posY < 0 || posY > ofGetWindowHeight()) {
	
			// determine new corrdinates based on how they are out
			if (posX < 0) {
				posX = ofGetWindowWidth();
			}
			else if (posX > ofGetWindowWidth()) {
				posX = 0;
			}
			else if (posY < 0) {
				posY = ofGetWindowHeight();
			}
			else if (posY > ofGetWindowHeight()) {
				posY = 0;
			}

			// create a new temporary line at the new position
			tempL.clear();
			// add the starting vertix
			tempL.addVertex(posX, posY);

			// stash the line
			lines[i].push_back(tempL);

	
		}

		// stash the new position
		positions[i].x = posX;
		positions[i].y = posY;

		// extend the last line to the new position
		lines[i][lines[i].size() - 1].lineTo(posX, posY);

		// turn according the line's delay
		// use < 10 instead of == 0 because fps means == 0 will rarely happen
		// higher numbers --> pauses followed by many turns
		if (time % delay[i] < 10) {
			// if moving horizontally
			if (xChanges[i] != 0) {
				// stop moving horizontally
				xChanges[i] = 0;
				// start moving vertically
				yChanges[i] = (int)ofRandom(2);
				if (yChanges[i] == 0) {
					yChanges[i] = -speeds[i];
				}
				else {
					yChanges[i] = speeds[i];
				}
			}
			// otherwise,
			else {
				// stop moving vertically
				yChanges[i] = 0;
				// start moving horizontally
				xChanges[i] = (int)ofRandom(2);
				if (xChanges[i] == 0) {
					xChanges[i] = -speeds[i];
				}
				else {
					xChanges[i] = speeds[i];
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// for each line
	for (int i = 0; i < lineCount; i++) {

		// simplify the last path of each line
		// to minimize overhead
		lines[i][lines[i].size()-1].simplify();

		// draw all the paths for the line
		for (auto l : lines[i]) {

			// set the color
			ofSetColor(lerpColors[i], 127);
			// set line thickness
			ofSetLineWidth(thicks[i]);

			// draw the lines
			l.draw();
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	// save the window to a png when the 's' key is pressed
	if (key == 's') {
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshot.save("screenshot" + ofToString(ofGetElapsedTimeMillis()) + ".png"); // use time to differentiate
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
