//Brandon DeVille, Jared Rainwater, John Maruska
//Algorithms 2500
//Project 1

#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <fstream>
#include <random>
using namespace std;

struct position{
	int x; //x position
	int y; //y position
};

class sensor{
	public:
		int eL = 1000; //energy
		int busy = 0; //busy time
		int mA = 0; //missions applicable
		position getPosition();
		void place(positon c);
	private:
		position p; //point
};

class mission{
	public:
		int sM; //sensors per mission
		int inRange = 0; //number of sensors in range
		int sIR[500]; //indexes of sensors in range
		int aN[500]; //indexes of applied nodes
		bool satisfied = false;
		int getDuration();
		int getStart();
		int getEnd();
		float getRadius();
		position getEpicenter();
		void setDuration(int dur);
		void setEpicenter();
	private:
		int sT = (rand()%100001 - 100); //start time
		int eT; //end time
		float r = 5; //radius
		position eC; //epicenter
};

position sensor::getPosition();

void sensor::place(position c);

position mission::getEpicenter();

void mission::setEpicenter();

int mission::getDuration();

void mission::setDuration(int dur);

int mission::getStart();

int mission:: getEnd();

float mission::getRadius();

void test(mission M[], sensor A[], sensor S[]);

int onlineSolution(mission &M, sensor &S[]);

int offlineSolution(mission &M[], sensor &S[], int num_sensors);

int randomSolution(mission &M, sensor &S[]);

 
int main()
{
		//Initiazlizes all values necessary to run the program
	clock_t start, finish; //start and end time variables for judging runtime
	mission M[1000]; //initial array of missions
	float OnTime, OffTime, RanTime; //variables to hold total runtime for each algorithm
	bool loop = true; //loop variable
	char fin; //variable used to end loop
	int style, num_sensors, sensors_perM, dur_mission = 0; //control variables input by user
	float vOn, vOff, vRan; //value variables for each algo
	default_random_engine generator(time(0)); 
	ofstream out("Data.csv");
	
	//Starts a loop, allowing the user to select as many different numbers of items as he/she desires
	cout << "Please select a deviation style" << endl;
	cout << "1. Number of Sensors" << endl;
	cout << "2. Mission Duration" << endl;
	cout << "3. Sensors per Mission" << endl;
	cin >> style;
	while (loop == true)
	{
		switch (style)
		{
			case 1:
				num_sensors = 25;
				dur_mission = 10;
				sensors_perM = 5;
				for (int k = 0; k < 1000; k++)
				{
					M[k].setDuration(dur_mission);
					M[k].sM = sensors_perM;
				}
				while(num_sensors < 500)
				{				
					sensor S[num_sensors];
					sensor A[num_sensors];
					position c;
				
					for (int i = 0; i < num_sensors; i++)
					{
						c.x = rand()%51;
						c.y = rand()%51;
						S[i].place(c);
						A[i].place(c);
					}
					
					test(A,S);
					
					num_sensors = num_sensors + 25;
				};
			case 2:
				num_sensors = 500;
				dur_mission = 5;
				sensors_perM = 5;
				for (int k = 0; k < 1000; k++)
				{
					M[k].setDuration(dur_mission);
					M[k].sM = sensors_perM;
				}
				while (dur_mission < 100)
				{
					sensor S[num_sensors];
					sensor A[num_sensors];
					position c;
				
					for (int i = 0; i < num_sensors; i++)
					{
						c.x = rand()%51;
						c.y = rand()%51;
						S[i].place(c);
						A[i].place(c);
					}
					
					test(A,S);
					
					dur_mission = dur_mission + 5;
				};
			case 3:
				num_sensors = 500;
				dur_mission = 10;
				sensors_perM = 1;
				for (int k = 0; k < 1000; k++)
				{
					M[k].setDuration(dur_mission);
					M[k].sM = sensors_perM;
					B[k].setDuration(dur_mission);
					B[k].sM = sensors_perM;
				}
				while (sensors_perM < 20)
				{	       
					sensor S[num_sensors];
					sensor A[num_sensors];
					position c;
				
					for (int i = 0; i < num_sensors; i++)
					{
						c.x = rand()%51;
						c.y = rand()%51;
						S[i].place(c);
						A[i].place(c);
					}
					
					test(A,S);
					
					sensors_perM++;
				};
		}
		cout << "End the test? (y/n)" << endl;
		cin << fin;
		if (fin == 'y')
			loop == false;
	}
}

