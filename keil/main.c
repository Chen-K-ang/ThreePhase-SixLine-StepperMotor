#include <reg52.h>
#include "LCD1602.h"
#define uchar unsigned char
#define uint unsigned int

sbit key1 = P1^0;
sbit key2 = P1^1;
sbit key3 = P1^2;
sbit key4 = P1^3;
sbit key5 = P1^7;

uchar flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
int speed = 65;
uchar code zheng[] = {0x09,0x08,0x0c,0x04,0x06,0x02,0x03,0x01};
uchar code fan[] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};

void delay1ms(uint t){
	char i;
	while(t--){
	 	for(i=0;i<113;i++);
	}
}

void Timer1Init(void)		//10毫秒@12.000MHz
{
//	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0xF0;		//设置定时初值
	TH1 = 0xD8;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	ET1 = 1;
	EA = 1;
	TR1 = 1;		//定时器1开始计时
}

void main()
{
	uchar i;
	uchar buf[5];
	LCD1602_init();
	Timer1Init();
	delay1ms(20);
	LCD1602_show_str(1, 0, "Mode:       ");
	LCD1602_show_str(0, 1, "Speed:      ");
	LCD1602_integer_to_str((140-speed), buf);
	LCD1602_show_str(8, 1, buf);
	while(1){
		if(flag1) {
			LCD1602_show_str(8, 0, "Forward ");
			for(i=0;i<8;i++){
				P2 = zheng[i];
				delay1ms(speed);	
			}
		} else if (flag2) {
			LCD1602_show_str(8, 0, "Reversal");
			for(i=0;i<8;i++){
				P2 = fan[i];
				delay1ms(speed);
			}
		}
		else {
		
		}

		if (flag3){
			speed = speed - 5;
			if (speed < 40)
				speed = 40;
			LCD1602_integer_to_str((140-speed), buf);
			LCD1602_show_str(8, 1, buf);
			flag3 = 0;
		} else if (flag4) {
			speed = speed + 5;
			if (speed > 100)
				speed = 100;
			LCD1602_integer_to_str((140-speed), buf);
			LCD1602_show_str(8, 1, buf);
			flag4 = 0;			
		} else {
		
		}
	}
}

void Timer1_ISR(void) interrupt 3
{
	unsigned char temp;
	TR1 = 0;
	TL1 = 0xF0;
	TH1 = 0xD8;

	temp = P1 & 0x8F;
	switch (temp) {
		case 0x8E: flag1 = 1; break;
		case 0x8D: flag2 = 1; break;
		case 0x8B: flag3 = 1; break;
		case 0x87: flag4 = 1; break;
		case 0x0F: flag1 = 0, flag2 = 0; break;
		default: break;		
	}
	TR1 = 1;
}
