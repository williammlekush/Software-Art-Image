#include "ofApp.h"

//-------------------------------------------------------------

/**
* func:		setCirclePos
* input:	circle parameters (ofVec3f),
*			circle id (int)
*			position seed offset (float)
* process:	calculates slightly random position coordinates
* output:	circle paramters (ofVec3f)
*/
ofVec3f ofApp::setCirclePos(ofVec3f circle, int id, float offset) {
	circle.x = ofMap(ofNoise(offset * pow(id, id) * sin(ofRandom(id))), 0.0f, 1.0f, 0.0f, ofGetWindowWidth());
	circle.y = ofMap(ofNoise(offset * pow(id, id) * cos(ofRandom(id))), 0.0f, 1.0f, 0.0f, ofGetWindowHeight());
	return circle;
}

/**
* func:		setCircleR
* input:	circle parameters (ofVec3f),
*			circle id (int)
* process:	calculates circle radius based on id
* output:	circle paramters (ofVec3f)
*/
ofVec3f ofApp::setCircleR(ofVec3f circle, int id) {
	circle.z = ofGetWindowHeight() / 4 * pow(1.618, id);
	return circle;
}

/**
* func:		getPoly
* input:	circle parameters (ofVec3f),
*			fft band value (float),
*			playback speed (float)
* process:	Calculates the points that define a circle
*			according to the parameters provided. The
*			radius of the circle is inversely related
*			to the playback speed and directly related
*			to the fft band value.
* output:	outline of a circle (ofPolyline)
*/
ofPolyline ofApp::getPoly(ofVec3f circle, float fft, float playback) {
	ofPolyline poly;
	float radius = ofMap(fft, 0.0f, 1.0f, 0.0f, circle.z) / playback;
	radius = upperLowerGuard(radius, radius, 5);
	poly.arc(circle.x, circle.y, radius, radius, 0, 360, 100);	
	return poly;
}

/**
* func:		getPath
* input:	outline of a circle (ofPolyline)
* process:	creates a shape with the given outline
* output:	a circle (ofPath)
*/
ofPath ofApp::getPath(ofPolyline circlePoly) {
	ofPath path;
	for (int i = 0; i < circlePoly.getVertices().size(); i++) {
		if (i == 0) {
			path.newSubPath();
			path.moveTo(circlePoly.getVertices()[i]);
		}
		else {
			path.lineTo(circlePoly.getVertices()[i]);
		}
	}

	path.close();
	path.simplify();

	return path;
}

/**
* func:		glitchCircle
* input:	outline of a circle (ofPolyline),
*			amount to vary x position of circle points (float)
*			amount to vary y position of circle points (float)
* process:	Semi-randomly offsets each point in the outline
* output:	outline of a glitched circle (ofPolyline)
*/
ofPolyline ofApp::glitchCircle(ofPolyline poly, float xVary, float yVary) {
	for (auto &point : poly.getVertices()) {
		point.x += ofMap(sin(ofRandom(ofGetElapsedTimef())), 0.0f, 1.0f, -xVary, xVary);
		point.y += ofMap(cos(ofRandom(ofGetElapsedTimef())), 0.0f, 1.0f, -yVary, yVary);
	}
	return poly;
}

/**
* func:		getKeyColor
* input:	none
* process:	generates a random-ish color
* output:	color (ofColor)
*/
ofColor ofApp::getKeyColor() {
	return ofColor(
		ofMap(ofNoise(ofRandom(255)), 0, 1, 0, 255),
		ofMap(sin(ofRandom(255)), 0, 1, 0, 255),
		ofMap(cos(ofRandom(255)), 0, 1, 0, 255),
		100);
}

/**
* func:		lerpColor
* input:	two colors to lerp between (ofColor),
* process:	lerps a random distance across the color space
*			between two colors
* output:	lerped color (ofColor)
*/
ofColor ofApp::lerpColor(ofColor keyColor, ofColor targetColor) {
	return keyColor.lerp(targetColor, ofRandom(1.0));
}

/**
* func:		getDecay
* input:	playback speed (float),
* process:	calculates the decay as inversely related
*			to the playback speed
* output:	decay rate (float)
*/
float ofApp::getDecay(float playback) {
	return 1 - playback / 100;
}

/**
* func:		getFftSize
* input:	number of frequency bands (int),
*			minimum playback speed (float),
*			maximum playback speed (float),
*			playback speed (float)
* process:	Calculates the size of the fft as inversely
*			related to the playback speed and directly
*			related to the number of visualized bands.
*			This allows	for higher frequencies to be 
*			visualized when	the playback is faster and
*			lower frequencies when the playback is slower.
* output:	number of fft bands to analyze (float)
*/
float ofApp::getFftSize(int bands, float playMin, float playMax, float playback) {
	return ofMap(
		bands / playback,
		bands / playMax,
		bands / playMin,
		bands,
		bands * 3
	);
}

