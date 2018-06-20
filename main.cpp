#include<cstdlib>  // Для system("pause")

#include <Windows.h> // Для  вывода/ввода в консоль на русском
#include "AnalyticalModel.h"

 
int main()
{
	setlocale(LC_ALL, "Russian"); // Изменение кодировки для вывода русского алфавита

	cout << "Старт" << endl;

	unsigned int start_time = clock();

	Equation  equation;
	Settings settings;
	double Array[1000];
	GDIMath::autoTime(0.001, 1000, 10, Array);

	AnalyticalModel::calcRecoveryTest( equation ,  settings, rate, Array , 64);

	unsigned int end_time = clock();

	cout << "Время работы :" << end_time - start_time << "мс" << endl;
	system("pause");

	return 0;
}