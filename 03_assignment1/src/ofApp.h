#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// number of visible lines
		int lineCount;

		// temporary path for instantiation
		ofPolyline tempL;

		// vector of all the paths that make up a single visible line
		// needed for screen wrapping
		vector<ofPolyline> tempLine;
		
		// bin for all the drawn lines
		vector<vector<ofPolyline>> lines;

		// parallel vector for varying frequency of turns line-to-line
		vector<int> delay;

		// parallel vector for varying speed line-to-line
		vector<int> speeds;

		// position vectors to vary positions
		vector<ofVec2f> positions;
		vector<int> xChanges;
		vector<int> yChanges;

		// thickness vectors to vary thicknesses
		vector<float> thicks;
		
		// color vectors to build and vary colors
		vector<ofColor> keyColors;
		vector<ofColor> lerpColors;

		// for docs
		ofImage screenshot;
		
};
