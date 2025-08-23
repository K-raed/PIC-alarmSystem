sbit LCD_RS at RC4_bit;
sbit LCD_EN at RC5_bit;
sbit LCD_D4 at RC0_bit;
sbit LCD_D5 at RC1_bit;
sbit LCD_D6 at RC2_bit;
sbit LCD_D7 at RC3_bit;
sbit LCD_RS_Direction at TRISC4_bit;
sbit LCD_EN_Direction at TRISC5_bit;
sbit LCD_D4_Direction at TRISC0_bit;
sbit LCD_D5_Direction at TRISC1_bit;
sbit LCD_D6_Direction at TRISC2_bit;
sbit LCD_D7_Direction at TRISC3_bit;

char keypadPort at PORTD;
unsigned short k, count=0, x=0, i, Temp , nb=150 ;
unsigned char mdp[4]={4,3,2,1} ;
unsigned char pin[4]={0,0,0,0};
char recentKeys[5] = {' ', ' ', ' ', ' ','\0'};
/////keypad void////////keypad void////////keypad void///
unsigned short key(void)
      {
          k = 0;
          do
          k = Keypad_Key_Click();
          while (k==0);
          switch (k)
           {
            case 1: k = 49; break; // 1
            case 2: k = 50; break; // 2
            case 3: k = 51; break; // 3
            case 5: k = 52; break; // 4
            case 6: k = 53; break; // 5
            case 7: k = 54; break; // 6
            case 9: k = 55; break; // 7
            case 10: k = 56; break; // 8
            case 11: k = 57; break; // 9
            case 13: k = 42; break; // *
            case 14: k = 48; break; // 0
            case 15: k = 35; break; // #
           }
          return k ;
       }
/////////////////////////INTERRUPTION///////////////////////////////////
void interrupt(){
    if(PORTB.RB0==1)
    { x=0;
      count=0;
      INTCON.INTF = 0;
      delay_ms(10);
     }
    else if(INTCON.T0IF==1)
    {    INTCON.T0IF=0 ;
         PORTA.RA2=1 ;
         nb=nb-1 ;
         OPTION_REG=0b11000111 ;
         TMR0=0 ;

         if(nb==0)
         { PORTA.RA2=0 ;
           nb=150;
           x=0;
           OPTION_REG=0b11101000 ;
           TMR0=253 ;
          }
          else if(PORTB.RB6=!PORTB.RB6)
         { TMR0=253 ;
           OPTION_REG=0b11101000 ;
           x=6;
           PORTA.RA1=1 ;
           PORTA.RA2=0 ;
           nb=150;
           INTCON.RBIF=0;
           delay_ms(100);
          }

    }

}
//////////////////////////////PROGRAMME PRINCIPAL/////////////////////////
void main() {
    TRISA = 0b110001 ;
    TRISB = 1 ;
    TRISC = 0 ;
    TRISE = 0 ;
    ADC_Init();
    Keypad_Init();
    Lcd_Init();
    Lcd_Cmd(_LCD_CURSOR_OFF);
    INTCON.GIE=1 ;
    INTCON.RBIE=1 ;
    ///BOUCLE INFINI//////////BOUCLE INFINI//////////BOUCLE INFINI//////

 while(x==0)
 {    INTCON.T0IE=1;
      OPTION_REG=0b11101000 ;
      TMR0=253;
      PORTC.RC7 = 0 ;
      PORTA.RA3 = 0 ;
      PORTA.RA2 = 0 ;
      PORTA.RA1 = 0 ;
      
      PORTE = 0 ;
      PORTC = 0 ;


      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1,1,"Bienvenue");
      Lcd_Out(2,1,"Saisir le code");
      PORTE = 0b010 ;



      for(i=0;i<4;i++)
        {
           k=key();
           Lcd_Out(1,12+i,"*");
           delay_ms(100);
           if(mdp[i]+48==k)
                {
                   count++;
                }
        }

           delay_ms(200);

            if(count==4)
          {  INTCON.INTE=1 ;
             OPTION_REG.INTEDG=1 ;
             while(INTCON.INTF==0)
            {
              PORTE = 0b101 ;
              count = 0;
              Lcd_Cmd(_LCD_CLEAR);
              Lcd_Out(1,1,"Acces autorise ");
              PORTA.RA1 = 1 ;
              delay_ms(5000);
              PORTA.RA1 = 0 ;
              
              Temp=adc_read(0);         // Read analog voltage
              Temp=Temp*0.488 ;         // convert it to degree Celsius (0.488 = 500/1023)

                if(Temp <= 15.0)
                {Lcd_Cmd(_LCD_CLEAR);
                 Lcd_Out(1,1,"Chauffage");
                 PORTA.RA3 = 1 ;
                 delay_ms(5000);
                 PORTA.RA3 = 0 ;

                }
                else if(Temp >= 28.0)
                {Lcd_Cmd(_LCD_CLEAR);
                 Lcd_Out(1,1,"Climatiseur");
                 PORTA.RA3 = 1 ;
                 delay_ms(5000);
                 PORTA.RA3 = 0 ;

                }
             }
           }

           else
            { x=1  ;
              INTCON.INTE=1 ;
              OPTION_REG.INTEDG=1 ;
              
              Lcd_Cmd(_LCD_CLEAR);
              Lcd_Out(1,1,"Acces refuse");
              count=0;
              PORTC.RC7=1 ;
              while(x==1)
                    {
                      PORTA.RA2=1 ;
                      delay_ms(300);
                      PORTA.RA2=0 ;
                      delay_ms(300);
                     }
            }


 }


    while(x==6)
    {       count=0;

            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Out(2,1,"Saisir le code");
            for(i=0;i<4;i++)
          {
           k=key();
           Lcd_Out(1,12+i,"*");
           delay_ms(100);
           pin[i]=k-48 ;
           count++;
          }
           if(count==4)
           {
             if(PORTB.RB7==1)
            {Lcd_Cmd(_LCD_CLEAR);
             Lcd_Out(1,1,"code change");
             for(i=0;i<4;i++)
             {  mdp[i]=pin[i] ;
             }
             x=0 ;
            }
           }
    }
}