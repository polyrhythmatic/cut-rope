#include "ofMain.h"
#include "ofApp.h"

int main()
{
	ofSetupOpenGL(1280, 720, OF_FULLSCREEN);
    ofHideCursor();
	ofRunApp( new ofApp());
}