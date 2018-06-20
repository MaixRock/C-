#pragma once

#include "Stefest.h"




class AnalyticalModel 
{
public:
	static void calcRecoveryTest(Equation equation, Settings settings, double rate[HEIGHT][WIDTH], double time[], int N);

	static double calcRecoveryResponse(Equation equation, Settings settings, double dRate[][3], double td);
	
	static void cutRate(double rate[][WIDTH], double quality);
	
private: 

	static void convertTime(double time[], Settings settings);
	
	static void convertRate(Settings settings);
};