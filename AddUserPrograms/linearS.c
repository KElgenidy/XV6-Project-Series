#include "types.h"
#include "stat.h"
#include "user.h"
//#include <stdio.h> 
//#include <stdlib.h>

int LINEAR_SEARCH(int inp_arr[], int size, int val) 
{ 
	 
	for (int i = 1; i < size; i++) 
		if (inp_arr[i] == val) 
			return i; 
	return -1; 
} 


int main(int argc, char *argv[]) 
{ 
	//int arr[] = { 10, 20, 30, 40, 50, 100, 0 }; 
	int *data;
	int size = argc - 2;
	int key = 0;
	data = (int*) malloc(size * sizeof(int));
	
	for(int i = 1; i < size; ++i){
		if(argv[i][0] == '-')
			*(data + i) = -atoi2(&argv[i][1]);
		else
			*(data + i) = atoi(argv[i]);
		
	}
	if(argv[argc-1][0] == '-')
		key = -atoi2(&argv[argc-1][1]); 
	else
		key = atoi(argv[argc-1]);
		
		
	
	
	int res = LINEAR_SEARCH(data, size, key); 
	if (res == -1)
	printf(1,"ELEMENT NOT FOUND!!\n");
    else
    printf(1,"Item is present at index %d\n", res);
    
	exit();
	return 0;
}
