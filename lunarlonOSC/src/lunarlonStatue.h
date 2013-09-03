#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


#define SEND_PORT 12346
#define RECEIVE_PORT 12345

//--------------------------------------------------------
class lunarlonStatue : public ofBaseApp {

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void sendTouch();
    void sendOff();

    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    string message;
    
    bool bTouched;
    
    //Touch controls & animation
    float touch(); //touch reaction triggering function
    bool bStartCount;
    float counter;
    bool bTimerReached;
    float touchReactionSpeed;


};

