

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "piBoard.h"
#include "RS485Devices.h"

#define BUFSIZE 1024
#define PI 3.141592653



int main (int argc, char **argv){

FILE *fp;
char linebuff[BUFSIZE];
char temp;
int i,k;
unsigned int timeOn, timeOff;
/*
usage ./strangerThing "message to send" <time on mS> <time off mS>

each RS485Digital output device has addresss corresponding to the ASCII value of text to display.
eg
to turn on "A", write to 0x41 ... 
*/

initializeBoard();

if (argc==4) {


	fp = fopen("msg.txt","w");
	fprintf(fp,"busy\n");
	fclose(fp);

	strcpy(linebuff,argv[1]);
	timeOn=atoi(argv[2]);
	timeOff=atoi(argv[3]);

	k = strlen(linebuff);
	printf("Writing message: %s\n",linebuff);
//	printf("string length %d\n",k);
	for (i=0; i<k; i++){
		//turn on light
		temp = linebuff[i];
		if (temp>0x60) temp-=0x20;
		if (temp!=32) {
			switch (temp){
				case 78 ... 90:
				printf("%c:%02x\n",temp,temp);
				fflush(stdout);
				setRS485DigitalOut(temp,1);
				delay(timeOn);
				setRS485DigitalOut(temp,0);
				delay(timeOff);
				break;
			default:
				printf("\"%c\" not supported\n",temp);
				fflush(stdout);
				break;
			}


		} else {
			// space
			printf("space:%02x\n",temp);
			fflush(stdout);
			delay(timeOn);
			delay(timeOff);
		}

	}
	printf("\n\n");
	remove("msg.txt");
} else {
	printf("Useage ./strangerThing <input message file> <delay time On mS> <delay time Off mS>\n");
}

return 0;

}
