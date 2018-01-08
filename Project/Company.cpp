#include "Company.h"
#include <fstream>

//Obtem informacao de ficheiros e cria vetor de linhas, condutores e autocarros na companhia
Company::Company(string nome, string fichCondutores, string fichLinhas) {
	name = nome;

	//Obter condutores

	ifstream fichCondutores_file;

	//Abrir ficheiro de condutores, se falhar encerra programa com erro

	fichCondutores_file.open(fichCondutores);

	if (fichCondutores_file.fail())
	{
		cerr << "Drivers' file couldn't be open. Please verify it's name and try again.\n";
		exit(1);
	}

	//Vai buscar informacao ao ficheiro linha a linha, e cria condutores
	while (!fichCondutores_file.eof())
	{
		string linha_condutor;
		getline(fichCondutores_file, linha_condutor);
		Driver condutor(linha_condutor);
		drivers.push_back(condutor);
	}

	//Fecha ficheiro
	fichCondutores_file.close();

	//Obter linhas
	ifstream fichLinhas_file;

	//Abre ficheiro de linhas, se nao conseguir encerra programa com erro
	fichLinhas_file.open(fichLinhas);

	if (fichLinhas_file.fail())
	{
		cerr << "Lines' file couldn't be open. Please verify it's name and try again.\n";
		exit(2);
	}

	//Vai buscar informacao ao ficheiro linha a linha, e cria condutores
	while (!fichLinhas_file.eof())
	{
		string linha_linha;
		getline(fichLinhas_file, linha_linha);
		Line linha(linha_linha);
		lines.push_back(linha);
	}

	//Fecha ficheiro
	fichLinhas_file.close();

	//Cria autocarros necessarios, sem condutor atribuido ainda
	for (unsigned int i = 0; i <= lines.size() - 1; i++)
	{
		unsigned int numero_autocarros_linha = lines[i].numberOfBus();
		unsigned int id_linha = lines[i].getId();
		unsigned int freq_circulacao = lines[i].getFreq_Circl();
		unsigned int tempo_ida_e_volta = 0;

		for (unsigned int n = 0; n <= lines[i].getTimings().size() - 1; n++)
		{
			tempo_ida_e_volta += lines[i].getTimings()[n];
		}

		tempo_ida_e_volta *= 2;

		for (unsigned int j = 0; j <= numero_autocarros_linha - 1; j++)
		{
			Bus autocarro(j + 1,id_linha,tempo_ida_e_volta,numero_autocarros_linha,freq_circulacao); 
			buses.push_back(autocarro);
		}
	}

}

////////////////////////////////
// metodos get
///////////////////////////////
string Company::getName() const {
	return name;
}

////////////////////////////
// other methods
///////////////////////////

void Company::criar_condutor()
{
	Driver condutor;
	bool igual_id = true, driver_deleted = false;

	//Chama construtor de condutor e faz push back para o vetor de condutores
	drivers.push_back(condutor);

	int id_novo_condutor = drivers[drivers.size() - 1].getId();

	//Verifica se ja há condutor com id igual ao introduzido
	while (igual_id)
	{
		for (unsigned int i = 0; i <= drivers.size() - 2; i++)
		{
			if (id_novo_condutor == drivers[i].getId())
			{
				unsigned int operacao;
				cout << endl << "Created driver has the same id has the following driver: " << endl << drivers[i].getId() << ". " << drivers[i].getName() << endl << "Do you want:" << endl << "1. Change created driver id" << endl << "2. Delete created driver" << endl;
				cin >> operacao;

				while ((operacao != 1 && operacao != 2) || cin.fail())
				{
					cout << "Input value is not a valid operation. Try again: ";
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> operacao;
				}

				cin.ignore(10000, '\n');

				if (operacao == 1)
				{
					cout << "New Id? ";
					cin >> id_novo_condutor;

					while (cin.fail() || id_novo_condutor <= 0)
					{
						cout << "Input value is not a valid id. Try again: ";
						cin.clear();
						cin.ignore(10000, '\n');
						cin >> id_novo_condutor;
					}

					cin.ignore(10000, '\n');

					drivers[drivers.size() - 1].setID(id_novo_condutor);
					igual_id = true;
					break;
				}

				else
				{
					drivers.pop_back();
					driver_deleted = true;
					igual_id = false;
					break;
				}
			}

			else if (i == drivers.size() - 2)
			{
				igual_id = false;
				break;
			}
		}
	}

	if (driver_deleted)
		cout << endl << "Created driver was not added to " << name << "'s drivers list." << endl;
	else
		cout << endl << "Created driver added successfully to " << name << "'s drivers list." << endl;
}

