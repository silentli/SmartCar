/*全局变量都定义在这里，方便整理*/
float Prop1,Prop2,Diff1,Diff2,SpeedAver;    /*P1,P2,D1,D2值,平均速度*/
int SpeedMax,SpeedMin,SpeedNow;   /*最大速度,最小速度,当前速度*/
char lcd[100];                    /*用于LCD显示的字符串*/
char SCIreceive[100];             /*用于串口显示的字符串*/
//===============时钟初始化========================//
void SetBusCLK_40M()
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x04;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=80MHz;
    _asm(nop);          //BUS CLOCK=40M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}   
//==============延时程序================================//
void delayms(int ms)    //延时程序。
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<3338;jj++);    //40MHz--1ms      
}