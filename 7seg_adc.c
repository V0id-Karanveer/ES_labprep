#include<LPC17xx.h>
#include<math.h>

int main(){
	int seven_seg[] = {0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; 
	unsigned int dig;
	int n,i,j;
	float ana;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL3 = 3<<30;
	LPC_GPIO0->FIODIR = 0XFF<<4;
	LPC_GPIO1->FIODIR = 0Xf<<23;
	LPC_SC->PCONP = 1<<15;
	LPC_SC->PCONP |=1<<12;
	while(1){
		LPC_ADC->ADCR = 1<<5|1<<21|1<<24;
		while(!((LPC_ADC->ADDR5>>31)&0X01));
		dig = (LPC_ADC->ADDR5>>4)&0XFFF;
		ana  = (float)dig*(3.3/pow(2,12));
		
		n = ana;
		for(i=0;i<4;i++){
			LPC_GPIO1->FIOPIN = i<<23;
			if(i==2){
				LPC_GPIO0->FIOPIN = ((seven_seg[n%10])|0x80)<<4;
			}
			else{
				LPC_GPIO0->FIOPIN = seven_seg[n%10]<<4;
			}
			n = n/10;
			for(j=0;j<1000;j++);
		}
		for(i=0;i<2000000;i++);
		
		
	}
}