// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define M_PI 3.14

typedef struct {
	char**flag;
	unsigned width;
	unsigned height;

}flag_t;

//function to generate the flag depending of its height and width
flag_t theflag(unsigned width, unsigned height);

//function to generate any flag with a definite wave(angle and radian)
void display_flag(flag_t flag, double wave);

//function to free a flag 
void freeFlag(flag_t*f);

#define STEPS 6 //the bigger step is ,the more flag there will be ,got time limite exceeded in code playground for more than 6



int main()
{
	flag_t flag;
	double wave, start;

	srand(time(0));
	flag = theflag(29, 11);
	if (flag.flag) {
		if (STEPS > 0) {
			start = (double)(rand()) / RAND_MAX * 2 * M_PI;
			for (wave = start; wave < start + 2 * M_PI; wave += 2 * M_PI / STEPS) {
				display_flag(flag, wave);
				putchar('\n');
			}
		}
		freeFlag(&flag);
	}else{
		puts("Failed due to memory issue");

	}

    return 0;
}
flag_t theflag(unsigned width, unsigned height) {
	char full[] = { '#','$','%','&','@','%' };
	unsigned f_len = 6;
	char empty[] = { '-','*','+','~',',','`' };
	unsigned e_len = 7;
	char colors[3]; //white ,blue,red//
	int i;
	unsigned j, k, count;
	unsigned ids[3];//it heps having a good display when width can`t be divided by 3//
	int h = height;
	flag_t flag;

	flag.flag = (char**)malloc(height * sizeof(char*));
	if (flag.flag) {
		flag.width = width;
		flag.height = height;

		//color choice//
		colors[0] = full[rand() % f_len];
		do {
			colors[2] = full[rand() % f_len];
		} while (f_len > 1 && colors[0] == colors[2]);
		colors[1] = empty[rand() % e_len];

		//id generation
		ids[0] = ids[1] = ids[2] = width / 3;
		if (width % 3 == 1) {
			++ids[1];
		}
		else if (width % 3 == 2) {
			++ids[0];
			++ids[2];
		}

		//flag generation
		for (i = 0; i < h; ++i) {
			flag.flag[i] = (char*)malloc(width * sizeof(char));
			if (!flag.flag[i]) {
				break;
			}
			count = 0;
			for (j = 0; j < 3; ++j) {
				for (k = 0; k < ids[j]; ++k) {
					flag.flag[i][count + k] = colors[j];
				}
				count += ids[j];
			}
		}
		//error managment
		if (i < h) {
			for (j = 0; j < i; ++j) {
				free(flag.flag[j]);
			}
			free(flag.flag);
			flag.flag = NULL;
		}
	}
	return flag;
}

void display_flag(flag_t flag, double wave) {
	unsigned j;
	int h = flag.height, i;
	double *limits;

	if (flag.flag) {
		limits = (double*)malloc(flag.width * sizeof(double));

		if (!limits) {
			puts("Failed to display due to memory issues");
			return;

		}
		//waving initialization
		for (j = 0; j < flag.width; j++) {
			limits[j] = (cos((double)(j / 2) / flag.width*M_PI * 4 * wave) + 1) + h / 8;
		}
		//displaying

		for (i = 0; i < h + h % 2 + h / 4 + h % 4; ++i) {
			if (i - (int)limits[0] >= 0) {
				putchar('|');
				putchar('|');
			}
			else {
				putchar(' ');
				putchar(' ');
			}
			for (j = 0; j < flag.width; ++j) {
				if (i - (int)limits[j] >= 0 && i - (int)limits[j] < h) {
					putchar(flag.flag[i - (int)limits[j]][j]);
				}
				else {
					putchar(' ');
				}
			}
			putchar('\n');
		}
		free(limits);
	}
}
void freeFlag(flag_t*f) {
	unsigned i;
	if (f && f->flag) {
		for (i = 0; i < f->height; ++i) {
			free(f->flag[i]);
		}
		free(f->flag);
		f->flag = NULL;

	}
}






			

			
		

