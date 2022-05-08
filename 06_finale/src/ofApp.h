#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	// see ofApp.cpp for IPO docs

	// circle parameter manipulation
	ofVec3f setCirclePos(ofVec3f circle, int id, float offset);
	ofVec3f setCircleR(ofVec3f circle, int id);

	// circle drawing utilities
	ofPolyline getPoly(ofVec3f circle, float fft, float playback);
	ofPath getPath(ofPolyline circlePoly);

	// visual glitching utitility
	ofPolyline glitchCircle(ofPolyline poly, float xVary, float yVary);

	// color manipulation
	ofColor getKeyColor();
	ofColor lerpColor(ofColor keyColor, ofColor targetColor);
	
	// sound utilities
	float getDecay(float playback);
	float getFftSize(int bands, float playMin, float playMax, float playback);

	// sound glitching utility
	float glitchSound(float soundPlayerPosition, float variation, bool simple);

	// calculation utility
	float upperLowerGuard(float num, float max, float min);	
	
	// bins for circle parameters
	vector<ofVec3f> circles;		// vectors to hold position and radius
	vector<ofPolyline> circlePolys; // polys to manipulate point-by-point
	vector<ofPath> circlePaths;		// paths to draw filled circles

	// bins for circle colors
	vector<ofColor> keyColors;
	vector<ofColor> colors;

	// bins for bacground color
	ofColor bgColor;

	// targets for the visual transitions
	vector<ofVec3f> targetCircles;
	vector<ofColor> targetColors;
	ofColor targetBGColor;

	// for screenshots
	ofImage screenshot;

	// for sound looping
	ofSoundPlayer loop;

	// for dividing up the sound to be visualized
	vector<float> fft;
	float* soundSpectrum;
	int bands;
	int bandsMax;

	// volume parameters
	float volume;
	float volMin;
	float volMax;
	
	// for ensuring variance in the visuals
	float decay;

	// playback parameters	
	float playback;
	float playMax;
	float playMin;

	// bool for glitch check
	bool isGlitch;

	// visual glitching parameters
	float visGlitchXVary;		// x shift range of points
	float visGlitchYVary;		// y shift range of points
	float circlesGlitched;		// number of circles to glitch

	// sound glitching parameters
	bool soundGlitchSubtle;		// subtle or obnoxious glitch
	float soundGlitchVary;		// position shift range of obnoxious glitch
};
