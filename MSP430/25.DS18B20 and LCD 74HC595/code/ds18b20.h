
#include <msp430.h>

#define DQ1 P1OUT |= BIT0       //doi thanh bit can dung
#define DQ0 P1OUT &=~ BIT0      //doi thanh bit can dung
#define DQ_BITx BIT0            //doi thanh bit can dung
#define DQ_DIR P1DIR            //doi thanh port can dung
#define DQ_IN P1IN              //doi thanh port can dung

typedef unsigned char uchar;
typedef unsigned int  uint;

void DelayNus(unsigned int n);
unsigned char Init_18B20(void);
void Write_18B20(unsigned char wdata);
unsigned char Read_18B20(void);
void Skip(void);
void Convert(void);
void Read_SP(void);
unsigned int ReadTemp(void);
unsigned int Do1Convert(void);
float DS18B20(void);

/*******************************************

********************************************/
uchar Init_18B20(void)
{
    uchar Error;

    _DINT();
    DQ0;
    __delay_cycles(500);
    DQ1;
    __delay_cycles(55);
    DQ_DIR &=~ DQ_BITx;
    _NOP();
    if(DQ_IN & DQ_BITx)
    {
        Error = 1;
        DQ_DIR |= DQ_BITx;
    }
    else
    {
        Error = 0;
        DQ_DIR |= DQ_BITx;
        DQ1;
    }
    _EINT();

    __delay_cycles(400);

    return Error;
}
/*******************************************

********************************************/
void Write_18B20(uchar wdata)
{
    uchar i;

    _DINT();
    for(i = 0; i < 8;i++)
    {
        DQ0;
        __delay_cycles(6);
        if(wdata & 0X01)    DQ1;
        else                DQ0;
        wdata >>= 1;
        __delay_cycles(50);
        DQ1;
        __delay_cycles(10);
    }
    _EINT();
}
/*******************************************

********************************************/
uchar Read_18B20(void)
{
    uchar i;
    uchar temp = 0;

    _DINT();
    for(i = 0;i < 8;i++)
    {
        temp >>= 1;
        DQ0;
        __delay_cycles(6);
        DQ1;
        __delay_cycles(8);
        DQ_DIR &= ~DQ_BITx;
        _NOP();
        if(DQ_IN & DQ_BITx)   temp |= 0x80;
        __delay_cycles(45);
        DQ_DIR |= DQ_BITx;
        DQ1;
        __delay_cycles(10);
    }
    _EINT();

    return  temp;
}
/*******************************************

********************************************/
void Skip(void)
{
    Write_18B20(0xcc);
}
/*******************************************
chuyen doi
********************************************/
void Convert(void)
{
    Write_18B20(0x44);
}
/*******************************************

********************************************/
void Read_SP(void)
{
    Write_18B20(0xbe);
}
/*******************************************
ham doc gia tri nhiet do
********************************************/
uint ReadTemp(void)
{
    uchar temp_low;
    uint  temp;

    temp_low = Read_18B20();
    temp = Read_18B20();
    temp = (temp<<8) | temp_low;

    return  temp;
}
/*******************************************
ham lay gia tri nhiet do da chuyen doi ( can chia 16 de lay gia tri nhiet do chuan " float Nhietdo =(float) Do1Convert/16 ")
********************************************/
uint Do1Convert(void)
{
    uchar i;

    do
    {
        i = Init_18B20();
    }
    while(i);
    Skip();
    Convert();
    for(i = 20;i > 0;i--)
        __delay_cycles(6000);
    do
    {
        i = Init_18B20();
    }
    while(i);
    Skip();
    Read_SP();
    return ReadTemp();
}

float DS18B20(void)
{
  return Do1Convert()/16.0;
  
}
