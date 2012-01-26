
#pragma once

#include "ofPopUpAd.h"


class ofWindowSetup{
protected:
	vector<ofPopUpAd*>adverts;
	ofPoint worldMin, worldMax;
	int numAdverts;
public:
	
	ofWindowSetup(ofPoint _worldMin = ofPoint(), 
				 ofPoint _worldMax = ofPoint(ofGetWidth(), ofGetHeight()));
	~ofWindowSetup();
	
	virtual void update(float timeStep = 1.0f);
	virtual void renderAdverts();
	virtual void render(){debugRender();}
	void debugRender();
	void addAdvert(ofPopUpAd *_p);
	void deleteAdvert(ofPopUpAd*_p);
	void removeAdvert(ofPopUpAd* p);
	void add(ofPopUpAd*p);
	bool hasAdvert(ofPopUpAd*p);
	bool has(ofPopUpAd* p);
	int getNumAdverts();
	vector<ofPopUpAd*>& getAdverts();
	void removeAllAdverts();
	void deleteAllAdverts();
	void removeAll();
	void deleteAll();
	void reserveForAdverts(int numberOfAdverts);
    
    void drawAdvertImage(ofImage *_cImg);
};

