#include "AnalyticalModel.h"

static int a, b;
static int Size;
static double *dTime; /*Выделена память*/
static double dRate[HEIGHT + 1][3];
static double **buffer_rate;/*Выделена память*/
static double cRate[HEIGHT][3];

void AnalyticalModel::calcRecoveryTest(Equation equation, Settings settings, double rate[HEIGHT][WIDTH], double time[],const int N)
{

	Size = N;
	double **model= new double*[N]; /*Выделена память*/
	for (int i = 0; i < N; i++)
	{
		model[i] = new double[4] ;
	}
	cutRate(rate, settings.getRateQuality());
	convertRate(settings);
	convertTime(time, settings);

for (int j = 0; j < Size; j++) 
{
	model[j][0] = time[j];
	model[j][1] = calcRecoveryResponse(equation, settings, dRate, dTime[j]);
	model[j][3] = GDIMath::superpositionTime(cRate, time[j]);
}

if (N > 2) 
{
	for (int i = 1; i < N - 1; i++) {
		if (!isnan(model[i - 1][0]) & !isnan(model[i + 1][0]) & !isnan(model[i - 1][1]) & !isnan(model[i + 1][1])) 
		{
			model[i][2] = (model[i + 1][1] - model[i - 1][1]) / (model[i + 1][3] - model[i - 1][3]);
		}
	}
}
/*
cout << " | Ответ |" << endl;
for (int i = 0; i < N; i++)
{
	for (int j = 0; j < 4; j++)
	{
		cout << j <<") :"<<model[i][j] <<" ";
	}
	
	cout << endl;
}
*/
}

double AnalyticalModel::calcRecoveryResponse(Equation equation, Settings settings, double dRate[][3], double td)
{ 
	static int number;
	number++;
	double buffer1 = 0, buffer2 = 0;
	Stefest stefest;
	
	for (int i = 1; i < HEIGHT ; i++) {
		buffer1 = buffer1 + (dRate[i][2] - dRate[i - 1][2])
			* settings.calcDPressure(stefest.stefest(equation, dRate[HEIGHT ][1] - dRate[i][1], 8));
	}
	for (int i = 1; i < HEIGHT+1; i++) {
		buffer2 = buffer2 + (dRate[i][2] - dRate[i - 1][2]) * settings
			.calcDPressure(stefest.stefest(equation, dRate[HEIGHT ][1] - dRate[i][1] + td, 8));	
	}
	
	return buffer1 - buffer2;
}

void AnalyticalModel::cutRate(double rate[][WIDTH], double quality)
{
	int key = 0;
	int start = 0;

	if (HEIGHT > 10)
	{
		double buffer[HEIGHT][4];

		buffer[0][0] = rate[HEIGHT - 1][0];
		buffer[0][1] = 0;
		buffer[0][2] = rate[HEIGHT - 1][2];
		buffer[0][3] = 0;

		for (int i = 1; i < HEIGHT; i++)
		{
			buffer[i][0] = rate[HEIGHT - i - 1][0];
			buffer[i][1] = buffer[i - 1][1] + buffer[i][0];
			buffer[i][2] = rate[HEIGHT - i - 1][2];
			buffer[i][3] = i;
		}

		int key = 0;
		int start = 0;

		do
		{
			start++;
			key++;
			buffer[start][3] = start;
		} while ((buffer[start][1] < buffer[0][0] & start < HEIGHT - 1) | start < 5);

		double time = exp(log(buffer[1][1]) + log(10) / quality);

		for (int i = start; i < HEIGHT; i++)
		{
			buffer[i][3] = key;
			if (buffer[i][1] > time | i == HEIGHT - 1)
			{
				key++;
				time = exp(log(buffer[i][1]) + log(10) / quality);
			}
		}

		a = key = HEIGHT; b = 3; 
		buffer_rate = new double*[HEIGHT];   /*Выделена память*/               
		for (int k = 0; k < key; k++)
		{
			buffer_rate[k] = new double[3];
		}

		double sum1 = 0;
		double sum2 = 0;
		key = 0;

		for (int i = 0; i < HEIGHT - 1; i++) {
			sum1 = sum1 + rate[i][0];
			sum2 = sum2 + rate[i][0] * rate[i][2];
			if (buffer[HEIGHT - 1 - i][3] != buffer[HEIGHT - 2 - i][3]) {
				buffer_rate[key][0] = sum1;
				if (key == 0) {
					buffer_rate[key][1] = 0;
				}
				else {
					buffer_rate[key][1] = buffer_rate[key - 1][1] + buffer_rate[key - 1][0];
				}
				buffer_rate[key][2] = sum2 / sum1;
				key++;
				sum1 = 0;
				sum2 = 0;
			}
		}
		buffer_rate[key][0] = rate[HEIGHT - 1][0];
		buffer_rate[key][1] = rate[HEIGHT - 1][1];
		buffer_rate[key][2] = rate[HEIGHT - 1][2];
	}
	else {
		for (int i = 0; i < a; a++)
		{
			for (int j = 0; j < b; b++)
			{
				buffer_rate[i][j] = rate[i][j];
			}
		}

	}
	for(int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			cRate[i][j] = buffer_rate[i][j];
		}
	}
}



void AnalyticalModel::convertTime(double time[], Settings settings)
	{
		dTime = new double[Size];

		for (int i = 0; i < Size; i++)
		{
			dTime[i] = settings.calcDLTime(time[i]);
		}
	}

void AnalyticalModel::convertRate( Settings settings)
	{
		dRate[0][0] = 0;
		dRate[0][1] = 0;
		dRate[0][2] = 0;
		for (int i = 0; i < HEIGHT; i++)
		{
			dRate[i + 1][0] = settings.calcDLTime(rate[i][0]);
			dRate[i + 1][1] = settings.calcDLTime(rate[i][1]);
			dRate[i + 1][2] = rate[i][2];
		}
	}