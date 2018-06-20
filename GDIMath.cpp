#include "GDIMath.h"
#include <vector>

static int SizeArrayTime; 

  double  GDIMath::besselI0(double x)
	{

		double ax, ans;
		double y;

		if ((ax = abs(x)) < 3.75)
		{
			y = x / 3.75;
			y = y*y;
			ans = 1.0 + y * (3.5156229
				+ y * (3.0899424 + y * (1.2067492 + y * (0.2659732 + y * (0.360768e-1 + y * 0.45813e-2)))));
		}
		else {
			y = 3.75 / ax;
			ans = (exp(ax) / sqrt(ax))
				* (0.39894228 + y * (0.1328592e-1 + y * (0.225319e-2 + y * (-0.157565e-2 + y * (0.916281e-2
					+ y * (-0.2057706e-1 + y * (0.2635537e-1 + y * (-0.1647633e-1 + y * 0.392377e-2))))))));
		}
		return ans;
	}

	  double GDIMath::besselK0(double x)
	{
		double y, ans;

		if (x <= 2.0)
		{
			y = x * x / 4.0;
			ans = (-log(x / 2.0) * besselI0(x)) + (-0.57721566 + y * (0.42278420
				+ y * (0.23069756 + y * (0.3488590e-1 + y * (0.262698e-2 + y * (0.10750e-3 + y * 0.74e-5))))));
		}
		else {
			y = 2.0 / x;
			ans = (exp(-x) / sqrt(x)) * (1.25331414 + y * (-0.7832358e-1 + y
				* (0.2189568e-1 + y * (-0.1062446e-1 + y * (0.587872e-2 + y * (-0.251540e-2 + y * 0.53208e-3))))));
		}
		
		return ans;
	}

	double GDIMath::superpositionTime(double rate[][WIDTH], double t) 
	{
		double sn = 0;
		double q[HEIGHT+1][WIDTH];
		q[0][0] = 0;
		q[0][1] = 0;
		q[0][2] = 0;
		for (int i = 0; i < HEIGHT; i++) 
		{
			q[i + 1][0] = rate[i][0];
			q[i + 1][1] = rate[i][1];
			q[i + 1][2] = rate[i][2];
		}

		for (int i = 1; i < HEIGHT; i++) 
		{
			sn = sn + (q[i][2] - q[i - 1][2]) * log(q[HEIGHT][1] - q[i][1] + t)
				/ (q[HEIGHT][2] - q[HEIGHT-1][2]);
		}
		sn = sn + log(t);

		return sn;
	}
	
	void GDIMath::autoTime(double lowerBound, double upperBound, double quality, double aTime[]) 
	{
		std::vector<double> buffer;
	
		upperBound = pow(10, log10(upperBound) + 1 / quality);
		int key = 0;

		do
		{
			buffer.push_back(pow(10, log10(upperBound) - key / quality));  
			key++;
		}
		while (pow(10, log10(upperBound) - key / quality) > lowerBound);

	    SizeArrayTime =  buffer.size() + 2;

		aTime[0] = pow(10, log10(lowerBound) - 1 / quality);
		aTime[1] = lowerBound;
		for (int i = 0; i < SizeArrayTime - 2; i++)
		{
			aTime[i + 2] = buffer[SizeArrayTime - 3 - i];
		}
	}
    int GDIMath::GetArraySizeTime(int L)
	{
		L = SizeArrayTime - 1;
		return L;
	}