void Company::editar_condutor()
{
	int ID; //ID é um inteiro com sinal pois mais à fente vai-se verificar se o ID inserido foi negativo (dá erro pois nós não o admitimos)

	cout << "Driver's ID: ";
	cin >> ID;

	while (cin.fail() || ID <= 0)
	{
		cout << "Input value is not a valid id. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> ID;
	}

	cin.ignore(10000, '\n');

	unsigned int i = 0;
	bool found = false; // booleano para saber se encontrou o ID do condutor inserido pelo utilizador

	for (i; i < drivers.size(); i++)
	{
		if (drivers[i].getId() == ID)
		{
			//mostra a informação do condutor caso o encontre
			found = true;
			cout << endl << "Driver's ID: " << ID << endl;
			cout << "Driver's name: " << drivers[i].getName() << endl;
			cout << "Driver's maximum shift duration: " << drivers[i].getShiftMaxDuration() << endl;
			cout << "Driver's maximum week working hours: " << drivers[i].getMaxWeekWorkingTime() << endl;
			cout << "Driver's minimum rest time per shift: " << drivers[i].getMinRestTime() << endl << endl;
			break;
		}
	}

	//caso não encontre condutor mostra mensagem de erro
	if (!found)
	{
		cout << "Driver ID is not associated with a Driver." << endl;
		return;
	}

	found = false; // coloca o found a falso outra vez; desta vez vai ser usado para verificar se o novo id  do condutor  já existe, caso o utilizador decida alterar o ID do condutor
	unsigned int index = i;

	char answer; 
	int input_numbers; //vai ser usado como input do ID, Max Shift Hours, Max Week Working Time, Min Rest Time;
	string input_name; //vai ser usado como input para Driver's name;

	cout << "Do you want to change Driver's ID?(Y/N) ";
	cin >> answer;

	//ciclo que verifica o que o utilizador inseriu (Y/N) ou (y/n), se inserir diferente volta a pedir para inserir
	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Invalid Input. Try again: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insert new ID: ";
		cin >> input_numbers;

		while (cin.fail() || input_numbers <= 0)
		{
			cout << "Invalid Input. Please try again: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> input_numbers;
		}

		cin.ignore(10000, '\n');

		do
		{
			for (i = 0; i < drivers.size(); i++)
			{
				if (input_numbers == drivers[i].getId() && i != index) //if the id is already taken by another driver that is not the same driver (i != index)
				{
					found = true;
					cout << "Driver's new ID already associated to another Driver. Try again: ";
					cin >> input_numbers;

					while (cin.fail() || input_numbers <= 0)
					{
						cout << "Invalid Input. Please try again: ";
						cin.clear();
						cin.ignore(1000, '\n');
						cin >> input_numbers;
					}

					cin.ignore(10000, '\n');

					break;
				}

				if (i = drivers.size())
				{
					found = false;
				}

			}

		} while (found);

		drivers[index].setID(input_numbers);

	}

	cout << "Do you want to change Driver's name?(Y/N): ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
	{
		cout << "Invalid input. Please try again: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}
	
	cin.ignore(10000, '\n');

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insert new Driver's name: ";
		getline(cin, input_name);

		while (cin.fail())
		{
			cout << "Conteúdo inválido. Tente novamente: ";
			cin.clear();
			cin.ignore(1000, '\n');
			getline(cin, input_name);
		}

		drivers[index].setName(input_name);
	}

	cout << "Do you want to change the number of maximum hours in the Driver's Shift?(Y/N): ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
	{
		cout << "Invalid input. Please try again:";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insert the new maximum hours in the Driver's shift: ";
		cin >> input_numbers;

		while (cin.fail() || input_numbers > ((min_fim / 60) - (min_inicio - 60)) || input_numbers < 0)
		{
			if (input_numbers > 14 || input_numbers < 0)
			{
				cout << "Number of hours exceeds (below or above) the number of possible daily working hours! Please try again: ";
				cin >> input_numbers;
			}

			else
			{
				cout << "Please try again:: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> input_numbers;
			}
		}

		cin.ignore(10000, '\n');
		drivers[index].setShiftMaxDuration(input_numbers);
	}

	cout << "Do you want to change the number of maximum hours the driver can drive for the week?(Y/N): ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
	{
		cout << "Invalid input. Please try again: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insert new number of maximum hours for a week: ";
		cin >> input_numbers;

		while (cin.fail() || input_numbers > 70 || input_numbers < 0)
		{
			if (input_numbers > 70 || input_numbers < 0)
			{
				cout << "Number of hours inserted exceeds (inferiormente ou superiormente) maximum number of weekly work hours(98 hours)! Please try again: "; //caso o nº de horas cmaximo por semana exceda as (14*7) 98 horas que é o máximo, assumindo que trabalha 7 dias por semana 
				cin >> input_numbers;
			}
			if (cin.fail())
			{
				cout << "Invalid input. Please try again: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> input_numbers;
			}
		}

		cin.ignore(1000, '\n');
		drivers[index].setMaxWeekWorkingTime(input_numbers);
	}

	cout << "Do you want to change the driver's number of minimum hours of rest time per shift ?(Y/N): ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
	{
		cout << "Invalid input. Please try again: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(1000, '\n');


	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insert new number of minimum rest time per shift: ";
		cin >> input_numbers;

		while (cin.fail() || input_numbers < 0)
		{
			if (input_numbers < 0)
			{
				cout << "Number of minimum rest hours per shift cannot be negative.Please try again: ";
				cin >> input_numbers;
			}

			else
			{
				cout << "Invalid input. Please try again. ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> input_numbers;
			}
		}
		cin.ignore(1000, '\n');
		drivers[index].setMinRestTime(input_numbers);
	}
	if (!found)
	{
		cout << endl << "Driver edited successfully!" << endl;
	}

}

