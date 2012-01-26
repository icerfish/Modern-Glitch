#pragma once

#define MAX_ADVERTS 200

#include "ofBaseGui.h"
//#include "ofPopUpAd.h"

class ofInternet : public ofBaseGui{
	
public:    
	void setup() {
        
        courier.loadFont("fonts/Courier.ttf", 22);
        lucidaGrande.loadFont("fonts/Lucida Grande.ttf", 11);
        impact.loadFont("fonts/impact.ttf", 22);
        ofRegisterMouseEvents(this);
        
        appWidth = 800;
        appHeight = 600;
        loadWidth = 0;
        
        iterations = 0;
        
        b.x = ofRandom(0, resX - appWidth);
        b.y = ofRandom(defaultHeight, resY - appHeight);
        b.width = appWidth;
        b.height = appHeight;
        
        left.loadImage("safari/topLeft.png");
        mid.loadImage("safari/topMid.png");
        right.loadImage("safari/topRight.png");
        red.loadImage("screen/appBar/red.png");
        redOver.loadImage("screen/appBar/redOver.png");
        button.loadImage("safari/button.png");
        urlBar.loadImage("safari/urlBar.png");
        urlBarLoad.loadImage("safari/urlBarLoad.png");
        openSource.loadImage("openSource.png");
        
        _left = new ofImage();
        _left->loadImage("screen/appBar/leftTop.png");
        _mid = new ofImage();
        _mid->loadImage("screen/appBar/midTop.png");
        _right = new ofImage();
        _right->loadImage("screen/appBar/rightTop.png");
        _red = new ofImage();
        _red->loadImage("screen/appBar/red.png");
        _redOver = new ofImage();
        _redOver -> loadImage("screen/appBar/redOver.png");
        
        
        exitButton.width = red.width;
        exitButton.height = red.height;
        exitButton.x = 9;
        exitButton.y = 6;
        
        
//        bCreateAdverts = false;
//        newAdvert = NULL;
        
        stringSetup();
        
        is404 = false;
        
        
        
	}
    
    void update(){
        
//        if(adverts.size() > 20){
//            delete adverts[0];
//            adverts.erase (adverts.begin());
//        }
//        
//        if(newAdvert){
//            newAdvert->moveTo(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
//        }
//        if(bCreateAdverts){
//            int del = ofRandom(10, 100);
//            if(ofGetFrameNum() % del == 0){
//                ofPopUpAd* p = new ofPopUpAd(ofRandom(ofGetScreenWidth() - WIDTH), ofRandom(defaultHeight+1, ofGetScreenHeight() - HEIGHT), WIDTH, HEIGHT);
//                //                float randomStep = 5;
//                p->getContent(adContent[ofRandom(adContent.size())]);
//                adverts.push_back(p);
//                iterations++;
//            }
//        }
        
//        if(iterations > 40){
//            bCreateAdverts = false;
//        }
	}
    
	
	virtual void mouseMoved(ofMouseEventArgs & args){
        ofMouseEventArgs a = args;
		a.x -= b.x;
		a.y -= b.y;
        isItOver(args.x, args.y, false);
//        for(int i = 0; i < adverts.size(); i++){
//            adverts[i]->isOver(args.x, args.y);
//        }
	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
		setValue(args.x, args.y, true);
        isItOver(args.x, args.y, true);
//        for(int i = 0; i < adverts.size(); i++){
//            if(adverts[i]->isOver(args.x, args.y))
//                adverts.erase(adverts.begin() + i);
//        }
	}
	
	virtual void mouseDragged(ofMouseEventArgs & args){
        setValue(args.x, args.y, false);	
	}
	
	virtual void mouseReleased(ofMouseEventArgs & args){
		bGuiActive = false;
	}	
	
