#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"

/*******************************direct address table***************************/
typedef struct DatSlot{
	int key;
	int value;
} DatSlot;

typedef struct Dat{
	DatSlot** slots;
	int size;
} Dat;

void direct_address_init(Dat* dat, int size){
	dat->size = size;
	dat->slots = (DatSlot**) malloc(size * sizeof(DatSlot*));
}

int direct_address_search(Dat* dat, int key){
	if(dat->slots[key] == NULL)
		return -1;
	return dat->slots[key]->value;
}

void direct_address_insert(Dat* dat, int key, int value){
	if(dat->slots[key] == NULL)
		dat->slots[key] = (DatSlot*) malloc(sizeof(DatSlot));
	dat->slots[key]->key = key;
	dat->slots[key]->value = value;
}

void direct_address_delete(Dat* dat, int key){
	free(dat->slots[key]);
	dat->slots[key] = NULL;
}

void direct_address_test(){
	Dat dat;
	int size = 10;
	/* key{0-9} */
	direct_address_init(&dat, size);
	
	/* insert {key, value} */
	int key, value;
	for(int i = 0; i < 5; i++){
		srand(i);
		key = rand() % size;
		value = rand();
		direct_address_insert(&dat, key, value);
		printf("insert key-value {%d, %d} into table {%d, %d}\n", key, value, dat.slots[key]->key, dat.slots[key]->value);
	}

	/* search */
	printf("search key {%d} in table correspond value {%d}\n", key, direct_address_search(&dat, key));
	
	/* delete {key, value} */
	direct_address_delete(&dat, key);
	printf("delete key-value {%d, %d} from table and search result is {%d}\n", key, value, direct_address_search(&dat, key));
}

/************************************hash*************************************/
/*
 * point 1. find hash function minimize the collisions
 * point 2. fix collision cases
 **/
typedef struct Slot{
	int key;
	int value;
	struct Slot* nextSlot;
} Slot;

typedef struct ChainedHashTable{
	int size;
	Slot** slots;
} Cht;

void print_list(Slot* pSlot){
	printf("Head %p\n", pSlot);
	while(pSlot != NULL){
		printf("\t->{%d,%d,%p}\n", pSlot->key, pSlot->value, pSlot);
		pSlot = pSlot->nextSlot;
	}
	printf("\t->NULL\n");
}

int hash_generate_key(int key){
	return key % 5;
}

void chained_hashtable_init(Cht* cht, int size){
	cht->size = size;
	cht->slots = (Slot**) malloc(size * sizeof(Slot*));
	memset(cht->slots, 0, size * sizeof(Slot*));
}

int chained_hashtable_search(Cht* cht, int key){
	int genKey = hash_generate_key(key);
	// travel list
	Slot* pSlot = cht->slots[genKey];
	while(pSlot != NULL && pSlot->key != key){
		pSlot = pSlot->nextSlot;
	}

	if(pSlot == NULL)
		return -1;
	return pSlot->value;
}

void chained_hashtable_insert(Cht* cht, int key, int value){
	int genKey = hash_generate_key(key);
	Slot* head = cht->slots[genKey];
	Slot* pSlot = head;
	
	// check empty list
	if(head == NULL){
		Slot* newSlot = (Slot*) malloc(sizeof(Slot));
		newSlot->key = key;
		newSlot->value = value;
		newSlot->nextSlot = NULL;
		// insert head
		cht->slots[genKey] = newSlot;
		head = cht->slots[genKey];
		return;
	}
	
	// travel list
	while(pSlot->key != key && pSlot->nextSlot != NULL){
		pSlot = pSlot->nextSlot;
	}
	
	if(pSlot->key == key){
		// key exist, just change value
		pSlot->value = value;
	}else{
		Slot* newSlot = (Slot*) malloc(sizeof(Slot));
		newSlot->key = key;
		newSlot->value = value;
		newSlot->nextSlot = NULL;
		// insert not head
		pSlot->nextSlot = newSlot;
	}

#ifdef DEBUG
	print_list(head);
#endif
}

void chained_hashtable_delete(Cht* cht, int key){
	int genKey = hash_generate_key(key);
	Slot* head = cht->slots[genKey];
	Slot* pSlot = head;
	Slot* preSlot;

	// check empty list
	if(head == NULL)
		return;

	// travel list
	while(pSlot->key != key && pSlot->nextSlot != NULL){
		preSlot = pSlot;
		pSlot = pSlot->nextSlot;
	}
	
	if(pSlot->key == key){
		if(pSlot == head){
			// delete head key
			cht->slots[genKey] = pSlot->nextSlot;
			head = cht->slots[genKey];
			free(pSlot);
		}else{
			// delete not head key
			preSlot->nextSlot = pSlot->nextSlot;
			free(pSlot);
		}
	}else{
		// key not exists
		return;
	}

#ifdef DEBUG
	print_list(head);
#endif
}

void chained_hashtable_test(){
	Cht cht;
	int size = 10;
	chained_hashtable_init(&cht, size);
	
	/* insert */
	int key, value;
	int num = 20;
	int arr[20];
	for(int i = 0; i < num; i++){
		srand(i);
		key = rand() % 100;
		value = rand() % 1000;
		// store key for test
		arr[i] = key;

		// insert {key,value}
		chained_hashtable_insert(&cht, key, value);
		// search key for check insert
		int search_result = chained_hashtable_search(&cht, arr[i]);
		if(search_result >= 0){
			printf("insert success and search key {%d} result {%d}\n", arr[i], search_result);
		}else{
			printf("insert {%d} failed\n", arr[i]);
		}
	}

	/* search */
	printf("\n");
	for(int i = 0; i < num; i++){
		int search_result = chained_hashtable_search(&cht, arr[i]);
		if(search_result >= 0){
			printf("search key {%d} result {%d}\n", arr[i], search_result);
		}else{
			printf("search {%d} failed\n", arr[i]);
		}
	}

	/* delete */
	printf("\n");
	for(int i = num-1; i >= 0; i--){
		// delete {key}
		chained_hashtable_delete(&cht, arr[i]);
		// search key for check delete
		int search_result = chained_hashtable_search(&cht, arr[i]);	
		if(search_result >= 0){
			printf("delete failed and seach key {%d} result {%d}\n", arr[i], search_result);
		}else{
			printf("delete {%d} success\n", arr[i]);
		}
	}
}

/************************************main**************************************/
int main(int argc, char** argv){
	//direct_address_test();

	chained_hashtable_test();
	return 0;
}
