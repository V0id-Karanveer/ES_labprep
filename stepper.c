#include<LPC17xx.h>
int var1,i,j,r;
void clockwise(){
	var1 = 0x8;
	for(i=0;i<4;i++){
		var1 = var1<<1;
		LPC_GPIO0->FIOPIN=~var1;
		for(j=0;j<40000;j++);
	}
	
}

void anticlock(){
	var1=0x100;
	for(i=0;i<4;i++){
		var1 = var1>>4;
		LPC_GPIO0->FIOPIN = var1;
		for(j=0;j<40000;j++);
	}
}

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	for(r=0;r<50;r++){
		clockwise();
	}

}