position sensor::getPosition()
{
	return p;
}

void sensor::place(position c)
{
	p.x = c.x;
	p.y = c.y;
	return;
}

position mission::getEpicenter()
{
	return eC;
}

void mission::setEpicenter(position b)
{
	eC.x = b.x;
	eC.y = b.y;
	return;
}

int mission::getDuration()
{
	return (eT - sT) + 1;
}

void mission::setDuration(int dur)
{
	eT = sT + dur;
	return;
}

int mission::getStart()
{
	return sT;
}

int mission::getEnd()
{
	return eT;
}

float mission::getRadius()
{
	return r;
}

void test(mission M[], sensor A[], sensor S[])
{
	start = clock();
	for (int j = 0; j < 1000; j++)
	{
		if (onlineSolution(B[j], A))
			vOn++;
	}
	finish = clock();
	cout << "The number of missions completed by the Online Solution is " << vOn << "." << endl;
	OnTime += ((double)(finish - start) *1000) / CLOCKS_PER_SEC;
	printf("Elapsed: %f miliseconds\n", ((double)(finish - start) *1000) / CLOCKS_PER_SEC);	
	
	for (k = 0; k < 1000; k++)
	{
		M[k].satisfied = false;
		M[k].inRange = 0;
	}
	
	for (i = 0; i < num_sensors; i++)
	{
		A[i].place(S[i].getPosition());
		A[i].eL = S[i].eL;
		A[i].busy = S[i].busy];
	}
	
	start = clock();
	for (int j = 0; j < 1000; j++)
	{
		if (randomSolution(B[j], A))
			vRan++;
	}
	finish = clock();
	cout << "The number of missions completed by the Random Solution is " << vRan << "." << endl;
	RanTime += ((double)(finish - start) *1000) / CLOCKS_PER_SEC;
	printf("Elapsed: %f miliseconds\n", ((double)(finish - start) *1000) / CLOCKS_PER_SEC);	
	
	for (k = 0; k < 1000; k++)
	{
		M[k].satisfied = false;
		M[k].inRange = 0;
	}
	
	for (i = 0; i < num_sensors; i++)
	{
		A[i].place(S[i].getPosition());
		A[i].eL = S[i].eL;
		A[i].busy = S[i].busy];
	}
	
	start = clock();
	vOff = offlineSolution(M, A);
	cout << "The number of missions completed by the Offline Solution is " << vOff << "." << endl;
	OffTime += ((double)(finish - start) *1000) / CLOCKS_PER_SEC;
	printf("Elapsed: %f miliseconds\n", ((double)(finish - start) *1000) / CLOCKS_PER_SEC);	
	finish = clock();
	return;
}

int offlineSolution(mission &M[], sensor &S[], int num_sensors)
{
	int n, q, a, missions_satisfied;
	float distance;
	position s;
	position m;
	for (int i = 0; i < 1000; i++)
	{
		n = 0;
		for (int j = 0; j < num_sensors; j++)
		{
			s = S[j].getPosition();
			m = M[i].getEpicenter();
			distance = sqrt(pow((m.x-s.x),2)+pow((m.y-s.y),2));
			if(M[i].getRadius() >= distance && S[j].eL > M[i].getDuration())
			{
				S[j].mA++;
				M[i].sIR[n] = j;
				n++;
			}
		}
		M[i].inRange = n;
	}
	for (i = 0; i < 1000; i++)
	{
		q = M[i].sM;
		if (M[i].inRange >= M[i].sM)
		{
			for (j = 0; j < M[i].sM; j++)
			{
				for (int k = 1; k < M[i].inRange; k++)
				{
					if (S[M[i].sIR[k]].mA < S[M[i].sIR[k-1]].mA)
						a = M[i].sIR[k];
					else
						a = M[i].sIR[k-1];
				}
				if (S[a].eL > M[i].getDuration() && M[i].getStart() > S[i].busy)
				{
					M[i].aN[j] = a;
					q--;
				}
			}
		}
		if (q == 0)
		{
			for (k = 0; k < M[i].sM; k++)
			{
				S[M[i].aN[k]].busy = M[i].getEnd();
				S[M[i].aN[k]].eL -= M[i].getDuration();
			}
			M[i].satisfied = true;
			missions_satisfied++;
		}
	return missions_satisfied;
}
