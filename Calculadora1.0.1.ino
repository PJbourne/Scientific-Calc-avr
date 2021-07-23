/*
 * Autor: Pablo T. Monteiro
 * Versão 1.0.1
 * Data inicio: 22/07/2021 - 22h:27min
 * Data fim:    xx/xx/xxxx - xxh:xxmin
 * CACULADORA CIENTIFICA MULTIFUNCIONAL
*/

#include <LiquidCrystal.h>

char control = 0x01;
char counter = 0x00;
int  number  = 0x00;

LiquidCrystal lcd(2, 4, 5, 6, 7, 8);

ISR(TIMER2_OVF_vect)
{
    TCNT2=100;          // Reinicializa o registrador do Timer2
    counter++;          // incrementa counter
    if(counter == 0x05) // counter igual a D'5'?
    {                   // sim...
       counter = 0x00;  //reinicia counter
// -- Varredura do Teclado Matricial --
      if(digitalRead(col_1) && control == 0x01)        //Coluna 1 em nível high? Control igual 1?
      {                                   //Sim...
         control = 0x02;                  //control igual a 2
         digitalWrite(col_1,  LOW);       //apenas coluna 1 em nível baixo
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3, HIGH);
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(1);
         else if(!digitalRead(row_B))  store(4);
         else if(!digitalRead(row_C))  store(7);
         else if(!digitalRead(row_D))  store(11);
      }
      else if(digitalRead(col_2) && control == 0x02)   //Coluna 2 em nível high? Control igual 2?
      {                                   //Sim...
         control = 0x03;                  //control igual a 3
         digitalWrite(col_1, HIGH);
         digitalWrite(col_2,  LOW);       //apenas coluna 2 em nível baixo
         digitalWrite(col_3, HIGH);
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(2);
         else if(!digitalRead(row_B))  store(5);
         else if(!digitalRead(row_C))  store(8);
         else if(!digitalRead(row_D))  store(0);
      }
      else if(digitalRead(col_3) && control == 0x03)   //Coluna 3 em nível high? Control igual 3?
      {                                   //Sim...
         control = 0x01;                  //control igual a 1     
         digitalWrite(col_1, HIGH);       //
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3,  LOW);       //apenas coluna 3 em nível baixo
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(3);
         else if(!digitalRead(row_B))  store(6);
         else if(!digitalRead(row_C))  store(9);
         else if(!digitalRead(row_D))  store(12);
      }
    } //end if counter
}

void setup() {
  lcd.begin(16, 2, LCD_5x8DOTS);
  TCCR2A = 0x00;   //Timer operando em modo normal
  TCCR2B = 0x07;   //Prescaler 1:1024
  TCNT2  = 100;    //10 ms overflow again
  TIMSK2 = 0x01;   //Habilita interrupção do Timer2
  

}

void loop() {
  

}
