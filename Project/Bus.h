#pragma once

#include <iostream>
#include <vector>

#include "Shift.h"


using namespace std;

class Bus{
 private:
  unsigned int orderInLine;
  unsigned int lineId;
  vector<Shift> schedule;
 public:
	Bus(unsigned int id, unsigned int line, unsigned int duracao, unsigned int numero_autocarros_linha, unsigned int freq_circl);
  // get methods
  unsigned int getBusOrderInLine() const;
  unsigned int getLineId() const;
  vector<Shift> getSchedule() const;
  // set methods
  // other methods
  void visualizar_autocarro() const; //Visualizao informacao autocarro
  void ver_periodos_sem_condutor() const; //Ver shifts sem condutor
  Shift *turno_pretendido(); //Funcao que mostra os shifts para a funcao de atribuir trabalho e returna um ptr para o shift pretendido pelo utilizador
};
