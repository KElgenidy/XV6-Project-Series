#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>

unsigned long long int parallel_sum_mmap(unsigned int n_proc, unsigned int n)
{
	unsigned long long int s = 0; 
	unsigned long long int partial = 0; 
	int start; 
	int end = 1; 
	unsigned int interval = n/n_proc; 

	unsigned long long int *shared = mmap(NULL, sizeof(unsigned long long int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0,0);
	
	if(shared == MAP_FAILED){
		printf("Mapping Failed\n"); 
		return 1; 
	}
	
	for(unsigned int i = 1; i <= n_proc; i++){
		start = end; 
		end+=interval;
		
		if(i == n_proc){
			end = n + 1; 
		}
		
		if(fork() == 0){
			for(start; start < end; start++){
				partial+=start; 
				shared[i] = partial; 		
			}
				
			printf("Partial Sum %d = %llu\n", i, shared[i]); 
			exit(0);
		}
		
		else{
			wait(NULL);  
			s+= shared[i]; 			
		}	
	}
	
	int err = munmap(shared, sizeof(unsigned long long int)); 
	
	if(err != 0){
		printf("Unmapping Failed\n"); 
		return 1;
	}
	
	return s; 	
}

int main()
{
	unsigned int n = 44; 
	unsigned int n_proc = 3; 
	unsigned long long int sum = parallel_sum_mmap(n_proc, n); 
	printf("Final Sum = %llu\n", sum); 
}
	
	
	
