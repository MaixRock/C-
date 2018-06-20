#pragma once
#include "Equation.h"
class Stefest
{
	public:
		double stefest(Equation f, double t, int N)
		{
			
			double sumN = 0;
			for (int n = 1; n <= N; n++)
			{
				double sumP = 0;
				for (int p = (n + 1) / 2; p <= fmin(n, N / 2); p++)
				{
					sumP = sumP
						+ (pow(-1, n + N / 2) * pow(p, N / 2) * factorial(2 * p)) / (factorial(N / 2 - p)
							* factorial(p) * factorial(p - 1) * factorial(n - p) * factorial(2 * p - n));
				}
				sumN = sumN + sumP * f.calc(n * log(2) / t);
			}
		
			return sumN * log(2) / t;
		}
private:
	static double factorial(double n)
	{
		double factorial = 1;
		for (int i = 1; i <= n; i++)
		{
			factorial = factorial * i;
		}
		return factorial;
		}
};
	