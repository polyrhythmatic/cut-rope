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
    setupGPIO();
    ropeNum = -1;
    score = 0.0;
    stageThreeStartTime = 0.0;
    endTime = 0;
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    currentVideo = & introVideo;
    font.loadFont("HelveticaNeue.ttf", 82);
    
    scoreScreen.load("images/score_screen.png");
    introScreen.load("images/intro_screen.jpg");
    endScoreScreen.load("images/end_score_screen.png");
    cryForHelp = 0;
    cryForHelp1 = 0;
    cryForHelp2 = 0;
    cryForHelp3 = 0;
}



//--------------------------------------------------------------
void ofApp::update(){
    update_gpio();
    if(stage == 1 && ofGetElapsedTimef() > 5.0){
        stage = 2;
        currentVideo = & introVideo;
        playVideo(introVideo, "INTRO.mp4");
    }
    if(stage == 2 && ofGetElapsedTimef() - startTime > 25.0){ //if the intro video is past 30 seconds long then they can make a decision
        stage = 3;
        stageThreeStartTime = ofGetElapsedTimef();
    }
    if(stage == 3 && !isPlaying(*currentVideo)){
        //close the video when it stops
        currentVideo->close();
    }
    if(stage == 3){
        ropeNum = update_gpio();
    }
    if(stage == 3 && ropeNum > 0){ //ropenum is greater than 0 if a button has been triggered
        stage = 4;
        string videoPath = "";
        currentVideo->close();
        if(ropeNum == 1){
            currentVideo = & choiceOneVideo;
            videoPath = "CHOSE1.mp4";
            score = -250.0;
        } else if(ropeNum == 2){
            currentVideo = & choiceTwoVideo;
            videoPath = "CHOSE2.mp4";
            score = -500.0;
        } else if(ropeNum == 3){
            currentVideo = & choiceThreeVideo;
            videoPath = "CHOSE3.mp4";
            score = -750.0;
        }
        playVideo(*currentVideo, videoPath);
    } else if(stage == 3 && ofGetElapsedTimef() - stageThreeStartTime > 15.0){ //else if 10 seconds has elapsed
        resetGame();
    } else if(stage == 4 && !isPlaying(*currentVideo)){
        cout << "changing stage" << endl;
        currentVideo->close();
        stage = 5;
        endTime = ofGetElapsedTimef();
        sendScores(currentUID);
    } else if(stage == 5 && ofGetElapsedTimef() - endTime > 10){
        resetGame();
        UID = "";
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    if(stage == 0){
        introScreen.draw(0, 0);
    } else if(stage == 1){
        scoreScreen.draw(0, 0);
        font.drawString("Game 1:", 200, 600);
        if(cryForHelp1 == -500){
            font.drawString("You've lost 10% of your supplies", 250, 700);
        } else if(cryForHelp1 == 1000){
            font.drawString("You've gained 20% more supplies.", 250, 700);
        }
        font.drawString("Game 2:", 200, 850);
        if(cryForHelp2 == -500){
            font.drawString("You've lost 10% more supplies.", 250, 950);
        } else if(cryForHelp2 == 250){
            font.drawString("You've gained 5% more supplies.", 250, 950);
        }
//        font.drawString("Game 3:", 200, 800);
//        if(cryForHelp3 == -500){
//            font.drawString("You’ve lost 10% more supplies.", 250, 900);
//        } else if(cryForHelp3 == 500){
//            font.drawString("You’ve gained 10% more supplies.", 250, 900);
//        }
    } else if(stage == 3){
//        font.drawString("chop the rope", 500, 500);
    } else if(stage == 5){
        endScoreScreen.draw(0, 0);
        if(score == -250.0){
            font.drawString("You've lost 10% of your supplies", 200, 500);
        } else if(score == -500.0){
            font.drawString("You've lost 10% of your supplies.", 200, 500);
        } else if(score == -750.0){
            font.drawString("You've lost 20% of your supplies.", 200, 500);
        }
    }
}

void ofApp::startGame(string userID){
    stage = 1;
    startTime = 0.0;
}

void ofApp::resetGame(){
    stage = 0;
    ropeNum = -1;
    currentVideo->close();
    ofResetElapsedTimeCounter();
    score = 0.0;
}

void ofApp::setupGPIO(){
    gpio17.setup("17");
    gpio17.export_gpio();
    gpio17.setdir_gpio("in");
    gpio27.setup("27");
    gpio27.export_gpio();
    gpio27.setdir_gpio("in");
    gpio22.setup("22");
    gpio22.export_gpio();
    gpio22.setdir_gpio("in");
    gpio26.setup("26");
    gpio26.export_gpio();
    gpio26.setdir_gpio("in");
}

int ofApp::update_gpio(){
    string state_button_17;
    string state_button_27;
    string state_button_22;
    string state_button_26;
    gpio17.getval_gpio(state_button_17);
    gpio27.getval_gpio(state_button_27);
    gpio22.getval_gpio(state_button_22);
    gpio26.getval_gpio(state_button_26);
    
    if(state_button_26 == "1"){
        ofLog() << "shutdown";
        ofSystem("sudo shutdown -h now");
    }

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
    settings.useHDMIForAudio = false;	//default true
    settings.enableTexture = false;		//default true
    settings.enableLooping = false;		//default true
    return settings;
    
}

void ofApp::getQScores(string userID){
    ofxJSONElement response;
    string url = "http://10.102.10.202/api/mh1uo7i0zwnopqfr9awo7j1ihmukrzfrnuzop4ylpgvw8kt9fcikr1am3c45z5mie3o233zub22tvs4i/project/ftwd2016/getticketmiscfield?&uid=" + userID + "&miscfieldid[]=83&miscfieldid[]=85&miscfieldid[]=87&miscfieldid[]=77&miscfieldid[]=79&miscfieldid[]=81";
    cout << url << endl;
    if (!response.open(url))
    {
        ofLogNotice("ofApp::keyPressed") << "Failed to parse JSON";
        // this is where we prompt the user to scan again?
    }
    cout << ofToInt(response["cry_for_help"].asString()) << endl;
    cryForHelp1 = ofToInt(response["cry_for_help_1"].asString());
    cryForHelp2 = ofToInt(response["cry_for_help_2"].asString());
//    cryForHelp3 = ofToInt(response["cry_for_help_3"].asString());

    cryForHelp = ofToInt(response["cry_for_help"].asString());
    cout << response << endl;
}

void ofApp::sendScores(string userID){
    //adds to the final score
    ofxJSONElement response;
    string scoreString = ofToString(floor(score));
    cout << scoreString << endl;
    string url = "http://10.102.10.202/api/mh1uo7i0zwnopqfr9awo7j1ihmukrzfrnuzop4ylpgvw8kt9fcikr1am3c45z5mie3o233zub22tvs4i/project/ftwd2016/setticketmiscfield?&uid=" + userID + "&miscfieldid=81&value=+" + scoreString;
    cout << url << endl;
    if (!response.open(url))
    {
        ofLogNotice("ofApp::keyPressed") << "Failed to parse JSON";
        // this is where we prompt the user to scan again?
    }
    ofLog() << "score submitted";
    ofLog() << response;
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
        ofLog() << UID;
        
        resetGame();
        getQScores(UID);
        startGame(UID);
        
        currentUID = UID;
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
    std::exit(1);
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

