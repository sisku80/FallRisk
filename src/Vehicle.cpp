#include "Vehicle.h"

Vehicle::Vehicle()
{
	
}

Vehicle::~Vehicle()
{
	
}

bool Vehicle::setup()
{
	return true;
}

void Vehicle::update()
{
	//this->setPosition
}

void Vehicle::draw()
{
	
	
}

void Vehicle::keyPressed(int key)
{
	
}

void Vehicle::keyReleased(int key)
{
	
}

//Car entity methods
void Vehicle::setPosition(ofPoint pos){
	this->position.x = pos.x;
	this->position.y = pos.y;
}
ofPoint Vehicle::getPosition(){
	return ofPoint(this->position.x, this->position.y);
}

void Vehicle::setDirection(ofPoint direction){
	this->direction.x = direction.x;
	this->direction.y = direction.y;
}
ofPoint Vehicle::getDirection(){
	return ofPoint(this->direction.x, this->direction.y);
}

void Vehicle::setRotation(float angle){
	this->rotation = angle;
}
void Vehicle::addRotation(float angle){
	this->rotation += angle;
}
float Vehicle::getRotation(){
	return this->rotation;
}

void Vehicle::setSize(float size){
	this->size = size;
}
float Vehicle::getSize(){
	return this->size;
}

void Vehicle::setSpeed(float speed){
	this->speed = speed;
}
float Vehicle::getSpeed(){
	return this->speed;
}

void Vehicle::setColor(ofColor c){
	this->color = c;
}
ofColor Vehicle::getColor(){
	return this->color;
}

