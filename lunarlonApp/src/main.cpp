#include "ofMain.h"
#include "lunarlon.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
        window.setGlutDisplayString("rgba double samples>=2");
	ofSetupOpenGL(&window, 1080,1080  , OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new lunarlon());

}
