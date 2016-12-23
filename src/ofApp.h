#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    int FPS;
    bool isGUI;
    float sequenceFPS;
    int sequenceSize;
    bool bFrameIndependent;
    vector<ofTexture> images;
    ofPoint points[4];
    float frameIndex;
    
    bool isFullscreen;
    string loopState;
    float startPosition;
    float initThrust;
    float friction;
    float thrust;
    float speed;
    string prevDirection;
    float minSpeed;
};
