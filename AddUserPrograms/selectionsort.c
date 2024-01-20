// Selection sort in C
#include "types.h"
#include "stat.h"
#include "user.h"
//#include <stdio.h>
//#include <stdlib.h>

// function to swap the the position of two elements
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectionSort(int array[], int size) {
  for (int step = 1; step < size - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < size; i++) {

      // To sort in descending order, change > to < in this line.
      // Select the minimum element in each loop.
      if (array[i] < array[min_idx])
        min_idx = i;
    }

    // put min at the correct position
    swap(&array[min_idx], &array[step]);
  }
}

// function to print an array
void printArray(int array[], int size) {
  for (int i = 1; i < size; ++i) {
    printf(1,"%d  ", array[i]);
  }
  printf(1,"\n");
}



// driver code
int main(int argc, char *argv[]) {
  //int data[] = {20, 12, 10, 15, 2};
  
  int *data;
  int size = argc;
  
  data = (int*) malloc(size * sizeof(int));
	
	for(int i = 1; i < size; ++i){
		
		if(argv[i][0] == '-')
			*(data + i) = -atoi2(&argv[i][1]);
		else
			*(data + i) = atoi(argv[i]);
		
	}
  
  
  selectionSort(data, size);
  printf(1, "Sorted array in Acsending Order using SelectionSort:\n");
  printArray(data, size);
  exit();
  return 0;
}