void Company::remover_condutor()
{
	int id_a_remover;

	//Mostra condutores existentes, pergunta o id do condutor a remover e remove se existir condutor com esse id
	cout << endl << "Existing drivers:" << endl;

	for (unsigned int i = 0; i <= drivers.size() - 1; i++)
		cout << drivers[i].getId() << ". " << drivers[i].getName() << endl;

	cout << endl << "ID from the driver to be removed?" << endl;

	cin >> id_a_remover;

	while (cin.fail() || id_a_remover <= 0)
	{
		cout << "Input value is not a valid id. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> id_a_remover;
	}

	cin.ignore(10000, '\n');

	for (unsigned int i = 0; i <= drivers.size() - 1; i++)
	{
		if (id_a_remover == drivers[i].getId())
		{
			drivers.erase(drivers.begin() + i);
			cout << endl << "Driver removed sucessfully" << endl;
			return;
		}

		else if (i == drivers.size() - 1)
		{
			cout << endl << "No driver found with input id" << endl;
			return;
		}
	}
}

void Company::horario_paragem()
{
	string paragem;
	cout << endl << "Name of Stop to see schedule? " << endl;
	getline(cin, paragem);

	struct Informacao
	{
		unsigned int id_linha;
		unsigned int freq_circl;
		string ida;
		string volta;
		unsigned int tempo_ate_paragem_1;
		unsigned int tempo_ate_paragem_2;
	};

	vector<Informacao> informacoes;

	//Obtem informacoes de todas as linhas com paragem

	for (unsigned int i = 0; i <= lines.size() - 1; i++)
	{
		vector<string> paragens_i = lines[i].getBusStops();
		for (unsigned int n = 0; n <= paragens_i.size() - 1; n++)
		{
			if (paragem == paragens_i[n])
			{
				Informacao information;
				information.id_linha = lines[i].getId();
				information.freq_circl = lines[i].getFreq_Circl();

				information.ida = paragens_i[paragens_i.size() - 1];
				information.volta = paragens_i[0];

				vector<unsigned int> tempos_entre_paragens_i = lines[i].getTimings();

				unsigned int soma = 0;
				unsigned int n_temp = 0;

				//Tempo ate a paragem no 1o sentido
				if (n > 0)
				{ 

				for (n_temp; n_temp <= n - 1; n_temp++)
					soma += tempos_entre_paragens_i[n_temp];

				}

				information.tempo_ate_paragem_1 = soma;

				//Tempo ate a paragem no 2o sentido
				soma = 0;

				for (n_temp; n_temp <= tempos_entre_paragens_i.size() - 1; n_temp++)
					soma += tempos_entre_paragens_i[n_temp];

				soma *= 2;

				information.tempo_ate_paragem_2 = soma;

				informacoes.push_back(information);

			}
		}
	}

	//Se nao houver linhas com a paragem, volta ao menu
	if (informacoes.size() == 0)
	{
		cout << endl << "Stop not found." << endl;
		return;
	}
	
	//Mostra horario paragem linha a linha
	for (unsigned int i = 0; i <= informacoes.size() - 1; i++)
	{
		cout << endl << informacoes[i].id_linha << endl;

		unsigned int minutos = min_inicio;

		unsigned int espacos = informacoes[i].ida.length();

		cout << "Sentido:" << endl << informacoes[i].ida << "     ";

		cout << informacoes[i].volta << endl;

		while (minutos < min_fim)
		{
			unsigned int minutos_ida = minutos + informacoes[i].tempo_ate_paragem_1;
			unsigned int minutos_volta = minutos_ida + informacoes[i].tempo_ate_paragem_2;

			if (minutos_ida / 60 < 10)
				cout << '0' << minutos_ida / 60 << ':';
			else
				cout << minutos_ida / 60 << ':';

			if (minutos_ida % 60 < 10)
				cout << '0' << minutos_ida % 60;
			else
				cout << minutos_ida % 60;

			for (int n = espacos; n > 0; n--)
				cout << ' ';

			if (minutos_volta / 60 < 10)
				cout << '0' << minutos_volta / 60 << ':';
			else
				cout << minutos_volta / 60 << ':';

			if (minutos_volta % 60 < 10)
				cout << '0' << minutos_volta % 60 << endl;
			else
				cout << minutos_volta % 60 << endl;

			minutos += informacoes[i].freq_circl;
		}
	}

}

void Company::visualizar_trabalho()
{
	unsigned int id;

	//Mostra todos os condutores, pergunta qual quer ver o trabalho e mostra se existir esse condutor
	cout << endl << "Existing drivers:" << endl;

	for (unsigned int i = 0; i <= drivers.size() - 1; i++)
		cout << drivers[i].getId() << ". " << drivers[i].getName() << endl;

	cout << endl << "Driver ID? " << endl;

	cin >> id;

	while (cin.fail())
	{
		cout << "Input value is not a valid id. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> id;
	}

	cin.ignore(10000, '\n');

	for (unsigned int i = 0; i <= drivers.size() - 1; i++)
	{
		if (id == drivers[i].getId())
		{
			drivers[i].showWork();
			return;
		}

		else if (i == drivers.size() - 1)
		{
			cout << endl << "No driver found with input id" << endl;
			return;
		}
	}
}

