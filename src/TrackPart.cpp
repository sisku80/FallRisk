#include "TrackPart.h"

TrackPart::TrackPart()
{
	instability = 0;
	iter = 0;
	column.loadImage("column.gif");
}

TrackPart::~TrackPart()
{
	
}

void TrackPart::update()
{
	if(ofGetElapsedTimef() == 5.0f){
		this->setPosition( this->getPosition().x , this->getPosition().y + instability);
		iter = 0;
	}
}

void TrackPart::draw()
{
	if(body == NULL) {
		return;	
	}
    
    ofPushMatrix();
    ofTranslate(ofxBox2dBaseShape::getPosition());
    ofRotate(getRotation());
	ofSetColor(100,80,40);
	column.draw(-40,0);
	mesh.draw(ofGetFill()==OF_FILLED?OF_MESH_FILL:OF_MESH_WIREFRAME);

	
    ofPopMatrix();
	
}

void TrackPart::setInstability(int instab){
	this->instability = instab;
}
