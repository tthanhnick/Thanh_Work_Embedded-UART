#include "header.h"

void SetOrClearBit(unsigned int *address, unsigned char position, unsigned char action)
{
	if (action == SET_BIT)
	{
		*address |= (1U<<position);
	}
	else
	{
		*address &= ~(1U<<position);
	}
	return;
}

void SetOrClearMultiBit(unsigned int *address, unsigned char position, unsigned int mask, unsigned char action)
{
	if (action == SET_BIT)
	{
		*address |= (mask<<position);
	}
	else
	{
		*address &= ~(mask<<position);
	}
	return;
}

void LEDConfig (void)
{
	SetOrClearBit((unsigned int*) PCC_PORTD, 30u, SET_BIT);
	SetOrClearMultiBit((unsigned int*) PORTD_PCR15, 8u, 1u, SET_BIT);
	SetOrClearBit((unsigned int*) GPIOD_PDDR, 15u, SET_BIT); 
	
	SetOrClearBit((unsigned int*) GPIOD_PDOR, 15u, SET_BIT); 
}

void SoscConfig(void)
{
	SetOrClearBit((unsigned int*) SCG_SOSCCSR, 0, CLEAR_BIT); // disble SOSCCSR
	SetOrClearBit((unsigned int*) SCG_SOSCCSR, 23, CLEAR_BIT); // Unlock SOSCCSR
	
	SetOrClearMultiBit((unsigned int*) SCG_SOSCDIV, 0u, 0b001 , SET_BIT); //SOSC div 1 div by 1
	SetOrClearMultiBit((unsigned int*) SCG_SOSCDIV, 8u, 0b001 , SET_BIT); //SOSC div 2 div by 1
	
	SetOrClearBit((unsigned int*) SCG_SOSCCFG, 2, SET_BIT); // XTAL - Internal Osc
	SetOrClearBit((unsigned int*) SCG_SOSCCFG, 3, CLEAR_BIT); // Low gain
	
	SetOrClearMultiBit((unsigned int*) SCG_SOSCCFG, 4u, 0b11 , CLEAR_BIT); //0b11 clear range select
	SetOrClearMultiBit((unsigned int*) SCG_SOSCCFG, 4u, 0b10 , SET_BIT); //0b10 Medium range
	
	SetOrClearBit((unsigned int*) SCG_SOSCCSR, 0, SET_BIT); //enable SOSCCSR
}

void UARTConfig(void)
{
	SetOrClearBit((unsigned int*) PCC_PORTC, 30u, SET_BIT); // PCC PORTC CGC
	SetOrClearMultiBit((unsigned int*) PORTC_PCR6, 8u, 2u , SET_BIT); // MUX chip specific
	SetOrClearMultiBit((unsigned int*) PORTC_PCR7, 8u, 2u , SET_BIT); // MUX chip specific
	
	SetOrClearMultiBit((unsigned int*) PCC_LPUART1, 24u, 1u, SET_BIT); // PCC PCS
	SetOrClearBit((unsigned int*) PCC_LPUART1, 30u, SET_BIT); // PCC CGC
	
	LPUART1->BAUD &=~ (0xFFF << 0); // clear baud - Baud required 9600
	LPUART1->BAUD |= (52<<0); // Modulo baud rate = 52
	//8x10^6/9600*16 = Clock/(Baudrate*sampling rate) 
	LPUART1->BAUD |= (0b01111 << 24); // sampling ratio 16
	
	LPUART1->BAUD &= ~(1<<13); // 1 stop bit
	LPUART1->CTRL &= ~(1<<4); // 8 bit format
	LPUART1->CTRL &= ~(1<<1); // no parity
	
	LPUART1->CTRL |= (1<<21); // Interrupt Receiver Enable
	
	LPUART1->CTRL |= (1<<19); // transmiter enable
	LPUART1->CTRL |= (1<<18); // receiver enable
}

void UARTSendChar(char c)
{
	if ((LPUART1->STAT) & (1<<23)) //transmit is empty
	{
		LPUART1->DATA = c; // send data
	}
	for(int i=0; i< 100000; i++); //delay ~ 300ms
	
}

void UARTReceiveChar(void)
{
	char receiveChar;
	if ((LPUART1->STAT) & (1<<21)) // received buffer is full
	{
		receiveChar = LPUART1->DATA; // read received data
	}
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
void UARTSendString (char data_string[])
{
	int i = 0;
	while (data_string [i] != '\0')
	{
		UARTSendChar(data_string [i]);
		i++;
	}
}

void NvicUart1Config(void)
{
	// Enable NVIC interrupt LPUART 1 Receiver
	SetOrClearBit((unsigned int*) NVIC_INTERRUPT, 1, SET_BIT);  // 33 Mod 32
}

void clearData(char str[]) // Clear all data in the array
{
    for (int i = 0; i < (int) strlen(str); i++)
    {
        str[i] = '\0'; // Set each element to null
    }
}