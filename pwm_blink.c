#include<LPC17XX.h>
long int flag=0;
void pwm_init(){
	LPC_SC->PCONP = 1<<15;
	LPC_SC->PCONP|=1<<12;
	LPC_PINCON->PINSEL3 = 2<<14;
	LPC_PWM1->PCR=0<<4|1<<12;
	LPC_PWM1->PR = 0;
	LPC_PWM1->MCR = 0X3;
	LPC_PWM1->MR4 = 50;
	LPC_PWM1->LER = 0X7F;
	LPC_PWM1->TCR = 0X2;
	LPC_PWM1->TCR = 0X9;
	NVIC_EnableIRQ(PWM1_IRQn);
}

void PWM1_IRQHandler(void){
	
	LPC_PWM1->IR = 0X01;
	if(flag==0x00){
		LPC_PWM1->MR4+=50;
		LPC_PWM1->LER = 0X7F;
		if(LPC_PWM1->MR4>29900){
			flag = 0xff;
		}
	}
	else if(flag == 0xff){
		LPC_PWM1->MR4 -=50;
		LPC_PWM1->LER = 0X7F;
		if(LPC_PWM1->MR4<100){
			flag=0x00;
		}
	}
}

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	pwm_init();
	while(1);
}