	void draw(){
        
        
        ofPushStyle();
		ofPushMatrix();
        
		currentFrame = ofGetFrameNum();
        
        ofPushMatrix();
        ofTranslate(b.x, b.y);
        
        left.draw(0,0,left.width,left.height);
        mid.draw(left.width, 0, appWidth-left.width*2, mid.height);
        right.draw(appWidth - right.width, 0, right.width, right.height);
        if(isOver){
            redOver.draw(exitButton.x, exitButton.y, exitButton.width, exitButton.height);
        } else {
            red.draw(exitButton.x, exitButton.y, exitButton.width,exitButton.height);
        }
        
        ofPushMatrix();
        ofTranslate(9,25);
        button.draw(0,0, button.width, button.height);
        ofTranslate(57,0);
        urlBar.draw(0,0, urlBar.width, urlBar.height);
        ofTranslate(28,0);
        if(loadWidth < urlBar.width - 60){
            is404 = false;
            loadWidth += ofRandom(0,2);
//            if(loadWidth > 300 && loadWidth < 400)
//                bCreateAdverts = true;
//        } else {
//            is404 = true;
        }
        
        urlBarLoad.draw(0,0, loadWidth, urlBarLoad.height);
        ofPopMatrix();
        ofPushMatrix();
        ofTranslate(1, 73);
        ofFill();
        ofSetColor(255);
        ofRect(0,0, appWidth-1, openSource.getHeight());
        ofNoFill();
        ofSetColor(0);
        ofRect(0,0, appWidth-1, openSource.getHeight());
        ofSetColor(255);
        openSource.draw(0,0, openSource.getWidth()-2, openSource.getHeight()-1);
        ofSetColor(0);
        if(is404)
        courier.drawString("404 Error \n Page can not be found.", 20, 30);
        ofPopMatrix();
        ofPopMatrix();
        
//        for(int i=0; i<adverts.size(); i++){
//            adverts[i]->render();
//            adverts[i]->graphics(_left, _right, _mid, _red, _redOver);
//        }
        ofPopMatrix();
		ofPopStyle();
		
	}
    
    bool isFalse(){
//        if(isQuit)
//            adverts.clear();
        return isQuit;
    }
    
protected:
	
	void setValue(float mx, float my, bool bCheck){
        
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGuiActive = false;
			return; 
		}
        
