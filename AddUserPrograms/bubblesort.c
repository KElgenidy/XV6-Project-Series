// Bubble sort in C
#include "types.h"
#include "stat.h"
#include "user.h"
//#include <stdio.h>
//#include <stdlib.h>

// perform the bubble sort
void bubbleSort(int array[], int size) {

  // loop to access each array element
  for (int step = 0; step < size - 1; ++step) {
      
    // loop to compare array elements
    for (int i = 1; i < size - step - 1; ++i) {
      
      // compare two adjacent elements
      // change > to < to sort in descending order
      if (array[i] > array[i + 1]) {
        
        // swapping occurs if elements
        // are not in the intended order
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}

// print array
void printArray(int array[], int size) {
  for (int i = 1; i < size; ++i) {
    printf(1, "%d  ", array[i]);
  }
  printf(1,"\n");
}


int main(int argc, char *argv[]) {
  //int data[] = {-2, 45, 0, 11, -9};
  
    int *data;
  int size = argc;
  
  data = (int*) malloc(size * sizeof(int));
	
	for(int i = 1; i < size; ++i){
		
		if(argv[i][0] == '-')
			*(data + i) = -atoi2(&argv[i][1]);
		else
			*(data + i) = atoi(argv[i]);
		
	}
  
  bubbleSort(data, size);
  
  printf(1, "Sorted Array in Ascending Order using BubbleSort:\n");
  printArray(data, size);
  exit();
  return 0;
}
