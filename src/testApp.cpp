#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetFrameRate(60);

	// Kinect initialization code
	kinect.initSensor();

	// We first set up data streams for the Kinect (color, depth and skeleton tracking)
	kinect.initColorStream(640, 480, true);
	kinect.initDepthStream(640, 480, true);
	kinect.initSkeletonStream(false);

	// Launch Kinect
	kinect.start();

	box2d.init();
	box2d.setGravity(1.5f, 10);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();


	track.setup(box2d.getWorld(),ofGetWidth()/2,2*ofGetHeight()/3,ofGetWidth(),20);
	/*zancoL.setPhysics(3.0, 0.53, 0.1);
	zancoL.setup(box2d.getWorld(), 0, 0, 30, 30);
	zancoR.setPhysics(3.0, 0.53, 0.1);
	zancoR.setup(box2d.getWorld(), 0, 0, 30, 30);*/
	/*feet.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
	feet.back().get()->setPhysics(3.0, 0.53, 0.1);
	feet.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);*/

}

//--------------------------------------------------------------
void testApp::update(){

	kinect.update();	

	box2d.update();	

}

//--------------------------------------------------------------
void testApp::draw(){

	ofDisableAlphaBlending();
		ofSetColor(255);
		kinect.draw(0, 0);
	ofEnableAlphaBlending();

	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		circles[i].get()->draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xBF2545);
		boxes[i].get()->draw();
	}
	ofFill();
	ofSetColor(40,180,70);
	track.draw();

	// draw the ground
	box2d.drawGround();
	
	string info = "";
	info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetColor(255);
	ofDrawBitmapString(info, 30, 30);
	
	if(kinect.getSkeletons().size() > 0)
	{
		if(kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(0).end())
		{
			SkeletonBone headJoint = kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HEAD)->second;
			if(kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HAND_LEFT) != kinect.getSkeletons().at(0).end())
			{
				SkeletonBone handLJoint = kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HAND_LEFT)->second;
				if(kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HAND_RIGHT) != kinect.getSkeletons().at(0).end())
				{
					SkeletonBone handRJoint = kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HAND_RIGHT)->second;
					if(kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_FOOT_LEFT) != kinect.getSkeletons().at(0).end())
					{
						SkeletonBone footLJoint = kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_FOOT_LEFT)->second;
						if(kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_FOOT_RIGHT) != kinect.getSkeletons().at(0).end())
						{
							SkeletonBone footRJoint = kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_FOOT_RIGHT)->second;
			
							if(handLJoint.getScreenPosition().y < headJoint.getScreenPosition().y && handRJoint.getScreenPosition().y < headJoint.getScreenPosition().y){
								float posX = ((handLJoint.getScreenPosition().x + handRJoint.getScreenPosition().x)/2);
								float posY = ((handLJoint.getScreenPosition().y+ handRJoint.getScreenPosition().y)/2);
								float r = ofRandom(4, 20);
								circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
								circles.back().get()->setPhysics(3.0, 0.53, 0.1);
								circles.back().get()->setup(box2d.getWorld(), posX, posY, r);
							}
							
							//zancoL.setPosition(footLJoint.getScreenPosition().x,footLJoint.getScreenPosition().y);
							//zancoR.setPosition(footRJoint.getScreenPosition().x,footRJoint.getScreenPosition().y);
								
						}
					}
				}
			}
		}
	}


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if(key == 'c') {
		float r = ofRandom(4, 20);
		circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
		circles.back().get()->setPhysics(3.0, 0.53, 0.1);
		circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
		
	}
	
	if(key == 'b') {
		float w = ofRandom(4, 20);
		float h = ofRandom(4, 20);
		boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
		boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
	}
	
	if(key == 't') ofToggleFullscreen();

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
