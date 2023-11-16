#include<LPC17XX.H>

void timer_init(){
	LPC_TIM0->TCR = 0X2;
	LPC_TIM0->CTCR = 0;
	LPC_TIM0->MCR = 0X2;
	LPC_TIM0->EMR = 0X20;
	LPC_TIM0->PR = 9999;
	LPC_TIM0->TCR = 0X1;
	LPC_TIM0->MR0 = 2999;
}

int main(){
	unsigned long int sev_seg[] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	int num,n,i,j;
	num = 0;
	SystemInit();
	SystemCoreClockUpdate();
	timer_init();
	LPC_PINCON->PINSEL0 = 0;
	LPC_PINCON->PINSEL10 = 0;
	LPC_PINCON->PINSEL3 = 0;
	LPC_GPIO0->FIODIR = 0XFF<<4;
	LPC_GPIO1->FIODIR = 0XF<<23;
	while(1){
		n = num;
		for(i=0;i<4;i++){
			LPC_GPIO1->FIOPIN = i<<23;
			LPC_GPIO0->FIOPIN = sev_seg[n%10];
			n=n/10;
			for(j=0;j<1000;j++);
			
		}
		if(LPC_TIM0->EMR&0X1){
			LPC_TIM0->EMR = 0X20;
			if((LPC_GPIO0->FIOPIN >>21) & 0X01){
				if(num == 9999){
					num = 0;
				}
				else{
					num--;
				}
			}
			else{
				if(num==0){
					num = 9999;
				}
				else{
					num--;
				}
			}
			
		}
		
	}
	
}