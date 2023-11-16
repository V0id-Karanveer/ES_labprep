#include<lpc17xx.H>
int i=0,x;
unsigned long int p[] = {1000,2500,5000,9999};
void pwm_init(){
	LPC_PINCON->PINSEL3 = 2<<14;
	LPC_PWM1->PCR = 0<<4|1<<12;
	LPC_PWM1->PR = 0;
	LPC_PWM1->MCR = 0X3;
	LPC_PWM1->MR0 = 10000;
	LPC_PWM1->LER= 0X7F;
	LPC_PWM1->TCR = 0X2;
	LPC_PWM1->TCR = 0X9;
}

void pulsewidth(unsigned int pulse){
	LPC_PWM1->MR4 = pulse;
	LPC_PWM1->LER = 0X7F;
}

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR=1<<8;
	LPC_GPIO0->FIOPIN = 1<<8;
	for(i=0;i<100;i++);
	while(1){
		
			x = (LPC_GPIO0->FIOPIN>>4)&0XF;
			if(x){
				if(x==1){
					pulsewidth(p[0]);
				}
				if(x==2){
					pulsewidth(p[0]);
				}
				if(x==4){
					pulsewidth(p[0]);
				}
				if(x==8){
					pulsewidth(p[0]);
				}
			}
	
	}
}
