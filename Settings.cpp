#include "Settings.h"

	double Settings::getRateQuality() 
	{
		return rateQuality;
	}

	double Settings::calcDLTime(double t) 
	{
		return 0.00036 * k * t / f / m / ct / xf / xf;
	}

	double Settings::calcDPressure(double pd) 
	{

		return 18.41 * b * m * pd / k / h;
	}


