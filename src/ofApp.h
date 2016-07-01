#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
    
        bool isPlaying(ofxOMXPlayer & player);
        int update_gpio();
        void resetChop();
    
        ofxOMXPlayerSettings createSettings(string dataPath);
    
        ofxOMXPlayer omxPlayer;
		ofxOMXPlayer introVideo;
        ofxOMXPlayer choiceOneVideo;
        ofxOMXPlayer choiceTwoVideo;
        ofxOMXPlayer choiceThreeVideo;
    
        float startTime;
    
        GPIO gpio17;
        GPIO gpio27;
        GPIO gpio22;
        string state_button_17;
        string state_button_27;
        string state_button_22;
        int ropeNum;
        bool hasChopped;
};

