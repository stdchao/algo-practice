#include <stdlib.h>
#include <limits.h>
#include "../leetcode/util.h"

#ifndef __HEAP_H__
#define __HEAP_H__

void maxHeapify(int* arr, int length, int i);

void buildMaxHeap(int* arr, int length);

int maximumMaxHeap(int* arr);

int maxExtractMaxHeap(int* arr, int length);

void increaseKeyMaxHeap(int* arr, int length, int i, int key);

void insertMaxHeap(int** arr, int length, int key);

#endif
