#ifndef HARDWARE_LCD1602_H
#define HARDWARE_LCD1602_H

#include <reg52.h>
#include <stdio.h>
#include <math.h>

#define LCD1602_DB  P0  //���ݶ˿ڶ���
sbit LCD1602_RS = P1^4; //RS
sbit LCD1602_RW = P1^5; //RW
sbit LCD1602_EN = P1^6; //E

//LCD1602ָ��
//��ʾģʽ����ָ��
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//  0   0   1   DL  N   F   *   *
// DL = 1��8λ���ݽӿڣ� DL = 0��4λ���ݽӿڡ�
// N  = 1��������ʾ��    N  = 0��������ʾ��
// F  = 1��5*10�����ַ���F  = 0, 5*8�����ַ�
#define LCD_MODE_PIN8      0x38 //8λ���ݽӿڣ����У�5*8����
#define LCD_MODE_PIN4      0x28 //4λ���ݽӿڣ����У�5*8����

#define LCD_SCREEN_CLR     0x01 //����
#define LCD_CURSOR_RST     0x02 //��긴λ

//��ʾ���ؿ���ָ��
#define LCD_DIS_CUR_BLK_ON 0x0F //��ʾ������꿪�������˸
#define LCD_DIS_CUR_ON     0x0E //��ʾ������꿪����겻��˸
#define LCD_DIS_ON         0x0C //��ʾ�������أ���겻��˸
#define LCD_DIS_OFF        0x08 //��ʾ�أ����أ���겻��˸

//��ʾģʽ����
#define LCD_CURSOR_RIGHT   0x06 //������ƣ���ʾ���ƶ�(proteus�������)
#define LCD_CURSOR_LEFT    0x04 //������ƣ���ʾ���ƶ�
#define LCD_DIS_MODE_RIGHT 0x05 //������AC�Լ�������ƽ��
#define LCD_DIS_MODE_LEFT  0x07 //������AC����������ƽ��

//��ꡢ��ʾ�ƶ�ָ��
#define LCD_CUR_MOVE_LEFT  0x10 //�������
#define LCD_CUR_MOVE_RIGHT 0x14 //�������
#define LCD_DIS_MOVE_LEFT  0x18 //��ʾ����
#define LCD_DIS_MOVE_RIGHT 0x1C //��ʾ����

//����
#define LCD_SET_CGRAM_ADDR 0x40
#define LCD_MODE_FIR       0x80 //��һ����ʾ
#define LCD_MODE_SEC       0xC0 //�ڶ�����ʾ

void LCD1602_write_cmd(unsigned char cmd);
void LCD1602_write_data(unsigned char dat);
void LCD1602_init(void);
void LCD1602_show_str(unsigned char x, unsigned char y, unsigned char *str);
void LCD1602_set_char(unsigned char x, unsigned char y, unsigned char pos, unsigned char *str);
unsigned char LCD1602_integer_to_str(int dat, unsigned char *str);
void LCD1602_char_to_str(unsigned char dat, unsigned char *str);
// CGRAM ��ַ���ã�character generator RAM (0~3FH)
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//  0   1   A5  A4  A3  A2  A1  A0

// DDRAM ��ַ����
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//  1   A6   A5  A4  A3  A2  A1  A0
// N  = 0��������ʾ A6~A0 = 00H~4FH
// N  = 1��������ʾ A6~A0 = 00H~27H
//         ������ʾ A6~A0 = 40H~67H

// ��BF��ACֵ(BF:Busy Flag)
// RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//  0  1  BF  A6  A5  A4  A3  A2  A1  A0

//д����
#endif