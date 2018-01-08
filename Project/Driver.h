#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Shift.h"


using namespace std;

//Construtor inicia shifts vazio

class Driver{
 private:
  unsigned int id;
  string name;
  unsigned int maxHours;        // maximum duration of a shift
  unsigned int maxWeekWorkingTime;  // maximum number of hours of work in a week
  unsigned int minRestTime;     // minimum number of rest hours between shifts
  vector<Shift> shifts;         // assigned shifts
 public:
  Driver(string textLine);
  Driver();
  // get methods
  unsigned int getId() const;
  string getName() const;
  unsigned int getShiftMaxDuration() const;
  unsigned int getMaxWeekWorkingTime() const;
  unsigned int getMinRestTime() const;
  vector<Shift> getShifts() const;
  unsigned int getShiftsSize() const;

  // set methods
  void setID(unsigned int id);
  void setName(string name);
  void setShiftMaxDuration(unsigned int maxHours);
  void setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime);
  void setMinRestTime(unsigned int minRestTime);

  // other methods
  void showWork() const; //Mostra trabalho atribuido a um condutor
  void servico_restante() const; //Mostrar tempo restante para a semana de um condutor
  int minutos_restantes() const; //Funcao igual à anterior, mas returna um inteiro em vez de o mostrar
  void adicionar_shift_sorted(Shift turno); //Adiciona um shift a um condutor, ordenado pelo tempo de inicio
};
