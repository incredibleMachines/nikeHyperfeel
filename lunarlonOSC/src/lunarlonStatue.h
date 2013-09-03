#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SculptureTouch.h"
#include "Camera.h"
#include "ofxOpenCv.h"
#include "ofxSyphon.h"
#include "AdminWindow.h"
#include "ofxControlPanel.h"


#define SEND_PORT 12346
#define RECEIVE_PORT 12345

class Blob {
public:
    ofxCvBlob blob;
    ofPoint closest;
    int centroidDist;
};

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

    //OSC Communication with lunarlonApp
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
  
    //Touch Mask
    SculptureTouch sculpture;
    vector <ofVec2f> blobPoints;
    
    //--- camera and CV stuffs
    //--- TODO: move to lunarCV.h
    Camera camera;
    
    int camWidth;
    int camHeight;
    ofxCvColorImage			colorImg;
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    ofxCvContourFinder      contourFinder;
    ofPoint corners[4];
    int selectedCorner;
    
    
    int stageWidth;
    int stageHeight;
    ofPoint camZoom, camOffset;
    ofxCvColorImage			colorImgStage;
    ofxCvGrayscaleImage 	grayImageStage;
    ofxCvGrayscaleImage 	grayBgStage;
    ofxCvGrayscaleImage 	grayDiffStage;
    ofxCvContourFinder      contourFinderStage;
    ofImage capturedBgImage;
    
    int 				threshold;
    bool				bLearnBakground;
    
    int stageCenterX, stageCenterY, stagingX, stagingY, offset;
    
    vector<Blob> blobs;
    int blobDist;
    
    //--- syphon
    ofTexture tex;
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;
    
    //--- admin, settings, gui
    ofxXmlSettings XML;
    AdminWindow admin;
    bool bDrawAdmin;
    
    //--- stage state - what page are we looking at
    int stageState;
    
    //--- debug
    bool mouseAsBlob;
    int nMouseBlobs;

};

