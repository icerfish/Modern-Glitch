#pragma once
#include "ofMain.h"

class ofPopUpAd: public ofPoint{
protected:
    
	ofPoint oldPos;
    float width, height;
	bool bActive;
    bool isOverRed;
	void init(float _x, float _y, float _width, float _height);
    int r, g, b;
    ofTrueTypeFont font;
    string adContent;
    
public:
	ofPopUpAd();
	ofPopUpAd(float x, float y, float _width = 640, float _height = 480);
	ofPopUpAd(ofPoint _iniPos, float _width = 640, float _height = 480);
	
	virtual ~ofPopUpAd(){}
    
    bool isOver(float ax, float ay);
    void setAtt(int _r = ofRandom(255), int _g = ofRandom(255), int _b = ofRandom(255));
    
    void getContent(string& _adContent);
	
	
	virtual void updateAdvert(float timeStep = 1.0f);
	virtual void render(){debugRender();}
	void debugRender();
    
	void setActive(bool _bActive);
	bool isActive();
    
    void moveTo(ofPoint& _target);
	void moveTo(float _x, float _y);
    
    //--------CUSTOM---------
    void graphics(ofImage* _left, ofImage* _right, ofImage* _mid, ofImage* _red, ofImage* _redOver);
};





