#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackgroundHex(0x000000);
    gameRunning = false;
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
    hasChopped = false;

	ofSetLogLevel(OF_LOG_VERBOSE);
    
    currentVideo = & introVideo;
    font.loadFont("arial.ttf", 32);
    drawStuff = false;
    drawString = "";
}



//--------------------------------------------------------------
void ofApp::update(){
    if(currentVideo == & introVideo && !hasChopped && !isPlaying(*currentVideo) && !gameRunning){
        gameRunning = true;
    }
    
    if(gameRunning && !hasChopped){
        ropeNum = update_gpio();
    }
    
    if(ropeNum > 0 && !hasChopped && gameRunning){
        hasChopped = true;
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
    if(drawStuff){
        font.drawString(drawString, 100, 100);
    }
}

int ofApp::update_gpio(){
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
    player.setup(settings);
}

void ofApp::startGame(string userID){
    drawStuff = true;
    drawString = userID;
    currentVideo = & introVideo;
    playVideo(introVideo, "INTRO.mp4");
}

void ofApp::resetGame(){
    hasChopped = false;
    gameRunning = false;
    ropeNum = -1;
    introVideo.close();
    choiceOneVideo.close();
    choiceTwoVideo.close();
    choiceThreeVideo.close();
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

