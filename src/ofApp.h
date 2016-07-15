#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "ofxGPIO.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
        void exit();
        
        void keyPressed (int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
        void playVideo(ofxOMXPlayer & player, string path);
        void getQScores(string userID);
        void sendScores(string userID);

        bool isPlaying(ofxOMXPlayer & player);
        void setupGPIO();
        int update_gpio();
    
        ofTrueTypeFont font;
    
        void startGame(string userID);
        void resetGame();
        int stage;
    
        ofxOMXPlayerSettings createSettings(string dataPath);
    
        ofxOMXPlayer * currentVideo;
    
        string drawString;
        float startTime;

        string UID;
        string currentUID;

		ofxOMXPlayer introVideo;
        ofxOMXPlayer choiceOneVideo;
        ofxOMXPlayer choiceTwoVideo;
        ofxOMXPlayer choiceThreeVideo;
        ofxOMXPlayer choiceFourVideo;
    
        GPIO gpio17;
        GPIO gpio27;
        GPIO gpio22;
        int ropeNum;
        float stageThreeStartTime;
        float endTime;
    
        ofImage scoreScreen;
    
        float score;
    
    
        float qScore1;
        float qScore2;
        float qScore3;
        float qScore4;
        float qScore5;
        float cryForHelp;
        string surveyOneChoice[5] = {"father", "sister", "best friend", "spouse", "mother"};
        string surveyTwoChoice[5] = {"length of rope", "toolkit", "first aid kit", "machete", "arrows"};
        string surveyThreeChoice[5] = {"medicine kit", "electronic gear", "outdoor gear", "extra clothing", "family photos"};
        string surveyFourChoice[5] = {"chainsaw", "shotgun", "butcher's knife", "axe", "handgun"};
};

