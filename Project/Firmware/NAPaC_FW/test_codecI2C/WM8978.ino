#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <Wire.h>

#define WM8978_ADDR 0X1A
 
#define EQ1_80Hz    0X00
#define EQ1_105Hz   0X01
#define EQ1_135Hz   0X02
#define EQ1_175Hz   0X03

#define EQ2_230Hz   0X00
#define EQ2_300Hz   0X01
#define EQ2_385Hz   0X02
#define EQ2_500Hz   0X03

#define EQ3_650Hz   0X00
#define EQ3_850Hz   0X01
#define EQ3_1100Hz    0X02
#define EQ3_14000Hz   0X03

#define EQ4_1800Hz    0X00
#define EQ4_2400Hz    0X01
#define EQ4_3200Hz    0X02
#define EQ4_4100Hz    0X03

#define EQ5_5300Hz    0X00
#define EQ5_6900Hz    0X01
#define EQ5_9000Hz    0X02
#define EQ5_11700Hz   0X03

const int SDA = 26;
const int SCL = 25;

// WM8978 register value buffer zone (total 58 registers 0 to 57), occupies 116 bytes of memory
// Because the IIC WM8978 operation does not support read operations, so save all the register values in the local
// Write WM8978 register, synchronized to the local register values, register read, register directly back locally stored value.
// Note: WM8978 register value is 9, so use uint16_t storage.
static uint16_t WM8978_REGVAL_TBL[58]=
{
  0X0000,0X0000,0X0000,0X0000,0X0050,0X0000,0X0140,0X0000,
  0X0000,0X0000,0X0000,0X00FF,0X00FF,0X0000,0X0100,0X00FF,
  0X00FF,0X0000,0X012C,0X002C,0X002C,0X002C,0X002C,0X0000,
  0X0032,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,
  0X0038,0X000B,0X0032,0X0000,0X0008,0X000C,0X0093,0X00E9,
  0X0000,0X0000,0X0000,0X0000,0X0003,0X0010,0X0010,0X0100,
  0X0100,0X0002,0X0001,0X0001,0X0039,0X0039,0X0039,0X0039,
  0X0001,0X0001
}; 

//WM8978 init
uint8_t WM8978_Init(void)
{
  Wire.begin(SDA,SCL,2);
  
  uint8_t res;
  res=WM8978_Write_Reg(0,0);
  if(res)return 1;
  
  WM8978_Write_Reg(1,0X1B); 
  WM8978_Write_Reg(2,0X1B0); 
  WM8978_Write_Reg(3,0X6C);  
  WM8978_Write_Reg(6,0);    
  WM8978_Write_Reg(43,1<<4); 
  WM8978_Write_Reg(47,1<<8);  
  WM8978_Write_Reg(48,1<<8);  
  WM8978_Write_Reg(49,1<<1);  
  WM8978_Write_Reg(10,1<<3);  
  WM8978_Write_Reg(14,1<<3);
  return 0;
}

uint8_t WM8978_Write_Reg(uint8_t reg,uint16_t val)
{ 
  byte buf[2];
  buf[0] = (reg<<1)|((val>>8)&0X01);
  buf[1] = val&0XFF;
  Wire.beginTransmission(WM8978_ADDR);
  Wire.write(buf,2);
  Wire.endTransmission();  
  WM8978_REGVAL_TBL[reg]=val;
  return 0; 
}  

// WM8978 read register
// Reads the value  of the local register buffer zone
// reg: Register Address
// Return Value: Register value
uint16_t WM8978_Read_Reg(uint8_t reg)
{  
  return WM8978_REGVAL_TBL[reg];  
} 

void WM8978_ADDA_Cfg(uint8_t dacen,uint8_t adcen)
{
  uint16_t regval;
  regval=WM8978_Read_Reg(3);  
  if(dacen)regval|=3<<0;    
  else regval&=~(3<<0);   
  WM8978_Write_Reg(3,regval); 
  regval=WM8978_Read_Reg(2);  
  if(adcen)regval|=3<<0;  
  else regval&=~(3<<0); 
  WM8978_Write_Reg(2,regval); 
}

void WM8978_Input_Cfg(uint8_t micen,uint8_t lineinen,uint8_t auxen)
{
  uint16_t regval;  
  regval=WM8978_Read_Reg(2);
  if(micen)regval|=3<<2;
  else regval&=~(3<<2);
  WM8978_Write_Reg(2,regval);
  
  regval=WM8978_Read_Reg(44);
  if(micen)regval|=3<<4|3<<0;
  else regval&=~(3<<4|3<<0);
  WM8978_Write_Reg(44,regval);
  
  if(lineinen)WM8978_LINEIN_Gain(5);
  else WM8978_LINEIN_Gain(0);
  if(auxen)WM8978_AUX_Gain(7);
  else WM8978_AUX_Gain(0);  
}

