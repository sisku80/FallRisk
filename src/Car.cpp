#include "Car.h"

Car::Car()
{
	
}

Car::~Car()
{
	
}

bool Car::setup()
{
	return true;
}

void Car::update()
{
	
}

void Car::draw()
{
	
	
}

void Car::keyPressed(int key)
{
	
}

void Car::keyReleased(int key)
{
	
}

//Car entity methods
void Car::setPosition(ofPoint pos){
	this->position.x = pos.x;
	this->position.y = pos.y;
}
ofPoint Car::getPosition(){
	return ofPoint(this->position.x, this->position.y);
}

void Car::setDirection(ofPoint direction){
	this->direction.x = direction.x;
	this->direction.y = direction.y;
}
ofPoint Car::getDirection(){
	return ofPoint(this->direction.x, this->direction.y);
}

void Car::setRotation(float angle){
	this->rotation = angle;
}
void Car::addRotation(float angle){
	this->rotation += angle;
}
float Car::getRotation(){
	return this->rotation;
}

void Car::setSize(float size){
	this->size = size;
}
float Car::getSize(){
	return this->size;
}

void Car::setSpeed(float speed){
	this->speed = speed;
}
float Car::getSpeed(){
	return this->speed;
}

void Car::setColor(ofColor c){
	this->color = c;
}
ofColor Car::getColor(){
	return this->color;
}

