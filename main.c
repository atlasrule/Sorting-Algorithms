/* 2019
 * Collection of sorting algorithms I've implemented.
 *
 * Includes:
 *  Bubble Sort
 *  Selection Sort
 *  Insertion Sort
 *  Binary Insertion Sort
 *  Merge Sort
 *  Bogo Sort
 *
 * Plus:
 *  Shuffle
 *  Binary Search
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


/*
=================
Swap
Swaps two values.
Time complexity: O(1)
Space complexity: O(1)
=================
*/
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}


/*
=================
Bubble-Sort
Bubble Sorts given array.
Best case: O(n*logn)
Average case: O(n*logn)
Worst case: O(n*n)
Space complexity: O(1)
Stability: Stable
=================
*/
void bubleSort(int A[], int size) {
  for (int i=size-1; i>0; i--) {
    for (int j=0; j<i; j++){
      if ( A[j+1] < A[j] ) {
        swap(&A[j+1], &A[j]);
      }
    }
  }
}


/*
=================
Selection-Sort
Selection Sorts given array.
Best case: O(n*logn)
Average case: O(n*logn)
Worst case: O(n*n)
Space complexity: O(1)
Stability: Not stable
=================
*/
void selectionSort(int A[], int size) {
  int i, j, minIdx;
  for (i=0; i<size-1; i++) {
    minIdx = i;
    for (j=i+1; j<size; j++) {
      if (A[j] < A[minIdx]) {minIdx = j;}
      
    }
    swap(&A[i], &A[minIdx]);
  }
}


/*
=================
Insertion-Sort
Insertion Sorts given array.
Best case: O(n)
Average case: O(n*n)
Worst case: O(n*n)
Space complexity: O(1)
Stability: Stable
=================
*/
void insertionSort(int A[], int size) {
  int i, j, key;

  for (i=1; i<size; i++) {
    key = A[i];
    j = i-1;

    while(j>=0 && A[j]>key) {
      A[j+1] = A[j];
      j--;
    }
    A[j+1]=key;
  }
}


/*
=================
Binary-Search
Finds first occured index of given integer with binary search. Divide and conquer.
Input array must be sorted in non-descending order
Returns -1 if query is not exist in the input array.
Time Complexity:  O(lg(n)+k) =  O(lg(n))
=================
*/
int binary(int A[], int query, int left, int right) {
  int mid = (right + left) / 2;
  int midNum = A[mid];
  int index = -1;

  if (right < left) {
    return -1;
  }
  
  if (midNum == query) {
    
    int i = mid;

    if (i>1) {
      while (A[i-1] == query) {
        i--;
      }
    }
    
    return i;
  }
  
  else if (midNum > query) {
    index = binary(A, query, left, mid-1);
  }
  
  else if (midNum < query) {
    index = binary(A, query, mid+1, right);
  }

  return index;
}


/*
=================
Binary-Insertion-Sort
Binary Insertion Sorts given array with binary searching.
Time Complexity:  O(lg(n)+k) =  O(lg(n))
Best case: O(n*logn)
Average case: O(n*n)
Worst case: O(n*n)
Space complexity: O(logn) (recursive variant)
Stability: Stable
=================
*/
int newIndex(int A[], int query, int left, int right) {
  int mid = (right + left) / 2;
  int midNum = A[mid];
  int index = -1;

  if (left == right) {
    
    if (query < A[left]) {
      return left;
    }
      
    else {
      return left+1;
    }
    
  }

  if (left > right) {
    return left;
  }

  if (query >= A[mid-1] && query <= midNum) {
    
    int i=mid;
    int index = mid;

    if (i>1) {
      while (A[i-1] == query) {
        i--;
      }
    }
    
    
    return index;
  }

  if (midNum > query) {
    index = newIndex(A, query, left, mid-1);
  }
  
  else if (midNum < query) {
    index = newIndex(A, query, mid+1, right);
    
  }

  return index;
}

void binaryInsertionSort(int A[], int size) {
  int i, j, key;
  
  if (A[1] < A[0]) { swap(&A[0], &A[1]); }

  for (i=1; i<size; i++) {
    key = A[i];

    if (A[i] < A[i-1]) {
      
      int index = newIndex(A, key, 0, i+1);
      
      if (index != -1) {
        for (int j = i-1; j>index-1; j--) {
          A[j+1] = A[j];
        }
        
        A[index] = key;
      }
    }
    
  }
}


