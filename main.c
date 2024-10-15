#include "header.h"
#include <string.h>
#include <stdbool.h>

char string[] = {'H','E','L','L','O','\r','\n','\0'};
char receiveString[10];
int	i=0;
volatile bool status = false;
volatile char receiveChar = 0;

void UartInterruptChar(void)
{
		if (receiveChar == '1')
		{
			SetOrClearBit((unsigned int*) GPIOD_PDOR, 15u, CLEAR_BIT); 
			for(int i=0; i< 150000; i++); //delay ~ 500ms
		}
		else if (receiveChar == '0')
		{
			SetOrClearBit((unsigned int*) GPIOD_PDOR, 15u, SET_BIT); 
			for(int i=0; i< 150000; i++); //delay ~ 500ms
		}	
}

void UartInterruptString (void)
{
		if (status == true)
		{
			if (i< sizeof (receiveString) -1)
			{
				receiveString[i]=receiveChar; 
				i++;
				
				if(receiveString[i-1] == ']')
				{
					receiveString[i] = '\0';
					i=0;
					if (strcmp(receiveString,"[LEDON]")==0)
					{
						SetOrClearBit((unsigned int*) GPIOD_PDOR, 15u, CLEAR_BIT);
						clearData(receiveString);
					}
					else if(strcmp(receiveString,"[LEDOFF]")==0) 
					{
						SetOrClearBit((unsigned int*) GPIOD_PDOR, 15u, SET_BIT);
						clearData(receiveString);
					}	
				}
					
			}
			status = false;	
		}
}

int main(void)
{	
	SoscConfig();
	LEDConfig();
	NvicUart1Config();
	UARTConfig();
	while(1)
	{
//		UARTSendChar('H'); //ex2
//		UARTReceiveChar(); //ex3
//		UARTSendString (string); //ex 4
//		UartInterruptChar(); // ex5
		UartInterruptString(); // ex6
	}
}

void LPUART1_RxTx_IRQHandler (void)
{ 
	receiveChar = LPUART1->DATA; // read received data
	status = true;
}




