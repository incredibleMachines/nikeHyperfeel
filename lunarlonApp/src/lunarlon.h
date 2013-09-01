#pragma onceof mes

#include "ofMain.h"
#include "ring.h"

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
    
    float touch();
    
    // Touch Controls
    bool bTouch;
    vector<ofVec2f>blobs;
    float startTime;
    float endTime;
    bool bTimerReached;
    float counter;
    bool bStartCount;
    float touchReactionSpeed;
    
    
    // Styling
    ofImage bg;
    
    
    // Rings
    vector<Ring>rings;
    ofVec2f centerOfRings;

    
    
    // Particles
    float particleDist;
    float particleSpringiness;
       

    
    // Fbo
    
    
    
    // Shader
    
    
    
    
    
		
};
