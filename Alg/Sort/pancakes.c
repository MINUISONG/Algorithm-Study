/*
202135784 Songminui
Assignment: Cooking delicious pancakes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
int find_Max(int[], int);
void flip(int[], int, int[], int*, int, int);


int main(void){
    int pancake[3][MAX], flip_arr[3][MAX];
    char* str;
    char input[100];
    
    FILE* fp = fopen("input.txt", "r");

    int num, test = 0;
    if (fp == NULL){
        puts("input.txt could not be opened");
        exit(1);
    }

    //read the input file until end-of-file
    while(!feof(fp)) {
        fgets(input, 100, fp);
        str = strtok(input, " ");

        int layer = 0, v = 0; //layer is the current number of pancakes in the stack
        while (str != NULL){ 
            num = atoi(str);
            if (num > 0 && num <= 10 && layer < 30){
                pancake[test][layer++] = num;
            }
            else { //when input number does not meet criteria
                puts("input number doesn't meet criteria");
                v = -1;
                break;
            }
            str = strtok(NULL, " ");
        }

        printf("==== test %d ====\n", test + 1);
        if(v == -1){
            exit(1);
        }
        else {
            //print original stack of pancakes
            for (int i = 0; i < layer; i++){
                printf("%d ", pancake[test][i]);
            }

            //if maximum delimiter index is different with current index, do flip
            int idx_max, flip_cnt = 0;
            for (int i = layer - 1; i >= 0; i--) {
                idx_max = find_Max(pancake[test], i);
                if (idx_max != i){
                    flip(pancake[test], layer, flip_arr[test], &flip_cnt, i, idx_max);
                }
             }
            flip_arr[test][flip_cnt] = 0; //If filp is no longer needed, put zero in the last index.

            if (flip_cnt > 0){
                printf("(");
                for (int i = 0; i < layer; i++){
                    if (i == (layer - 1))
						printf("%d", pancake[test][i]);
					else
						printf("%d ", pancake[test][i]);
                }
                printf(")\n");

				//print the position of the flipped pancakes
				for (int i = 0; i < flip_cnt + 1; i++)
					printf("%d ", flip_arr[test][i]);
			}
			else {
				//when flip didn't happen, print 0
				for (int i = 0; i < flip_cnt + 1; i++)
					printf("\n%d", flip_arr[test][i]);
            }
        }
        puts("\n");

        test++;

         //test using 3 different data set
		if (test == 3) {
			puts("< Tested using 3 different data set >");
			break;
		}   
    }

    fclose(fp);

    return 0;
}

//find array index of maximum delimiter
int find_Max(int pancake[MAX], int range){
    
    int idx = range;
    for(int i = range - 1; i >= 0; i --){
        if (pancake[i] > pancake[idx]){
            idx = i;
        }
    }
    return idx;
}

/*
arr_flip indicates the position of the pancake where the flip occurs
flip_cnt indicates the number of times flip occurs
- When maximum delimeter index is 0,
there's no need to do flip from that index. Just flip from the i index.
- When maximum delimeter index is not 0,
Flip the largest value in the array to move forward the most, and flip it with the i index.
*/
void flip(int pancake[MAX], int layer, int flip_arr[MAX], int *flip_cnt, int i, int idx_max)
{
    int temp, start;
    if (idx_max != 0) { //filp only if maximum value isn't the first index of the array
        flip_arr[*flip_cnt] = layer - idx_max; //store flip pancake's position
        *flip_cnt = *flip_cnt + 1;
        start = 0;
        while (start < idx_max){
            temp = pancake[start];
            pancake[start] = pancake[idx_max];
            pancake[idx_max] = temp;
            
            start++;
            idx_max--;
        }
    }
    
    flip_arr[*flip_cnt] = layer - i; //store flip pancake's position
    *flip_cnt = *flip_cnt + 1;
    start = 0;
    while (start < i){
        temp = pancake[start];
        pancake[start] = pancake[i];
        pancake[i] = temp;
        start++;
        i--;
    }

}