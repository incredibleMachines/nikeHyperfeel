#include "lunarlonStatue.h"

//--------------------------------------------------------------
void lunarlonStatue::setup(){

	ofBackground(40, 100, 40);

	// open an outgoing connection to HOST:PORT
	sender.setup("192.168.1.10", SEND_PORT);
    receiver.setup(RECEIVE_PORT);
    bTouched=false;
    ofBackground(255);
    
    //Touch Controls
    bTouched = false;
    counter = 0;
    touchReactionSpeed = 0.005;
    bTimerReached = false;
    bStartCount = false;
    
    //Mask
    sculpture.setup();
    
    //--- camera
    camWidth = 320;//640;
    camHeight = 240;//480;
    
    camZoom.x=850;
    camZoom.y=400;
    camOffset.x=-350;
    camOffset.y=100 ;
    
    camera.setup(camWidth, camHeight);  //-- ofxPs3Eye
    camera.ps3eye.setBrightness(admin.gui.getValueF("CAM1:BRIGHTNESS"));
    camera.ps3eye.setGamma(admin.gui.getValueF("CAM1:GAMMA"));
    camera.ps3eye.setContrast(admin.gui.getValueF("CAM1:CONTRAST"));
    camera.ps3eye.setHue(admin.gui.getValueF("CAM1:HUE"));
    threshold = admin.gui.getValueF("CAM1:THRESH");
    
    stageCenterX = ofGetWidth()/2;
    stageCenterY = ofGetHeight()/2;
    stagingX = camOffset.x; //stageCenterX-stageWidth/2;
    stagingY = camOffset.y; //stageCenterY-stageHeight/2;
    offset = 150;
    
    colorImg.allocate(camWidth,camHeight);
	grayImage.allocate(camWidth,camHeight);
	grayBg.allocate(camWidth,camHeight);
	grayDiff.allocate(camWidth,camHeight);
    
    stageWidth = ofGetWidth()+camZoom.x;//960;
    stageHeight = ofGetHeight()+camZoom.y;//960;
    
    
	bLearnBakground = false;
    blobDist = 10; //distance in pixels under which blobs will be combined/ignored
    
    
    //loadLatestBgCapture(); //pull last captured BG image from file!
    
    //--- staging, pagination
    stageState = 2; //0=camera raw; 1=CV debug; 2=LIVE
    
    //--- debuggin
    mouseAsBlob = true; //for debug purposes
    nMouseBlobs = 3; //supports up to 4 only!
    tex.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);

    
}

