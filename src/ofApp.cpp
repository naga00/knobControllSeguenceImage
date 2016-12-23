#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxXmlSettings settings;
    settings.loadFile("settings.xml");
    
    FPS = settings.getValue("group:FPS", 60);
    isGUI = settings.getValue("group:isGUI", false);
    sequenceFPS = settings.getValue("group:sequenceFPS", 60);
    sequenceSize = settings.getValue("group:sequenceSize", 100);
    int width = settings.getValue("group:width", 1024);
    int height = settings.getValue("group:height", 576);
    string dirName = settings.getValue("group:dirName", "images");
    bFrameIndependent = settings.getValue("group:bFrameIndependent", true);
    loopState = settings.getValue("group:loopState", "NORMAL");
    startPosition = settings.getValue("group:startPosition", 0.0);
    initThrust = settings.getValue("group:initThrust", 1.0);
    friction = settings.getValue("group:friction", 0.97);
    isFullscreen = settings.getValue("group:isFullscreen", false);
    prevDirection = "next";
    
    if(bFrameIndependent) {
        minSpeed = sequenceFPS / FPS;
    }else{
        minSpeed = 1.0;
    }
        
    ofBackground(0, 0, 0);
    ofSetWindowTitle("Knob Controll Images");
    ofSetFrameRate(FPS);
    ofSetFullscreen(isFullscreen);
    if(isFullscreen){
        ofSetWindowShape(ofGetWidth(), ofGetHeight());
    }else{
        ofSetWindowShape(width, height);
    }
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(true);
    
    points[0].x = 0; points[0].y = 0;
    points[1].x = ofGetWidth(); points[1].y = 0;
    points[2].x = ofGetWidth(); points[2].y = ofGetHeight();
    points[3].x = 0; points[3].y = ofGetHeight();
    
    ofDirectory dir;
    int nFiles = dir.listDir(dirName);
    if(nFiles) {
        int imageSize = (sequenceSize == 0) ? dir.numFiles() : sequenceSize;
        for(int i=0; i<imageSize; i++) {
            string filePath = dir.getPath(i);
            images.push_back(ofTexture());
            ofLoadImage(images[i], filePath);
        }
    }else{
        printf("Could not find folder\n");
    }
    
    frameIndex = (int)(images.size() * startPosition);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if((int)images.size() <= 0) {
        ofSetColor(255);
        ofDrawBitmapString("No Images...", 150, ofGetHeight()/2);
        return;
    }

    float accel = thrust;
    speed += accel;
    speed *= friction;
    
    if(prevDirection == "next"){
        if(speed < minSpeed){
            speed = minSpeed;
        }
    }else if(prevDirection == "prev"){
        if(speed > - minSpeed){
            speed = - minSpeed;
        }
    }
    
    frameIndex += speed;
    
    if(loopState == "NONE"){
        if(frameIndex <= 0) {
            frameIndex = 0;
        }else if(frameIndex >= images.size() - 1){
            frameIndex = images.size() -1;
        }
    }else{
        if(frameIndex < 0) {
            frameIndex = images.size() -1;
        }else if(frameIndex > images.size() - 1){
            frameIndex = 0;
        }
    }
    images[(int)frameIndex].draw(points[0], points[1], points[2], points[3]);
    thrust = 0.0;
    
    if(isGUI){
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(ofToString(ofGetFrameRate(), 0) + " FPS", 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 358){
        thrust = initThrust;
        prevDirection = "next";
    }else if(key == 356){
        thrust = -initThrust;
        prevDirection = "prev";
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
