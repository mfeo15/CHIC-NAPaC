void setup() {
  // put your setup code here, to run once:

  /*init codec */
  //hal_i2c_init(0,19,18);
  //hal_i2s_init(0,48000,16,2);

  WM8978_Init();
  WM8978_ADDA_Cfg(1, 1);
  WM8978_Input_Cfg(1, 0, 0);
  WM8978_Output_Cfg(1, 0);
  WM8978_MIC_Gain(25);
  WM8978_AUX_Gain(0);
  WM8978_LINEIN_Gain(0);
  WM8978_SPKvol_Set(0);
  WM8978_HPvol_Set(15, 15);
  WM8978_EQ_3D_Dir(0);
  WM8978_EQ1_Set(0, 24);
  WM8978_EQ2_Set(0, 24);
  WM8978_EQ3_Set(0, 24);
  WM8978_EQ4_Set(0, 24);
  WM8978_EQ5_Set(0, 24);

  //TEST
  WM8978_Write_Reg(1, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}
