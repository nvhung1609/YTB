
#include "msp430f2122.h"
#include "lm35.h"

#define DATA BIT0
#define LATCH BIT1
#define CLK BIT2

#define OUT595 P1OUT

long cout = 1;
int coutnum = 0;

char DATA_8LED[8] = {0, 0, 0, 0, 0, 0, 0, 0};
char SCAN[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
char led7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void outByte(unsigned char hex, int latch);
void Data(long long num);
void Scan_8LED(void);
void init_timer(void);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    init_timer();

    P1DIR |= (DATA + LATCH + CLK);

    init_lm35();

    _BIS_SR(GIE);

    while (1)
    {
        int nhiet_do = read_lm35();

        Data(nhiet_do);
        
        __delay_cycles(100000);
    }
}

void outByte(unsigned char hex, int latch)
{
    for (char i = 0; i < 8; i++)
    {
        if ((hex << i) & 0x80)
        {
            OUT595 |= DATA;
        }
        else
        {
            OUT595 &= ~DATA;
        }
        OUT595 |= CLK;
        OUT595 &= ~CLK;
    }
    if (latch)
    {
        OUT595 &= ~LATCH;
        OUT595 |= LATCH;
    }
}

void Data(long long num)
{
    for (int i = 0; i < 8; i++)
    {
        if (num >= cout)
        {
            cout *= 10;
            coutnum += 1;
        }
    }
    for (int n = 0; n < coutnum; n++)
    {
        DATA_8LED[n] = num % 10;
        num /= 10;
    }
}

void Scan_8LED(void)
{
    for (int i = 0; i < coutnum; i++)
    {
        outByte(led7[DATA_8LED[i]], 0);
        outByte(SCAN[i], 1);
        outByte(0xff, 0);
        outByte(0xff, 1);
    }
}

void init_timer(void)
{
    TACCR0 = 3000;
    TACCTL0 |= CCIE;
    TACTL |= (TASSEL_2 + MC_1 + ID_3);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    Scan_8LED();
}
