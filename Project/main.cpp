#include <iostream>
#include "Company.h"

using namespace std;

int main()
{
	//Pergunta ao utilizador o nome dos ficheiros de condutores e linhas e cria uma companhia se conseguir abrir, se nao fecha o programa com erro

	cout << "Semprarrolar" << endl << endl;

	string nome_ficheiro_linhas;
	string nome_ficheiro_condutores;

	cout << "Drivers' file name? ";
	getline(cin, nome_ficheiro_condutores);

	cout << "Lines' file name? ";
	getline(cin, nome_ficheiro_linhas);

	Company Semprarrolar("Semprearrolar", nome_ficheiro_condutores, nome_ficheiro_linhas);


	int operacao = -1; // Inicializar com um valor diferente de 0

	//Ciclo do menu principal

	while (operacao != 0)
	{

		cout << endl << "What do you want to do? (Enter the corresponding number)" << endl << "0. Exit" << endl << "1. Drivers' Management" << endl << "2. See Information" << endl << "3. Schedule Drivers" << endl << endl;
		cin >> operacao;

		cin.clear();
		cin.ignore(1000, '\n');
		
		int operacao_ciclo;

		switch (operacao)
		{
		case 1: cout << endl << "What do you want to do? (Enter the corresponding number)" << endl << "1. Create driver" << endl << "2. Edit driver" << endl << "3. Remove driver" << endl << endl << "When you enter any other character you will return to the initial menu" << endl << endl;
			cin >> operacao_ciclo;
			cin.clear();
			cin.ignore(1000, '\n');
			if (operacao_ciclo == 1)
			{
				cout << endl;
				Semprarrolar.criar_condutor();
			}
			else if (operacao_ciclo == 2)
			{
				cout << endl;
				Semprarrolar.editar_condutor();
			}
			else if (operacao_ciclo == 3)
			{
				cout << endl;
				Semprarrolar.remover_condutor();
			}
			break;
		case 2: cout << endl << "What do you want to do? (Enter the corresponding number)" << endl << "1. Bus Stop time table" << endl << "2. Drivers' assigned work" << endl << "3. Bus' information" << endl << "4. Line information" << endl << "5. Lines with bus stop" << endl << "6. Route between stops" << endl << "7. Bus schedule without assigned driver" << endl << "8. Driver schedule without complete service" << endl << endl << "When you enter any other character you will return to the initial menu" << endl << endl;
			cin >> operacao_ciclo;
			cin.clear();
			cin.ignore(1000, '\n');
			if (operacao_ciclo == 1)
			{
				cout << endl;
				Semprarrolar.horario_paragem();
			}
			else if (operacao_ciclo == 2)
			{
				cout << endl;
				Semprarrolar.visualizar_trabalho();
			}
			else if (operacao_ciclo == 3)
			{
				cout << endl;
				Semprarrolar.visualizar_autocarro();
			}
			else if (operacao_ciclo == 4)
			{
				cout << endl;
				Semprarrolar.visualizar_linha();
			}
			else if (operacao_ciclo == 5)
			{
				cout << endl;
				Semprarrolar.linhas_paragem();
			}
			else if (operacao_ciclo == 6)
			{
				cout << endl;
				Semprarrolar.percurso_entre_paragens();
			}
			else if (operacao_ciclo == 7)
			{
				cout << endl;
				Semprarrolar.autocarros_sem_condutor();
			}
			else if (operacao_ciclo == 8)
			{
				cout << endl;
				Semprarrolar.condutores_sem_servico_completo();
			}
			break;
		case 3: 
		{
			cout << endl;
			Semprarrolar.distribuiServico();
		}
			break;
		}

		cout << endl;

	}

	char guardar;

	//Pergunta ao utilizador se quer guardar, se sim guarda e depois fecha

	cout << "Do you want to save changes (Y/N) ?" << endl;

	guardar = cin.get();

	while (guardar != 'Y' && guardar != 'y' && guardar != 'N' && guardar != 'n')
	{
		cin.ignore(10000, '\n');
		cout << "Conteudo introduzido incorretamente. Tente novamente: ";
		guardar = cin.get();
	}

	cin.clear();
	cin.ignore(1000, '\n');

	if (guardar == 'Y' || guardar == 'y')
	{
		Semprarrolar.guardar_ficheiros(nome_ficheiro_condutores, nome_ficheiro_linhas);
	}

	cout << endl << endl;

  return 0;
}