void Company::visualizar_autocarro()
{
	int id_linha;
	int id_autocarro;

	//Pergunta o id da linha e do autocarro pretendido, se existirem mostra a informacao do autocarro

	cout << "Line ID? ";
	cin >> id_linha;

	while (cin.fail() || id_linha <= 0)
	{
		cout << "Input value is not a valid id. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> id_linha;
	}

	cin.ignore(10000, '\n');

	for (unsigned int i = 0; i <= lines.size() - 1; i++)
	{
		if (id_linha == lines[i].getId())
		{
			break;
		}

		else if (i == lines.size() - 1)
		{
			cout << "Line not found" << endl;
			return;
		}
	}

	cout << "Bus ID? ";
	cin >> id_autocarro;

	while (cin.fail() || id_autocarro <= 0)
	{
		cout << "Input value is not a valid id. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> id_autocarro;
	}

	cin.ignore(10000, '\n');

	for (unsigned int i = 0; i <= buses.size() - 1; i++)
	{
		if (id_linha == buses[i].getLineId())
		{
			if (id_autocarro == buses[i].getBusOrderInLine())
			{ 
				buses[i].visualizar_autocarro();
				break;
			}
		}

		else if (i == buses.size() - 1)
		{
			cout << "Bus not found." << endl;
			return;
		}

	}

	cout << endl;

}

void Company::visualizar_linha()
{
	int id_linha;

	//Pergunta a linha, se encontrar essa linha mostra a informacao

	cout << "Line ID? ";
	cin >> id_linha;

	while (cin.fail() || id_linha <= 0)
	{
		cout << "Input value is not a valid id. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> id_linha;
	}

	cin.ignore(10000, '\n');


	unsigned int posicao_encontrada = 0;

	for (posicao_encontrada; posicao_encontrada <= lines.size() - 1; posicao_encontrada++)
	{
		if (lines[posicao_encontrada].getId() == id_linha)
			break;

		else if (posicao_encontrada == lines.size() - 1)
		{
			cout << "ID not found." << endl;
			return;
		}
	}

	lines[posicao_encontrada].ver_informacao_linha();
	
}


void Company::linhas_paragem()
{
	string paragem; //paragem que vai ser inserida pelo utilizador
	cout << "Insert Bus Stop: ";
	getline(cin, paragem);
	unsigned int i = 0, j = 0;
	bool encontrado = false;

	cout << endl;
	// percorre o vetor de linhas
	for (i; i < lines.size(); i++)
	{
		vector<string> paragens_i = lines[i].getBusStops();
		//percorre o vetor de paragens e se encontrar a paragem inserida faz cout dela
		for (j; j < paragens_i.size(); j++)
		{
			if (paragem == paragens_i[j])
			{
				cout << "Line " << lines[i].getId() << endl;
				encontrado = true;
				break;
			}
		}

		j = 0;
	}

	if (!encontrado)
	{
		cout << "Stop not found" << endl;
	}
}

