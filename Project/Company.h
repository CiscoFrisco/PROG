#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Line.h"
#include "Driver.h"
#include "Bus.h"

using namespace std;


class Company{
 private:
  string name;
  vector<Driver> drivers;
  vector<Line> lines;
  vector<Bus> buses;
 public:
	 Company(string name, string fichDrivers, string fichLines);
  // metodos get
  string getName() const;
  // metodos set
  // outros metodos
  void criar_condutor();
  void editar_condutor();
  void remover_condutor();
  void horario_paragem(); // Mostra tabela horario de uma paragem
  void visualizar_trabalho();
  void visualizar_autocarro();
  void visualizar_linha();
  void linhas_paragem(); // Mostra todas as linhas com uma paragem
  void percurso_entre_paragens(); //Mostra os varios percursos entre paragens, ordenados por menor tempo
  void autocarros_sem_condutor(); //Mostra shifts de autocarros sem condutores
  void condutores_sem_servico_completo(); //Mostrar tempo restante de condutores sem servico semanal completo
  void autocarros_na_linha_sem_condutor(int line_id); //Mostra todos os shifts de autocarros sem condutor atribuido duma determindada linha
  void guardar_ficheiros(string nome_ficheiro_condutores, string nome_ficheiro_linhas); //Guarda informacao
  void distribuiServico(); // funcao que implementa a afectacao de servico
};