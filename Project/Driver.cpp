#include "Driver.h"
#include <sstream>

Driver::Driver(string textLine){

  //Cria um condutor para uma determinada linha do ficheiro de condutores

	stringstream textLine_stream(textLine);
	char ponto_virgula; // Para retirar o ponto e virgula da stringstream

	textLine_stream >> id >> ponto_virgula;

	textLine_stream.ignore();

	char caracter = textLine_stream.get();

	//Ciclo para obter nome
	while (caracter != ';')
	{
		name += caracter;
		caracter = textLine_stream.get();
	}
	
	name.erase(name.size() - 1);
	textLine_stream.ignore();

	textLine_stream >> maxHours >> ponto_virgula >> maxWeekWorkingTime >> ponto_virgula >> minRestTime;
  
}

Driver::Driver()
{

	//Cria condutor pergntando ao utilizador os parametros
	int temp;

	cout << "Driver's ID? " << endl;
	cin >> temp;

	while (cin.fail() || temp <= 0)
	{
		cout << "Input value is not a valid ID. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> temp;
	}

	id = temp;
	cin.ignore(10000, '\n');

	cout << endl << "Driver's Name? " << endl;
	getline(cin, name);

	cout << endl << "Driver's max duration of a shift? " << endl;
	cin >> temp;

	while (cin.fail() && temp <= 0)
	{
		cout << "Input value is not valid. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> temp;
	}

	maxHours = temp;
	cin.ignore(10000, '\n');

	cout << endl << "Driver's maximum number of hours of work in a week? " << endl;
	cin >> temp;

	while (cin.fail() && temp <= 0)
	{
		cout << "Input value is not valid. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> temp;
	}

	maxWeekWorkingTime = temp;
	cin.ignore(10000, '\n');
	
	cout << endl << "Driver's minimum number of rest hours between shifts? " << endl;
	cin >> temp;

	while (cin.fail() && temp <= 0)
	{
		cout << "Input value is not valid. Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> temp;
	}

	minRestTime = temp;
	cin.ignore(10000, '\n');

	cout << endl << "Driver created successfully." << endl;

}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
  return name;
}