//--------------------------------------------------------------
void lunarlonStatue::update(){
    while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if(m.getAddress()=="/touch"){
            if (m.getArgAsInt32(0)==1)
            {
                message="touched";
                bTouched=true;
            }
            else if (m.getArgAsInt32(0)==0)
            {
                bTouched=false;
                message="off";
            }
        }
    }
    
    
    if (camera.update()){ //returns true if frame is new
        colorImg.setFromPixels(camera.getPixels(), camWidth, camHeight);
        grayImage = colorImg;
        if (bLearnBakground == true){
            grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
            /*** save this new bg image to file! ***/
            ofImage backgroundImg;
            backgroundImg.setFromPixels(camera.getPixels(), camWidth, camHeight, OF_IMAGE_COLOR);
            string archiveFileName = "bg_background_capture_"+ofGetTimestampString()+".png"; //dated
            string fileName = "bg_latestBackgroundCapture.png"; //static name
            backgroundImg.saveImage(fileName);
            backgroundImg.saveImage(archiveFileName);
            cout<<"SAVED BG IMAGE: "<< archiveFileName << endl;
            
            bLearnBakground = false;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayDiff, 20, (camWidth*camHeight)/3, 10, true);	// find holes
    }
    
    blobs.clear();
    blobPoints.clear();
    
    for (int i = 0; i < contourFinder.nBlobs; i++){ //for every blob
        float distFromCenter = ofDist(contourFinder.blobs[i].centroid.x,
                                      contourFinder.blobs[i].centroid.y, camWidth/2, camHeight/2);
        ofPoint blobClosest;
        
        
        //        contourFinder.blobs[i].draw( stagingX, stagingY ); //draw this blob on the stage
        
        bool bNewBlob=true;
        
        for(int j=0; j<blobs.size();j++){
            if (ofDist(contourFinder.blobs[i].centroid.x,
                       contourFinder.blobs[i].centroid.y, blobs[j].blob.centroid.x, blobs[j].blob.centroid.y)<blobDist)
            {
                bNewBlob=false;
                if(distFromCenter<blobs[j].centroidDist){
                    blobs[j].blob=contourFinder.blobs[i];
                    blobs[j].centroidDist=distFromCenter;
                    float blobCenterDist;
                    for(int k=0;k<blobs[j].blob.nPts;k++){
                        if(k==0){
                            blobCenterDist=ofDist(blobs[j].blob.pts[k].x+stagingX,
                                                  blobs[j].blob.pts[k].y+stagingY, stageCenterX, stageCenterY);
                            blobClosest.x=blobs[j].blob.pts[k].x+stagingX;
                            blobClosest.y=blobs[j].blob.pts[k].y+stagingY;
                        }
                        float currentCenterDist=ofDist(blobs[j].blob.pts[k].x+stagingX,
                                                       blobs[j].blob.pts[k].y+stagingY, stageCenterX, stageCenterY);
                        if(currentCenterDist<blobCenterDist){
                            blobCenterDist=currentCenterDist;
                            blobClosest.x=blobs[j].blob.pts[k].x+stagingX;
                            blobClosest.y=blobs[j].blob.pts[k].y+stagingY;
                        }
                    }
                    blobs[j].closest=blobClosest;
                }
            }
        }
        
        if(bNewBlob==true){
            Blob tempBlob;
            tempBlob.blob=contourFinder.blobs[i];
            tempBlob.centroidDist=distFromCenter;
            float blobCenterDist;
            for(int k=0;k<tempBlob.blob.nPts;k++){
                if(k==0){
                    blobCenterDist=ofDist(tempBlob.blob.pts[k].x,
                                          tempBlob.blob.pts[k].y,camWidth/2, camHeight/2);
                    blobClosest.x=tempBlob.blob.pts[k].x+stagingX;
                    blobClosest.y=tempBlob.blob.pts[k].y+stagingY;
                }
                float currentCenterDist=ofDist(tempBlob.blob.pts[k].x,
                                               tempBlob.blob.pts[k].y,camWidth/2, camHeight/2);
                if(currentCenterDist<blobCenterDist){
                    blobCenterDist=currentCenterDist;
                    blobClosest.x=tempBlob.blob.pts[k].x;
                    blobClosest.y=tempBlob.blob.pts[k].y;
                    
                }
            }
            tempBlob.closest=blobClosest;
            blobs.push_back(tempBlob);
        }
        
        
        //        int blue = ofMap(distFromCenter, 50, stageWidth/2, 0, 255);
        //        int red =ofMap(distFromCenter, 50, stageWidth/2, 255, 0);
        //        ofSetColor(red,0,blue);
        //        ofFill();
        //        ofEllipse(contourFinder.blobs[i].centroid.x + stagingX, contourFinder.blobs[i].centroid.y + stagingY, 50, 50); //draw ID circles
        //        ofSetColor(255);
        //        ofDrawBitmapString(ofToString(i), contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y + stagingY); //draw ID number
    }
    
    //--- debuggin
    if(mouseAsBlob){
        blobPoints.clear();
        for (int i=0; i<nMouseBlobs; i++){
            int thisX = mouseX;
            int thisY = mouseY;
            ofVec2f mouse;
            if(i == 0){
            } else if (i==1){
                thisX = ofGetWidth() - mouseX;
                thisY = ofGetHeight() - mouseY;
            } else if (i==2){
                thisX = ofGetWidth() - mouseX;
            } else if(i ==3){
                thisY = ofGetHeight() - mouseY;
            } else break;
            mouse.set(thisX, thisY);
            //blobPoints[i] = ofVec2f(thisX, thisY);
            blobPoints.push_back(mouse);
        }
    }
    //-------- let's do this
    else {
        for(int j=0; j<blobs.size();j++){
            ofVec2f thisBlob;
            thisBlob.x=ofMap(blobs[j].closest.x,0,camWidth,0,stageWidth);
            thisBlob.x+=stagingX;
            thisBlob.y=ofMap(blobs[j].closest.y,0,camHeight,0,stageHeight);
            thisBlob.y+=stagingY;
            blobPoints.push_back(thisBlob);
        }
    }
    
