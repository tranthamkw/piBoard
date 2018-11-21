/*
 * This is a template file to show all of the necessary components to add
 * to new data collection files that are created. 

starting point. 


*/

#include "piBoard.h"
#include "morse.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define DOT 100
#define OFF 0
#define ON 1
#define BUFSIZE 1024



int main (int argc, char* argv[])
{
	FILE *fp;

	char message[1024],temp;
	unsigned int j,k,i,len,t,dot;


	initializeBoard();
	pinMode(3,OUTPUT);
	digitalWrite(3,OFF);//off


	if (argc==3) {
		strcpy(message,argv[1]);
		dot = atoi(argv[2]);
	if (dot<20) dot = 20;
	if (dot>200) dot = 200;
	fp=fopen("msg.txt", "w");
	fprintf(fp," \n");
	fclose(fp);

		len = strlen(message);
		for (j=0;j<len;j++){
			i = message[j];
			if (i>0x60) i-=0x20;
			printf("\t%c  ",toupper(message[j]));

			if (i==0x20){ //space
				delay(7*dot);
				printf("\n");
			}

			if ((i>0x40) & (i<0x5B)){ //between A and Z
				temp = morse[i-65];
				for (k=0;k<4;k++){
					t=temp & ((0b11)<<((3-k)*2));
					t=t >>((3-k)*2);
				switch (t) {
					case 3: printf("_ ");
					break;
					case 1: printf(". ");
					break;
					}
				fflush(stdout);
				if (t>0){
					digitalWrite(3,ON);//on
					delay(t*dot);
					digitalWrite(3,OFF);//off
					delay(dot);
				}
			}
			printf("\n");
			fflush(stdout);
			delay(3*dot);
			} else {
			printf("\n");  // not A-Z
			}

		}//for j
	remove("msg.txt");

	} else {
		printf("Usage: sudo ./<programName> \"message\" <decimal delay for dot> \n");
		return 0;
	}
	return 0 ;
}
