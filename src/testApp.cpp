#include "testApp.h"
#include "ofGui.h"

ofMenuBar menu;
ofMenuItem finder, file, lol, chicken;
ofDesktop desk;
ofIcon webcam, windows, safari, quickTime;
ofWallpaper backg;
ofCursor curs;
ofSlit slit;
ofErrorBall errorBall;
ofBlueScreen blueScreen;
ofInternet internet;
ofGlitchCreator glitch;

//--------------------------------------------------------------
void testApp::setup(){
    
//    int windowMode = ofGetWindowMode();  
//    if(windowMode == OF_FULLSCREEN){  
//        this->windowWidth = ofGetScreenWidth();  
//        this->windowHeight = ofGetScreenHeight();
//    }
    ofSetFullscreen(true);
    
    desk.resX=backg.resX=curs.resX=slit.resX=errorBall.resX=blueScreen.resX=internet.resX=menu.resX=glitch.resX = ofGetScreenWidth();
    desk.resY=backg.resY=curs.resY=slit.resY=errorBall.resY=blueScreen.resY=internet.resY=menu.resY=glitch.resY = ofGetScreenHeight();

    
    menu.setup("Menu Bar"); // most of the time you don't need a name
    menu.add(finder.setup("GlitchOS", true));
//    menu.add(file.setup("Time", false));
//    menu.add(lol.setup("Truth", false));
//    menu.add(chicken.setup("Hearts", false));
    glitch.setup();
    desk.setup();
    desk.add(webcam.setup("icons/webcam.png", "Webcam"));
    desk.add(windows.setup("icons/windows.png", "Windows"));
    desk.add(safari.setup("icons/chrome.png", "Internet"));
//    desk.add(quickTime.setup("icons/video.png", "Video Player"));
    backg.setup("screen/background.jpg");
    curs.setup("screen/cursor.png");
    slit.setup(6, 20);
    errorBall.setup();
    blueScreen.setup();
    internet.setup();
        
    ofNoFill();
    ofEnableAlphaBlending();
    ofSetEscapeQuitsApp(false);
//    ofHideCursor();
    CGDisplayHideCursor(NULL);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    slitIR = false;
    blueScreenIR = false;
    internetIR = false;
    quickVideoIR = false;

}


//--------------------------------------------------------------
void testApp::update(){

    webcam.update();
    windows.update();
    safari.update();
//    quickTime.update();
    
    if(webcam.isRunning()){
        slitIR = true;  
    }else if(slit.isFalse()){
        slitIR = false;
    }
    
    if(safari.isRunning()){
        internetIR = true;
    } else if(internet.isFalse()){
        internetIR = false;
    }
    
//    if(quickTime.isRunning()){
//        quickVideo.playMovie();
//        quickVideoIR = true;
//    } else if(quickVideo.isFalsed()){
//        quickVideo.stopMovie();
//        quickVideoIR = false;
//    }
    
    if(windows.isRunning()){
        blueScreenIR = true;
    }else if(blueScreen.isFalse()){
        blueScreenIR = false;
    }
    
    if(internetIR)
        internet.update();
    
    if(slitIR)
        slit.update();
    
    curs.update();
    
    errorBall.update();
    
    glitch.update();
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    backg.draw();
    desk.draw();
    menu.draw();
    
    if(slitIR)
    slit.draw();
    
    
    if(internetIR)
    internet.draw();
    
    errorBall.draw();
    curs.draw();
    
    glitch.draw();

    if(blueScreenIR)
        blueScreen.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}