#include<LPC17xx.h>
int main(){
	int i,r;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 = 0;
	LPC_GPIO0->FIODIR = 0XFF<<4;
	while(1){
		for(i=0;i<8;i++){
			LPC_GPIO0->FIOPIN = 1<<(i+4);
			for(r=0;r<3000;r++);
		}
  }
}