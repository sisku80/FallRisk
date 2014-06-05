#pragma once

#include "ofMain.h"

#include "ofxKinectCommonBridge.h"
#include "ofxBox2d.h"
//#include "Vehicle.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxKinectCommonBridge kinect;
		ofxBox2d                            box2d;			  //	the box2d world
		vector    <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
		vector	  <ofPtr<ofxBox2dRect> >	boxes;			  //	defalut box2d rects
		ofxBox2dRect track;
		//Vehicle coche;

		
};
