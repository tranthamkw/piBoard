/*
	STRANGER THING MESSAGE TRANSLATOR

	User passes message to display with timeon and time off parameters.
	Program sequentally goes through message, character by character,
	and addresses the appropriate RS485GUEST device. The GUEST devices
	are programmed so that their address is equal to the ASCII value of
	the letter they are to represent.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "piBoard.h"
#include "RS485Devices.h"

#define BUFSIZE 1024

int main (int argc, char **argv){

	FILE *fp;
	char linebuff[BUFSIZE];
	char temp;
	int i,k;
	unsigned int timeOn, timeOff;

	initializeBoard();// establish communication with serial UART

	if (argc==4) {
		fp = fopen("msg.txt","w"); // this is a lockfile
		fprintf(fp,"busy\n");	//the script that is called from PHP checks
		fclose(fp); // if this file exists, then return 'BUSY' to web

		strcpy(linebuff,argv[1]); //grab parameters from command line
		timeOn=atoi(argv[2]);  // no error trapping, so external script/user must pass
		timeOff=atoi(argv[3]); // valid timeOn and timeOff
		k = strlen(linebuff); // length of message

		printf("Writing message: %s\n",linebuff);
	
		for (i=0; i<k; i++){  // go through each character of the message
			temp = linebuff[i];
			if (temp>0x60) temp-=0x20;  // only print capital letters

			if (temp!=32) {  // ASCII 32 is space

				switch (temp){
					case 78 ... 90: // only act on ASCII letters that we've got
						// if a guest is addressed that does not exist,
						// the RS485 code will time out (after an uncomfortable amount of time)
					printf("%c:%02x\n",temp,temp);
					fflush(stdout);
					setRS485DigitalOut(temp,1);  // turn on the approp LED
					delay(timeOn);
					setRS485DigitalOut(temp,0); // then turn it off.
					delay(timeOff);
					break;
				default:
					printf("\"%c\" not supported\n",temp);
					fflush(stdout);
					break;
				}// end switch
			} else {
			// "print" a space
			printf("space:%02x\n",temp);
			fflush(stdout);
			delay(timeOn);  // all LEDs are off
			delay(timeOff); // this time gives illusion of space
			}// end if space
		}//end for loop
		printf("\n\n");
		remove("msg.txt");// we're essentially done with message so remove lock file.
	} else {
		printf("Useage: ./strangerThing \"message to send\" <delay time On mS> <delay time Off mS>\n");
		printf("E.G. sudo ./strangerThing \"This is a test\" 500 800\n");
	}
return 0;
}// end main.
