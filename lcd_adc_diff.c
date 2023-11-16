#include<LPC17xx.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
int i,r;
unsigned int temp1, temp2 , flag1 = 0,dig1,dig2;
float ana1,ana2,diff;

void port_write(){
	LPC_GPIO0->FIOPIN = temp2<<23;
	if(flag1 == 0){
		LPC_GPIO0->FIOCLR = 1<<27;
	}
	else{
		LPC_GPIO0->FIOSET = 1<<27;
	}
	LPC_GPIO0->FIOSET = 1<<28;
	for(r=0;r<25;r++);
	LPC_GPIO0->FIOCLR = 1<<28;
	for(r=0;r<30000;r++);
	
}

void lcd_write(){
	temp2 = temp1&0xf0;
	temp2 = temp2>>4;
	port_write();
	if(!((flag1==0)&&((temp1 == 0x30)||(temp1==0x20)))){
		temp2 = temp1&0x0f;
		port_write();
	}
}
int main(){
	unsigned long int cmd[] = {0x30,0x30,0x30,0x20,0x28,0x01,0x06,0x0C,0X08};
	char diffstr[16];
	char msg[] = {"Voltage: "};
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL1 = 0;
	LPC_GPIO0->FIODIR = 0XF<<23|1<<27|1<<28;
	flag1 = 0;
	for(i=0;i<9;i++){
		temp1 = cmd[i];
		lcd_write();
	}
	flag1 = 1;
	i = 0;
	while(msg[i]!='\0'){
		temp1 = msg[i];
		i++;
		lcd_write();
	}
	LPC_SC->PCONP = 1<<15;
	LPC_SC->PCONP |= 1<<12;
	LPC_PINCON->PINSEL3 = (3<<30)|(3<<28);
	while(1){
		LPC_ADC->ADCR = 1<<5|1<<21|1<<24;
		while(!((LPC_ADC->ADDR5>>31)&0X01));
		dig1 = (LPC_ADC->ADDR5 >>4)&0XFFF;
		ana1 = (float)dig1*(3.3/pow(2,12));
		LPC_ADC->ADCR = 1<<4|1<<21|1<<24;
		while(!((LPC_ADC->ADDR4>>31)&0X01));
		dig2 = (LPC_ADC->ADDR4 >>4)&0XFFF;
		ana2 = (float)dig2*(3.3/pow(2,12));
		diff = ana1-ana2;
		sprintf(diffstr,"%3.2fV",diff);
		flag1 = 0;
		temp1 = 0x89;
		lcd_write();
		flag1 = 1;
		i = 0;
		while(diffstr[i]!='\0'){
			temp1 = diffstr[i];
			i++;
			lcd_write();
		}
		for(i=0;i<2000000;i++);
	}
	
}