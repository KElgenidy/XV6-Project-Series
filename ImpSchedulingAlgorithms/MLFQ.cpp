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
process Q1[n], Q2[n]; 

bool sortFcfs(process p, process p1)   //comparator function that's passed as 3rd parameter in sort() function  
{
    return (p.arrivalTime < p1.arrivalTime); 
} 

bool BT(process p, process p1)   //comparator function that's passed as 3rd parameter in sort() function  
{
    return (p.burstTime < p1.burstTime); 
}

void MLFQ()
{
    double totalTurnaround = 0; 
    double totalWaiting = 0; 
    double totalResponse = 0; 
     double totalTurnaround1 = 0; 
    double totalWaiting1 = 0; 
    double totalResponse1 = 0; 
     double totalTurnaround2 = 0; 
    double totalWaiting2 = 0; 
    double totalResponse2 = 0; 
    int j = 0;
    int i;
    
    
	sort(Q1, Q1 + n, BT);
	Q1[0].waitingTime=0;                   
    Q1[0].responseTime=0;                 
    Q1[0].finishTime = 0 + Q1[0].burstTime;
    
    cout<<"Queue 1: "<<endl; 
    for( i=0; i<n; i++) 
      {  cout<<"Process No.: "<< Q1[i].pid<<", Arrival Time: " << Q1[i].arrivalTime << ", Burst Time: "<< Q1[i].burstTime<<endl;
        
      }
      
       for( i=1; i<n; i++)
    {
        Q1[i].waitingTime=0; 
        Q1[i].responseTime=0;
        
        Q1[i].finishTime = Q1[i-1].finishTime + Q1[i].burstTime;  
    
        for(int count=1; count<=i; count++)
            Q1[i].btSum+=Q1[i-count].burstTime;     
    }
      
      int count = 0; 
      int start; 
      
      for(i=0; i<n; i++)
      {
          count++; 
          if(count <=5){
            Q1[i].turnaroundTime = Q1[i].finishTime - Q1[i].arrivalTime; 
            Q1[i].waitingTime = Q1[i].turnaroundTime - Q1[i].burstTime;
            
            Q1[i].responseTime += Q1[i].btSum - Q1[i].arrivalTime; 
            
            totalWaiting1 += Q1[i].waitingTime; 
            totalTurnaround1 += Q1[i].turnaroundTime;
            totalResponse1 += Q1[i].responseTime; 
            
          }
          
          if(count > 5)
          {
                start = Q1[4].finishTime;  
                Q2[j].burstTime = Q1[i].burstTime; ;
                Q2[j].pid = Q1[i].pid; 
                Q2[j].arrivalTime = Q1[i].arrivalTime; 
                
                j++;
          }
      } 
      
     sort(Q2, Q2+j, sortFcfs);
     Q2[0].finishTime = start + Q2[0].burstTime; 
     
       cout<<"Queue 2: "<<endl; 
    for( i=0; i<j; i++) 
      {  cout<<"Process No.: "<< Q2[i].pid<<", Arrival Time: " << Q2[i].arrivalTime << ", Burst Time: "<< Q2[i].burstTime<<endl;
        
      }
      
     for(i=1; i<j; i++)
      {
           Q2[i].waitingTime=0; 
         Q2[i].responseTime=0;
        
        Q2[i].finishTime = Q2[i-1].finishTime + Q2[i].burstTime; 
        
          for(int count=1; count<=i; count++)
            Q2[i].btSum+=Q2[i-count].burstTime;
      }
      
      for(int i=0; i<j; i++){
           
          Q2[i].turnaroundTime = Q2[i].finishTime - Q2[i].arrivalTime;  
        Q2[i].waitingTime = Q2[i].turnaroundTime - Q2[i].burstTime;
        Q2[i].responseTime = Q2[i].btSum - Q2[i].arrivalTime;
        
         totalWaiting2 += Q2[i].waitingTime; 
        totalTurnaround2 += Q2[i].turnaroundTime;
        totalResponse2 += Q2[i].responseTime;
      }
      
    
      totalWaiting = totalWaiting1+totalWaiting2; 
      totalTurnaround = totalTurnaround1 + totalTurnaround2; 
      totalResponse = totalResponse1 + totalResponse2;
      
    cout<< "Average Waiting Time= "<< (totalWaiting/n) << endl; 
    cout<< "Average Turnaround Time= "<< (totalTurnaround/n) <<endl;
    cout<< "Average Response Time= "<< (totalResponse/n) <<endl;
}  

int main()
{
  
    for (int i=0; i<n; i++)
    {
        Q1[i].pid = i;

        Q1[i].burstTime = 1 + (rand() % 10);

        Q1[i].arrivalTime = 0 + (rand() % 10);
    }
    MLFQ(); 
    return 0;
}