/*
=================
Merge-Sort
Merge Sorts given array.
Best case: O(n*logn)
Average case: O(n*logn)
Worst case: O(n*logn)
Space complexity: O(n)
Stability: Stable
=================
*/
void merge(int A[], int left, int mid, int right) {
  int lenOne = mid - left+1;
  int lenTwo = right - mid;
  int leftPart[lenOne];
  int rightPart[lenTwo];

  // Seperating the part into two parts physically
  for (int i=0; i<lenOne; i++) {
    leftPart[i] = A[left+i];
  }
  for (int j=0; j<lenTwo; j++) {
    rightPart[j] = A[mid+1+j];
  }

  int i=0;
  int j=0;
  int k=left;
  while (i<lenOne && j<lenTwo) {
    // Get the smallest between same indexes of
    // lefts and rights to merge as sorted
    if (leftPart[i] <= rightPart[j]) {
      A[k] = leftPart[i];
      i++;
    }
    else {
      A[k] = rightPart[j];
      j++;
    }
    k++;
  }
  
  // Merge rest of the left or right parts
  for (; i<lenOne; i++) {
    A[k] = leftPart[i];
    k++;
  }
  for (; j<lenTwo; j++) {
    A[k] = rightPart[j];
    k++;
  }
  
}

void mergeSort(int A[], int left, int right) {
  
  if (right - left > 0) {

    int mid = left + (right-left) / 2;
  
    mergeSort(A, left, mid);
    mergeSort(A, mid+1, right);
    merge(A, left, mid, right);
  }
}


// //// Tim-Sort
// void timSort(int A[], int size) {
// }

/*
//// Heap-Sort
void heapSort(int A[], int size) {
}
*/

/*
//// Quick-Sort
void quickSort(int A[], int size) {
}
*/

/*
//// Multithreaded Quick-Sort
void quickSortMultithread(int A[], int size) {
}
*/

/*
//// Counting-Sort
void countingSort(int A[], int size) {
}
*/

/*
//// Radix-Sort
void radixSort(int A[], int size) {
}
*/

/*
//// Bucket-Sort
void bucketSort(int A[], int size) {
}
*/



/*
=================
Bogo-Sort
Bogo Sorts given array. See: Infinite monkey theorem
Best case: O(n)
Average case: O((n-1)*n!)
Worst case: Infinite
Stability: Not stable
=================
*/
void shuffle(int A[], int size) {
  int r, i;
  for (i=size-1; i>=0; i--) {
    r = rand() % (i+1);
    swap(&A[i], &A[r]);
  }
}

void bogoSort(int A[], int size) {
  int i; bool sorted=false;
  while ( sorted == false ) {
    sorted = true;
    shuffle(A, size);
    //Check if sorted
    for (i=0; i < size-1; i++) {

      if ( A[i] > A[i+1]) {
        sorted = false;
        break;
      }
    }
  }
}


/*
=================
Reverse
Reverses given array in n/2 steps.
Time complexity: O(n)
Space complexity: O(1)
=================
*/
void reverse(int A[], int size) {
  for (int i=0; i < size/2; i++) {
    swap(&A[i], &A[size-1-i]);
  }
}


/*
=================
Print Array
Prints given array in n steps.
Time complexity: O(n)
=================
*/
void printArray(int A[], int size) {
  printf("[");
  for (int i=0; i<size; i++) {
    printf("%d", A[i]);
    if (i == size-1) { printf("]"); }
    else { printf(","); }
  }
}


/*
=================
Randomly Fill Array
Fills given array with integers within given range in n steps.
Time complexity: O(n)
=================
*/
void randomlyFillArray(int A[], int min, int max, int size) {
  time_t t;
  srand((unsigned) time(&t));
  for (int i=0; i<size; i++) {
    A[i] = (rand() % (max-min)) + min;
  }
}

int main() {
  const int n = 10;
  int arr[n];

  randomlyFillArray(arr, 0, 100, n);
  
  printf("\n\n\n Unsorted array:\n\n");
  printArray(arr, n);

  // bubleSort(arr, n);
  // printf("\n\n\n\n Bubble-Sorted:\n\n");
  // printArray(arr, n);

  // selectionSort(arr, n);
  // printf("\n\n\n\n Selection-Sorted:\n\n");
  // printArray(arr, n);

  // insertionSort(arr, n);
  // printf("\n\n\n\n Insertion-Sorted:\n\n");
  // printArray(arr, n);
  
  // binaryInsertionSort(arr, n);
  // printf("\n\n\n\n Binary-Insertion-Sorted:\n\n");
  // printArray(arr, n);

  mergeSort(arr, 0, n-1);
  printf("\n\n\n\n Merge-Sorted:\n\n");
  printArray(arr, n);
  
  // bogoSort(arr, n);
  // printf("\n\n\n\n Bogo-Sorted:\n\n");
  // printArray(arr, n);
  
  // reverse(arr, n);
  // printf("\n\n\n\n Reversed:\n\n");
  // printArray(arr, n);

  // int search_value = 16;
  // int index = binary(arr, search_value, 0, n+1);
  // if (index == -1) {
  //   printf("\n\nValue %d is not in the array.\n\n", search_value);
  // }
  // else {
  //   printf("\n\nValue %d found at %d.\n\n", search_value, index);
  // }
  
  return 0;
}