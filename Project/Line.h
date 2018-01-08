#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Shift.h" //Para incluir as constantes do tempo de inicio e do fim

using namespace std;

class Line{
 private:
  unsigned int id;
  unsigned int freq_circl;
  vector<string> busStopList;
  vector<unsigned int> timesList;
 public:
  Line(string textLine);
  // metodos get
  unsigned int getId() const;
  unsigned int getFreq_Circl() const;
  vector<string> getBusStops() const;
  vector<unsigned int> getTimings() const;
  // set methods
  // other methods
  unsigned int numberOfBus(); //Returna numero de autocarros necessario para a linha
  void ver_informacao_linha(); //Mostra a inforamacao da linha
};