unsigned int Driver::getShiftMaxDuration() const{
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const{
  return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const{
  return minRestTime;
}

vector<Shift> Driver::getShifts() const{
  return shifts;
}

unsigned int Driver::getShiftsSize() const
{
	return shifts.size();
}

//////////////
// set methods
//////////////

void Driver::setID(unsigned int id)
{
	this->id = id;
}

void Driver::setName(string name)
{
	this->name = name;
}

void Driver::setShiftMaxDuration(unsigned int maxHours)
{
	this->maxHours = maxHours;
}

void Driver::setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime)
{
	this->maxWeekWorkingTime = maxWeekWorkingTime;
}

void Driver::setMinRestTime(unsigned int minRestTime)
{
	this->minRestTime = minRestTime;
}

////////////////
// other methods
////////////////

void Driver::showWork() const
{
	//Mostra o trabalho do condutor, separado pelos dias da semana

	cout << endl << endl;

	//Se nao tiver trabalho atribuido, mostra uma mensagem e volta ao menu inicial
	if (shifts.size() == 0)
	{
		cout << "Driver has no work attributed. " << endl << endl;
		return;
	}

	else
	{
		unsigned int i = 0;

		cout << "Monday:" << endl << endl;

		bool work_this_day = false;

		for (i; i <= shifts.size() - 1; i++)
		{
			if (shifts[i].getStartTime() >= (1 * 24 * 60))
				break;

			else
			{
				unsigned int inicio = shifts[i].getStartTime();
				unsigned int fim = shifts[i].getEndTime();

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

				cout << "  LineID: " << shifts[i].getBusLineId() << "  BusID: " << shifts[i].getBusOrderNumber() << endl;

				work_this_day = true;

			}
		}

		if (!work_this_day)
			cout << "Driver has no work attributed for this day. " << endl;

		cout << endl << endl;

		cout << "Tuesday:" << endl << endl;

		work_this_day = false;
		for (i; i <= shifts.size() - 1; i++)
		{
			if (shifts[i].getStartTime() >= (2 * 24 * 60))
				break;


			else
			{
				unsigned int inicio = shifts[i].getStartTime() - (1 * 24 * 60);
				unsigned int fim = shifts[i].getEndTime() - (1 * 24 * 60);

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

				cout << "  LineID: " << shifts[i].getBusLineId() << "  BusID: " << shifts[i].getBusOrderNumber() << endl;

				work_this_day = true;
			}
		}

		if (!work_this_day)
			cout << "Driver has no work attributed for this day. " << endl;

		cout << endl << endl;

		cout << "Wednesday:" << endl << endl;

		work_this_day = false;
		for (i; i <= shifts.size() - 1; i++)
		{


			if (shifts[i].getStartTime() >= (3 * 24 * 60))
				break;

			else
			{
				unsigned int inicio = shifts[i].getStartTime() - (2 * 24 * 60);
				unsigned int fim = shifts[i].getEndTime() - (2 * 24 * 60);

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

				cout << "  LineID: " << shifts[i].getBusLineId() << "  BusID: " << shifts[i].getBusOrderNumber() << endl;

				work_this_day = true;
			}
		}

		if (!work_this_day)
			cout << "Driver has no work attributed for this day. " << endl;

		cout << endl << endl;

		cout << "Thursday:" << endl << endl;

		work_this_day = false;
		for (i; i <= shifts.size() - 1; i++)
		{
			if (shifts[i].getStartTime() >= (4 * 24 * 60))
				break;

			else
			{
				unsigned int inicio = shifts[i].getStartTime() - (3 * 24 * 60);
				unsigned int fim = shifts[i].getEndTime() - (3 * 24 * 60);

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

				cout << "  LineID: " << shifts[i].getBusLineId() << "  BusID: " << shifts[i].getBusOrderNumber() << endl;

				work_this_day = true;

			}
		}

		if (!work_this_day)
			cout << "Driver has no work attributed for this day. " << endl;

		cout << endl << endl;

		cout << "Friday:" << endl << endl;

		work_this_day = false;
		for (i; i <= shifts.size() - 1; i++)
		{
			if (shifts[i].getStartTime() >= (5 * 24 * 60))
				break;

			else
			{
				unsigned int inicio = shifts[i].getStartTime() - (4 * 24 * 60);
				unsigned int fim = shifts[i].getEndTime() - (4 * 24 * 60);

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

				cout << "  LineID: " << shifts[i].getBusLineId() << "  BusID: " << shifts[i].getBusOrderNumber() << endl;

				work_this_day = true;

			}
		}

		if (!work_this_day)
			cout << "Driver has no work attributed for this day. " << endl;

	}

	cout << endl << endl;
}

void Driver::servico_restante() const
{

	//Mostra o numero de minutos restantes semanais para cada condutor
	if (shifts.size() == 0)
	{
		cout << id << ". " << name << " - " << maxWeekWorkingTime * 60 << " minutes left" << endl;
		return;
	}

	int tempo_restante = maxWeekWorkingTime * 60;

	for (unsigned int i = 0; i <= shifts.size() - 1; i++)
	{
		tempo_restante -= shifts[i].getEndTime() - shifts[i].getStartTime();
	}

	if (tempo_restante == 0)
		return;

	else
		cout << id << ". " << name << " - " << tempo_restante << " minutes left" << endl;

}

int Driver::minutos_restantes() const
{
	//Igual a funcao de cima, mas em vez de mostrar no ecra, retorna o valor como int
	if (shifts.size() == 0)
		return maxWeekWorkingTime * 60;

	int tempo_restante = maxWeekWorkingTime * 60;

	for (unsigned int i = 0; i <= shifts.size() - 1; i++)
	{
		tempo_restante -= shifts[i].getEndTime() - shifts[i].getStartTime();
	}

	return tempo_restante;
}

void Driver::adicionar_shift_sorted(Shift turno)
{
	//Se nao tiver shifts, fica como 1º elemento
	if (shifts.size() == 0)
	{
		shifts.push_back(turno);
		return;
	}

	//Se a sua posicao for no meio do vetor de shifts, e introduzido neste ciclo
	for (unsigned int i = 0; i <= shifts.size() - 1; i++)
	{
		if (shifts[i].getStartTime() > turno.getStartTime())
		{
			shifts.insert(shifts.begin() + i, turno);
			return;
		}
	}

	//Se a sua posicao for no fim, e introduzido agora
	shifts.push_back(turno);

}
