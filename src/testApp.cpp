#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	kinect.initSensor();
	//kinect.initIRStream(640, 480);
	kinect.initColorStream(640, 480, true);
	kinect.initDepthStream(640, 480, true);
	kinect.initSkeletonStream(true);

	//simple start
	kinect.start();
	ofDisableAlphaBlending(); //Kinect alpha channel is default 0;
}

//--------------------------------------------------------------
void testApp::update(){
	kinect.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofSetColor(255);
	kinect.draw(0,0);
	//ofDisableAlphaBlending();
	//kinect.drawDepth(0, 0,ofGetWidth(),ofGetHeight());

	if(kinect.isNewSkeleton())
	{
		ofSetColor(255);
		for(int i = 0 ; i < kinect.getSkeletons().size(); i++)
		{
			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
			{
				SkeletonBone headBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD)->second;
				ofVec2f headScreenPosition(headBone.getScreenPosition().x, headBone.getScreenPosition().y);
				ofCircle(headScreenPosition.x, headScreenPosition.y, 10);
				

				//RIGHT SHOULDER
				ofSetColor(255,0,0); //shoulder color
				if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_RIGHT) != kinect.getSkeletons().at(i).end())
				{
					SkeletonBone bone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_RIGHT)->second;
					ofVec2f partScreenPosition(bone.getScreenPosition().x, bone.getScreenPosition().y);
					ofCircle(partScreenPosition.x, partScreenPosition.y, 10);
					
					//LEFT SHOULDER
					if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_LEFT) != kinect.getSkeletons().at(i).end())
					{
						SkeletonBone bone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_LEFT)->second;
						ofVec2f partScreenPosition(bone.getScreenPosition().x, bone.getScreenPosition().y);
						ofCircle(partScreenPosition.x, partScreenPosition.y, 10);

						//RIGHT HAND
						ofSetColor(0,255,0);
						if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_RIGHT) != kinect.getSkeletons().at(i).end())
						{
							SkeletonBone bone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_RIGHT)->second;
							ofVec2f partScreenPosition(bone.getScreenPosition().x, bone.getScreenPosition().y);
							ofCircle(partScreenPosition.x, partScreenPosition.y, 10);

							//LEFT HAND
							if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_LEFT) != kinect.getSkeletons().at(i).end())
							{
								SkeletonBone bone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_LEFT)->second;
								ofVec2f partScreenPosition(bone.getScreenPosition().x, bone.getScreenPosition().y);
								ofCircle(partScreenPosition.x, partScreenPosition.y, 10);

								//RIGHT ELBOW
								ofSetColor(0,0,255);
								if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_RIGHT) != kinect.getSkeletons().at(i).end())
								{
									SkeletonBone bone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_RIGHT)->second;
									ofVec2f partScreenPosition(bone.getScreenPosition().x, bone.getScreenPosition().y);
									ofCircle(partScreenPosition.x, partScreenPosition.y, 10);

									//LEFT ELBOW
									if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_LEFT) != kinect.getSkeletons().at(i).end())
									{
										SkeletonBone bone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_LEFT)->second;
										ofVec2f partScreenPosition(bone.getScreenPosition().x, bone.getScreenPosition().y);
										ofCircle(partScreenPosition.x, partScreenPosition.y, 10);


									}
								}
							}
						}
					}
				}
				return;
			}
		}
	}
	
	/*
	if(kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(0).end()){
		kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HEAD)->second;
		SkeletonBone headJoint = kinect.getSkeletons().at(0).find(NUI_SKELETON_POSITION_HEAD)->second;
		ofCircle(headJoint.getScreenPosition().x, headJoint.getScreenPosition().y, 10);
	}*/
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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