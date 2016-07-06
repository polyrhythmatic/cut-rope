#include "ofApp.h"

/*
 stage zero is before the card is swiped
 stage one is after the card is swiped - welcome screen and other info
 stage two is playing the intro video
 stage three is telling the user they have to make a decision
 stage four is playing the video that shows your selection
 stage five is the exit screen
 */
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackgroundHex(0x000000);
    stage = 0;
    startTime = ofGetElapsedTimef();
    
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
    
    currentVideo = & introVideo;
    font.loadFont("arial.ttf", 32);
    drawString = "";
}



//--------------------------------------------------------------
void ofApp::update(){
    if(stage == 1 && ofGetElapsedTimef() > 5.0){
        stage = 2;
        currentVideo = & introVideo;
//        playVideo(introVideo, "../../../video/Timecoded_Big_bunny_1.mov");
        playVideo(introVideo, "INTRO2.mov");
    }
    if(stage == 2 && !isPlaying(*currentVideo)){
        currentVideo->close();
        stage = 3;
    }
    if(stage == 3){
        ropeNum = update_gpio();
    }
    if(ropeNum > 0 && stage == 3){
        stage = 4;
        string videoPath = "";
        if(ropeNum == 1){
            currentVideo = & choiceOneVideo;
            videoPath = "CHOSE1.mp4";
        } else if(ropeNum == 2){
            currentVideo = & choiceTwoVideo;
            videoPath = "CHOSE2.mp4";
        } else if(ropeNum == 3){
            currentVideo = & choiceThreeVideo;
            videoPath = "CHOSE3.mp4";
        }
        playVideo(*currentVideo, videoPath);
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    if(stage == 0){
        font.drawString("swipe your card to begin", 500, 500);
    }
    if(stage == 1){
        float elapsed = ofGetElapsedTimef() - startTime;
        font.drawString(drawString, 100, 100);
        font.drawString(ofToString(elapsed), 100, 200);
    }
    if(stage == 3){
        font.drawString("chop the rope now", 100, 100);
    }
}

void ofApp::startGame(string userID){
    stage = 1;
//    startTime = ofGetElapsedTimef();
    drawString = userID;
}

void ofApp::resetGame(){
    stage = 0;
    ropeNum = -1;
    currentVideo->close();
    ofResetElapsedTimeCounter();
}


int ofApp::update_gpio(){
    string state_button_17;
    string state_button_27;
    string state_button_22;
    gpio17.getval_gpio(state_button_17);
    gpio27.getval_gpio(state_button_27);
    gpio22.getval_gpio(state_button_22);
    
    if(state_button_17 == "1"){
        return 1;
    } else if(state_button_27 == "1"){
        return 2;
    } else if(state_button_22 == "1"){
        return 3;
    } else {
        return -1;
    }
}

bool ofApp::isPlaying(ofxOMXPlayer & player){
    if((ofGetElapsedTimef() - startTime) > player.getDurationInSeconds()){
        return false;
    } else {
        return true;
    }
}

void ofApp::playVideo(ofxOMXPlayer & player, string path){
    ofxOMXPlayerSettings settings;
    settings = createSettings("video/" + path);
//    settings = createSettings(path);
    player.setup(settings);
    startTime = ofGetElapsedTimef();
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

//--------------------------------------------------------------
void ofApp::exit() {
    gpio17.unexport_gpio();
    gpio27.unexport_gpio();
    gpio22.unexport_gpio();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == 10){
        ofLog() << "reset";
        //make the API calls here
        //add a splash screen to let users know its loading?
        
        string url = "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22nome%2C%20ak%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
        if (!response.open(url))
        {
            ofLogNotice("ofApp::keyPressed") << "Failed to parse JSON";
        }
        cout << response["query"]["count"].asInt() << endl;
        
        ofLog() << UID;
        
        resetGame();
        startGame(UID);

        UID = "";
    } else {
        UID += key;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

