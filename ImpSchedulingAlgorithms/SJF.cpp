//Shortest Job First is an algorithm in which the process having the smallest execution
//time (burst time) is chosen for the next execution.

//Non-preemptive SJF, once the CPU cycle is allocated to process, the process holds it 
//till it reaches a waiting state or terminated



//sort the vector in order of arrival time
//while exceuting comparing the remaing burst time with the burst time of next process




//Shortest Job First is an algorithm in which the process having the smallest execution
//time (burst time) is chosen for the next execution.

//Non-preemptive SJF, once the CPU cycle is allocated to process, the process holds it 
//till it reaches a waiting state or terminated



//sort the vector in order of arrival time
//while exceuting comparing the remaing burst time with the burst time of next process



#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;



struct pcb {
	int  pid;
	int burstTime;
	int arrivalTime;
	int finishTime;
	int turnaroundTime;
	int waitingTime;
	int responseTime;
};

//wait turnaround repsonse
vector <double> OC;

/*
Equations Used:
Turnaround Time = Finish Time - Arrival Time
Waiting Time = Turnaround Time - Burst time
Response Time = Sum of Prev Burst Times - Arrival Time
*/

bool AT(const pcb& a, const pcb& b) {

	return a.arrivalTime < b.arrivalTime;
};

bool BT(const pcb& a, const pcb& b) {

	return a.burstTime < b.burstTime;
};

void SJF(vector <pcb> processes) {

	sort(processes.begin(), processes.end(), AT);

	/*
	for (int i = 0; i < processes.size(); i++) {

		cout << processes[i].name<<endl;
	}
	*/

	//once the process takes hold of the cpu, it does not give it up
	//next process that to be selected is the one with the shortest burst time
	

	int j;
	int CycleTime = 0;
	for (int i = 0; i < processes.size(); i++) {
		j = i;

		while (j != processes.size() && processes[j].arrivalTime <= CycleTime) {
			j++;
		}

		
		sort(processes.begin() + i, processes.begin() + j, BT);
		processes[i].finishTime = CycleTime + processes[i].burstTime;
		CycleTime += processes[i].burstTime;
	}

	int totalTurnaroundTime = 0;
	int totalWaitingTime = 0;
	int totalResponseTime = 0;
	int bsum = 0;;

	/*
	Equations Used:
	Turnaround Time = Finish Time - Arrival Time
	Waiting Time = Turnaround Time - Burst time
	Response Time = Sum of Prev Burst Times - Arrival Time
	*/
	cout << "Pid  AT\tBT\tCT\tTAT\tWT\tRT" << endl;
	for (int i = 0; i < processes.size(); i++) {
		cout << processes[i].pid << "\t";
		cout << processes[i].arrivalTime << "\t";
		cout << processes[i].burstTime << "\t";
		cout << processes[i].finishTime << "\t";
		processes[i].turnaroundTime = abs(processes[i].finishTime - processes[i].arrivalTime);
		cout << processes[i].turnaroundTime << "\t";
		processes[i].waitingTime = abs(processes[i].turnaroundTime - processes[i].burstTime);
		cout << processes[i].waitingTime << "\t";
		processes[i].responseTime = abs(bsum - processes[i].arrivalTime);
		cout << processes[i].responseTime;

		cout << endl;
		bsum += processes[i].burstTime;
		totalTurnaroundTime += processes[i].turnaroundTime;
		totalWaitingTime += processes[i].waitingTime;
		totalResponseTime += processes[i].responseTime;
	}


	cout << "Average Waiting Time= " << (float)totalWaitingTime / processes.size() << endl;
	cout << "Average Turnaround Time= " << (float)totalTurnaroundTime / processes.size() << endl;
	cout << "Average Response Time= " << (float)totalResponseTime / processes.size() << endl;


	
	
};


int main() {

	vector<pcb> p(200);
	
	for (int i = 0; i < p.size() ;i++)
	{
		p[i].pid = i;

		p[i].burstTime = 1 + (rand() % 10);

		p[i].arrivalTime = 0 + (rand() % 10);
	}

	SJF(p);

	

	return 0;
}