void Company::percurso_entre_paragens()
{
	string paragem_inicial, paragem_final;

	cout << "Insert first Bus Stop: ";
	getline(cin, paragem_inicial);

	cout << "Insert last Bus Stop: ";
	getline(cin, paragem_final);

	cout << endl;

	//procura as paragens inseridas

	unsigned int i = 0, j = 0, k;

	vector<unsigned int> i_paragem_inicial, i_paragem_final; // onde se vai guardar os valores do contador j, que vão servir para dizer se a paragem de origem aparece antes ou depois da paragem de destino
	vector<unsigned int> i_linha_inicial, i_linha_final; //onde se vai guardar o indice da linha para saber se as linhas de origem e destino são as mesmas
	bool found_inicial = false, found_final = false; //booleanos para o caso de encontrar as paragens de origem e de fim

	//percorre as paragens de cada linha e quando encontrar as paragens de origem ou de destino atualiza os booleanos e os vetores de inteiros.
	for (i; i < lines.size(); i++)
	{
		vector<string> paragens = lines[i].getBusStops();

		for (j; j < paragens.size(); j++)
		{

			if (paragens[j] == paragem_inicial)
			{
				found_inicial = true;
				i_linha_inicial.push_back(i);
				i_paragem_inicial.push_back(j);
			}

			else if (paragens[j] == paragem_final)
			{
				found_final = true;
				i_linha_final.push_back(i);
				i_paragem_final.push_back(j);
			}
		}

		j = 0;

	}
	//caso não tenha encontrado a paragem de origem ou de destino mostra mensagem de erro
	//caso as paragens de origem e destino sejam as mesmas então só o booleano found_inicial é que é colocado a "true" e resulta em erro
	if (!found_inicial || !found_final)
	{
		cout << "Itinerary could not be generated. The stops entered are incorrect." << endl;
		return;
	}

	i = 0;
	j = 0;

	bool found_itinerary = false; // booleano que determina se encontrou itinerário ou não
	unsigned int tempo_total = 0; // tempo total do percurso
	vector<unsigned int> tempos_totais; //vetor que vai servir para ordenar os percursos por tempos (do menor para o maior)

	//uma vez que é necessário ordenar, é preciso armazenar a informação útil. Para isso definiu-se esta struct 
	typedef struct {

		vector<int> line_ID; //vetor de ids da linha (no maximo 2 ids) pois so se consideram percursos na mesma linha ou entre duas linhas)
		vector<string> paragens_linha_inicial; //vetor com as paragens pertencentes à linha com a paragem de origem (caso o percurso seja sempre feito na mesma linha só este vetor fica preenchido
		vector<string> paragens_linha_final; //vetor com as paragens pertencentes à linha com a paragem de destino (caso o percurso seja sempre feito na mesma linha este vetor fica vazio
		vector<unsigned int> tempos_entre_paragens; //vetor com o tempo entre paragens

	} Itinerary;

	vector<Itinerary> percursos; //vetor de structs onde vão ser armazenados os diferentes percursos possiveis, por ordem crescente de tempo

	for (i; i < i_linha_inicial.size(); i++)
	{
		for (j; j < i_linha_final.size(); j++)
		{

			if (i_linha_inicial[i] == i_linha_final[j]) //se as duas paragens estão na mesma linha
			{
				found_itinerary = true;
				tempo_total = 0;
				vector<string> paragens = lines[i_linha_inicial[i]].getBusStops();
				vector<unsigned int> tempos_entre_paragens = lines[i_linha_inicial[i]].getTimings();
				Itinerary percurso;

				if (i_paragem_inicial[i] < i_paragem_final[j]) // se a paragem de origem aparecer primeiro na lista de paragens em relação à paragem de destino
				{
					percurso.line_ID.push_back(lines[i_linha_inicial[i]].getId());

					k = i_paragem_inicial[i];

					percurso.paragens_linha_inicial.push_back(paragens[k]);

					k++;

					while (k < i_paragem_final[j])
					{
						percurso.paragens_linha_inicial.push_back(paragens[k]);
						percurso.tempos_entre_paragens.push_back(tempos_entre_paragens[k - 1]);
						tempo_total += tempos_entre_paragens[k - 1];
						k++;
					}

					percurso.paragens_linha_inicial.push_back(paragens[k]);
					percurso.tempos_entre_paragens.push_back(tempos_entre_paragens[k - 1]);
					tempo_total += tempos_entre_paragens[k - 1];

					if (percursos.size() == 0)
					{
						tempos_totais.push_back(tempo_total);
						percursos.push_back(percurso);
					}

					else
					{
						k = 0;

						for (k; k < tempos_totais.size(); k++)
						{
							if (tempos_totais[k] >= tempo_total)
								break;
						}

						if (k == tempos_totais.size() - 1)
						{
							tempos_totais.push_back(tempo_total);
							percursos.push_back(percurso);
						}

						else
						{
							unsigned int k_final = tempos_totais.size();

							tempos_totais.resize(tempos_totais.size() + 1);
							percursos.resize(percursos.size() + 1);

							while (k_final > k)
							{
								tempos_totais[k_final] = tempos_totais[k_final - 1];
								percursos[k_final] = percursos[k_final - 1];
								k_final--;
							}


							tempos_totais[k] = tempo_total;
							percursos[k] = percurso;
						}
					}
				}

				else if (i_paragem_inicial[i] > i_paragem_final[j]) // se a paragem de destino aparecer primeiro na lista de paragens
				{
					percurso.line_ID.push_back(lines[i_linha_inicial[i]].getId());

					k = i_paragem_inicial[i];

					percurso.paragens_linha_inicial.push_back(paragens[k]);

					k--;

					while (k > i_paragem_final[j])
					{
						percurso.paragens_linha_inicial.push_back(paragens[k]);
						percurso.tempos_entre_paragens.push_back(tempos_entre_paragens[k]);
						tempo_total += tempos_entre_paragens[k];
						k--;
					}

					percurso.paragens_linha_inicial.push_back(paragens[k]);
					percurso.tempos_entre_paragens.push_back(tempos_entre_paragens[k]);
					tempo_total += tempos_entre_paragens[k];

					if (percursos.size() == 0)
					{
						tempos_totais.push_back(tempo_total);
						percursos.push_back(percurso);
					}

					else
					{
						k = 0;

						for (k; k < tempos_totais.size(); k++)
						{
							if (tempos_totais[k] >= tempo_total)
								break;
						}

						unsigned int k_final = tempos_totais.size();

						tempos_totais.resize(tempos_totais.size() + 1);
						percursos.resize(percursos.size() + 1);

						while (k_final > k)
						{
							tempos_totais[k_final] = tempos_totais[k_final - 1];
							percursos[k_final] = percursos[k_final - 1];
							k_final--;
						}


						tempos_totais[k] = tempo_total;
						percursos[k] = percurso;
					}
				}
			}


			else
			{
				vector<unsigned int> i_comum_inicial, i_comum_final; //vetor onde vão ser guardados os indices das paragens em comum (na linha de origem e na de destino)
				vector<string> paragens_iniciais = lines[i_linha_inicial[i]].getBusStops(); //vetor que contém as paragens da linha da paragem de origem
				vector<string> paragens_finais = lines[i_linha_final[j]].getBusStops(); //vetor que contém as paragens da linha da paragem de destino
				vector<unsigned int> tempos_entre_paragens_iniciais = lines[i_linha_inicial[i]].getTimings(); //vetor com os tempos entre paragens na linha da paragem de origem
				vector<unsigned int> tempos_entre_paragens_finais = lines[i_linha_final[j]].getTimings(); //vetor com os tempos entre paragens na linha da paragem de destino
				unsigned int count_inicial = 0, count_final = 0; //contadores que percorrem os vetores linha_inicial e linha_final à procura de paragens em comum, mandado os indices para i_comum_inicial i_comum_final;

				for (count_inicial; count_inicial < paragens_iniciais.size(); count_inicial++)
				{
					for (count_final; count_final < paragens_finais.size(); count_final++)
					{
						if ((paragens_iniciais[count_inicial] == paragens_finais[count_final]) && (paragens_iniciais[count_inicial] != paragem_inicial) && (paragens_finais[count_final] != paragem_final))
						{
							found_itinerary = true;
							i_comum_inicial.push_back(count_inicial);
							i_comum_final.push_back(count_final);
						}
					}

					count_final = 0;
				}


				unsigned int count = 0; //contadores que percorrem os vetores i_comum_inicial e i_comum_final (só preciso de um vetor pois eles são percorridos ao mesmo tempo)

				for (count; count < i_comum_inicial.size(); count++)
				{
					Itinerary percurso;
					tempo_total = 0;
					if (i_comum_inicial[count] > i_paragem_inicial[i])
					{
						percurso.line_ID.push_back(lines[i_linha_inicial[i]].getId());

						k = i_paragem_inicial[i];

						percurso.paragens_linha_inicial.push_back(paragens_iniciais[k]);

						k++;

						while (k < i_comum_inicial[count])
						{
							percurso.paragens_linha_inicial.push_back(paragens_iniciais[k]);
							percurso.tempos_entre_paragens.push_back(tempos_entre_paragens_iniciais[k - 1]);
							tempo_total += tempos_entre_paragens_iniciais[k - 1];
							k++;
						}

						percurso.paragens_linha_inicial.push_back(paragens_iniciais[k]);
						percurso.tempos_entre_paragens.push_back(tempos_entre_paragens_iniciais[k - 1]);
						tempo_total += tempos_entre_paragens_iniciais[k - 1];

					}


					else if (i_comum_inicial[count] < i_paragem_inicial[i])
					{
						percurso.line_ID.push_back(lines[i_linha_inicial[i]].getId());

						k = i_paragem_inicial[i];

						percurso.paragens_linha_inicial.push_back(paragens_iniciais[k]);

						k--;

						while (k > i_paragem_inicial[i])
						{
							percurso.paragens_linha_inicial.push_back(paragens_iniciais[k]);
							percurso.tempos_entre_paragens.push_back(tempos_entre_paragens_iniciais[k]);
							tempo_total += tempos_entre_paragens_iniciais[k];
							k--;
						}

						percurso.paragens_linha_inicial.push_back(paragens_iniciais[k]);
						percurso.tempos_entre_paragens.push_back(tempos_entre_paragens_iniciais[k]);
						tempo_total += tempos_entre_paragens_iniciais[k];

					}

					if (i_comum_final[count] > i_paragem_final[j])
					{
						percurso.line_ID.push_back(lines[i_linha_final[j]].getId());

						k = i_comum_final[count];

						percurso.paragens_linha_final.push_back(paragens_finais[k]);

						k--;

						while (k > i_comum_inicial[count])
						{
							percurso.paragens_linha_final.push_back(paragens_finais[k]);
							percurso.tempos_entre_paragens.push_back(tempos_entre_paragens_finais[k]);
							tempo_total += tempos_entre_paragens_finais[k];
							k--;
						}

						percurso.paragens_linha_final.push_back(paragens_finais[k]);
						percurso.tempos_entre_paragens.push_back(tempos_entre_paragens_finais[k]);
						tempo_total += tempos_entre_paragens_finais[k];

						if (percursos.size() == 0)
						{
							tempos_totais.push_back(tempo_total);
							percursos.push_back(percurso);
						}

						else
						{
							k = 0;

							for (k; k < tempos_totais.size(); k++)
							{
								if (tempos_totais[k] >= tempo_total)
									break;
							}

							unsigned int k_final = tempos_totais.size();

							tempos_totais.resize(tempos_totais.size() + 1);
							percursos.resize(percursos.size() + 1);

							while (k_final > k)
							{
								tempos_totais[k_final] = tempos_totais[k_final - 1];
								percursos[k_final] = percursos[k_final - 1];
								k_final--;
							}


							tempos_totais[k] = tempo_total;
							percursos[k] = percurso;
						}
					}

					else if (i_comum_final[count] < i_paragem_final[j])
					{
						percurso.line_ID.push_back(lines[i_linha_final[j]].getId());

						k = i_comum_final[count];

						percurso.paragens_linha_final.push_back(paragens_finais[k]);

						k++;

						while (k < i_paragem_final[j])
						{
							percurso.paragens_linha_final.push_back(paragens_finais[k]);
							percurso.tempos_entre_paragens.push_back(tempos_entre_paragens_finais[k - 1]);
							tempo_total += tempos_entre_paragens_finais[k - 1];
							k++;
						}

						percurso.paragens_linha_final.push_back(paragens_finais[k]);
						percurso.tempos_entre_paragens.push_back(tempos_entre_paragens_finais[k - 1]);
						tempo_total += tempos_entre_paragens_finais[k - 1];


						if (percursos.size() == 0)
						{
							tempos_totais.push_back(tempo_total);
							percursos.push_back(percurso);
						}

						else
						{
							k = 0;

							for (k; k < tempos_totais.size(); k++)
							{
								if (tempos_totais[k] >= tempo_total)
									break;
							}

							unsigned int k_final = tempos_totais.size();

							tempos_totais.resize(tempos_totais.size() + 1);
							percursos.resize(percursos.size() + 1);

							while (k_final > k)
							{
								tempos_totais[k_final] = tempos_totais[k_final - 1];
								percursos[k_final] = percursos[k_final - 1];
								k_final--;
							}


							tempos_totais[k] = tempo_total;
							percursos[k] = percurso;
						}
					}
				}
			}
		}
		j = 0;
	}
	// caso não tenha encontrado percurso (não existe ligação entre duas linhas e não há percurso na mesma linha)
	if (!found_itinerary)
	{
		cout << "Itinerary could not be generated" << endl << "There is no connection between the line of the first stop and the line of the last stop." << endl;
		return;
	}

	i = 0;
	j = 0;

	//fazer cout do vetor percursos
	for (i; i < percursos.size(); i++)
	{
		for (j; j < percursos[i].paragens_linha_inicial.size(); j++)
		{
			if (percursos[i].paragens_linha_inicial[j] == paragem_final)
			{
				cout << "Last Stop: " << paragem_final << endl;
				cout << "Time between " << percursos[i].paragens_linha_inicial[j - 1] << " and " << percursos[i].paragens_linha_inicial[j] << ": " << percursos[i].tempos_entre_paragens[j - 1] << " minutes" << endl << endl;
				cout << "Total time: " << tempos_totais[i] << " minutes" << endl;
				break;
			}

			else if (percursos[i].paragens_linha_inicial[j] == paragem_inicial)
			{
				cout << "Line: " << percursos[i].line_ID[0] << endl << endl;
				cout << "First Stop: " << paragem_inicial << endl;
			}

			else
			{
				cout << "Next Stop: " << percursos[i].paragens_linha_inicial[j] << endl;
				cout << "Time between " << percursos[i].paragens_linha_inicial[j - 1] << " and " << percursos[i].paragens_linha_inicial[j] << ": " << percursos[i].tempos_entre_paragens[j - 1] << " minutes" << endl << endl;

			}
		}

		k = j - 1;
		j = 0;

		for (j; j < percursos[i].paragens_linha_final.size(); j++)
		{
			if (percursos[i].paragens_linha_final[j] == paragem_final)
			{
				cout << "Last Stop: " << paragem_final << endl;
				cout << "Time between " << percursos[i].paragens_linha_final[j - 1] << " and " << percursos[i].paragens_linha_final[j] << ": " << percursos[i].tempos_entre_paragens[k] << " minutes" << endl << endl;
				cout << "Total time: " << tempos_totais[i] << " minutes" << endl;
				break;
			}

			else if (j == 0)
			{
				cout << "Change to line " << percursos[i].line_ID[1] << endl << endl;
			}

			else
			{
				cout << "Next Stop: " << percursos[i].paragens_linha_final[j] << endl;
				cout << "Time between " << percursos[i].paragens_linha_final[j - 1] << " and " << percursos[i].paragens_linha_final[j] << ": " << percursos[i].tempos_entre_paragens[k] << " minutes" << endl << endl;
				k++;
			}
		}

		j = 0;

		cout << endl << "/////////////////////////////////////////////////////////" << endl;
	}
}

