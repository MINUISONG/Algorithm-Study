/*
202135784 Song Minui
Assignment: Fashionable dressmaker's problem
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 1000

typedef struct dressmaker{
    int num;
    int time;
    int fine;
    float rate;
}Dressmaker;


void initCnt(Dressmaker*, int);
void searchCnt(Dressmaker*, int);
void printResult(Dressmaker*, int);


int main(void)
{
    FILE *fp;
    int test, job, t, f;
    char blank[1000];

    
    fp = fopen("input.txt", "r");
    if (fp == NULL){
        puts("input.txt could not be opened");
        exit(1);
    }

    fscanf(fp, "%d", &test);
    if (test < 0){
        puts("ERROR: invalid input");
        exit(1);
    }

    for (int i = 0; i < test; i++){
        fgets(blank, 1000, fp);
        fscanf(fp, "%d", &job);
        
        if (job > 1000 || job < 1){
        puts("ERROR: invalid input");
        exit(1);
        }

        Dressmaker cnt[job];
        initCnt(cnt, job);

        for(int j = 0; j < job; j++){
            fscanf(fp, "%d %d", &t, &f);
            cnt[j].num = j + 1;
			cnt[j].time = t;
			cnt[j].fine = f;
			cnt[j].rate = (float)cnt[j].fine / cnt[j].time;
        }

        searchCnt(cnt, job); 
		printResult(cnt, job);
    } 

    return 0;
}

//inintialize the cnt structure array
void initCnt(Dressmaker* cnt, int job)
{
    for (int j = 0; j < job; j++){
        cnt[j].num = cnt[j].time = cnt[j].fine = cnt[j].rate = 0;
    }

}

void searchCnt(Dressmaker* cnt, int n)
{
	int i, j;
	float maxRate;
	int maxi;
	Dressmaker tmp;

	for (i = 0; i < n; i++) {
		maxRate = cnt[i].rate;
		maxi = i;
		for (j = i + 1; j < n; j++) {
			//select highest rate cnt
			if (maxRate < cnt[j].rate) {
				maxRate = cnt[j].rate;
				maxi = j;
			}
			//when same rate, select minimum number of cnt
			else if (maxRate == cnt[j].rate && cnt[maxi].num > cnt[j].num) {
				maxi = j;
			}
		}

		//swap
		if (maxi != i) {
			tmp = cnt[i];
			cnt[i] = cnt[maxi];
			cnt[maxi] = tmp;
		}
	}
}

//print the result
void printResult(Dressmaker* cnt, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", cnt[i].num);
	puts("");
	puts("");
}