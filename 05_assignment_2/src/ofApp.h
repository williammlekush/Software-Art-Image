#pragma once

#include "ofMain.h"

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

		ofVec3f setCirclePos(ofVec3f circle, int id, float offset);
		ofVec3f setCircleR(ofVec3f circle, int id);
		
		ofColor getKeyColor();

		ofVec3f circles[3];
		ofColor keyColors[4];
		ofColor colors[3];

		ofVec3f targetCircles[3];
		ofColor targetColors[3];

		ofImage screenshot;		
};