void Company::autocarros_sem_condutor()
{
	for (unsigned int i = 0; i <= buses.size() - 1; i++)
	{
		buses[i].ver_periodos_sem_condutor();
	}

}

void Company::condutores_sem_servico_completo()
{
	for (unsigned int i = 0; i <= drivers.size() - 1; i++)
	{
		drivers[i].servico_restante();
	}

	cout << endl << endl;
}

void Company::autocarros_na_linha_sem_condutor(int line_id)
{
	for (unsigned int i = 0; i <= buses.size() - 1; i++)
	{
		if (buses[i].getLineId() == line_id)
		{
			buses[i].ver_periodos_sem_condutor();
		}
	}
}


void Company::guardar_ficheiros(string nome_ficheiro_condutores, string nome_ficheiro_linhas)
{
	//Guardar ficheiro condutores

	ofstream ficheiro_condutores_stream;

	ficheiro_condutores_stream.open(nome_ficheiro_condutores);

	for (unsigned int i = 0; i <= drivers.size() - 1; i++)
	{
		ficheiro_condutores_stream << drivers[i].getId() << " ; " << drivers[i].getName() << " ; " << drivers[i].getShiftMaxDuration() << " ; " << drivers[i].getMaxWeekWorkingTime() << " ; " << drivers[i].getMinRestTime();

		if (i != drivers.size() - 1)
			ficheiro_condutores_stream << endl;
	}

	ficheiro_condutores_stream.close();

	//Guardar ficheiro linhas

	ofstream ficheiro_linhas_stream;

	ficheiro_linhas_stream.open(nome_ficheiro_linhas);

	for (unsigned int i = 0; i <= lines.size() - 1; i++)
	{
		ficheiro_linhas_stream << lines[i].getId() << " ; " << lines[i].getFreq_Circl() << " ; ";

		vector<string> paragens = lines[i].getBusStops();

		for (unsigned int n = 0; n <= paragens.size() - 1; n++)
		{
			if (n != paragens.size() - 1)
				ficheiro_linhas_stream << paragens[n] << ", ";
			else
				ficheiro_linhas_stream << paragens[n] << "; ";
		}

		vector<unsigned int> tempos = lines[i].getTimings();

		for (unsigned int n = 0; n <= tempos.size() - 1; n++)
		{
			if (n != tempos.size() - 1)
				ficheiro_linhas_stream << tempos[n] << ", ";

			else
				ficheiro_linhas_stream << tempos[n];
		}

		if (i != lines.size() - 1)
			ficheiro_linhas_stream << endl;

	}
}



