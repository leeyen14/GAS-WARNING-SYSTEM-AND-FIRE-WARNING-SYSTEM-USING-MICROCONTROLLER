#include <main.h>
#define LCD_ENABLE_PIN PIN_D1
#define LCD_RS_PIN PIN_D2
#define LCD_RW_PIN PIN_D3
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>
float value;
int max = 65, cb;
void main()
{
   output_c(0xfc);
   set_tris_a(0x02);
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   delay_us(10);

   lcd_init();
   lcd_putc("\fReady...\n");
   delay_ms(1000);
   // -------- lay mau ----------
   value=(float)read_adc();
   value = ((5*value)*100)/1024;
   // --------- main ------------
   while(TRUE)
   {
      // --------- doc cam bien --------
      cb = input(PIN_A1);
      value=(float)read_adc();
      value = ((5*value)*100)/1024;
      // -------- xu ly hien thi -------
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Temp: %f",value);
      lcd_gotoxy(12,1);
      lcd_putc(0xdf);
      lcd_gotoxy(13,1);
      lcd_putc("C");
      lcd_gotoxy(1,2);
      lcd_putc("TT: ");

      if (value >= max || cb == 1)
      {
         output_high(PIN_C0);
         output_high(PIN_C1);
         lcd_gotoxy(5,2);
         lcd_putc("Bao Dong!!!");
      }
      else
      {
         output_low(PIN_C0);
         output_low(PIN_C1);
         lcd_gotoxy(5,2);
         lcd_putc("Binh Thuong");
      }
   }

}
