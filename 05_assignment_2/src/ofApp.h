#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		// see ofApp for PIO docs
		ofVec3f setCirclePos(ofVec3f circle, int id, float offset);
		ofVec3f setCircleR(ofVec3f circle, int id);
		ofColor getKeyColor();
		ofColor lerpColor(ofColor keyColor, ofColor targetColor);

		// vector bins for the circle parameters
		vector<ofVec3f> circles;
		vector<ofColor> keyColors;
		vector<ofColor> colors;

		// targets for the transitions
		vector<ofVec3f> targetCircles;
		vector<ofColor> targetColors;

		// count for circles
		int count;

		// for screenshots
		ofImage screenshot;

		// for sound looping
		ofSoundPlayer chordsLoop;

		float* fft;
		float* soundSpectrum;
		int bands;

		float decay;
		float playback;

};
