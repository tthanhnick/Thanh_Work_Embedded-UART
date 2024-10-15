#include <string.h>

#define SET_BIT 1
#define CLEAR_BIT 0

#define PCC_PORTD (0x40065000u + 0x130u) //PORTD PIN 15
#define PORTD_PCR15 (0x4004C000u + 0x3Cu)
#define GPIOD_PDDR (0x400FF0C0u + 0x14u)
#define GPIOD_PDOR (0x400FF0C0u + 0x0u)

#define PCC_PORTC (0x40065000u + 0x12Cu) //PORTC PIN 13 
#define PORTC_PCR15 (0x4004B000u + 0x34u)
#define GPIOC_PDDR (0x400FF080u + 0x14u)
#define GPIOC_PDIR (0x400FF080u + 0x10u)

#define SYSTICK_CTRL (0xE000E010)
#define SYSTICK_LOAD (0xE000E014)
#define SYSTICK_VAL (0xE000E018)

#define SCG_RCCR (0x40064000u + 0x14u)
#define SCG_SPLLCSR (0x40064000u + 0x600u)
#define SCG_SPLLDIV (0x40064000u + 0x604u)
#define SCG_SPLLCFG (0x40064000u + 0x608u)
#define SCG_SOSCCSR (0x40064000u + 0x100u)
#define SCG_SOSCDIV (0x40064000u + 0x104u)
#define SCG_SOSCCFG (0x40064000u + 0x108u)

#define PCC_PORTB (0x40065000u + 0x128u) //PCC_PORTB
#define PORTC_PCR6 (0x4004B000u + 0x18u) //PORTB 6
#define PCC_LPUART1 (0x40065000u + 0x1ACu) //UART1
#define PORTC_PCR7 (0x4004B000u + 0x1Cu) //PORTB 7

#define NVIC_INTERRUPT (0xE000E100u + 4*1) // NVIC Interrupt ID=33, n*4 LPUART1 Receive Interrupt 

// Point to struct LPUART
#define LPUART0_base_address (0x4006A000u)
#define LPUART0 ((LPUART_Type*)LPUART0_base_address)

#define LPUART1_base_address (0x4006B000u)
#define LPUART1 ((LPUART_Type*)LPUART1_base_address)

#define LPUART2_base_address (0x4006C000u)
#define LPUART2 ((LPUART_Type*)LPUART2_base_address)


typedef struct {
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	volatile unsigned int GLOBAL;
	volatile unsigned int PINCFG;
	volatile unsigned int BAUD;
	volatile unsigned int STAT;
	volatile unsigned int CTRL;
	volatile unsigned int DATA;
	volatile unsigned int MATCH;
	volatile unsigned int MODIR;
	volatile unsigned int FIFO;
	volatile unsigned int WATER;
}LPUART_Type;

// ex 1 above

void SetOrClearBit(unsigned int *address, unsigned char position, unsigned char action);
void SetOrClearMultiBit(unsigned int *address, unsigned char position, unsigned int mask, unsigned char action);
void LEDConfig (void);
void SysTick(void);
void PLLConfig(void);
void SoscConfig(void);
void ClkOutput(void);
void UARTConfig(void);
void UARTSendChar(char c);
void UARTReceiveChar(void);
void UARTSendString (char string[]);
void NvicUart1Config(void);
void clearData(char str[]);