/**
* func:		glitchSound
* input:	position of a sound player (float),
*			range of position change to apply (float),
*			check for simplifed or complex glitch (bool)
* process:	Calculates a new position for a soundplayer
*			to move to, glitching the sound. A subtle 
*			glitch continues moving forward through the
*			sound at a noisy rate. An obvious glitch
*			jumps around the sound within particular
*			variation bounds.
* output:	a new sound player position (float)
*/
float ofApp::glitchSound(float soundPlayerPosition, float variation, bool subtle) {
	float noise = ofNoise(ofGetElapsedTimef());

	if (subtle) {
		return soundPlayerPosition + noise;
	}
	else {
		float min = ofMap(soundPlayerPosition - noise, 0.0f, 1.0f, 0.0f, -variation);
		float max = ofMap(soundPlayerPosition + noise, 0.0f, 1.0f, 0.0f, variation);
		return ofRandom(min, max);
	}
}

/**
* func:		upperLowerGuard
* input:	a number (float),
*			a maximum (float),
*			a minimum (float)
* process:	checks if the number is out of bounds
*			and returns the appropriate value
* output:	bounded number (float)
*/
float ofApp::upperLowerGuard(float num, float max, float min) {
	if (num > max) {
		return max;
	}
	else if (num < min) {
		return min;
	}
	else {
		return num;
	}
}

