#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	// see ofApp for PIO docs
	ofVec3f setCirclePos(ofVec3f circle, int id, float offset);
	ofVec3f setCircleR(ofVec3f circle, int id);

	ofPolyline getPoly(ofVec3f circle, float fft, float playback);
	ofPath getPath(ofPolyline circlePoly);

	ofPolyline glitchCircles(ofPolyline poly, float xVary, float yVary);

	ofColor getKeyColor();
	ofColor lerpColor(ofColor keyColor, ofColor targetColor);
	
	float getDecay(float playback);
	float getFftSize(int bands, float playMin, float playMax, float playback);

	float glitchSound(float soundPlayerPosition, float variation, bool simple);

	float upperLowerGuard(float num, float max, float min);	
	
	// vector bins for the circle parameters
	vector<ofVec3f> circles;
	vector<ofPolyline> circlePolys;
	vector<ofPath> circlePaths;

	vector<ofColor> keyColors;
	vector<ofColor> colors;
	
	ofColor bgColor;
	ofColor targetBGColor;

	// targets for the transitions
	vector<ofVec3f> targetCircles;
	vector<ofColor> targetColors;


	// for screenshots
	ofImage screenshot;

	// for sound looping
	ofSoundPlayer chordsLoop;

	vector<float> fft;
	float* soundSpectrum;
	
	int bands;
	int bandsMax;

	float volume;
	float volMin;
	float volMax;

	float decay;
	
	float playback;
	float playMax;
	float playMin;

	bool isGlitch;

	float visGlitchXVary;
	float visGlitchYVary;
	float circlesGlitched;

	bool soundGlitchSimple;
	float soundGlitchVary;
};
