#include "cloudSender.h"

//--------------------------------------------------------------
void cloudSender::setup(){

	ofBackground(40, 100, 40);

	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void cloudSender::update(){

}

//--------------------------------------------------------------
void cloudSender::draw(){
	// display instructions
	string buf;
	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
}

//--------------------------------------------------------------
void cloudSender::keyPressed(int key){
	if(key == '1'){
		ofxOscMessage m;
		m.setAddress("/on");
		m.addIntArg(1);
		sender.sendMessage(m);
	}
    if(key == '2'){
		ofxOscMessage m;
		m.setAddress("/on");
		m.addIntArg(2);
		sender.sendMessage(m);
	}
    if(key == '3'){
		ofxOscMessage m;
		m.setAddress("/on");
		m.addIntArg(3);
		sender.sendMessage(m);
	}
    if(key == '4'){
		ofxOscMessage m;
		m.setAddress("/on");
		m.addIntArg(4);
		sender.sendMessage(m);
	}
}

//--------------------------------------------------------------
void cloudSender::keyReleased(int key){
    if(key == '1'){
		ofxOscMessage m;
		m.setAddress("/off");
		m.addIntArg(1);
		sender.sendMessage(m);
	}
    if(key == '2'){
		ofxOscMessage m;
		m.setAddress("/off");
		m.addIntArg(2);
		sender.sendMessage(m);
	}
    if(key == '3'){
		ofxOscMessage m;
		m.setAddress("/off");
		m.addIntArg(3);
		sender.sendMessage(m);
	}
    if(key == '4'){
		ofxOscMessage m;
		m.setAddress("/off");
		m.addIntArg(4);
		sender.sendMessage(m);
	}
}

//--------------------------------------------------------------
void cloudSender::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void cloudSender::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void cloudSender::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void cloudSender::mouseReleased(int x, int y, int button){


}

//--------------------------------------------------------------
void cloudSender::windowResized(int w, int h){

}

//--------------------------------------------------------------
void cloudSender::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void cloudSender::dragEvent(ofDragInfo dragInfo){

}

