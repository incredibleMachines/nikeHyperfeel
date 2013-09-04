#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

#include "ofxSyphon.h"

#define PORT 12345
#define SCREEN 3

class cloudPlayer : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void fadeOut();
    void fadeIn();

		ofVideoPlayer 		cloudMovie;
        ofxOscReceiver receiver;
    
    bool bFadingOut, bFadingIn;
    float fadeOutTimer, fadeInTimer;
    float fadeOutSpeed, fadeInSpeed;
    
    bool bMask, bWhite, bHorizBorder, bVertBorder;
    bool bAdjustHoriz;
    bool bAdjustVert;
    
    int gradientCenter;
    int gradientWidth, gradientFadeWidth, horizWidth, horizFadeWidth, vertWidth, vertFadeWidth;
    
    ofxXmlSettings settings;
    		string message;
    
    //--- syphon
    ofTexture tex;
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;

};

