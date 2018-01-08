#pragma once

#include <iostream>
#include <vector>


using namespace std;

//Constantes inicio e fim linhas
//Shift.h está incluido em todos os ficheiros de codigo para aceder a estas constantes

const unsigned int min_inicio = (6 * 60);
const unsigned int min_fim = (20 * 60);

class Shift{
 private:
  unsigned int busLineId;
  unsigned int driverId;  
  unsigned int busOrderNumber; 
  unsigned int startTime; 
  unsigned int endTime;   

 public:
  Shift(unsigned int busLineId, unsigned int driverId, unsigned int busNumber, unsigned int startTime, unsigned int endTime);
  // get methdos
  unsigned int getBusLineId() const;
  unsigned int getDriverId() const;
  unsigned int getBusOrderNumber() const; // order of the bus within the bus line
  unsigned int getStartTime() const;
  unsigned int getEndTime() const;

  //  set methods
  void setBusLineId(unsigned int);
  void setDriverId(unsigned int);
  void setBusOrderNumber(unsigned int);
  void setStartTime(unsigned int);
  void setEndTime(unsigned int);

  // other methods
};
