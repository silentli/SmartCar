/*--------------------------------------------
	Written by:	Unkown
	Modify by: 	林震
    Date:       2011.04.09
    Update:     2011.04.10
	说明：LCD显示初始化及相关函数调用
----------------------------------------------*/
#define uchar 	unsigned char
#define uint 	unsigned int
#define RST PTM_PTM4      		//复位用B5口   
#define SCE PTM_PTM3          //片选用B6口
#define DC PTM_PTM2           //DC用A5口
#define SDIN PTM_PTM1         //数据用A6口
#define SCLK PTM_PTM0       	//时钟用A7口
/*
sbit    \SCE = SCE;  //片选		
sbit    \RST = RST;  //复位,0复位
sbit    D/C  = DC;  //1写数据，0写指令
sbit    SDIN = SDIN;  //数据
sbit    SCLK = SCLK;  //时钟
*/

/*--------------------------------------------
data: 5*8字符
说明：根据ASCII码排列，字模数据是由空格(sp)开始,空格字符的ASCII的值就是32  
编写日期：20110409 
----------------------------------------------*/
unsigned char data[]={
0x00, 0x00, 0x00, 0x00, 0x00,   // sp     
0x00, 0x00, 0x2f, 0x00, 0x00,   // !     
0x00, 0x07, 0x00, 0x07, 0x00,   // "     
0x14, 0x7f, 0x14, 0x7f, 0x14,   // #     
0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $     
0x62, 0x64, 0x08, 0x13, 0x23,   // %     
0x36, 0x49, 0x55, 0x22, 0x50,   // &     
0x00, 0x05, 0x03, 0x00, 0x00,   // ’     
0x00, 0x1c, 0x22, 0x41, 0x00,   // (     
0x00, 0x41, 0x22, 0x1c, 0x00,   // )     
0x14, 0x08, 0x3E, 0x08, 0x14,   // *     
0x08, 0x08, 0x3E, 0x08, 0x08,   // +     
0x00, 0x00, 0xA0, 0x60, 0x00,   // ,     
0x08, 0x08, 0x08, 0x08, 0x08,   // -     
0x00, 0x60, 0x60, 0x00, 0x00,   // .     
0x20, 0x10, 0x08, 0x04, 0x02,   // /     
0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0     
0x00, 0x42, 0x7F, 0x40, 0x00,   // 1     
0x42, 0x61, 0x51, 0x49, 0x46,   // 2     
0x21, 0x41, 0x45, 0x4B, 0x31,   // 3     
0x18, 0x14, 0x12, 0x7F, 0x10,   // 4     
0x27, 0x45, 0x45, 0x45, 0x39,   // 5     
0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6     
0x01, 0x71, 0x09, 0x05, 0x03,   // 7     
0x36, 0x49, 0x49, 0x49, 0x36,   // 8     
0x06, 0x49, 0x49, 0x29, 0x1E,   // 9     
0x00, 0x36, 0x36, 0x00, 0x00,   // :     
0x00, 0x56, 0x36, 0x00, 0x00,   // ;     
0x08, 0x14, 0x22, 0x41, 0x00,   // <     
0x14, 0x14, 0x14, 0x14, 0x14,   // =     
0x00, 0x41, 0x22, 0x14, 0x08,   // >     
0x02, 0x01, 0x51, 0x09, 0x06,   // ?     
0x32, 0x49, 0x59, 0x51, 0x3E,   // @     
0x7C, 0x12, 0x11, 0x12, 0x7C,   // A     
0x7F, 0x49, 0x49, 0x49, 0x36,   // B     
0x3E, 0x41, 0x41, 0x41, 0x22,   // C     
0x7F, 0x41, 0x41, 0x22, 0x1C,   // D     
0x7F, 0x49, 0x49, 0x49, 0x41,   // E     
0x7F, 0x09, 0x09, 0x09, 0x01,   // F     
0x3E, 0x41, 0x49, 0x49, 0x7A,   // G     
0x7F, 0x08, 0x08, 0x08, 0x7F,   // H     
0x00, 0x41, 0x7F, 0x41, 0x00,   // I     
0x20, 0x40, 0x41, 0x3F, 0x01,   // J     
0x7F, 0x08, 0x14, 0x22, 0x41,   // K     
0x7F, 0x40, 0x40, 0x40, 0x40,   // L     
0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M     
0x7F, 0x04, 0x08, 0x10, 0x7F,   // N     
0x3E, 0x41, 0x41, 0x41, 0x3E,   // O     
0x7F, 0x09, 0x09, 0x09, 0x06,   // P     
0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q     
0x7F, 0x09, 0x19, 0x29, 0x46,   // R     
0x46, 0x49, 0x49, 0x49, 0x31,   // S     
0x01, 0x01, 0x7F, 0x01, 0x01,   // T     
0x3F, 0x40, 0x40, 0x40, 0x3F,   // U     
0x1F, 0x20, 0x40, 0x20, 0x1F,   // V     
0x3F, 0x40, 0x38, 0x40, 0x3F,   // W     
0x63, 0x14, 0x08, 0x14, 0x63,   // X     
0x07, 0x08, 0x70, 0x08, 0x07,   // Y     
0x61, 0x51, 0x49, 0x45, 0x43,   // Z     
0x00, 0x7F, 0x41, 0x41, 0x00,   // [     
0x55, 0x2A, 0x55, 0x2A, 0x55,   // 55     
0x00, 0x41, 0x41, 0x7F, 0x00,   // ]     
0x04, 0x02, 0x01, 0x02, 0x04,   // ^     
0x40, 0x40, 0x40, 0x40, 0x40,   // _     
0x00, 0x01, 0x02, 0x04, 0x00,   // ’     
0x20, 0x54, 0x54, 0x54, 0x78,   // a     
0x7F, 0x48, 0x44, 0x44, 0x38,   // b     
0x38, 0x44, 0x44, 0x44, 0x20,   // c     
0x38, 0x44, 0x44, 0x48, 0x7F,   // d     
0x38, 0x54, 0x54, 0x54, 0x18,   // e     
0x08, 0x7E, 0x09, 0x01, 0x02,   // f     
0x18, 0xA4, 0xA4, 0xA4, 0x7C,   // g     
0x7F, 0x08, 0x04, 0x04, 0x78,   // h     
0x00, 0x44, 0x7D, 0x40, 0x00,   // i     
0x40, 0x80, 0x84, 0x7D, 0x00,   // j     
0x7F, 0x10, 0x28, 0x44, 0x00,   // k     
0x00, 0x41, 0x7F, 0x40, 0x00,   // l     
0x7C, 0x04, 0x18, 0x04, 0x78,   // m     
0x7C, 0x08, 0x04, 0x04, 0x78,   // n     
0x38, 0x44, 0x44, 0x44, 0x38,   // o     
0xFC, 0x24, 0x24, 0x24, 0x18,   // p     
0x18, 0x24, 0x24, 0x18, 0xFC,   // q     
0x7C, 0x08, 0x04, 0x04, 0x08,   // r     
0x48, 0x54, 0x54, 0x54, 0x20,   // s     
0x04, 0x3F, 0x44, 0x40, 0x20,   // t     
0x3C, 0x40, 0x40, 0x20, 0x7C,   // u     
0x1C, 0x20, 0x40, 0x20, 0x1C,   // v     
0x3C, 0x40, 0x30, 0x40, 0x3C,   // w     
0x44, 0x28, 0x10, 0x28, 0x44,   // x     
0x1C, 0xA0, 0xA0, 0xA0, 0x7C,   // y     
0x44, 0x64, 0x54, 0x4C, 0x44,   // z     
0x00, 0x08, 0x36, 0x41, 0x00,   // {     
0x00, 0x00, 0x7F, 0x00, 0x00,   // |     
0x00, 0x41, 0x36, 0x08, 0x00,   // }     
0x08, 0x10, 0x08, 0x04, 0x08   // ~    
};

