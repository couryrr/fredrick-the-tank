//data display from right to left, from bottom to top, HIGH level display. 
#define IIC_SCL  A5
#define IIC_SDA  A4

unsigned char data_line = 0;
unsigned char delay_count = 0;
unsigned char data_display1 = 0;
unsigned char data_display2 = 0;
unsigned char data_display3 = 0;
unsigned char data_display4 = 0;
unsigned char data_display5 = 0;
unsigned char data_display6 = 0;
unsigned char data_display7 = 0;
unsigned char data_display8 = 0;
unsigned char data_display9 = 0;
unsigned char data_display10 = 0;
unsigned char data_display11 = 0;
unsigned char data_display12 = 0;
unsigned char data_display13 = 0;
unsigned char data_display14 = 0;
unsigned char data_display15 = 0;
unsigned char data_display16 = 0;
void IIC_start();
void IIC_send(unsigned char send_data);
void IIC_end();
//unsigned char table[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01}; 
unsigned char table[4][16] = {
 {0x00,0x00,0x00,0x00,0x26,0x41,0x86,0x80,0x80,0x80,0x86,0x41,0x26,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x42,0x84,0x42,0x22,0x1C,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x20,0x44,0x42,0x84,0x80,0x84,0x42,0x44,0x20,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0xC0,0x40,0xF8,0xD8,0x7E,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00}}; 
void setup() 
{
  pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);
}
/*----------------------------------------------------------------*/
void loop() 
{
    /**************set the address plus 1***************/
    IIC_start();
    IIC_send(0x40);// set the address plus 1 automatically
    IIC_end();
    /************end the process of address plus 1 *****************/
    /************set the data display*****************/ 
    IIC_start();
    IIC_send(0xc0);// set the initial address as 0
    for(char i = 0;i < 16;i++)
    {
       IIC_send(table[data_line][i]);// send the display data 
    }
    if(++delay_count >= 10)
    {
      delay_count = 0;
      data_line++;
      if(data_line >= 4)
      {
        data_line = 0;
      }
    }

    IIC_end();
    /************end the data display*****************/
    /*************set the brightness display***************/ 
    IIC_start();
    IIC_send(0x8A);// set the brightness display
    IIC_end(); 
    /*************end the brightness display***************/ 
    delay(100);
}
/*----------------------------------------------------------------*/
void IIC_start()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
}
void IIC_send(unsigned char send_data)
{
  for(char i = 0;i < 8;i++)
  {
      digitalWrite(IIC_SCL,LOW);
      delayMicroseconds(3); 
      if(send_data & 0x01)
      {
        digitalWrite(IIC_SDA,HIGH);
      }
      else
      {
        digitalWrite(IIC_SDA,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(IIC_SCL,HIGH); 
      delayMicroseconds(3);
      send_data = send_data >> 1;
  }
}
void IIC_end()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
}