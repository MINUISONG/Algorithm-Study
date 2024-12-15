/*
202135784 Song Minui
Assignment: Distinct subsequences
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sequence 10000
#define subsequence 100

void setTable(int**, int, int);
int cntSub(int**, char*, char*, int, int);
void freeTable(int**, int);

int main(void)
{
    FILE *fp;
    int num;
    char str[sequence];
    char substr[subsequence];
    int row, col;
    int** table;
    int cnt;

    
    fp = fopen("input.txt", "r");
    if (fp == NULL){
        puts("input.txt could not be opened");
        exit(1);
    }

    fscanf(fp, "%d", &num);
    for (int i = 0; i < num; i++){
        fscanf(fp, "%s", str);
        fscanf(fp, "%s", substr);

        row = strlen(substr) + 1;
        col = strlen(str) + 1;

        table = (int**)malloc(sizeof(int*) * row);
        for(int j = 0; j < row; j++){
            table[j] = (int *)malloc(sizeof(int) * col);
        }
        setTable(table, row, col);

        cnt = cntSub(table, str, substr, row, col);

        printf("%d\n", cnt);

		freeTable(table, row);

        
    }
    fclose(fp);
    return 0;
}

/*
set the table
table[0][j] = 1 for all j: If the substr is an empty string, there is always 1 subsequence.
table[i][0] = 0 (i> 0): Conversely, if the str is an empty string, if the substr is not an empty string, 
then it is 0 because no subsequence exists.
*/

void setTable(int** table, int row, int col)
{
    int i = 0;

    for(i = 0; i < row; i++){
        table[i][0] = 0;
    }
    for(i = 0; i < col; i++){
        table[0][i] = 1;
    }
}

//count the number of didtinct occurrences 
int cntSub(int** table, char* str, char* substr, int row, int col)
{
    int i, j;

    if(row > col){
        return 0;
    }

    for (i = 1; i < row; i++) {
		for (j = 1; j < col; j++) {
			if (substr[i - 1] == str[j - 1]) //when if the character match
				table[i][j] = table[i - 1][j - 1] + table[i][j - 1]; //When using this character to create a subsequence (table[i-1][j-1]) When creating a subsequence without this character (table[i][j-1])
			else
				table[i][j] = table[i][j - 1];
		}
	}

	return table[row - 1][col - 1];
}

void freeTable(int** table, int row)
{
	for (int i = 0; i < row; i++)
		free(table[i]);

	free(table);
}
