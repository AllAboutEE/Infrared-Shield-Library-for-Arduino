#include "AllAboutEEIRControlButton.h"

AllAboutEE::IRControlButton::IRControlButton(AllAboutEE::IRControlButton::ButtonID id)
{
	setId(id);
}


void AllAboutEE::IRControlButton::setId(AllAboutEE::IRControlButton::ButtonID id)
{
	this->id = id;
}

AllAboutEE::IRControlButton::ButtonID AllAboutEE::IRControlButton::getId(){
	return this->id;
}

unsigned long AllAboutEE::IRControlButton::getHexCode(){
	return this->hexCode;
}

void AllAboutEE::IRControlButton::setHexCode(unsigned long hexCode){
	
	this->hexCode = hexCode;
}

void AllAboutEE::IRControlButton::setCodeLength(int length){
	this->codeLength = length;
}

int AllAboutEE::IRControlButton::getCodeLength(){
	return this->codeLength;
}

unsigned int* AllAboutEE::IRControlButton::getRawCode(){
	return rawCode;
}

void AllAboutEE::IRControlButton::setRawCode(unsigned int* rawCode,int length){

	setCodeLength(length);
	this->rawCode = rawCode;
}

void AllAboutEE::IRControlButton::setProtocol(uint8_t irProtocol){
	this->irProtocol = irProtocol;
}

uint8_t AllAboutEE::IRControlButton::getProtocol(){
	return this->irProtocol;
}
