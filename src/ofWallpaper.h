#pragma once

#include "ofBaseGui.h"

class ofWallpaper : public ofBaseGui{
    
public:    
    void setup(string image) {
        background.loadImage(image);
        b.x = 0;
        b.y = 0;
        b.width = resX;
        b.height = resY;
        currentFrame = 0;
		bGuiActive = false;
	}
	
	virtual void mouseMoved(ofMouseEventArgs & args){

	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
        
	}
	
	virtual void mouseDragged(ofMouseEventArgs & args){

	}
	
	virtual void mouseReleased(ofMouseEventArgs & args){
		bGuiActive = false;		
	}	
	
	void draw(){
		currentFrame = ofGetFrameNum();

		ofPushStyle();
		ofPushMatrix();
        interlace();
        background.draw(b.x, b.y, b.width, b.height);
        ofPopMatrix();
		ofPopStyle();
		
	}
    
    void interlace() {
        
        int h = background.height;
        int w = background.width;
        unsigned char * pix = background.getPixels();
        int temp[3];
        
        
        for(int y = 0; y < h*3; y+=3){
            for(int x = 0; x < w*3; x+= 3) {
                for(int i = 0; i < 3; i++) {
                    if(((y*w+x) > 2) && ((y*w+x) < w*h*3 - 3)) {
                                             pix[y*w+x+i-3] = pix[y*w+x+i*2];    
                    }
                }   
            }
        }
        
        background.setFromPixels(pix, w, h, OF_IMAGE_COLOR);

    }
    
protected:
	
	void setValue(float mx, float my, bool bCheck){
        
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGuiActive = false;
			return; 
		}
    }
    
    string name;
    ofImage background;
    ofImage background2;
    ofImage final;

};