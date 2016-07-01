#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    gpio17.setup("17");
    gpio17.export_gpio();
    gpio17.setdir_gpio("in");
    
    gpio27.setup("27");
    gpio27.export_gpio();
    gpio27.setdir_gpio("in");

    gpio22.setup("22");
    gpio22.export_gpio();
    gpio22.setdir_gpio("in");
    ropeNum = -1;
    
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	string videoPath = ofToDataPath("../../../video/Timecoded_Big_bunny_1.mov", true);
//
	//Somewhat like ofFboSettings we may have a lot of options so this is the current model
	ofxOMXPlayerSettings settings;
	settings.videoPath = videoPath;
	settings.useHDMIForAudio = true;	//default true
	settings.enableTexture = false;		//default t`rue
	settings.enableLooping = false;		//default true
	
	
	//so either pass in the settings
//    omxPlayer.setup(settings);
	
	//or live with the defaults
//	omxPlayer.loadMovie("./data/video/orb.mp4");
    secondVidTriggered = false;
	
}



//--------------------------------------------------------------
void ofApp::update()
{
    update_gpio();
		
}


//--------------------------------------------------------------
void ofApp::draw(){
//    if(!secondVidTriggered){
//        ofxOMXPlayerSettings settings;
//        settings = createSettings("../../../video/Timecoded_Big_bunny_1.mov");
//        introVideo.setup(settings);
//        secondVidTriggered = true;
//    }
   
}

void ofApp::update_gpio(){
    gpio17.getval_gpio(state_button_17);
    gpio27.getval_gpio(state_button_27);
    gpio22.getval_gpio(state_button_22);
    
    ropeNum = -1;
    if(state_button_17 == "1"){
        ropeNum = 1;
    } else if(state_button_27 == "1"){
        ropeNum = 2;
    } else if(state_button_22 == "1"){
        ropeNum = 3;
    }
}

void onButtonPress(int button){
    
}

bool ofApp::isPlaying(ofxOMXPlayer & player){
    if((ofGetElapsedTimef() - startTime) > player.getDurationInSeconds()){
        return false;
    } else {
        return true;
    }
}

ofxOMXPlayerSettings ofApp::createSettings(string dataPath){
    string videoPath = ofToDataPath(dataPath, true);
    ofxOMXPlayerSettings settings;
    settings.videoPath = videoPath;
    settings.useHDMIForAudio = true;	//default true
    settings.enableTexture = false;		//default true
    settings.enableLooping = false;		//default true
    return settings;
    
}
