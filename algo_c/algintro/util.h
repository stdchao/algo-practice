#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* public functions */

// get current time
uint64_t getCurrentMilliSec();

// calculate runtime
void startRuntime(char* str);
void endRuntime(char* str);

// debug print for array
void printArr(int* arr, int length, int process);
void printSubArr(int* arr, int i, int j);


// generate random array
void generateRandom(int* randomArr, int length, int low, int high);

