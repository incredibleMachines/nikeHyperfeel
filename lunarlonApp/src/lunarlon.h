#pragma onceof mes

#include "ofMain.h"
#include "ring.h"
#include "ringMaster.h"
#include "user.h"
#include "AdminWindow.h"
#include "ofxControlPanel.h"
#include "ofxOpenCv.h"
#include "ofxSyphon.h"
#include "Camera.h"
#include "ofxOsc.h"
#include "SculptureTouch.h"

#define SEND_PORT 12345
#define RECEIVE_PORT 12346

class Blob {
public:
    ofxCvBlob blob;
    ofPoint closest;
    int centroidDist;
};

class lunarlon : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    

    void sendTouch();
    void sendOff();
    void receiveTouch();
    float animateTouch(); //touch reaction triggering function
    void loadLatestBgCapture();

    

    // Styling
    ofImage bg;
    
    //Ring Master
    RingMaster ringmaster;
    vector <ofVec2f> blobPoints;

    //User graphics
    vector <User> users;
    
    // Touch
    bool bTouch;
    
    // Touch animation
    float startTime;
    float endTime;
    bool bTimerReached;
    float counter;
    bool bStartCount;
    float touchReactionSpeed;
    float  TouchReactionAmt;
    
    
    //--- stage state - what page are we looking at
    int stageState;
    

    
    //--- debug
    bool mouseAsBlob;
    int nMouseBlobs;
    
    //--- admin, settings, gui
    ofxXmlSettings XML;
    AdminWindow admin;
    bool bDrawAdmin;
    
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
    
    //--- OSC communication with lunarlonOSC
    ofxOscSender touchSend;
    ofxOscReceiver touchReceive;
    
    //--- sculpture detection
    SculptureTouch sculpture;
    bool bShowSculpture;

};



