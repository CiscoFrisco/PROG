#include "Shift.h"

Shift::Shift(unsigned int linha, unsigned int condutor, unsigned int autocarro, unsigned int inicio, unsigned int fim){

	busLineId = linha;
	driverId = condutor;
	busOrderNumber = autocarro;
	startTime = inicio;
	endTime = fim;

}

/////////////
//get methods
/////////////
unsigned int Shift::getBusLineId() const{
  return busLineId;
}

unsigned int Shift::getDriverId() const{
  return driverId;
}
unsigned int Shift::getBusOrderNumber() const{
  return busOrderNumber;
}

unsigned int Shift::getStartTime() const{
  return startTime;
}

unsigned int Shift::getEndTime() const{
  return endTime;
}

//////////////
// set methods
//////////////

void Shift::setBusLineId(unsigned int busLineId){
  this->busLineId = busLineId;
}

void Shift::setDriverId(unsigned int driverId){
  this->driverId = driverId;
}

void Shift::setBusOrderNumber(unsigned int busOrderNumber){
  this->busOrderNumber = busOrderNumber;
}

void Shift::setStartTime(unsigned int startTime){
  this->startTime = startTime;
}

void Shift::setEndTime(unsigned int endTime){
  this->endTime = endTime;
}