#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "util.h"

#define DEBUG

typedef struct Node{
	int x;
	int pos;
	int h;
}Node;

// return negtive if nodeA is smaller than nodeB
int compareNode(Node* nodeA, Node* nodeB){
	if(nodeA->x != nodeB->x){
		return nodeA->x - nodeB->x;
	}else{
		return nodeA->h * nodeA->pos - nodeB->h * nodeB->pos;
	}
}

// quickSort
void quickSort(Node* pNodes, int i, int j, int(*compare)(Node* nodeA, Node*nodeB)){
	if(i >= j)
		return;

	int k = rand() % (j-i+1) + i;
	Node keyNode = pNodes[k];
	pNodes[k] = pNodes[i];
	int ipos = i;
	int jpos = i+1;
	while(jpos <= j){
		if(compare(&keyNode, &pNodes[jpos]) > 0){
			ipos++;
			Node tmp = pNodes[ipos];
			pNodes[ipos] = pNodes[jpos];
			pNodes[jpos] = tmp;
		}
		jpos++;
	}
	pNodes[i] = pNodes[ipos];
	pNodes[ipos] = keyNode;

	// recursive
	quickSort(pNodes, i, ipos-1, compare);
	quickSort(pNodes, ipos+1, j, compare);
}

/*=============================== maxHeap ==========================*/
void maxHeapify(int* arr, int length, int i){
	int left = 2*i;
	int right = 2*i+1;

	int maxPos = i;
	if(left < length && arr[left] > arr[maxPos]){
		maxPos = left;
	}
	
	if(right < length && arr[right] > arr[maxPos]){
		maxPos = right;
	}

	if(maxPos != i){
		int tmp = arr[i];
		arr[i] = arr[maxPos];
		arr[maxPos] = tmp;
		maxHeapify(arr, length, maxPos);
	}
}

void buildMaxHeap(int* arr, int length){
	for(int i = (length-2)/2; i >= 0; i--)
		maxHeapify(arr, length, i);
}

int maximumMaxHeap(int* arr){
	return arr[0];
}

int maxExtractMaxHeap(int** arr, int length){
	if(length < 1)
		return -1;

	int max = **arr;
	**arr = *(*arr + length-1);
	int* tmp = (int*) realloc(*arr, sizeof(int) * (length-1));
	*arr = tmp;
	maxHeapify(tmp, length-1, 0);

	return max;
}

void increaseKeyMaxHeap(int* arr, int length, int i, int key){
	if(key < arr[i])
		return;

	arr[i] = key;
	int iParent = (i-1)/2;
	while(i > 0 && arr[i] > arr[iParent]){
		arr[i] = arr[iParent];
		arr[iParent] = key;
		
		i = iParent;
		iParent = (i-1)/2;
	}
}

void insertMaxHeap(int** arr, int length, int key){
	int* tmp = (int*) realloc(*arr, sizeof(int) * (length+1));
	*arr = tmp;
	tmp[length] = INT_MIN;

	increaseKeyMaxHeap(tmp, length+1, length, key);
#ifdef DEBUG
	printArr(tmp, length+1, length+1);
#endif
}

void removeMaxHeap(int** arr, int length, int key){
	int i;
	for(int i = 0; i < length; i++){
		if(key == *(*arr+i)){
			*(*arr+i) = *(*arr+length-1);
			break;
		}
	}
	
	int* tmp = (int*) realloc(*arr, sizeof(int) * (length-1));
	*arr = tmp;
	maxHeapify(tmp, length-1, i);
#ifdef DEBUG
	printArr(tmp, length-1, length-1);
#endif
}

// skyline 
int** getSkyline(int** buildings, int buildingsRowSize, int buildingsColSize, int* returnSize) {
	int length = buildingsRowSize * 2;
	Node* nodes = (Node*) malloc(sizeof(Node) * length);
	for(int i = 0; i < buildingsRowSize; i++){
#ifdef DEBUG
	//	printf("[%d,%d,%d]\n", buildings[i][0], buildings[i][1], buildings[i][2]);
#endif
		// left point of segment 
		nodes[2*i].x = buildings[i][0];
		nodes[2*i].pos = -1;
		nodes[2*i].h = buildings[i][2];
		// right point of segment
		nodes[2*i+1].x = buildings[i][1];
		nodes[2*i+1].pos = 1;
		nodes[2*i+1].h = buildings[i][2];
	}
	
	// sort nodes
	quickSort(nodes, 0, length-1, compareNode);

	// init return
	int** returnKeyPoints = NULL;
	*returnSize = 0;

	// get skyline
	int* pMaxHeap = (int*) malloc(sizeof(int));
	pMaxHeap[0] = 0;
	int sizeMaxHeap = 1;
	int preH = 0;
	for(int i = 0; i < length; i++){
#ifdef DEBUG
		printf("[%d,%d,%d]\n", nodes[i].x, nodes[i].pos, nodes[i].h);
#endif

		if(nodes[i].pos == -1){
			insertMaxHeap(&pMaxHeap, sizeMaxHeap, nodes[i].h);
			sizeMaxHeap++;
		} else {
			removeMaxHeap(&pMaxHeap, sizeMaxHeap, nodes[i].h);
			sizeMaxHeap--;
		}

		int curH = maximumMaxHeap(pMaxHeap);
		if(preH != curH){
			if(returnKeyPoints != NULL){
				returnKeyPoints = (int**) realloc(returnKeyPoints, sizeof(int*) * (*returnSize+1));
				returnKeyPoints[*returnSize] = (int*) malloc(sizeof(int)*2);
				returnKeyPoints[*returnSize][0] = nodes[i].x;
				returnKeyPoints[*returnSize][1] = curH;
				(*returnSize)++;
			}else{
				returnKeyPoints = (int**) malloc(sizeof(int*) * (*returnSize+1));
				returnKeyPoints[*returnSize] = (int*) malloc(sizeof(int)*2);
				returnKeyPoints[*returnSize][0] = nodes[i].x;
				returnKeyPoints[*returnSize][1] = curH;
				(*returnSize)++;
			}
			preH = curH;
		}
	}

	for(int i = 0; i < *returnSize; i++){
		for(int j = 0; j < 2; j++)
			printf("%d\t", returnKeyPoints[i][j]);
		printf("\n");
	}

	free(pMaxHeap);		
	return returnKeyPoints;
}

int main(int argc, char** argv){
//	int buildings[5][3] = {{2,9,10}, {3,7,15}, {5,12,12}, {15,20,10}, {19,24,8}};
//	int buildingsRowSize = 5;
//	int buildingsColSize = 3;
//	int* p_buildings[5] = {buildings[0], buildings[1], buildings[2], buildings[3], buildings[4]};
//	int** ip_buildings = p_buildings;
	
	int buildings[4][3] = {{0,3,3}, {1,5,3}, {2,4,3}, {3,7,3}};
	int buildingsRowSize = 4;
	int buildingsColSize = 3;
	int* p_buildings[4] = {buildings[0], buildings[1], buildings[2], buildings[3]};
	int** ip_buildings = p_buildings;

	int returnSize;
	getSkyline(ip_buildings, buildingsRowSize, buildingsColSize, &returnSize);
	return 0;	
}
