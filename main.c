#include "header.h"
#include <string.h>
#include <stdbool.h>

char string[] = {'H','E','L','L','O','\r','\n','\0'};
char receiveString[10];

int main(void)
{	
	SoscConfig();
//	PLLConfig();
//	ClkOutput();
	LEDConfig();
	UARTConfig();
	while(1)
	{
//		UARTSendChar('H'); //ex2
//		UARTReceiveChar(); //ex3
		UARTSendString (string); //ex 4
	}
}



