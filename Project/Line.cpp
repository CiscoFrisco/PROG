#include <sstream>
#include "Line.h"

Line::Line(string textLine){

	//Cria uma linha para uma determinada linha do ficheiro de linhas

	stringstream textLine_stream(textLine);

	char ponto_virgula; //Para retirar facilmente o ponto e virgula da stringstream

	textLine_stream >> id >> ponto_virgula >> freq_circl >> ponto_virgula;

	textLine_stream.ignore();

	char ch;

	ch = textLine_stream.get(); 
	string paragem;
	
	//Ciclo para retirar os nomes das paragens

	while (ch != ';')
	{ 
		if (ch == ',')
		{
			busStopList.push_back(paragem);
			paragem = "";
			textLine_stream.ignore();
			ch = textLine_stream.get();
		}

		else
		{
			paragem += ch;
			ch = textLine_stream.get();
		}
	}

	busStopList.push_back(paragem);
	textLine_stream.ignore();

	ch = textLine_stream.get();
	unsigned int tempo = 0;

	//Ciclo para retirar os tempos entre paragens

	while (ch != -1)
	{
		if (ch == ',')
		{
			timesList.push_back(tempo);
			tempo = 0;
			textLine_stream.ignore();
			ch = textLine_stream.get();
		}

		else
		{
			tempo = (tempo * 10) + ch - '0';
			ch = textLine_stream.get();
		}
	}

	timesList.push_back(tempo);
}

////////////////
// get methods
////////////////

unsigned int Line::getId() const{
  return id;
}

unsigned int Line::getFreq_Circl() const {
	return freq_circl;
}

vector<string> Line::getBusStops() const{
  return busStopList;
}

vector<unsigned int> Line::getTimings() const{
  return timesList;
}

////////////////
// Other Methods
////////////////

unsigned int Line::numberOfBus()
{
	//Devolve numero de autocarros necessários para linha

	unsigned int soma = 0;

	for (unsigned int i = 0; i <= timesList.size() - 1; i++)
	{
		soma += timesList[i];
	}

	soma *= 2;

	unsigned int resultado = soma / freq_circl;

	if (soma % freq_circl == 0)
		return resultado;

	else
		return ++resultado;
}

void Line::ver_informacao_linha()
{
	//Mostra o numero necessario de autocarros para uma linha

	cout << endl <<  "Line " << id << endl << "This line needs " << numberOfBus() << " buses." << endl << endl;

	//Mostra o sentido "direto"

	cout << busStopList[0] << " -> " << busStopList[busStopList.size() - 1] << endl;

	//Ciclo mostra as paragens
	//Espaços para formataçao

	for (unsigned int i = 0; i <= busStopList.size() - 1; i++)
	{
		if (busStopList[i].length() >= 5)
			cout << busStopList[i] << ' ';

		else
		{
			cout << busStopList[i];

			for (unsigned int n = 1; n <= 6 - busStopList[i].length(); n++)
				cout << ' ';
		}
	}

	cout << endl;

	vector<unsigned int> tamanho_paragem;

	for (unsigned int i = 0; i <= busStopList.size() - 1; i++)
		tamanho_paragem.push_back(busStopList[i].length()); //Obtem o tamanho de cada paragem para formatar os horarios

	unsigned int minutos = min_inicio;

	//Ciclo para mostrar os horarios no sentido "direto"
	for (minutos; minutos < min_fim; minutos += freq_circl)
	{
		unsigned int i = 0;

		if (minutos / 60 < 10)
			cout << '0' << minutos / 60 << ":";
		else cout << minutos / 60 << ":";

		if (minutos % 60 < 10)
			cout << '0' << minutos % 60;
		else cout << minutos % 60;

		unsigned int minutos_temp = minutos;

		while (i <= timesList.size() - 1)
		{

			unsigned int espacos;

			if (tamanho_paragem[i] < 5)
				espacos = 0;
			else espacos = tamanho_paragem[i] - 5;

			for (espacos; espacos > 0; espacos--)
				cout << ' '; //Espaços para "cobrir" o nome da paragem anterior

			cout << ' '; //Espaço para "cobrir" o espaço entre o nome das paragens

			minutos_temp += timesList[i];

			if (minutos_temp / 60 < 10)
				cout << '0' << minutos_temp / 60 << ":";
			else cout << minutos_temp / 60 << ":";

			if (minutos_temp % 60 < 10)
				cout << '0' << minutos_temp % 60;
			else cout << minutos_temp % 60;

			i++;

		}
		cout << endl;
	}

	//Mostra o sentido "inverso"
	cout << endl << endl << busStopList[busStopList.size() - 1] << " -> " << busStopList[0] << endl << endl;

	//Mostras as paragens no sentido "inverso"
	//Espacos para formatacao
	for (int i = busStopList.size() - 1; i >= 0; i--)
	{
		if (busStopList[i].length() >= 5)
			cout << busStopList[i] << ' ';

		else
		{
			cout << busStopList[i];

			for (unsigned int n = 1; n <= 6 - busStopList[i].length(); n++)
				cout << ' ';
		}
	}

	cout << endl;

	unsigned int soma = 0;

	for (unsigned int i = 0; i <= timesList.size() - 1; i++)
		soma += timesList[i];

	minutos = min_inicio + soma;

	//Mostra horario sentido "inverso"
	for (minutos; minutos < min_fim + soma; minutos += freq_circl)
	{
		int i = timesList.size() - 1;

		if (minutos / 60 < 10)
			cout << '0' << minutos / 60 << ":";
		else cout << minutos / 60 << ":";

		if (minutos % 60 < 10)
			cout << '0' << minutos % 60;
		else cout << minutos % 60;

		unsigned int minutos_temp = minutos;

		while (i >= 0)
		{

			unsigned int espacos;

			if (tamanho_paragem[i + 1] < 5)
				espacos = 0;
			else espacos = tamanho_paragem[i + 1] - 5;

			for (espacos; espacos > 0; espacos--)
				cout << ' '; //Espaços para "cobrir" o nome da paragem anterior

			cout << ' '; //Espaço para "cobrir" o espaço entre o nome das paragens

			minutos_temp += timesList[i];

			if (minutos_temp / 60 < 10)
				cout << '0' << minutos_temp / 60 << ":";
			else cout << minutos_temp / 60 << ":";

			if (minutos_temp % 60 < 10)
				cout << '0' << minutos_temp % 60;
			else cout << minutos_temp % 60;

			i--;

		}
		cout << endl;
	}

	cout << endl << endl;
}