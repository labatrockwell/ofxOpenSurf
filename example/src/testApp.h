#pragma once

// based on simple example from here: http://code.google.com/p/ofxopensurf

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "surflib.h"
#include "ofxOpenSurf.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofVideoGrabber cam;

        bool bCapturing;

        //ofxCvColorImage marker;
        //ofxCvColorImage camImg;
        //ofxCvColorImage mtcImg;
        ofxCvColorImage vtcImg;
        IpVec ipts; //static img
        IpVec vpts; //video only
        IpVec vspts;//video src
        IpVec vtpts;//video trg
        IpVec spts; //static src
        IpVec tpts; //static trg
        IpPairVec matches;
        IpPairVec vmatches;

        ofPoint src_corners[4];
        ofPoint dst_corners[4];

        string opts[6];
        int opt;
        int oldOpt;

        ofxSurfImage sImg;
        ofxSurfImage dImg;
        ofxSurfImage camImg;

        ofxSurfMotion mov;
        //ofxSurfStaticMatch staticMatch;
		
};
