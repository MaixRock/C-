#pragma once
#include <math.h> 
#include <cmath> 
#include "Input.h"

class GDIMath {

private:
		static double besselI0(double x);
		
	/*	static double factorial(double n);*/
public:
		static double besselK0(double x);

		/*double stefest(Equation f, double t, int N);*/
	
		static double superpositionTime(double rate[][WIDTH], double t);
	
		static void autoTime(double lowerBound, double upperBound, double quality, double aTime[]);

		static int GetArraySizeTime(int L); 
};