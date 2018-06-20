#pragma once
#include <ctime>
#include <iostream>

using namespace std;
class Settings {

private: 
	 double rateQuality = 5;
	 double b = 1;
	 double m = 5;
	 double ct = 0.00005;
	 double h = 10;
	 double f = 0.2;
	 double k = 100;
	 double xf = 100;

public:
	double getRateQuality();

	double calcDLTime(double t);

	double calcDPressure(double pd);

};
