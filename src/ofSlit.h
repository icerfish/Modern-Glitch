#pragma once

#include "ofBaseGui.h"
#include "ofxSlitScan.h"

#define WIDTH 640
#define HEIGHT 480

class ofSlit : public ofBaseGui{
    
public:    
    void setup(int _map, int _capacity) {
        
        ofSetLogLevel(OF_LOG_VERBOSE);
		
        capacity = _capacity;
        
        currentMilli = 0;
        
        sampleMapStrings.push_back("maps/left_to_right.png");
        sampleMapStrings.push_back("maps/right_to_left.png");
        sampleMapStrings.push_back("maps/up_to_down.png");
        sampleMapStrings.push_back("maps/down_to_up.png");
        sampleMapStrings.push_back("maps/hard_noise.png");
        sampleMapStrings.push_back("maps/soft_noise.png");
        sampleMapStrings.push_back("maps/random_grid.png");
        sampleMapStrings.push_back("maps/video_delay.png");
        
        for(int i = 0; i < sampleMapStrings.size(); i++){
            ofImage* map = new ofImage();
            map->allocate(WIDTH, HEIGHT, OF_IMAGE_GRAYSCALE);
//            map->loadImage(sampleMapStrings[i]);
            sampleMaps.push_back( map );
        }
		
        warpImage.allocate(WIDTH, HEIGHT, OF_IMAGE_COLOR);
        colorImg.allocate(WIDTH, HEIGHT, OF_IMAGE_COLOR);
        
        currentSampleMapIndex = _map;
        
		
        changeCapacity();
        initLiveVideo();
        
        warp.setBlending(false);
        warp.setDelayMap(*(sampleMaps[currentSampleMapIndex]));
        
        left.loadImage("screen/appBar/leftTop.png");
        mid.loadImage("screen/appBar/midTop.png");
        right.loadImage("screen/appBar/rightTop.png");
        red.loadImage("screen/appBar/red.png");
        redOver.loadImage("screen/appBar/redOver.png");
        redPressed.loadImage("screen/appBar/redPressed.png");
        
        exitButton.width = red.width;
        exitButton.height = red.height;
        exitButton.x = 9;
        exitButton.y = 6;
        
        b.y = ofRandom(defaultHeight, resY - (HEIGHT + defaultHeight + 1));
        b.x = ofRandom(0, resX - WIDTH);
        b.width = WIDTH;
        b.height = defaultHeight+1;
        
        appMenuBar.width = WIDTH;
        appMenuBar.height = defaultHeight + 1;
        appMenuBar.x = 0;
        appMenuBar.y = 0;
        
        ofRegisterMouseEvents(this);

	}
    
    void initLiveVideo(){
        if(!useLiveVideo){
            useLiveVideo = true;		
            vidPlayer.close();
        }
        
        vidGrabber.initGrabber(WIDTH,HEIGHT);	
        
        vidGrabber.listDevices();
        vidGrabber.setDeviceID(10);
    }
        
	
	virtual void mouseMoved(ofMouseEventArgs & args){	
        isItOver(args.x, args.y, false);
	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
        setValue(args.x, args.y, true);
	}
	
	virtual void mouseDragged(ofMouseEventArgs & args){
        setValue(args.x, args.y, false);	
	}
	
	virtual void mouseReleased(ofMouseEventArgs & args){
        isItOver(args.x, args.y, true);
		bGuiActive = false;		
	}
	
    void update(){
        bool bNewFrame = false;	
        if(useLiveVideo){
            vidGrabber.grabFrame();
            bNewFrame = vidGrabber.isFrameNew();
        }
        
        if (bNewFrame && !isPaused){
            if(useLiveVideo){
                colorImg.setFromPixels(vidGrabber.getPixels(), WIDTH,HEIGHT, OF_IMAGE_COLOR);
            }
            //each frame, call addImage to ofxSlitScan.
            warp.addImage(colorImg);
        }
        
        if (5000 < (ofGetElapsedTimeMillis() - currentMilli)) {
            warpImage.setFromPixels(warp.getOutputImage()->getPixels(), WIDTH, HEIGHT, OF_IMAGE_COLOR);
            warp.setDelayMap(warpImage);
            currentMilli = ofGetElapsedTimeMillis();
        }
    }

    
	void draw(){
        
        //Draw view ports
        ofPushStyle(); 
        ofPushMatrix();
        
        currentFrame = ofGetFrameNum();
        
        ofTranslate(b.x, b.y);
        
        
        left.draw(0,0,left.width,left.height);
        mid.draw(left.width, 0, WIDTH-left.width*2, mid.height);
        right.draw(WIDTH - right.width, 0, right.width, right.height);
        if(isOver){
            redOver.draw(exitButton.x, exitButton.y, exitButton.width, exitButton.height);
        } else {
            red.draw(exitButton.x, exitButton.y, exitButton.width,exitButton.height);
        }
        ofPushMatrix();
        ofTranslate(0, defaultHeight +1);
        warp.getOutputImage()->draw(0, 0, WIDTH, HEIGHT);
        ofPopMatrix();
            
        ofPopMatrix();
        ofPopStyle();	
	}
    
    void changeCapacity(){
        if(warp.isSetup()){
            warp.setCapacity(capacity);
        }
        else{
            warp.setup(WIDTH, HEIGHT, capacity, OF_IMAGE_COLOR);
            warp.setDelayMap(*sampleMaps[currentSampleMapIndex]);
            
        }
        warp.setTimeDelayAndWidth(int( 0 * warp.getCapacity() + .5), 
                                  int( (1 - 0) * warp.getCapacity() + .5) );
    }
    
    bool isFalse(){
        return isQuit;
    }

    
    
protected:
	
	void setValue(float mx, float my, bool bCheck){
        
		if( ofGetFrameNum() - currentFrame > 1 ){
            bGrabbed = false;
			bGuiActive = false;
			return; 
		}
        
        if( bCheck ){
            ofRectangle checkRect = appMenuBar;
            checkRect.x += b.x;
			checkRect.y += b.y;
            
			if( checkRect.inside(mx, my) ){
				bGuiActive = true;
                bGrabbed = true;
                grabPt.set(mx-b.x, my-b.y);
            } else {
                bGuiActive = false;
                bGrabbed = false;
            }
		} else if( bGrabbed ){
			b.x = mx - grabPt.x;
			b.y = my - grabPt.y;
		}
    }
    
    void isItOver(float mx, float my, bool isReleased) {
        ofRectangle checkRect = exitButton;
        checkRect.x += b.x;
        checkRect.y += b.y;
        if(checkRect.inside(mx, my)) {
            isOver = true;
            if(isReleased) {
                isQuit = true;
            }
        } else {
            isOver = false;
            isQuit = false;
        }
    }
    
	ofVideoGrabber	vidGrabber;
	ofVideoPlayer	vidPlayer;
	
	ofImage	colorImg;
	ofImage	warpImage;
    ofImage blackImg;
    
    ofImage left;
    ofImage mid;
    ofImage right;
    
    ofImage red;
    ofImage redOver;
    ofImage redPressed;
    
    ofRectangle exitButton;
    ofRectangle appMenuBar;
    
    ofPoint grabPt;
    bool bGrabbed;
    bool isOver;
    bool isQuit;

    ofxSlitScan warp;
    
	int capacity;
    int map;
	
	//sample map selector
	vector<string> sampleMapStrings;
	vector<ofImage*> sampleMaps;
    
	int currentSampleMapIndex;
	
	//input selection
	bool useLiveVideo;
	bool isPaused;
    int currentMilli;
};