#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		// line moving
		ofPolyline activeLine;
		// bin for static lines, enables screen wrapping
		vector<ofPolyline> lines;

		// position vector
		ofVec2f pos;
		
		// speed of movement
		int speed;

		// position change variables
		int xChange;
		int yChange;
		
		// gui variables
		ofxPanel gui;
		ofxFloatSlider thickSlider;
		ofxLabel rotateLabel;
		ofxColorSlider colorSlider;

		// screenshot variables
		ofImage screenshot;

		
};
