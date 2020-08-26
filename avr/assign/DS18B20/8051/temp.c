# include<reg51.h>

sbit dq = P3^5; // connect with DS1820 Data pin
sbit led=P3^7;
sbit rs=P3^0;
sbit en=P3^1;

void delay_ms(int j)
{
unsigned char i;

for(;j;j--)
for(i=122;i<=0;i--);
}

void data_lcd(unsigned char dat)
{
P2=dat;
rs=1;
en=1;
delay_ms(200);
en=0;
}
void cmd_lcd(unsigned char cmd)
{
P2=cmd;
rs=0;
en=1;
delay_ms(200);
en=0;
}

void init_lcd()
{
cmd_lcd(0x38);
cmd_lcd(0x01);
cmd_lcd(0x0e);
cmd_lcd(0x06);

}

void str_lcd(unsigned char *p)
{ 
while(*p)
data_lcd(*p++);
}


void delayus(int us)
{
int i;
for (i=0; i<us; i++);
}

bit reset(void)
{
bit presence;
dq = 0;
delayus(29);
dq = 1;
delayus(3);
presence = dq;
delayus(25);
return(presence);
}

bit readbit(void)
{
unsigned char i=0;
dq = 0;
dq=1;
for (i=0; i < 3; i++);
return(dq);
}


void writebit(bit Dbit)
{
unsigned char i=0;
dq=0;
dq = Dbit?1:0;
delayus(5);
dq = 1;
}

unsigned char readbyte(void)
{
unsigned char i;
unsigned char din = 0;
for (i=0;i<8;i++)
{
din|=readbit()? 0x01<<i:din;
delayus(6);
}
return(din);
}

void writebyte(unsigned char dout)
{
unsigned char i;
for (i=0; i<8; i++)
{
writebit((bit)(dout & 0x1));
dout = dout >> 1;
}
delayus(5);
}

unsigned char * ReadTemp()
{
unsigned char n;
unsigned char buff[2]=0;
reset();

writebyte(0xcc);
writebyte(0x44);

while (readbyte()==0xff);
delay_ms(500);

reset();

writebyte(0xcc);
writebyte(0xbe);


for (n=0; n<9; n++)
buff[n]=readbyte();

return buff;
}

void int_lcd(int dat)
{
int str[5]={0},i=0;
if(dat==0)
data_lcd('0');
else
while(dat>0)
{
str[i]= (dat%10)+48;
dat=dat/10;
i++;
}
i--; 
for(;i>=0;i--)
data_lcd(str[i]);
}

 
void main()
{
unsigned char tp,*temp,t=0x00;
init_lcd();
cmd_lcd(0x80);
while(1)
{
 
temp=ReadTemp();

temp[1]=temp[1]&0x07;

tp=temp[0]>>4;
temp[1]=temp[1]<<4;

tp=tp+temp[1];

cmd_lcd(0x80);

str_lcd("Temp :- ");

cmd_lcd(0x89);

int_lcd(tp);
data_lcd(223);
if(tp<35)
{
led=1;
}
else
{
led=0;
}

}
}