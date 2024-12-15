/*
202135784 Songminui
Assignment: Smart elepthant
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct elephat {
    int weight;
    int iq;
    int index;
}Elephant;

void sortByWeight(Elephant*, int);
void swap(Elephant*, int, int);
void disprove(Elephant*, int);
void printSequence(int*, int);

int main(void){
    FILE *fp;
    Elephant elephants[MAX_SIZE];

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        puts("input.txt could not be opened");
        exit(1);
    }

    int weight, iq;
    int i=0;

    while(fscanf(fp, "%d %d\n", &weight, &iq) != EOF){
        if(!(iq <= 100000 && iq >= 0) || !(weight <= 100000 && weight >= 0) || (i > 1000)){
            puts("Invalid input");
			exit(1);
        }
        else{
            elephants[i].weight = weight;
            elephants[i].iq = iq;
            elephants[i].index = i;
            i++;
        }
    }
    fclose(fp);

    disprove(elephants, i);



    return 0;
}

//swap two values
void swap(Elephant* elephants, int i, int mini) {
	Elephant tmp;

	tmp = elephants[i];
	elephants[i] = elephants[mini];
	elephants[mini] = tmp;
}

/*Sort by weight
If the weight is the same, sort IQs in descending order
*/
void sortByWeight(Elephant* elephants, int cnt) {
	int i, j, mini;

	for (i = 0; i < cnt; i++) {
		mini = i;
		for (j = i + 1; j < cnt; j++) {
			if ((elephants[mini].weight > elephants[j].weight) || 
			    (elephants[mini].weight == elephants[j].weight && elephants[mini].iq < elephants[j].iq)) {

				mini = j;
			}
		}
		if (mini != i) {
			swap(elephants, i, mini);
		}
	}
}

//recursively print sequence
void printSequence(int* prev, int i) {
	if (prev[i] == -1) {
		printf("%d\n", i + 1);
	}
	else {
		printSequence(prev, prev[i]);
		printf("%d\n", i + 1);
	}
}

/*
find the case that weights are increasing but IQ's are decreasing
returns the length of the longest increasing subsequence
*/
void disprove(Elephant* elephants, int size) {
	int* prev;
	int* len;
	int i, j;
	int max = -1, lastIdx = -1;

	prev = (int*)malloc(sizeof(int) * size);
	len = (int*)malloc(sizeof(int) * size);

	for (i = 0; i < size; i++) {
		prev[i] = -1;
		len[i] = 1;
	}

	//sort elephants by weight
	sortByWeight(elephants, size);

	for (i = 0; i < size; i++) {
		for (j = i + 1; j < size; j++) {
			if (elephants[i].weight < elephants[j].weight && elephants[i].iq > elephants[j].iq) {
				if (len[elephants[i].index] + 1 > len[elephants[j].index]) { //finding subsequence, storing previous sequence
					prev[elephants[j].index] = elephants[i].index;
					len[elephants[j].index] = len[elephants[i].index] + 1;

					if (max <= len[elephants[j].index]) { //maximum length(Equivalent to output values such as in the example)
						max = len[elephants[j].index];
						lastIdx = elephants[j].index;
					}
				}
			}
		}
	}

	printf("%d\n", max);
	printSequence(prev, lastIdx);

	free(prev);
	free(len);
}
