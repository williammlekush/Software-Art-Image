#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		ofVec3f setCirclePos(ofVec3f circle, int id, float offset);
		ofVec3f setCircleR(ofVec3f circle, int id);


		ofColor getKeyColor();
		ofColor lerpColor(ofColor keyColor, ofColor targetColor);

		ofVec3f circles[3];
		ofColor keyColors[4];
		ofColor colors[3];

		ofVec3f targetCircles[3];
		ofColor targetColors[3];

		ofImage screenshot;

		ofSoundPlayer chordsLoop;

		float* fft;
		float* soundSpectrum;
		int bands;

		float decay;
		float volume;
		float playback;

};