void ofApp::setup() {
	// the frequency bands that will be visualized
	bands = 0;			// start low
	bandsMax = 32;		// 32 seems like the sweet spot
	
	// volume constrained from 0-70%
	volMin = 0.0f;
	volMax = 0.7f;
	volume = volMin;

	// playback constrained from 20-100%
	playMax = 1.0f;
	playMin = 0.2f;
	playback = playMin;

	// set decay based on playback
	decay = getDecay(playback);

	// don't start with a glitch!
	isGlitch = false;

	// visual glitch parameters
	// glitch horizontally more than vertically
	// TO_DO, use min max like vol/playback
	visGlitchXVary = 10.0f;
	visGlitchYVary = 2.0f;

	// start with only one circle glitched
	circlesGlitched = 1;

	// start subtle
	soundGlitchSubtle = true;
	// keep the obvious glitch
	soundGlitchVary = 0.1;

	// resize bins to minimize overhead
	circles.resize(bandsMax);		// use max to prevent memory error!
	circlePolys.resize(bandsMax);
	circlePaths.resize(bandsMax);
	keyColors.resize(bandsMax + 1); // need an extra key color for the lerping!
	colors.resize(bandsMax);
	targetCircles.resize(bandsMax);
	targetColors.resize(bandsMax);

	// load the audio loop
	loop.load("chords.mp3");

	// set audio to loop
	loop.setLoop(true);
	loop.setVolume(volume);
	loop.setSpeed(playback);

	// play audio
	loop.play();

	/*	
	*	Set the size of the bins for the full sound analysis.
	*	We are only interested in portions of this analysis
	*	based on the current playback speed, so we change the
	*	size of the bins to watch lower and higher frequencies.
	*/
	fft.resize(getFftSize(bands, playMin, playMax, playback));

	// set the key colors for the color harmonies
	for (int i = 0; i < bandsMax + 1; i++) {
		keyColors[i] = getKeyColor();
	}

	for (int i = 0; i < bandsMax; i++) {
		// initialize circle parameters
		targetCircles[i] = circles[i] = setCirclePos(setCircleR(circles[i], i), i, 1);
		// lerp for color harmonies
		targetColors[i] = colors[i] = lerpColor(keyColors[i], keyColors[i + 1]);
	}

	// set background color
	targetBGColor = bgColor = keyColors[0];
	bgColor.setBrightness(200);
	bgColor.setSaturation(100);

	// enable this for smoother visuals
	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update() {
	// speed of positiona and color transitions
	float speed = 0.1f;

	// update sound every frame
	ofSoundUpdate();

	// update decay from playback speed
	decay = getDecay(playback);

	// update the size of the fft array (for when bands/playback changes)
	fft.resize(getFftSize(bands, playMin, playMax, playback));

	// geta sound spectrum for entire fft
	soundSpectrum = ofSoundGetSpectrum(fft.size());

	for (int i = 0; i < bands; i++) {
		// decrease the frequency bands using decay
		fft[i] *= decay;
		// ensure the ft value is below the sound value
		if (fft[i] < soundSpectrum[i]) {
			fft[i] = soundSpectrum[i];
		}
	}

	// update the circles and colors with each frame
	for (int i = 0; i < bands; i++) {
		ofVec3f circle = circles[i];
		ofVec3f target = targetCircles[i];

		// always be approaching the target destiatnion
		circles[i] = ofVec3f(
			speed * target.x + (1 - speed) * circle.x,
			speed * target.y + (1 - speed) * circle.y,
			setCircleR(circle, i).z						// keep radius constant for now
		);
		
		// update the circle outline points
		circlePolys[i] = getPoly(circles[i], fft[i], playback);

		// move the colors toward the target colors using lerping
		colors[i] = colors[i].getLerped(targetColors[i], speed);
		bgColor = bgColor.getLerped(targetBGColor, speed);
	}

	// glitching updates
	if (isGlitch) {

		// glitch the sound by modifying the sound player's position
		loop.setPosition(glitchSound(
			loop.getPosition(), 
			soundGlitchVary, 
			soundGlitchSubtle));

		// glitch the circles by modifying their outlines
		for (int i = 0; i < circlesGlitched; i ++) {
			ofPolyline &poly = circlePolys[i];	// use '&' to modify values!
			poly = glitchCircle(
				poly,
				visGlitchXVary / playback,
				visGlitchYVary / playback
			);
		}
	}

	// create shapes from the final outlines!
	for (int i = 0; i < circlePolys.size(); i++) {
		circlePaths[i] = getPath(circlePolys[i]);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// set background color for better transitions
	ofBackground(bgColor);
	
	// draw the circles
	for (int i = bands - 1; i > -1; i--) {
		ofPath path = circlePaths[i];
		path.setFillColor(colors[i]);
		path.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
		/* 
		*	When r is pressed, move circles to new positions and
		*	update the color scheme.
		*/
	case'r':
		for (int i = 0; i < bands + 1; i++) {
			keyColors[i] = getKeyColor();
		}
		for (int i = 0; i < bands; i++) {
			targetCircles[i] = setCirclePos(targetCircles[i], i, ofGetElapsedTimef()); // use elapsed time to offset the noise seed
			targetColors[i] = lerpColor(keyColors[i], keyColors[i + 1]);
		}
		targetBGColor = keyColors[0];
		targetBGColor.setBrightness(200);
		targetBGColor.setSaturation(100);
		break;
		// press 's' for a screenshot
	case 's':
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshot.save("screenshot" + ofToString(ofGetElapsedTimeMillis()) + ".png"); // use time to differentiate
		break;
		// press up to increase playback speed
	case OF_KEY_UP:
		playback = upperLowerGuard(playback + 0.01, playMax, playMin);
		loop.setSpeed(playback);
		break;
		// press down to decrease playback speed
	case OF_KEY_DOWN:
		playback = upperLowerGuard(playback - 0.01, playMax, playMin);
		loop.setSpeed(playback);
		break;
		// press left to decrease volume
	case OF_KEY_LEFT:
		volume = upperLowerGuard(volume - 0.01, volMax, volMin);
		loop.setVolume(volume);
		break;
		// press right to increase volume
	case OF_KEY_RIGHT:
		volume = upperLowerGuard(volume + 0.01, volMax, volMin);
		loop.setVolume(volume);
		break;
		// press 'g' to glitch
	case 'g':
		isGlitch = !isGlitch;
		break;
		// press 'u' to increase the number of circles glitched
	case 'u':
		circlesGlitched = upperLowerGuard(circlesGlitched + 1, bands, 0);
		break;
		// press 'y' to increase the visual glitch intensity
	case 'y':
		visGlitchXVary = upperLowerGuard(visGlitchXVary + 0.1, 100, 10);
		visGlitchYVary = upperLowerGuard(visGlitchYVary + 0.02, 20, 2);
		break;
		// press 't' to decrease the visual glitch intensity
	case 't':
		visGlitchXVary = upperLowerGuard(visGlitchXVary - 0.1, 100, 10);
		visGlitchYVary = upperLowerGuard(visGlitchYVary - 0.02, 20, 2);
		break;
		// press 'c' to trigger between subtle and obvious glitches
	case 'c':
		soundGlitchSubtle = !soundGlitchSubtle;
		break;
		// press 'b' to increase the noise of the obvious glitch
	case 'b':
		soundGlitchVary = upperLowerGuard(soundGlitchVary + 0.01f, 1.0f, 0.0f);
		break;
		// press 'v' to decrease the noise of the obvious glitch
	case 'v':
		soundGlitchVary = upperLowerGuard(soundGlitchVary - 0.01f, 1.0f, 0.1f);
		break;
		// press 'd' to delete a circle
	case 'd':
		if (bands >= 1) {
			bands -= 1;
		}
		break;
		// press 'a' to add a circle
	case 'a':
		if (bands < 32) {
			bands += 1;
		}
		break;
		// press 'k' to kill the visualization, reset everything
	case 'k':
		volume = volMin;
		playback = playMin;
		isGlitch = false;
		bands = 0;
		bgColor = ofColor(0);
		circlesGlitched = 0;
		soundGlitchSubtle = true;
		soundGlitchVary = 0.1;
		visGlitchXVary = 10;
		visGlitchYVary = 2;
		break;
		// press 'esc' to exit
	case OF_KEY_ESC:
		OF_EXIT_APP(0);
		break;
	}
}