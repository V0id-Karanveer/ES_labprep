#include<LPC17xx.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
int cnt,flag1,temp1,temp2,r,i,k,j,x,c,key,a,b,ans;
char op;
char ansstr[2];
void port_write(){
	LPC_GPIO0->FIOPIN = temp2<<23;
	if(flag1==0){
		LPC_GPIO0->FIOCLR = 1<<27;
	}
	else{
		LPC_GPIO0->FIOSET = 1<<27;
	}
	LPC_GPIO0->FIOSET = 1<<28;
	for(r=0;r<25;r++);
	LPC_GPIO0->FIOCLR = 1<<28;
	for(r=0;r<25;r++);
}

void lcd_write(){
	temp2 = temp1&0xf0;
	temp2 = temp2>>4;
	port_write();
	if(!((flag1=0)&&(temp1==0x30||temp1==0x20))){
		temp2 = temp1&0x0f;
		port_write();
	}
}
int main(){
	
	unsigned long int cmd[] = {0x30,0x30,0x30,0x20,0x28,0x01,0x06,0x0C,0x080};
	char ascii[][4] = {{'0','1','2','3'},{'0','1','2','3'},{'0','1','2','3'},{'0','1','2','3'}};
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL1 = 0;
	LPC_PINCON->PINSEL3 = 0;
	LPC_PINCON->PINSEL4=0;
	LPC_GPIO0->FIODIR = 0XF<<23|1<<27|1<<28;
	LPC_GPIO2->FIODIR = 0XF<<10;
	LPC_GPIO1->FIODIR = 0;
	flag1 = 0;
	for(i=0;i<9;i++){
		temp1 = cmd[i];
		lcd_write();
	}
	flag1 =1;
	while(cnt<3){
		for(k=0;k<4;k++){
			LPC_GPIO2->FIOPIN = 1<<(k+10);
			for(j=0;j<100;j++);
			x = LPC_GPIO1->FIOPIN>>23&0XF;
			if(x){
				if(x==1){
					c = 0;
				}
				if(x==2){
					c = 1;
				}
				if(x==4){
					c = 2;
				}
				if(x==8){
					c = 3;
				}
				
			}
			
			key = ascii[k][c];
			temp1 = key;
			lcd_write();
			if(cnt==0){
				a = key-0x30;
			}
			if(cnt==1){
				op = key;
			}
			if(cnt==2){
				b = key-0x30;
			}
			cnt++;
			for(j=0;j<200000;j++);
		}
		
	}
	switch(op){
		case '+':
			ans = a+b;
			break;
		case '-':
			ans = a-b;
			break;
	}
	sprintf(ansstr,"%d",ans);
	i=0;
	flag1 = 0;
	temp1 = 0xC0;
	lcd_write();
	flag1 =1;
	while(ansstr[i]!='\0'){
		temp1 = ansstr[i];
		i++;
		lcd_write();
	}
}