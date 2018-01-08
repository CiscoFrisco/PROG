#include "Bus.h"

Bus::Bus(unsigned int id, unsigned int line, unsigned int duracao, unsigned int numero_autocarros_linha, unsigned int freq_circl) {

	orderInLine = id;
	lineId = line;

	unsigned int tempo_inicio;
	unsigned int tempo_fim;

	//Cria shifts para toda a semana
	for (unsigned int dia = 0; dia < 5; dia++)
	{
		tempo_inicio = min_inicio + ((id - 1) * freq_circl) + (dia * 24 * 60);

		while (tempo_inicio < (min_fim + (dia * 24 * 60)))
		{
			tempo_fim = tempo_inicio + duracao;

			Shift turno(line, 0, id, tempo_inicio, tempo_fim); //Shifts com id do condutor a 0 não têm condutor atribuido

			schedule.push_back(turno);

			tempo_inicio += numero_autocarros_linha * freq_circl;
		}

	}
}


////////////////////////////////
// get methods
///////////////////////////////
unsigned int Bus::getBusOrderInLine() const {
	return orderInLine;
}
unsigned int Bus::getLineId() const {
	return lineId;
}

vector<Shift> Bus::getSchedule() const {
	return schedule;
}

////////////////////////////
// other methods
////////////////////////////

void Bus::visualizar_autocarro() const
{
	cout << endl << "Line: " << lineId << endl << "Bus: " << orderInLine << endl << endl;

	//Ciclo para mostrar todos os turnos
	for (unsigned int i = 0; i <= schedule.size() - 1; i++)
	{
		unsigned int inicio = schedule[i].getStartTime();
		unsigned int fim = schedule[i].getEndTime();

		unsigned int dia = inicio / (24 * 60);

		inicio -= dia * 24 * 60;
		fim -= dia * 24 * 60;

		switch (dia)
		{
		case 0:
			cout << "Monday  ";
			break;
		case 1:
			cout << "Tuesday  ";
			break;
		case 2:
			cout << "Wednesday  ";
			break;
		case 3:
			cout << "Thursday  ";
			break;
		case 4:
			cout << "Friday  ";
			break;
		}

		if (inicio / 60 < 10)
			cout << '0' << inicio / 60 << ':';
		else
			cout << inicio / 60 << ':';

		if (inicio % 60 < 10)
			cout << '0' << inicio % 60;
		else
			cout << inicio % 60;

		cout << " - ";

		if (fim / 60 < 10)
			cout << '0' << fim / 60 << ':';
		else
			cout << fim / 60 << ':';

		if (fim % 60 < 10)
			cout << '0' << fim % 60;
		else
			cout << fim % 60;

		if (schedule[i].getDriverId() == 0)
			cout << "  Driver ID:  No driver";

		else cout << "  Driver ID: " << schedule[i].getDriverId();

		cout << endl;

	}

	cout << endl << endl;

}

void Bus::ver_periodos_sem_condutor() const
{
	
	//Verifica se existe algum algum turno sem condutor
	for (unsigned int i = 0; i <= schedule.size() - 1; i++)
	{
		if (schedule[i].getDriverId() == 0)
			break;

		else if (i == schedule.size() - 1)
			return;
	}

	cout << "Line: " << lineId << "  Bus: " << orderInLine << endl;

	//Ciclo para mostrar os turnos de toda a semana
	for (unsigned int i = 0; i <= schedule.size() - 1; i++)
	{
		if (schedule[i].getDriverId() == 0)
		{
			unsigned int inicio = schedule[i].getStartTime();
			unsigned int fim = schedule[i].getEndTime();

			unsigned int dia = inicio / (24 * 60);

			inicio -= dia * 24 * 60;
			fim -= dia * 24 * 60;

			switch (dia)
			{
			case 0:
				cout << "Monday  ";
				break;
			case 1:
				cout << "Tuesday  ";
				break;
			case 2:
				cout << "Wednesday  ";
				break;
			case 3:
				cout << "Thursday  ";
				break;
			case 4:
				cout << "Friday  ";
				break;
			}

			if (inicio / 60 < 10)
				cout << '0' << inicio / 60 << ':';
			else
				cout << inicio / 60 << ':';

			if (inicio % 60 < 10)
				cout << '0' << inicio % 60;
			else
				cout << inicio % 60;

			cout << " - ";

			if (fim / 60 < 10)
				cout << '0' << fim / 60 << ':';
			else
				cout << fim / 60 << ':';

			if (fim % 60 < 10)
				cout << '0' << fim % 60;
			else
				cout << fim % 60;
		}

		cout << endl;
	}

	cout << endl;
}

Shift *Bus::turno_pretendido()
{
	unsigned int index = 0;

	//Ciclo para mostrar turnos sem condutor atribuido
	for (unsigned int i = 0; i <= schedule.size() - 1; i++)
	{
		if (schedule[i].getDriverId() == 0)
		{
			unsigned int inicio = schedule[i].getStartTime();
			unsigned int fim = schedule[i].getEndTime();

			unsigned int dia = inicio / (24 * 60);

			inicio -= dia * 24 * 60;
			fim -= dia * 24 * 60;

			cout << index << ". ";

			switch (dia)
			{
			case 0:
				cout << "Monday  ";
				break;
			case 1:
				cout << "Tuesday  ";
				break;
			case 2:
				cout << "Wednesday  ";
				break;
			case 3:
				cout << "Thursday  ";
				break;
			case 4:
				cout << "Friday  ";
				break;
			}

			if (inicio / 60 < 10)
				cout << '0' << inicio / 60 << ':';
			else
				cout << inicio / 60 << ':';

			if (inicio % 60 < 10)
				cout << '0' << inicio % 60;
			else
				cout << inicio % 60;

			cout << " - ";

			if (fim / 60 < 10)
				cout << '0' << fim / 60 << ':';
			else
				cout << fim / 60 << ':';

			if (fim % 60 < 10)
				cout << '0' << fim % 60;
			else
				cout << fim % 60;

			cout << endl;

			index++;
		}
	}

	cout << endl;

	unsigned int shift_id;

	cout << "Shift ID? " << endl;

	cin >> shift_id;

	while (cin.fail() || shift_id > index)
	{
		cout << "Input value is not a valid id. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> shift_id;
	}

	int index_temp = -1;
	int posicao_shift_encontrado = -1;

	//posicao_shift_encontrado tem o indice do shift que o utilizador selecionou
	for (unsigned int i = 0; i <= schedule.size() - 1; i++)
	{
		if (schedule[i].getDriverId() == 0)
			index_temp++;
		
		if (index_temp == shift_id)
		{
			posicao_shift_encontrado = i;
		}
	}

	cin.ignore(10000, '\n');
	
	cout << endl << endl;

	//retorna a posicao de memoria do shift pretendido pelo utilizador
	return &schedule[posicao_shift_encontrado];
}