//    cout<<"blobPoints.size(): "<<blobPoints.size()<<endl;
    
    //--- admin
    if(bDrawAdmin) {
        admin.update();
        camera.ps3eye.setBrightness(admin.gui.getValueF("CAM1:BRIGHTNESS"));
        
        //    gain1=gui.getValueF("CAM1:GAIN:CURRENT");
        camera.ps3eye.setGamma(admin.gui.getValueF("CAM1:GAMMA"));
        //    shutter1=gui.getValueF("CAM1:SHUTTER:CURRENT");
        camera.ps3eye.setContrast(admin.gui.getValueF("CAM1:CONTRAST"));
        camera.ps3eye.setHue(admin.gui.getValueF("CAM1:HUE"));
        threshold=admin.gui.getValueF("CAM1:THRESH");
    }
    
    sculpture.update();
}

//--------------------------------------------------------------
void lunarlonStatue::draw(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    
    ofBackground(10,10,10);
    //------------------------- debug camera view -- raw camera input
    if (stageState == 0){
        camera.draw(stagingX, stagingY, stageWidth, stageHeight);
        for(int j=0;j<blobPoints.size();j++){
            
            blobs[j].blob.draw();
            ofFill();
            ofSetColor(255,0,0);
            ofEllipse(blobPoints[j].x, blobPoints[j].y,10,10);
        }
    }
    //------------------------- debug image processing
    else if(stageState == 1){
        // draw the incoming, the grayscale, the bg and the thresholded difference
        ofSetHexColor(0xffffff);
        colorImg.draw(20,20);
        grayImage.draw(360,20);
        grayBg.draw(20,280);
        grayDiff.draw(360,280);
        
        
        // then draw the contours:
        ofFill();
        ofSetHexColor(0x333333);
        ofRect(360,540,320,240);
        ofSetHexColor(0xffffff);
        
        // we could draw the whole contour finder
        //contourFinder.draw(360,540);
        
        // or, instead we can draw each blob individually from the blobs vector,
        // this is how to get access to them:
        for (int i = 0; i < contourFinder.nBlobs; i++){
            contourFinder.blobs[i].draw(360,540);
            
            // draw over the centroid if the blob is a hole
            ofSetColor(255);
            if(contourFinder.blobs[i].hole){
                ofDrawBitmapString("hole",
                                   contourFinder.blobs[i].boundingRect.getCenter().x + 360,
                                   contourFinder.blobs[i].boundingRect.getCenter().y + 540);
            }
        }
        
        // finally, a report:
        ofSetHexColor(0xffffff);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
        << "press 'b' to capture bg" << endl
        << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
        ofDrawBitmapString(reportStr.str(), 20, 600);
    }
    
    
    //------------------------ draw rings, user animation
    else if(stageState == 2){
        ofColor bgColor;
        bgColor.setHsb(78, 100 + 155*touch(), 255*touch());
        ofBackground(0);
        
        // display instructions
        string buf;
        buf = "sending osc messages to " + string("192.168.1.10") + ofToString(SEND_PORT);
        ofDrawBitmapString(buf, 10, 20);
        buf = "receiving osc message" + message+" from "+ string("192.168.1.10") + ofToString(RECEIVE_PORT);
        ofDrawBitmapString(buf, 10, 40);
        
        sculpture.draw(bgColor);

    }
    
    //--- syphon
    tex.loadScreenData(0, 0, ofGetWidth(), ofGetHeight());
    individualTextureSyphonServer.publishTexture(&tex);
    ofSetColor(255);
    
    //--- admin
    if(bDrawAdmin) admin.draw();

}

