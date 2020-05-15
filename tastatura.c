#include <LiquidCrystal.h>
#include <util/delay.h>
 

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }
  
  return taster;
}

bool start = false;

byte srce[] = {
  B00000,
  B00000,
  B11011,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte karo[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000
};

byte pik[] = {
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B10101,
  B00100,
  B00100
};

byte tref[] = {
  B00000,
  B01110,
  B00100,
  B10101,
  B11111,
  B10101,
  B00100,
  B00100
};

int kombinacija[4];
int pozicija = 0;
int scrool[4] = {-1,-1,-1,-1};

int main()
{
  	lcd.begin(16, 2);
    lcd.createChar(0, srce);
    lcd.createChar(1, karo);
    lcd.createChar(2, pik);
    lcd.createChar(3, tref);
    lcd.home();
	
	while(1)
    { 
      if(start == false){
        lcd.clear();
  		lcd.print("pritisni *");  
        //lcd.write(byte(0));

        _delay_ms(500);
      }      
	  char taster = ocitaj_taster();
      if (taster == '*')
      {
        start = true;
        lcd.clear();
        kombinacija[0] = random(0,4);
        kombinacija[1] = random(0,4);
        kombinacija[2] = random(0,4);
        kombinacija[3] = random(0,4);
        lcd.clear();
        lcd.write(byte(kombinacija[0]));
        lcd.write(byte(kombinacija[1]));
        lcd.write(byte(kombinacija[2]));
        lcd.write(byte(kombinacija[3]));
        _delay_ms(2000);
        lcd.clear();
        lcd.blink();
      }
      
      if(taster == '4'){
        pozicija--;
        if(pozicija < 0) pozicija = 0;
        taster = '0';
         _delay_ms(500);
      }
      
      if(taster == '6'){
        pozicija++;
        if(pozicija>3) pozicija = 3;
        taster = '0';
         _delay_ms(500);
      }
      
      if(taster == '2'){
        scrool[pozicija]++;
        if(scrool[pozicija] > 3) scrool[pozicija] = 3;
        lcd.write(byte(scrool[pozicija]));
        taster = '0';
         _delay_ms(500);
      }
      
      if(taster == '8'){
        scrool[pozicija]--;
        if(scrool[pozicija] < 0) scrool[pozicija] = 0;
        lcd.write(byte(scrool[pozicija]));
        taster = '0';
         _delay_ms(500);
      }
      
      if(taster == '5'){
        lcd.clear();
        bool ok = false;
        for(int i = 0; i < 4; i++){
          if(scrool[i] == kombinacija[i]){
            ok = true;
          }
        }
        
        if(ok == true) lcd.print("Zapamtio si");
        else lcd.print("Nisi zapamtio");
      }
      
      lcd.setCursor(pozicija, 0);
      
      
      
    }
  
  	return 0;
}