void WM8978_Output_Cfg(uint8_t dacen,uint8_t bpsen)
{
  uint16_t regval=0;
  if(dacen)regval|=1<<0;
  if(bpsen)
  {
    regval|=1<<1;
    regval|=5<<2;
  } 
  WM8978_Write_Reg(50,regval);
  WM8978_Write_Reg(51,regval);
}

void WM8978_MIC_Gain(uint8_t gain)
{
  gain&=0X3F;
  WM8978_Write_Reg(45,gain); 
  WM8978_Write_Reg(46,gain|1<<8);
}

void WM8978_LINEIN_Gain(uint8_t gain)
{
  uint16_t regval;
  gain&=0X07;
  regval=WM8978_Read_Reg(47);
  regval&=~(7<<4);
  WM8978_Write_Reg(47,regval|gain<<4);
  regval=WM8978_Read_Reg(48);
  regval&=~(7<<4);
  WM8978_Write_Reg(48,regval|gain<<4);
} 

void WM8978_AUX_Gain(uint8_t gain)
{
  uint16_t regval;
  gain&=0X07;
  regval=WM8978_Read_Reg(47);
  regval&=~(7<<0);
  WM8978_Write_Reg(47,regval|gain<<0);
  regval=WM8978_Read_Reg(48);
  regval&=~(7<<0); 
  WM8978_Write_Reg(48,regval|gain<<0);
}  

void WM8978_I2S_Cfg(uint8_t fmt,uint8_t len)
{
  fmt&=0X03;
  len&=0X03;
  WM8978_Write_Reg(4,(fmt<<3)|(len<<5)); 
} 

void WM8978_HPvol_Set(uint8_t voll,uint8_t volr)
{
  voll&=0X3F;
  volr&=0X3F;//限定范围
  if(voll==0)voll|=1<<6;
  if(volr==0)volr|=1<<6; 
  WM8978_Write_Reg(52,voll);
  WM8978_Write_Reg(53,volr|(1<<8));
}

void WM8978_SPKvol_Set(uint8_t volx)
{ 
  volx&=0X3F;
  if(volx==0)volx|=1<<6;
  WM8978_Write_Reg(54,volx);
  WM8978_Write_Reg(55,volx|(1<<8));
}

void WM8978_3D_Set(uint8_t depth)
{ 
  depth&=0XF;
  WM8978_Write_Reg(41,depth);  
}

void WM8978_EQ_3D_Dir(uint8_t dir)
{
  uint16_t regval; 
  regval=WM8978_Read_Reg(0X12);
  if(dir)regval|=1<<8;
  else regval&=~(1<<8); 
  WM8978_Write_Reg(18,regval);
}

void WM8978_EQ1_Set(uint8_t cfreq,uint8_t gain)
{ 
  uint16_t regval;
  cfreq&=0X3; 
  if(gain>24)gain=24;
  gain=24-gain;
  regval=WM8978_Read_Reg(18);
  regval&=0X100;
  regval|=cfreq<<5;
  regval|=gain;  
  WM8978_Write_Reg(18,regval);  
}

void WM8978_EQ2_Set(uint8_t cfreq,uint8_t gain)
{ 
  uint16_t regval=0;
  cfreq&=0X3;
  if(gain>24)gain=24;
  gain=24-gain; 
  regval|=cfreq<<5;
  regval|=gain; 
  WM8978_Write_Reg(19,regval);  
}

void WM8978_EQ3_Set(uint8_t cfreq,uint8_t gain)
{ 
  uint16_t regval=0;
  cfreq&=0X3;
  if(gain>24)gain=24;
  gain=24-gain; 
  regval|=cfreq<<5; 
  regval|=gain;
  WM8978_Write_Reg(20,regval);  
}

void WM8978_EQ4_Set(uint8_t cfreq,uint8_t gain)
{ 
  uint16_t regval=0;
  cfreq&=0X3; 
  if(gain>24)gain=24;
  gain=24-gain; 
  regval|=cfreq<<5; 
  regval|=gain;  
  WM8978_Write_Reg(21,regval);   
}

void WM8978_EQ5_Set(uint8_t cfreq,uint8_t gain)
{ 
  uint16_t regval=0;
  cfreq&=0X3; 
  if(gain>24)gain=24;
  gain=24-gain; 
  regval|=cfreq<<5; 
  regval|=gain; 
  WM8978_Write_Reg(22,regval);   
}

void WM8978_ALC_Set(uint8_t enable, uint8_t maxgain, uint8_t mingain)
{ 
  uint16_t regval;

  if(maxgain>7) maxgain=7;
  if(mingain>7) mingain=7;

  regval=WM8978_Read_Reg(32);
  if(enable)
    regval |= (3<<7);
  regval |= (maxgain<<3)|(mingain<<0);
  WM8978_Write_Reg(32,regval);
}

void WM8978_Noise_Set(uint8_t enable,uint8_t gain)
{ 
  uint16_t regval;

  if(gain>7) gain=7;

  regval=WM8978_Read_Reg(35);
  regval = (enable<<3);
  regval|=gain;  
  WM8978_Write_Reg(35,regval);  
}
