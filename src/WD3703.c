/*
 * WD3703.c
 *
 *  Created on: 2021骞�7鏈�2鏃�
 *      Author: zhoushuguang
 */
#include "WD3703.h"
#include<msp430.h>
#define CPU_F ((double)16000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define Delay_Nms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
unsigned char CalculateCRC8(unsigned char x)
{
   unsigned char i, Xinput,CRC8;

   Xinput=x;
   for(i=0;i<8;i++)
   {
      if( ((CRC8^Xinput)&0x01)==1 )
      {
        CRC8^=0x18;
        CRC8=CRC8>>1;
        CRC8|=0x80;
      }
      else
        CRC8=CRC8>>1;
      Xinput=Xinput>>1;
   }
   return CRC8;
}


void _delay_us(unsigned int  nTimes)
{
    unsigned int  i,j;
    for(i=0;i<nTimes;i++)
    {
        for(j=0;j<7;j++);
        //for(j=0;j<16;j++);
    }
}

void _delay_ms(unsigned int nTimes)
{
    unsigned int  i,j;
    for(i=0;i<nTimes;i++)
    {
        for(j=0;j<7600;j++);
    }
}

//uint8_t test_reset;
unsigned int  WD3703_Reset(void)//
{
   unsigned int Reset_val = 0;

    unsigned int ret = 0;

    WD3703_Data_out;
    WD3703_Write_High;
    Delay_Nms(1);

    WD3703_Write_Low;
    delay_us(520);
    WD3703_Data_in;
    delay_us(60);
    Reset_val = (P1IN&BIT5);
    delay_us(400);
    WD3703_Data_out;
    WD3703_Write_High;
    if(Reset_val==0)ret =1;
    else ret = 0;
    return ret;
}

void WD3703_Write_Byte(unsigned char Data_in)
{
    unsigned int i;
    WD3703_Data_out;
    for(i=0;i<8;i++)
    {
        WD3703_Write_Low;
        delay_us(4);
        if(Data_in&0x01)
        {
            WD3703_Write_High;
        }
        else
        {
            WD3703_Write_Low;
        }
        delay_us(65);
        WD3703_Write_High;
        delay_us(4);
        Data_in>>=1;
    }
    delay_us(4);
}

char WD3703_Read_Byte(void)
{
    unsigned int  i;
    char  Read_val=0;

    for(i=0;i<8;i++)
    {
        WD3703_Data_out;
        WD3703_Write_Low;
        delay_us(4);
        WD3703_Data_in;
        delay_us(15);
        if((P1IN&BIT5)==BIT5)Read_val |= 0x01<<i;
        else                Read_val = Read_val&(~(0x01<<i));
        delay_us(40);
    }
    //_delay_us(7);

    return Read_val;
}
float WD3703_Read_Temperature(void)
{
    unsigned int Reset = 0;
  //  unsigned int  i;
   // char WD3703_Buf[9];
    char data_L;
    char data_H;
    float temp=0;
    Reset = WD3703_Reset();
    if(Reset)
    {
        WD3703_Write_Byte(SKIP_ROM);
        WD3703_Write_Byte(Convert_T);

        _delay_cycles(350);
    if(WD3703_Reset())
    {
        WD3703_Write_Byte(SKIP_ROM);
                WD3703_Write_Byte(READ_SCRATCHPAD);
              /*  for(i=0;i<9;i++)
                {
                    WD3703_Buf[i]=WD3703_Read_Byte();//WD3703_Data_in
                    CalculateCRC8(WD3703_Buf[i]);//CRC8==0鐨勬椂鍊欒鏁颁负鐪燂紝Buf[0]涓烘俯搴︿綆锛孊Uf[1]娓╁害涓洪珮锛屽皢娓╁害楂樹负闄勭粰鏈夌鍙风殑鏁存暟銆俠uf[8]涓篊RC鏍￠獙鍊�
                }
                i=255;
                if(WD3703_Buf[1]<0x30)
                {
                    i=127;
                }*/
                data_L=WD3703_Read_Byte();
                data_H=WD3703_Read_Byte();

    }
    }
    temp=(data_H*256+data_L)/256.0;
    return temp;

}

/*void Read_ROM_ID(void)
{

    uint8_t ii;
    WD3703_Reset();
    WD3703_Write_Byte(0x33);

    ytemp=xtemp = WD3703_Read_Byte(WD3703_Data_in);
    temp =  xtemp;

}*/