//--------------------------------------------------------------
float lunarlonStatue::touch(){
    
    if (bTouched) {
        bStartCount = true;
    }
    
    if (bStartCount && !bTimerReached) {
        counter+=touchReactionSpeed;
    }
    
    if (counter>=1) {
        bTimerReached = true;
    }
    
    if(!bTouched && bTimerReached){
        counter-=touchReactionSpeed;
        if (counter<=0.1) {
            bStartCount = false;
            bTimerReached = false;
            bTouched = false; // pointer to bTouch on lunarlon.cpp
        }
    }
    return counter;
}

//--------------------------------------------------------------
void lunarlonStatue::keyPressed(int key){
    
    switch (key) {
        case 't':
            bTouched = true;
            sendTouch();
            break;
            
        case 'r':
            for (int i=0; i<blobPoints.size(); i++) {
                blobPoints[i].set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
            }
            break;
            
		case 'b':
            //---camera.saveBackgroundCaptureImg();
            //---loadLatestBgCapture();
			bLearnBakground = true;
			break;
            
        case ' ':
            stageState++;
            if (stageState>2) stageState = 0;
            cout<<"stageState: "<<stageState<<endl;
            break;
            
        case 'c':
            camera.printCurrentSettings();
            break;
            
        case '`':
            bDrawAdmin = !bDrawAdmin;
            cout<<"bDrawAdmin = "<<bDrawAdmin<<endl;
            break;
            
        case 'm':
            mouseAsBlob = !mouseAsBlob; //use mouse as a blob
            break;
            
            //        case 'r':
            //            //stage.toggleTranslucentMode();
            //            break;
            
	}
    
    if(bDrawAdmin){
        admin.keyPressed(key);
    }

}

//--------------------------------------------------------------
void lunarlonStatue::keyReleased(int key){
    switch (key) {
        case 't':
            bTouched = false;
            sendTouch();
            break;
    }
    if(bDrawAdmin){
        admin.keyReleased(key);
    }

}

//--------------------------------------------------------------
void lunarlonStatue::mouseMoved(int x, int y){
    if(bDrawAdmin){
        admin.mouseMoved(x,y);
    }
}

//--------------------------------------------------------------
void lunarlonStatue::mouseDragged(int x, int y, int button){
    if(bDrawAdmin){
        admin.mouseDragged(x,y,button);
    }
}

//--------------------------------------------------------------
void lunarlonStatue::mousePressed(int x, int y, int button){
    if(bDrawAdmin){
        admin.mouseReleased(x,y,button);
    }
}

//--------------------------------------------------------------
void lunarlonStatue::mouseReleased(int x, int y, int button){


}

//--------------------------------------------------------------
void lunarlonStatue::windowResized(int w, int h){

}

//--------------------------------------------------------------
void lunarlonStatue::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void lunarlonStatue::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void lunarlonStatue::sendTouch(){
    ofxOscMessage m;
    m.setAddress("/touch");
    m.addIntArg(1);
    sender.sendMessage(m);
    
    cout<<"bang"<<endl;
    
}
//--------------------------------------------------------------
void lunarlonStatue::sendOff(){
    ofxOscMessage m;
    m.setAddress("/touch");
    m.addIntArg(0);
    sender.sendMessage(m);
    
}

