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

        float startTime;

        string UID;
        string currentUID;

		ofxOMXPlayer introVideo;
        ofxOMXPlayer choiceOneVideo;
        ofxOMXPlayer choiceTwoVideo;
        ofxOMXPlayer choiceThreeVideo;
    
        GPIO gpio17;
        GPIO gpio27;
        GPIO gpio22;
        GPIO gpio26;
        int ropeNum;
        float stageThreeStartTime;
        float endTime;
    
        ofImage scoreScreen;
        ofImage introScreen;
    
        float score;
    
        int cryForHelp;
        int cryForHelp1;
        int cryForHelp2;
        int cryForHelp3;
};

