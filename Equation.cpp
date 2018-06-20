#pragma once
#include "Equation.h"



	double Equation::calc(double t)
	{
		double ans = 0;
		int n = 100;
		double dx = 2 / (double)n;
		double x;

		for (int i = 0; i < n; i++)
		{
			x = dx * i + dx / 2 - 1;
			ans = ans + GDIMath::besselK0(sqrt(t) * abs(x)) * dx;
		}

		ans = ans / 2 / t;
		
		return ans;
	}