void Company::distribuiServico() 
{
	int driver_id; 

	//Pergunta ID do condutor, verifica se existe

	cout << "Driver ID? " << endl;
	cin >> driver_id;

	while (cin.fail() || driver_id <= 0)
	{
		cout << "Input value is not a valid id. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> driver_id;
	}

	cin.ignore(10000, '\n');

	unsigned int posicao_driver_encontrado;
	
	for (unsigned int i = 0; i <= drivers.size() - 1; i++)
	{
		if (driver_id == drivers[i].getId())
		{
			posicao_driver_encontrado = i;
			break;
		}

		else if (i == drivers.size() - 1)
		{
			cout << endl << "Driver not found" << endl;
			return;
		}
	}

	if (drivers[posicao_driver_encontrado].minutos_restantes() == 0)
	{
		cout << "Driver has reached max week working time." << endl << endl;
		return;
	}

	cout << endl;

	autocarros_sem_condutor();

	int line_id;

	//Pergunta ID da linha, se encontrar mosta todos os shifts dessa linha

	cout << "Line ID? " << endl;
	cin >> line_id;

	int posicao_linha_encontrado = -1;

	while (posicao_linha_encontrado == -1)
	{ 
		while (cin.fail() || line_id <= 0)
		{
			cout << "Input value is not a valid id. Try again: ";
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> line_id;
		}

		cin.ignore(10000, '\n');

		for (unsigned int i = 0; i <= lines.size() - 1; i++)
		{
			if (line_id == lines[i].getId())
			{
				posicao_linha_encontrado = i;
				break;
			}

			if (i == lines.size() - 1)
			{
				cout << "Line not found. Try again: ";
				cin >> line_id;
			}
		}
	}

	cout << endl;

	autocarros_na_linha_sem_condutor(line_id);

	int bus_id;

	//Pergunta ID do autocarro, se existir mostra todos os shifts

	cout << "Bus ID? " << endl;
	cin >> bus_id;

	int posicao_autocarro_encontrado = -1;

	while (posicao_autocarro_encontrado == -1)
	{
		while (cin.fail() || bus_id <= 0)
		{
			cout << "Input value is not a valid id. Try again: ";
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> bus_id;
		}

		cin.ignore(10000, '\n');

		for (unsigned int i = 0; i <= buses.size() - 1; i++)
		{
			if (bus_id == buses[i].getBusOrderInLine() && line_id == buses[i].getLineId())
			{
				posicao_autocarro_encontrado = i;
				break;
			}

			if (i == buses.size() - 1)
			{
				cout << "Bus not found. Try again: ";
				cin >> bus_id;
			}
		}
	}

	cout << endl;

	//Verifica se o autocarro já tem todos os seus turnos atribuidos

	for (unsigned int i = 0; i <= buses[posicao_autocarro_encontrado].getSchedule().size() - 1; i++)
	{
		if (buses[posicao_autocarro_encontrado].getSchedule()[i].getDriverId() == 0)
			break;

		if (i == buses[posicao_autocarro_encontrado].getSchedule().size() - 1)
		{
			cout << "Selected bus already has full shedule" << endl;
			return;
		}
	}


	//Pede ao utilizador um turno do autocarro escolhido e returna um pointer para esse shift
	Shift *ptrturno = buses[posicao_autocarro_encontrado].turno_pretendido();

	unsigned int tempo_viagem = ptrturno->getEndTime() - ptrturno->getStartTime();

	//Verifica se o tempo de viagem é maior que o tempo maximo de turno do condutor
	if (tempo_viagem > (drivers[posicao_driver_encontrado].getShiftMaxDuration() * 60))
	{
		cout << "Shift duration exceeds driver max shift time" << endl;
		return;
	}

	unsigned int minutos_restantes = drivers[posicao_driver_encontrado].minutos_restantes();
	
	//Verifica se, com o novo turno, o condutor irá exceder o numero maximo de horas semanaias
	if (minutos_restantes < tempo_viagem)
	{
		cout << "Shift would make driver exceeds max week working time" << endl;
		return;
	}

	if (!(drivers[posicao_driver_encontrado].getShiftsSize() == 0))
	{
		int acaba_ultimo_turno = drivers[posicao_driver_encontrado].getShifts()[drivers[posicao_driver_encontrado].getShiftsSize() - 1].getEndTime();

		//Verifica se o condutor descanca o suficiente entre o ultimo turno e este novo turno
		if ((ptrturno->getStartTime() - acaba_ultimo_turno) < (drivers[posicao_driver_encontrado].getMinRestTime() * 60))
		{
			cout << "Shifts would make not rest min rest time." << endl;
			return;
		}

		//Verifica se nao esta atribuido ao novo condutor um shift com as mesmas horas de outro turno 
		if (((int) ptrturno->getStartTime() - acaba_ultimo_turno) < 0)
		{
			cout << "Driver is already working at that time." << endl;
			return;
		}
	}

	ptrturno->setDriverId(driver_id);
	Shift turno(line_id, driver_id, bus_id, ptrturno->getStartTime(), ptrturno->getEndTime());

	//Inserir por ordem
	drivers[posicao_driver_encontrado].adicionar_shift_sorted(turno);

	cout << endl  << "Shift sucessfully assigned to driver" << endl << endl;
}