/*--------------------------------------------
hanzi: 自定义汉字字库
说明：如需添加汉字，在最后面按顺序添加，切勿中间插入
编写日期：20110409 
----------------------------------------------*/
unsigned char hanzi[]=
{
/*--  文字:  厦  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xFF,0x05,0x05,0xF5,0x55,0x5D,0x55,0x55,0x55,0x55,0xF5,0x05,0x01,0x00,
0x40,0x30,0x0F,0x80,0xA0,0x97,0xBD,0x55,0x55,0x55,0x55,0x55,0xB7,0x80,0x80,0x00,

/*--  文字:  门  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xF8,0x01,0x06,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,

/*--  文字:  大  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,

/*--  文字:  学  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x30,0x11,0x96,0x90,0x90,0x91,0x96,0x90,0x90,0x98,0x14,0x13,0x50,0x30,0x00,
0x04,0x04,0x04,0x04,0x04,0x44,0x84,0x7E,0x06,0x05,0x04,0x04,0x04,0x04,0x04,0x00,

/*--  文字:  嘉  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x02,0x02,0x0A,0xEA,0xAA,0xAA,0xAA,0xAF,0xAA,0xAA,0xAA,0xEA,0x0A,0x02,0x02,0x00,
0x82,0x4A,0x2A,0x1E,0x0B,0x4A,0x8A,0x7A,0x02,0xFA,0x4B,0x4A,0x4A,0xFA,0x02,0x00,

/*--  文字:  庚 --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xFC,0x04,0x24,0x24,0x24,0x25,0xF6,0x24,0x24,0x24,0xE4,0x04,0x04,0x00,
0x40,0x30,0x8F,0x81,0x49,0x49,0x29,0x19,0x0F,0x19,0x29,0x49,0x4F,0x81,0x81,0x00,

/*--  文字:  学  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x30,0x10,0x12,0x5C,0x54,0x50,0x51,0x5E,0xD4,0x50,0x18,0x57,0x32,0x10,0x00,
0x00,0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

/*--  文字:  院  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0xFE,0x02,0x32,0x4A,0x86,0x0C,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x0C,0x04,0x00,
0xFF,0x00,0x02,0x04,0x83,0x41,0x31,0x0F,0x01,0x01,0x7F,0x81,0x81,0x81,0xF1,0x00,

/*--  文字:  光  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x40,0x42,0x44,0x58,0xC0,0x40,0x7F,0x40,0xC0,0x50,0x48,0x46,0x40,0x40,0x00,
0x80,0x80,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x3F,0x40,0x40,0x40,0x40,0x78,0x00,

/*--  文字:  电  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,

/*--  文字:  一  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  队  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xFE,0x02,0x22,0xDA,0x06,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xFF,0x08,0x10,0x88,0x47,0x20,0x18,0x07,0x00,0x07,0x18,0x20,0x40,0x80,0x00,
};
//==============延时程序================================//
void delayms(int ms)    //延时程序。
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<3338;jj++);    //40MHz--1ms      
}
/*--------------------------------------------
LCD_write_byte: 使用SPI接口写数据到LCD
输入参数：dt：写入的数据；
command ：写数据/命令选择；
编写日期：20080918 
----------------------------------------------*/
void LCD_write_byte(unsigned char dt, unsigned char command)
{
	unsigned char i; 
	SCE=0;	
	DC=command;	
	for(i=0;i<8;i++)
	{ 
		if(dt&0x80)
			SDIN=1;
		else
			SDIN=0;
		dt=dt<<1;		
		SCLK=0; 		
		SCLK=1; 
	}	
	DC=1;	
	SCE=1;	
	SDIN=1;
}
/*---------------------------------------
LCD_start: 5110LCD初始化
编写日期：20080918 
-----------------------------------------  */
void LCD_start(void)
{
	  RST=0;  	
  	delayms(1);
  	RST=1;  
	LCD_write_byte(0x21,0);//初始化Lcd,功能设定使用扩充指令
	LCD_write_byte(0xd0,0);//设定液晶偏置电压
	LCD_write_byte(0x20,0);//使用基本指令
	LCD_write_byte(0x0C,0);//设定显示模式，正常显示
}
/*---------------------------------------------
LCD_position: 显示LCD字符当前位置
说明：判断当前位置并返回到lcdx和lcdy这两个全局变量，lcdx是行，lcdy是列
编写日期：20110410
-----------------------------------------------
void LCD_position(unsigned char row, unsigned char line)
 {

  int i;
  row++;
  i=row;
  if(i%13==0&&i!=0)
 {
  line++;
  row=0; 
 }
 lcdx=line;
 lcdy=row;
}                       */
/*-------------------------------------------
LCD_set_XY: 设置LCD坐标函数
输入参数：X：0－83  Y：0－5
编写日期：20080918 
---------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y)
{
	LCD_write_byte(0x40 | Y, 0);// column
	LCD_write_byte(0x80 | X, 0);// row
} 

/*------------------------------------------
LCD_clear: LCD清屏函数
编写日期：20080918 
--------------------------------------------*/
void LCD_clear(void)
{
	unsigned char t;
	unsigned char k;
	LCD_set_XY(0,0);
	for(t=0;t<6;t++)
	{ 
		for(k=0;k<84;k++)
		{ 
			LCD_write_byte(0x00,1);
				
		} 
	}
}

/*---------------------------------------------
LCD_write_zi: 显示5（宽）*8（高）点阵列数字字母符号等半角类
输入参数：c：显示的字符；
编写日期：20110409 
-----------------------------------------------*/
void LCD_write_zi(unsigned char row, unsigned char line,unsigned char c) //row:列 line:行 dd:字符
{
unsigned char i=0;     
unsigned int No;     
No=c-32;                 //字模数据是由空格开始,空格字符的ASCII的值就是32  
No*=5;  
	LCD_set_XY(row, line);// 列，行
while(i<5)                     //一个字符的字模是5个字节,就是5*8点阵     
  {      
    LCD_write_byte(data[No],1);       
    i++;     
   No++;
  } 
}
/*---------------------------------------------
LCD_write_cizu: 显示5（宽）*8（高）点阵列数字字母符号等半角类字符串
输入参数：c：显示的字符串
编写日期：20110410
-----------------------------------------------*/
 void LCD_write_cizu(unsigned char row, unsigned char line,const char a[]) //row:列 line:行 dd:字符 
 {
 int i;
 for(i=0;i<strlen(a);i++) {
 if(row>80)
 {
  line++;
  row=0;
  LCD_write_zi( row+=6,line,a[i]); 
 } 
 else if(a[i]=='\n'){
  line++;
  row=0;
 } 
 else LCD_write_zi( row+=6,line,a[i]); 
 }
 }


/*---------------------------------------------
LCD_write_hanzi: 显示16（宽）*16（高）点阵列汉字等半角类
输入参数：c：显示的字符；
编写日期：20080918 
-----------------------------------------------*/
void LCD_write_hanzi(unsigned char row, unsigned char line,unsigned char c) //row:列 line:行 dd:字符
{
	unsigned char i;  	
	
	LCD_set_XY(row*4, line);// 列，行 
	for(i=0; i<16;i++) 
	{
		LCD_write_byte(hanzi[c*32+i],1); 
	}
	
    LCD_set_XY(row*4, line+1);// 列，行 
	for(i=16; i<32;i++) 
	{
		LCD_write_byte(hanzi[c*32+i],1);
	}	
}
/*---------------------------------------------
LCD_startshow: 显示屏启动时显示"厦门大学嘉庚学院光电一队"
编写日期：20110409
-----------------------------------------------*/
void LCD_startshow(void) 
{
	LCD_write_hanzi(0,0,0);   //厦
	LCD_write_hanzi(5,0,1);   //门
	LCD_write_hanzi(10,0,2);  //大
	LCD_write_hanzi(15,0,3);  //学
	
	LCD_write_hanzi(0,2,4);   //嘉
	LCD_write_hanzi(5,2,5);   //庚
	LCD_write_hanzi(10,2,6);  //学
	LCD_write_hanzi(15,2,7);  //院
	
	LCD_write_hanzi(0,4,8);   //光
	LCD_write_hanzi(5,4,9);   //电
	LCD_write_hanzi(10,4,10); //一
	LCD_write_hanzi(16,4,11); //队
  delayms(5000);
	}