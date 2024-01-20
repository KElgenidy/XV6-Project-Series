/*
In Preemptive SJF Scheduling, jobs are put into the ready queue as they come. A
process with shortest burst time begins execution. If a process with even a shorter 
burst time arrives, the current process is removed 
preempted from execution, and the shorter job is allocated CPU cycle.
*/


/*
TurnAround Time =  finishTime - arrivalTime
Waiting Time = Turn Around Time - burstTime
Response Time is the time when the process gets selected the first time
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct pcb {
	int pid;
	int burstTime;
	int arrivalTime;
	int remainingTime;
	int finishTime;
	int turnaroundTime;
	int waitingTime;
	int responseTime = -1;
};

//wait turnaround repsonse
vector <double> OC;


bool AT(const pcb& a, const pcb& b) {

	return a.arrivalTime < b.arrivalTime;
};


void SRTF(vector <pcb> processes) {

	sort(processes.begin(), processes.end(), AT);
	
	vector <pcb> temp;
	

	
	int cycleTime = 0;
	int sp = 0; //index of the shortest process
	bool process_available = false; 

	int minTime = INT_MAX;
	int size = processes.size();

	while (temp.size() != size) {

		//check the shortest time in accordance with the arrival time
		for (int i = 0; i < processes.size(); i++) {
			if (processes[i].arrivalTime <= cycleTime 
				&& processes[i].remainingTime < minTime) {

				minTime = processes[i].remainingTime;
				sp = i;

				process_available = true;
			}
		}
		
		//if there is available process during this clock cycle
		if (process_available == false) {
			cycleTime++;
			continue;
		}

		if (processes[sp].responseTime == -1) {
			processes[sp].responseTime = cycleTime - processes[sp].arrivalTime;
		}

		processes[sp].remainingTime--;
		minTime = processes[sp].remainingTime;
		
		if (processes[sp].remainingTime == 0) {
			
			processes[sp].finishTime = cycleTime + 1;
			temp.push_back(processes[sp]);
			vector<pcb>::iterator it = processes.begin() + sp;

			processes.erase(it);
			minTime = INT_MAX;
		}
		cycleTime++;
	}

	processes = temp;


	int totalTurnaroundTime = 0;
	int totalWaitingTime = 0;
	int totalResponseTime = 0;

	/*
	TurnAround Time =  finishTime - arrivalTime
	Waiting Time = Turn Around Time - burstTime
	Response Time is the time when the process gets selected the first time
	*/
	
	cout << "Pid  AT\tBT\tCT\tTAT\tWT\tRT" << endl;
	for (int i = 0; i < processes.size(); i++) {
		cout << processes[i].pid << "\t";
		cout << processes[i].arrivalTime << "\t";
		cout << processes[i].burstTime << "\t";
		cout << processes[i].finishTime << "\t";
		processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
		cout << processes[i].turnaroundTime << "\t";
		processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
		cout << processes[i].waitingTime << "\t";
		cout << processes[i].responseTime;

		cout << endl;
		
		totalTurnaroundTime += processes[i].turnaroundTime;
		totalWaitingTime += processes[i].waitingTime;
		totalResponseTime += processes[i].responseTime;
	}


	cout << "Average Waiting Time= " << (float)totalWaitingTime / processes.size() << endl;
	cout << "Average Turnaround Time= " << (float)totalTurnaroundTime / processes.size() << endl;
	cout << "Average Response Time= " << (float)totalResponseTime / processes.size() << endl;

}

int main() {
	vector<pcb> p(5);

	for (int i = 0; i < p.size(); i++)
	{
		p[i].pid = i;

		p[i].burstTime = 1 + (rand() % 10);

		p[i].arrivalTime = 0 + (rand() % 10);
	}



	SRTF(p);

	return 0;
}

