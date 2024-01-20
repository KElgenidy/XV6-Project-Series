#include <iostream>
#include <algorithm>
#include <queue> 
using namespace std; 

struct process 
{
    int pid; 
    int arrivalTime; 
    int burstTime; 
    int finishTime;    
    int btSum;      
    int remTime;           //remaining time for RR 
    int turnaroundTime; 
    int waitingTime; 
    int responseTime; 
}; 

const int n=10; 
int timeQuantum = 5; 
process p[n];
 

bool sortFcfs(process p, process p1)   //comparator function that's passed as 3rd parameter in sort() function  
{
    return (p.arrivalTime < p1.arrivalTime); 
}

void roundRobin()
{
    double totalTurnaround = 0; 
    double totalWaiting = 0;
    double totalResponse = 0;
    int cycleTime = 0; 
    int done = 0; 


    sort(p, p+n, sortFcfs); 
    p[0].waitingTime=0;                     
    p[0].responseTime=0;   
    
    for(int i=0; i<n; i++) 
      {  cout<<"Process No.: "<< p[i].pid<<", Arrival Time: " << p[i].arrivalTime << ", Burst Time: "<< p[i].burstTime<<endl;
        
        p[i].remTime = p[i].burstTime;   
      }
      
    cout<<endl<<endl; 

    while(done < n)
    {
        for(int i=0; i<n; i++)
        {
            if(p[i].remTime > 0)
            {
    
                if(p[i].remTime <= timeQuantum)   
                {
                    done ++; 
                    cycleTime += p[i].remTime;
                    p[i].finishTime = cycleTime;
                     
                     for(int j=1; j<=i; j++)
                         p[i].btSum+=p[i-j].remTime;
                    
                    p[i].turnaroundTime = p[i].finishTime - p[i].arrivalTime; 
                    p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime; 
                    p[i].responseTime = p[i].btSum - p[i].arrivalTime; 
                    
                    
                    totalWaiting += p[i].waitingTime; 
                    totalTurnaround += p[i].turnaroundTime;
                    totalResponse +=p[i].responseTime;
                   
                    p[i].remTime = 0; 
                
                }
            
                else if(p[i].remTime > timeQuantum)
                {
                    cycleTime += timeQuantum; 
                    p[i].remTime = p[i].remTime - timeQuantum;
         
                }
            
            }
        }
    
    }
    
    cout<<totalWaiting; 
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

        p[i].arrivalTime = 0;
    }

    roundRobin(); 
    return 0;
}