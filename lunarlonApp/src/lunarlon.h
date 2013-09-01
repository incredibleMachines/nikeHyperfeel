#pragma onceof mes

#include "ofMain.h"
#include "ring.h"
#include "ringMaster.h"
#include "user.h"

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
    

    // Styling
    ofImage bg;
    
    //Ring Master
    RingMaster ringmaster;
    vector<ofVec2f>blobPoints;

    // Touch
    bool bTouch;
    
    //User graphics
    vector<User>users;
    

};
