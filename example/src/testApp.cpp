#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,0);
    ofSetVerticalSync(true);
    
    camImg.allocate(320,240);
    bCapturing = false;
    
    sImg.loadImage("images/pepe.jpeg");
    sImg.calcSurf(OFX_SURF_VIDEOMATCH);
    
    dImg.loadImage("images/keyboard-cats-moon.jpg");
    dImg.calcSurf(OFX_SURF_VIDEOMATCH);
    
    mov.setup(&camImg);
    
    //makeMarkerFromImg("Images/img1.jpg",ipts);
    
    /*ofImage img;
     img.loadImage("Images/img2.jpg");
     mtcImg.allocate(img.width,img.height);
     unsigned char * pix = img.getPixels();
     mtcImg.setFromPixels(pix,img.width,img.height);
     surfDetDes(mtcImg.getCvImage(),tpts,false,4,4,2,0.0006f);
     surfDetDes(marker.getCvImage(),spts,false,4,4,2,0.0006f);
     getMatches(spts,tpts,matches);*/
    
    /*ofImage img2;
     img2.loadImage("Images/marker.png");
     vtcImg.allocate(img2.width,img2.height);
     pix = img2.getPixels();
     vtcImg.setFromPixels(pix,img2.width,img2.height);
     surfDetDes(vtcImg.getCvImage(),vtpts,false,4,4,2,0.0001f);*/
    
    src_corners[0].set(0,0);
    src_corners[1].set(vtcImg.width,0);
    src_corners[2].set(vtcImg.width,vtcImg.height);
    src_corners[3].set(0,vtcImg.height);
    
    opt = 2;
    opts[0]="Image";
    opts[1]="Video";
    opts[2]="Match";
    opts[3]="MotionPts";
    opts[4]="StaticMatch";
    opts[5]="Kmeans";
}

//--------------------------------------------------------------
void testApp::update(){
    if(bCapturing){
        if(opt!=1 && opt!=2 && opt!=3){
            cam.close();
            bCapturing=false;
        }else{
            cam.update();
            if(cam.isFrameNew()){
                camImg.setFromPixels(cam.getPixels(),320,240);
                switch(opt){
                    case 1:
                        //video only
                        camImg.calcSurf(OFX_SURF_VIDEO);
                        break;
                    case 2:
                        //video match
                        //surfDetDes(camImg.getCvImage(),vspts,false,4,4,2,0.001f);
                        //getMatches(vspts,vtpts,vmatches);
                        ofxSurfVideoMatch(&camImg,&sImg,&vmatches);
                        break;
                    case 3:
                        //motion
                        mov.update();
                        break;
                }
            }
        }
    }else if(!bCapturing && (opt==1 || opt==2 || opt==3)){
        cam.initGrabber(320,240);
        bCapturing = true;
    }
    
    oldOpt=opt;
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0xffffff);
    glPushMatrix();
    glTranslatef(250,100,0);
    switch(opt){
        case 0:
            //single img
            //marker.draw(0,0,marker.width/2,marker.height/2);
            sImg.draw(0,0,sImg.width/2,sImg.height/2);
            ofxDrawIpoints(0,0,.5,sImg.ipts);
            break;
        case 1:
            //video only
            camImg.draw(0,0);
            ofxDrawIpoints(0,0,1,camImg.ipts);
            break;
        case 2:
            //video match
            camImg.draw(0,0);
            sImg.draw(camImg.width,0);
            ofxDrawIpoints(0,0,1,camImg.ipts);
            ofxDrawIpoints(camImg.width,0,1,sImg.ipts);
            ofSetColor(0xffff00);
            if(ofxSurfObjCorners(vmatches,src_corners,dst_corners)){
                
            }
            for(uint i=0;i<vmatches.size();i++){
                ofLine(vmatches[i].first.x,vmatches[i].first.y,vmatches[i].second.x+camImg.width,vmatches[i].second.y);
            }
            
            ofSetColor(0xff0000);
            ofDrawBitmapString(ofToString((int)(vmatches.size()))+" matches found",10,camImg.height+10);
            break;
        case 3:
            //motion
            camImg.draw(0,0);
            mov.draw();
            break;
        case 4:
            //static match
            if(oldOpt!=opt){
                ofxSurfStaticMatch(&sImg,&dImg,&matches);
            }
            
            sImg.draw(0,0,sImg.width/2,sImg.height/2);
            dImg.draw(sImg.width/2,0,dImg.width/2,dImg.height/2);
            glPushMatrix();
            glScalef(.5,.5,1);
            for(uint i=0;i<matches.size();i++){
                ofSetColor(0xff0000);
                ofNoFill();
                ofCircle(matches[i].first.x,matches[i].first.y,3);
                ofCircle(matches[i].second.x+sImg.width,matches[i].second.y,3);
                ofSetColor(0xffff00);
                ofLine(matches[i].first.x,matches[i].first.y,matches[i].second.x+sImg.width,matches[i].second.y);
            }
            glPopMatrix();
            ofSetColor(0xff0000);
            ofDrawBitmapString(ofToString((int)(matches.size()))+" matches found",10,sImg.height/2+10);
            break;
            
    }
    glPopMatrix();
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