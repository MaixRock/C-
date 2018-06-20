#include<cstdlib>  // ��� system("pause")

#include <Windows.h> // ���  ������/����� � ������� �� �������
#include "AnalyticalModel.h"

 
int main()
{
	setlocale(LC_ALL, "Russian"); // ��������� ��������� ��� ������ �������� ��������

	cout << "�����" << endl;

	unsigned int start_time = clock();

	Equation  equation;
	Settings settings;
	double Array[1000];
	GDIMath::autoTime(0.001, 1000, 10, Array);

	AnalyticalModel::calcRecoveryTest( equation ,  settings, rate, Array , 64);

	unsigned int end_time = clock();

	cout << "����� ������ :" << end_time - start_time << "��" << endl;
	system("pause");

	return 0;
}