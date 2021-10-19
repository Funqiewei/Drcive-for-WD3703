/*
 * UCS_INIT.c
 *
 *  Created on: 2015锟斤拷7锟斤拷7锟斤拷
 *      Author: yumin
 *
 *系统默锟较ｏ拷ACLK使锟斤拷REFOCLK=32.768KHz,MCLK锟斤拷SMCLK使锟斤拷DCOCLKDIV=1.048576MHz
 *锟斤拷锟斤拷锟斤拷    锟斤拷ACLK使锟斤拷X1锟斤拷锟斤拷=32.768KHz,MCLK使锟斤拷X2锟斤拷锟斤拷=4MHz锟斤拷SMCLK使锟斤拷DCOCLKDIV=15.99MHz
 */
#include <msp430F5529.h>


void UCS_init(void)
{
/************************************************锟斤拷锟斤拷时锟斤拷频锟斤拷*/

//	P1SEL |= BIT0; //ACLK
//	P1DIR |= BIT0;
//	P2SEL |= BIT2; //SMCLK
//	P2DIR |= BIT2;
//	P7SEL |= BIT7; //MCLK
//	P7DIR |= BIT7;

/*******************************************锟斤拷XT1锟斤拷2锟解部锟斤拷锟斤拷*/
	P5SEL |= BIT4|BIT5;
	UCSCTL6 |= XCAP_3;
	UCSCTL6 &= ~XT1OFF;//锟斤拷XT1锟斤拷锟斤拷锟斤拷XT1LFOFFG锟斤拷锟杰憋拷锟斤拷

	P5SEL |= BIT2|BIT3;
	UCSCTL6 &= ~XT2OFF;//锟斤拷XT2锟斤拷锟斤拷锟斤拷XT2OFFG锟斤拷锟杰憋拷锟斤拷

	__bis_SR_register(SCG0);//锟斤拷锟斤法为锟教讹拷锟斤拷式锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟节的憋拷锟斤拷锟斤拷位锟斤拷SCG0锟斤拷系统锟斤拷锟斤拷模式锟叫关ｏ拷锟斤拷时MCLK锟斤拷停锟斤拷锟斤拷
/***************************************************锟斤拷锟斤拷DCO*/
		UCSCTL0 = 0x00;   //锟斤拷锟斤拷锟姐，FLL锟斤拷锟斤拷时锟斤拷锟矫寄达拷锟斤拷系统锟斤拷锟皆讹拷锟斤拷锟矫ｏ拷锟斤拷锟矫癸拷
		UCSCTL1 = DCORSEL_6;//锟斤拷锟节凤拷围约为 ~ MHZ锟斤拷锟斤拷锟斤拷DCO锟斤拷频锟绞凤拷围锟斤拷之锟斤拷锟斤拷锟矫碉拷DCO时锟斤拷要锟斤拷锟斤拷锟斤拷锟轿э拷冢锟斤拷锟斤拷锟斤拷锟斤拷锟�
		UCSCTL2 = FLLD_1 | 243;//FLLD=1,FLLN=243,锟斤拷频锟斤拷为2*锟斤拷243+1锟斤拷*32.768=15.99MHZ
		                       //DCOCLK = D*(N+1)*(REFCLK/n)
		                       //DCOCLKDIV = (N+1)*(REFCLK/n)

	__bic_SR_register(SCG0);
	__delay_cycles(782000);//系统锟皆达拷锟侥撅拷确锟斤拷时锟斤拷锟斤拷位us

/************************************************锟饺达拷锟斤拷锟斤拷锟斤拷锟斤拷*/
	while (SFRIFG1 & OFIFG)
	{
			UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
			SFRIFG1 &= ~OFIFG;
	}

    UCSCTL4=(UCSCTL4&(~(SELA_7|SELS_7|SELM_7)))|SELA_0|SELS_3|SELM_3;
       //(UCSCTL4&(~(SELA_7|SELS_7|SELM_7)))锟饺帮拷SELA,SELS,SELM锟斤拷锟姐，然锟斤拷锟斤拷锟矫革拷锟斤拷时锟接碉拷锟斤拷源
       //ACLK->X1COK(32.768KHz),SMCLK->X2CLK(4MHz),MCLK->DCOCLK(15.99MHZ)
}

/*void SetVcoreUp (unsigned int level)
{
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}
void UCS_init(void) {

	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	  P1SEL |= BIT0;P1DIR |= BIT0;	//锟斤拷锟斤拷ACLK锟斤拷
	  P2SEL |= BIT2;P2DIR |= BIT2;	//锟斤拷锟斤拷SMCLK锟斤拷
	  P7SEL |= BIT7;P7DIR |= BIT7;	//锟斤拷锟斤拷MCLK锟斤拷
	  P5SEL |= BIT2+BIT3;
	  UCSCTL6 &= ~XT2OFF;          	//锟斤拷XT2
	  SetVcoreUp(3);
	  __bis_SR_register(SCG0);
	  UCSCTL0 =0;
	  UCSCTL1 = DCORSEL_7;                    //DCO频锟绞凤拷围锟斤拷28.2MHZ锟斤拷锟斤拷
	  UCSCTL2 = FLLD_0+24;		//D=16锟斤拷N=1
	  UCSCTL3 = SELREF_5 + FLLREFDIV_2;    //n=8,FLLREFCLK时锟斤拷源为XT2CLK锟斤拷
	  UCSCTL4=SELM_3+SELS_4+SELA_2;
	  __bic_SR_register(SCG0);
	  __delay_cycles(8192);
	  do
	  {
	  	UCSCTL7 &=~(XT2OFFG+DCOFFG+XT1LFOFFG);//锟斤拷锟�3锟斤拷时锟接达拷锟斤拷锟街�
	  	SFRIFG1&=~(OFIFG);//锟斤拷锟绞憋拷哟锟斤拷锟斤拷志位
	  }while(SFRIFG1 & OFIFG);	//锟斤拷锟斤拷锟绞憋拷哟锟斤拷锟�
}*/