        if( bCheck ){
            ofRectangle checkRect = ofRectangle(0,0, appWidth, left.height);
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
    
    void stringSetup(){
        adContent.push_back("15% Off on Fashionable Peanut \n Watch 3-color LED Wrist Watch! \n Coupon Code: H-Z-PDM-58821 \n http://tinyurl.com/3h58s99");
        adContent.push_back("Toshiba DVR670 DVD Recorder/VCR Combo \n $219.99 \n Offered By: http://TigerDirect.com \n Category: Tigerdirect Top 10... \n http://tinyurl.com/3tobwby");
        adContent.push_back("ContourHD 1080P Hands Free Camcorder \n $119.99 \n Offered By: CompUSA Category: \n CompUSA Top 10 Camcorders... \n http://tinyurl.com/3hsfj76");
        adContent.push_back("$10 Off on Video Games $50+! \n Coupon Code: LS8850B \n Dollar off Offered By: SooBest Start... \n http://tinyurl.com/3hw2nyy");
        adContent.push_back("10% Off \n Worldwide Free Shipping on All Orders! \n Coupon Code: BBGK2011 \n Free Shipping...  \n http://tinyurl.com/3es4m6z");
        adContent.push_back("Save 31% on The Dyson DC33 Multi floor \n http://ElectronicsExpo.com! \n Reg. $399.99 Sale $278.00! \n http://tinyurl.com/3cfu4no");
        adContent.push_back("Free Shipping on Dark Souls at \n http://GameStop.com! \n Free Shipping Offered By:\n GameStop Start Date:2011-10-20...  \n http://tinyurl.com/3f5hvua");
        adContent.push_back("Up To 93% Off iPhone 4 Cases \n and Extra 20% Off! \n Coupon Code: -20iphonecs \n Percentage off... \n http://tinyurl.com/3fqwx6d");
        adContent.push_back("Intel Core i5-2500K 3.30GHz \n Quad-Core Unlocked CPU \n $219.99 \n Offered By: http://TigerDirect.com \n http://tinyurl.com/4xx6r9y");
        adContent.push_back("46% Off Birkenstock \n Boston Soft Footbed Clog! \n Percentage off Offered By: \n http://SmartBargains.com \n http://tinyurl.com/3zrdaow");
        adContent.push_back("iPhone4/ipad/ipod Controller i-helicopter \n $39.09 Shipped! \n Dollar off Offered By: PickEgg Start... \n http://tinyurl.com/3rtzz2u");
        adContent.push_back("Caribbean Cruises \n Sail From $40 Per Nt \n Plus Free Upgrades on Orbitz! \n Dollar off Offered By: Orbitz... \n http://tinyurl.com/42z8fnp");
        adContent.push_back("Rabbit Ears Silicon Case \n Holder for iPhone 4! \n Only $4.68! \n Get One Set at http://eforchina.com Now! \n Dollar off... http://tinyurl.com/3lkt2d7");
        adContent.push_back("Check Out The Sims 3: \n Fast Lane Stuff from HP Download Store. \n Now Only $19.99! - - Dollar off \n Offered By: HP... \n \n http://tinyurl.com/42jgvcb");
        adContent.push_back("Cisco WRVS4400N Wireless N VPN Router \n $79.99 \n Offered By: CompUSA \n Category: CompUSA Top 10 Wireless... \n http://tinyurl.com/3w67sob");
        adContent.push_back("ContourHD 1080P Hands Free Camcorder \n $109.99* \n Offered By: http://TigerDirect.com \n Category: Tigerdirect Top 10... \n http://tinyurl.com/3gg59o6");
        adContent.push_back("Nikon D3100 14MP Digital SLR Camera \n $599.99 \n Offered By: CompUSA \n Category: CompUSA \n Top 10 Cameras Deals \n http://tinyurl.com/3oujpj7");
        adContent.push_back("Acer S230HL 23 Class Widescreen \n LED Monitor \n $149.99 \n Offered By: http://TigerDirect.com \n http://tinyurl.com/3oc3wto");
        adContent.push_back("Interstate Music Free Shipping \n on orders Over $99! \n Free Shipping \n Offered By: Cascio Interstate Music... \n http://tinyurl.com/3reocjc");
        adContent.push_back("Free Sheet Music Downloads! \n Free Trial / Usage \n Offered By: http://Musicnotes.com \n Start Date:2010-03-02 End... \n http://tinyurl.com/3vfym52");
        adContent.push_back("Bangkok Thailand Deals! \n Dollar off Offered By: BookingBuddy \n Start Date:2010-09-27 \n End Date:ongoing... \n http://tinyurl.com/3dltgk9");
        adContent.push_back("Save 26% on \n The Dyson AM04 Hot fan heater \n at http://ElectronicsExpo.com! \n Reg. $449.00  \n Sale $333.00! \n http://tinyurl.com/3chhkmk");
        adContent.push_back("Save Up To 65% Off \n on Hotel Holiday Deals \n http://TripMama.com! \n Percentage off \n Offered By: TripMama \n http://tinyurl.com/3l277qt");
        adContent.push_back("$200 OFF any Purchase over $2000 \n only at Diamonds International! \n Coupon Code: WEB200 \n http://tinyurl.com/447qfcr");
        adContent.push_back("Shop Big Girls (3-8 yrs) \n Umi Shoes! \n General Promotion \n Offered By: UMI Children's Shoes Start... \n http://tinyurl.com/3oj4mwn");
        adContent.push_back("HP ProBook 4530s 15.6 \n Notebook PC Bundle \n $444.99* \n Offered By: http://TigerDirect.com \n http://tinyurl.com/3khnhvg");
        adContent.push_back("Samsung UN55D6400 55 \n Ultra Thin LED 3D HDTV \n $1649.99 \n Offered By: CompUSA \n Category: CompUSA Top 10...  \n http://tinyurl.com/3usmq99");
        adContent.push_back("Mario Bros Luigi Child Halloween Costume \n Offered By: http://Wal-Mart.com \n Category: Apparel - 97-cent \n http://tinyurl.com/3rz9y4y");
        adContent.push_back("GEAR HEAD 1.4IN CSTN \n $13.99 \n Offered By: CompUSA \n Category: CompUSA Top 10 \n Digital Picture Frames Deals \n http://tinyurl.com/3aqvzh6");
    }
    
    
    bool bGrabbed;
    ofImage left, right, mid, red, redOver;
    ofImage openSource;
    
    ofImage* _left;
    ofImage* _right;
    ofImage* _mid;
    ofImage* _red;
    ofImage* _redOver;
    
    vector<string> adContent;
    
    ofImage button, urlBar, urlBarLoad;
    string num;
    ofRectangle exitButton;
    ofRectangle appMenu;
    
    int appWidth, appHeight;
    int loadWidth;
    
    int iterations;
    
    ofPoint grabPt;
    bool isOver;
    bool isQuit;
    
//    bool bCreateAdverts;
    
//	ofPopUpAd* newAdvert;
//	vector<ofPopUpAd*>adverts;
    
    ofTrueTypeFont courier;
    ofTrueTypeFont impact;
    
    bool is404;
};