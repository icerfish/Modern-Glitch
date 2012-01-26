
#include "ofPopUpAd.h"

ofPopUpAd::ofPopUpAd(){
	init(0,0,640,480);
}

ofPopUpAd::ofPopUpAd(float _x, float _y, float _width, float _height){
	init(_x, _y, _width, _height);
}

ofPopUpAd::ofPopUpAd(ofPoint iniPos, float _width, float _height){
	init(iniPos.x, iniPos.y, _width, _height);
}

void ofPopUpAd::init(float _x, float _y, float _width, float _height){
	x = _x;
	y = _y;
	oldPos.x = x;
	oldPos.y = y;
    width = _width;
    height = _height;
    setAtt();
	bActive = true;
    isOverRed = false;
    font.loadFont("fonts/impact.ttf", 25);
}

bool ofPopUpAd::isOver(float ax, float ay){
    ofRectangle checkRect = ofRectangle(9, 6, 12, 12);
    checkRect.x += x;
    checkRect.y += y;
    if(checkRect.inside(ax, ay)) {
        isOverRed = true;
        return true;
    } else {
        isOverRed = false;
        return false;
    }
}

void ofPopUpAd::setAtt(int _r, int _g, int _b){
    r = _r;
    g = _g;
    b = _b;
}

void ofPopUpAd::getContent(string& _adContent){
    adContent = _adContent;
}

void ofPopUpAd::updateAdvert(float timeStep){
	if(!bActive) return;
	float tempX = x, tempY = y;
	oldPos.x = tempX;
	oldPos.y = tempY;
}

void ofPopUpAd::debugRender(){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(x, y);
    ofRect(1, 22, width-2, height-22);
    ofSetColor(r, g, b);
    ofFill();
    ofRect(1, 23, width-2, height-23);
    ofSetColor(255);
    ofTranslate(0, 55 + 23);
    font.drawString(adContent, 20, 20);
    ofPopStyle();
    ofPopMatrix();
}


//--------CUSTOM-------
void ofPopUpAd::graphics(ofImage* _left, ofImage* _right, ofImage* _mid, ofImage* _red, ofImage* _redOver){
//    _cImg->draw(x-radius, y-radius, radius*2, radius*2);
    
    ofPushStyle(); 
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(x, y);
    

    _left->draw(0,0,_left->width, _left->height);
    _mid->draw(_left->width, 0, width-_left->width*2, _mid->height);
    _right->draw(width - _right->width, 0, _right->width, _right->height);
    if(isOverRed){
        _redOver->draw(9, 6, _redOver->width,_redOver->height);
    } else {
        _red->draw(9, 6, _red->width,_red->height); 
    }

    
//    ofPushMatrix();
//    ofTranslate(0, defaultHeight +1);
//    ofPopMatrix();
    
    ofPopMatrix();
    ofPopStyle();
}


void ofPopUpAd::setActive(bool _bActive){
	bActive = _bActive;
}

bool ofPopUpAd::isActive(){
	return bActive;	
}

void ofPopUpAd::moveTo(ofPoint& _target){
	moveTo(_target.x, _target.y);
}

void ofPopUpAd::moveTo(float _x, float _y){
	float diffX = _x - x;
	float diffY = _y - y;
	oldPos.x += diffX;
	oldPos.y += diffY;
	x = _x;
	y = _y;
}


