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

        bool isPlaying(ofxOMXPlayer & player);
        int update_gpio();
    
        ofTrueTypeFont font;
    
        void startGame(string userID);
        void resetGame();
    
        ofxOMXPlayerSettings createSettings(string dataPath);
    
        ofxOMXPlayer * currentVideo;
        bool gameRunning;
        bool drawStuff;
        string drawString;

        string UID;
        ofxJSONElement response;
    
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

