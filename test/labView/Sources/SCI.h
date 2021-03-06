/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.06.02
	说明：串口调用及无线模块
----------------------------------------------*/
int SCI_i=0;
int SCI_PWMDTY01,SCI_PWMDTY23;      
int SCI_DP1,SCI_DP2,SCI_DP3,SCI_DP4,SCI_DP5,SCI_DP6,SCI_DP7;
/*--------------------------------------------
SCI_RXD: 串口接收函数
编写日期：20110411
----------------------------------------------*/
char SCI_RXD(void)
{
    char ch; 
    while (!(SCI0SR1 & 0x20));       //等待接收数据完毕
    SCI0SR1_RDRF = 1;
    ch = SCI0DRL;
    return ch;
}
/*---------------------------------------------
SCISend: 串口输出显示函数(显示单个字符)
输入参数：ch：显示的字符；
编写日期：20110411
-----------------------------------------------*/
void SCISend(unsigned char ch)
{ 
  if (ch == '\n')  
  {
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0d;   
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0a;               
     return;
  } 
  else while (!(SCI0SR1&0x80));
    SCI0DRH=0;
    SCI0DRL=ch;
}
/*---------------------------------------------
LCD_write_cizu: 串口输出显示函数(显示字符串)
输入参数：ch：显示的字符串
编写日期：20110411
-----------------------------------------------*/
void SCISend_chars(const signed char ch[])
 {
 int i=0;
 do{
 SCISend(ch[i]);
 i++;
 }while(ch[i]!='\0');
 }
 /*---------------------------------------
SCI_Init: SCI初始化
编写日期：200110411
-----------------------------------------  */
static void SCI_Init(void)  //SCI
{
    SCI0CR1=0x00;
    SCI0CR2=0x2c;
     SCI0BD=260;                     //设置波特率公式=总线频率/所需要的波特率/16=所要设置的值;
                  
}
/*---------------------------------------
发送激光管信息数组
编写日期：200110602
-----------------------------------------  */ 
void Testjiguang(byte temp_laser_array[]) {
    int i; 
    int data;
	SCISend_chars("SEDJG");
    for(i=LASER_MAX-1;i>=0;i--)    //发送激光管信息数组
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        } 
    SCISend_chars("END");
    SCISend('\n'); 		
}     
/*---------------------------------------
发送红外信息数组（不成熟，暂不使用）
编写日期：200110607
----------------------------------------- */ 
void TestIR(uint temp_laser_array[],int Test_IR_position) {
    int i; 
    char data[5];
	SCISend_chars("SEDIR");
    for(i=0;i<=6;i++)    //发送激光管信息数组
        {  
    (void)sprintf(data,"%.3d",temp_laser_array[i]);
		SCISend_chars(data);
        }
		(void)sprintf(data,"%.3d",Test_IR_position+10);		
		SCISend_chars(data);
		SCISend_chars("END");
	    SCISend('\n'); 	
}      
/*---------------------------------------
发送相关参数
编写日期：2001100607
-----------------------------------------  */ 
void Testpara(int test_sdj,int test_xdj,int test_speed,int test_position) {
	(void)sprintf(SCIreceive,"SEDPR%.5d%.4d%.4d%.4dEND",test_position+10000,test_sdj,test_xdj,test_speed);
    SCISend_chars(SCIreceive);  
    SCISend('\n');  
}  
/*---------------------------------------
无线模块发送总函数
编写日期：200110602
参数 t：用于循环几次发送一次
-----------------------------------------  */  
void TestSMinfo(void){
Testjiguang(light_temp_laser_array);	//发送激光数组
Testpara(PWMDTY67,PWMDTY45,speed_clera[1],JG_clear[3]);//发送相关参数
TestIR(IR_temp_laser_array,IR_position[1]);
}
/*---------------------------------------
无线模块接收处理
编写日期：200110611
参数  command：填入字符串处理
-----------------------------------------  */ 
void SCI_REC_chuli(char a[])
{
	char *p;
	char rectemp[10];
	switch(a[strlen(a)-1]){
 	  case '@':{
	p = strtok(a, ";");
	if(p!='F'){SCI_DP1=atoi(p));DP1=SCI_DP1;} 
	p = strtok(NULL, ";");
	if(p!='F'){SCI_DP2=atoi(p));DP2=SCI_DP2;} 
	p = strtok(NULL, ";");
	if(p!='F'){SCI_DP3=atoi(p));DP3=SCI_DP3;} 
	p = strtok(NULL, ";");
	if(p!='F'){SCI_DP4=atoi(p));DP4=SCI_DP4;} 
	p = strtok(NULL, ";");
	if(p!='F'){SCI_DP5=atoi(p));DP5=SCI_DP5;} 
	p = strtok(NULL, ";");
	if(p!='F'){SCI_DP6=atoi(p));DP6=SCI_DP6;} 
	p = strtok(NULL, ";");
	if(p!='F'){SCI_DP7=atoi(p));DP7=SCI_DP7;} 
      }
      break;   
	case '*':{
	p = strtok(a, "*");
	SCI_PWMDTY01=atoi(p); 
	PWMDTY01=SCI_PWMDTY01;
	}
	break;
	case '%':{
	p = strtok(a, "%");
	SCI_PWMDTY23=atoi(p); 
	PWMDTY23=SCI_PWMDTY23;
	}
	break;
	}
}

 	    

/*---------------------------------------
无线串口中断接收
编写日期：20110411
-----------------------------------------*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SCI(void)
{
    DisableInterrupts;  
      SCIreceive[SCI_i]=SCI_RXD();
      switch(SCIreceive[SCI_i]) {
        case '@': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive);
         // SCISend_chars(SCIreceive);
        }  
        break;
        case '*': 
        {
          SCI_i=0;
         SCI_REC_chuli(SCIreceive);
        } 
        case '%': 
        {
          SCI_i=0;
        SCI_REC_chuli(SCIreceive);
        }  
        break;
      default:
        SCI_i++;
         break; 
      }
    EnableInterrupts;
} 
#pragma CODE_SEG DEFAULT