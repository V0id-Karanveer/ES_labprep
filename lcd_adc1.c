#include<LPC17xx.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
unsigned int flag1=0,temp1=0,temp2=0,i=0,r=0,dig;
float ana;
char strana[16];

void port_write(){
	LPC_GPIO0->FIOPIN = temp2<<23;
	if(flag1 == 1){
		LPC_GPIO0->FIOSET = 1<<27;
	}
	else{
		LPC_GPIO0->FIOCLR = 1<<27;
	}
	LPC_GPIO0->FIOSET = 1<<28;
	for(r=0;r<25;i++);
	LPC_GPIO0->FIOCLR = 1<<28;
	for(r=0;r<30000;i++);
}

void lcd_write(){
	temp2 = temp1&0xf0;
	temp2 = temp2>>4;
	port_write();
	if(!((flag1==0)&&((temp1 == 0x30)||(temp1 == 0x20)))){
		temp2 = temp1&0x0f;
		port_write();
	}
}

int main(){
	char data[] = {"Volatge: "};
	unsigned long int cmd[] = {0x30,0x30,0x30,0x20,0x28,0x01,0x06,0x0C,0x80};
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL1 = 0;
	LPC_GPIO0->FIODIR = 0XF<<23|1<<27|1<<28;
	flag1 =0;
	for(i=0;i<9;i++){
		temp1 = cmd[i];
		lcd_write();
	}
	flag1 = 1;
	i = 0;
	while(data[i]!='\0'){
		if(i==16){
			flag1 = 0;
			temp1 = 0xC0;
			lcd_write();
			flag1 = 1;
		}
		temp1 = data[i];
		lcd_write();
		i++;
	}
	LPC_PINCON->PINSEL3 = 3<<30;
	LPC_SC->PCONP = 1<<15;
	LPC_SC->PCONP |= 1<<12;
	while(1){
		LPC_ADC->ADGDR = 1<<5|1<<21|1<<24;
		while(!((LPC_ADC->ADGDR>>31)&0X01));
		dig = (LPC_ADC->ADGDR >> 4)&0XFFF;
		ana = (float)dig*(3.3/pow(2,12));
		sprintf(strana,"%3.2fV",ana);
		i = 0;
		flag1 = 0;
		temp1 = 0x89;
		lcd_write();
		flag1 = 1;
		i = 0;
		while(strana[i]!='\0'){
			temp1 = strana[i];
			i++;
			lcd_write();
		}
		
		
	}
}
