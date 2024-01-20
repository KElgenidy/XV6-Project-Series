#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


unsigned long long int sum_t;
struct thread_data{
	int i;
	int s;
	int e;
	int n;
	int num_thread;
};

pthread_mutex_t mutex1;
unsigned long long int temp;

void * threaded_sums(void* arg){

	struct thread_data *data = (struct thread_data *) arg;
	int partial = 0;
	if(data->i == data->num_thread)
	{
	
		data->e = data->n;
	}
	
	for(data->s; data->s <= data->e; data->s += 1){
		partial += data->s;
	}
	
	
	pthread_mutex_lock(&mutex1);
	sum_t += partial;
	if(data->i == data-> num_thread) temp = sum_t;
	pthread_mutex_unlock(&mutex1);
	
	return (void *)temp;
		
}

unsigned long long int parallel_sum_threads (unsigned int n_thread, unsigned int N) 
{

    int interval = N / n_thread;
    int start = 1;
    int end = interval;
    int ret;
    void *status;
    
    struct thread_data ta[n_thread];
    pthread_t threads[n_thread];
    
    for(int j = 0; j < n_thread; j++){
    
    	ta[j].i = j + 1;
    	ta[j].n = N;
    	ta[j].num_thread = n_thread;
    	ta[j].s = start;
    	ta[j].e = end;
    	ret = pthread_create(&threads[j], NULL, threaded_sums, (void *) &ta[j]);
    	if(ret != 0){
    		printf("Thread can't be created");
    	}
    	start = end + 1; 
    	end = end+interval;
    }
    for(int j = 0; j < n_thread; j++){
    	pthread_join(threads[j], &status);
    }
   
	
      return (unsigned long long int)status;
}
int main()
{
    unsigned int n = 10; 
    unsigned int n_thread = 5;
    unsigned long long int sum = parallel_sum(n_thread, n); 
    printf("Final sum = %llu\n", sum);
}
