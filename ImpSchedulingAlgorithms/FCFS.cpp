// Equations Used
// Turnaround Time = Finish Time - Arrival Time
// Waiting Time = Turnaround Time - Burst time
// Response Time = Sum of Prev Burst Times - Arrival Time 

#include <iostream>
#include <algorithm> 
using namespace std; 

struct process 
{
    int pid; 
    int arrivalTime; 
    int burstTime; 
    int finishTime;    
    int btSum;            //used to calculate response time 
    int turnaroundTime; 
    int waitingTime; 
    int responseTime; 
}; 

const int n=10; 
process p[n]; 

bool sortFcfs(process p, process p1)   //comparator function that's passed as 3rd parameter in sort() function  
{
    return (p.arrivalTime < p1.arrivalTime); 
}

void fcfs()
{
    double totalTurnaround = 0; 
    double totalWaiting = 0;
    double totalResponse = 0;
    
    sort(p, p+n, sortFcfs); 

    p[0].waitingTime=0;                     //wait time for 1st process is always 0
    p[0].responseTime=0;                    //response time for 1st process is always 0
    p[0].finishTime = 0 + p[0].burstTime;   //finish time for 1st process is always equal to its burst time

    for(int i=0; i<n; i++) 
        cout<<"Process No.: "<< p[i].pid<<", Arrival Time: " << p[i].arrivalTime << ", Burst Time: "<< p[i].burstTime<<endl;  
    
    cout<<endl<<endl;

    for(int i=1; i<n; i++)
    {
        p[i].waitingTime=0; 
        p[i].responseTime=0;
        
        p[i].finishTime = p[i-1].finishTime + p[i].burstTime;  //finish time of prev process + burst time of current process
    
        for(int count=1; count<=i; count++)
            p[i].btSum+=p[i-count].burstTime;     //sums burst times of prev processes - used to calculate response time
    }

    for(int i=0; i<n; i++)
    {
        p[i].turnaroundTime = p[i].finishTime - p[i].arrivalTime;     //calculates turnaround time for each process
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;      //calculates wait time for each process
        p[i].responseTime += p[i].btSum - p[i].arrivalTime;           //calculates response time for each process 
    
        totalWaiting += p[i].waitingTime; 
        totalTurnaround += p[i].turnaroundTime;
        totalResponse += p[i].responseTime; 
    } 
    
    cout<< "Average Waiting Time= "<< (totalWaiting/n) << endl; 
    cout<< "Average Turnaround Time= "<< (totalTurnaround/n) <<endl; 
    cout<< "Average Response Time= "<< (totalResponse/n) <<endl;

}

int main()
{
    for (int i=0; i<n; i++)
    {
        p[i].pid = i;

        p[i].burstTime = 1 + (rand() % 10);

        p[i].arrivalTime = 0 + (rand() % 10);
    }
    fcfs(); 
    return 0;
}