#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <time.h>

unsigned long long int sum(unsigned int n)
{
	unsigned long long int s = 0; 
	
	for(int i = 1; i <= n; i++)
		s+= i;
}

unsigned long long int parallel_sum_pipes(unsigned int n_proc, unsigned int n) 
{

    int parent_pid = getpid();
    pid_t child_pid, wpid;
    int status = 0;
    unsigned long long int s = 0;
    unsigned long long int inpipe_sum = 0;
    
    int interval = n / n_proc;
    int start = 1;
    int end = interval;
    
     int p[n_proc][2];
    for(int i = 0; i < n_proc; i++)
    {
    	if( pipe(p[i]) == -1){
    		printf("Failed to create pipe");
    		exit(0);
    	}
    }

 
    for(unsigned int i = 0; i < n_proc; i++){
    	
    	if(getpid() == parent_pid && (child_pid = fork()) == 0)
    	{
    		
    		if(i+1 == n_proc)
    		{
    		
    			end = n;
    		}
    
    		inpipe_sum = 0;
    		for(start; start <= end; start++){
    
        		inpipe_sum += start;
        	}
        
		close(p[i][0]);
		write(p[i][1], &inpipe_sum, sizeof(unsigned long long int));
		
    	}
    	
    	start = end + 1; 
    	end=end+interval;
    	
    }
    
	
	if(getpid() == parent_pid)
    	{
	    	while((wpid = wait(&status)) > 0);
		
		    for(unsigned int i = 0; i < n_proc; i++){
			read(p[i][0], &inpipe_sum, sizeof(unsigned long long int));
		      s += inpipe_sum;
		      close(p[i][0]);
		      close(p[i][1]);
		      
		    }
	}
	
	else exit(0);
      //return s;
    
}



int main()
{
	unsigned int n; 
	unsigned int n_proc = 3 ; 

	
	clock_t t1; 
	clock_t t2;
	
	double time1, time2;
	
	for(unsigned int n = 1; n < 1000000; n+=5000)
	{
	
			t1 = clock();
			sum(n); 
			t1 = clock() - t1;
			 time1 = ((double) t1)/CLOCKS_PER_SEC;
		

			t2 = clock();
			parallel_sum_pipes(n_proc, n); 
			t2 = clock() - t2;
			 time2 = ((double) t2)/CLOCKS_PER_SEC;

	}
		
		printf("%u %f %f \n", n, time1, time2); 
		
}
	
	
