

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "piBoard.h"
#include "RS485Devices.h"

#define BUFSIZE 1024
#define PI 3.141592653



int main (int argc, char **argv){

FILE *fp;
char fileName[BUFSIZE];
char linebuff[BUFSIZE];
int i,k;
unsigned int timeOn, timeOff;
/*
usage ./strangerThing "filename" <time on mS> <time off mS>

each RS485Digital output device has addresss corresponding to the ASCII value of text to display.
eg
to turn on "A", write to 0x41 ... 
*/

initializeBoard();

if (argc==4) {

	strcpy(fileName,argv[1]);
	timeOn=atoi(argv[2]);
	timeOff=atoi(argv[3]);
	//check to see if outFileName exists
	fp=fopen(fileName,"r");
	if (!fp){
		// file does not exist
		printf("Input file does NOT exist. Terminating\n");
		exit(1);
	} else {
		fscanf(fp,"%[^\n]",linebuff);
		fclose(fp);
	}

	k = strlen(linebuff);
	printf("Input message %s\n",linebuff);
	printf("string length %d\n",k);
	for (i=0; i<k; i++){
		//turn on light
		printf("%02x ",linebuff[i]);
		fflush(stdout);
	if (linebuff[i]!=32) {
		setRS485DigitalOut(linebuff[i],1);
		delay(timeOn);
		setRS485DigitalOut(linebuff[i],0);
		delay(timeOff);
	} else {
	// space
	delay(timeOn);
	delay(timeOff);
	}

	}
	printf("\n\n");
} else {
	printf("Useage ./strangerThing <input message file> <delay time On mS> <delay time Off mS>\n");
}

return 0;

}
