/*
 * Autor: Pablo T. Monteiro
 * Versão 1.0.4
 * Data inicio: 22/07/2021 - 22h:27min
 * Data fim:    23/xx/xxxx - xxh:xxmin
 * CACULADORA CIENTIFICA MULTIFUNCIONAL
*/

#include <LiquidCrystal.h>

#define  col_0   A0                   //coluna 1 controlada pelo pino analógico 0 (será usado como digital)
#define  col_1   A1                   //coluna 2 controlada pelo pino analógico 1 (será usado como digital)
#define  col_2   A2                   //coluna 3 controlada pelo pino analógico 2 (será usado como digital)
#define  col_3   A3                   //coluna 3 controlada pelo pino analógico 3 (será usado como digital)
#define  col_4   A4                   //coluna 3 controlada pelo pino analógico 4 (será usado como digital)
#define  row_A   10                    //linha A  controlada pelo pino digital 10
#define  row_B   11                    //linha B  controlada pelo pino digital 11
#define  row_C   12                    //linha C  controlada pelo pino digital 12
#define  row_D   13                    //linha D  controlada pelo pino digital 13

char control = 0x01;
char counter = 0x00, dec = 0x00, num;
boolean shift=false;
char calcM1 = 0x00, oper=0x00,  n[15], m=0x00;
float x;

LiquidCrystal lcd(2, 4, 5, 6, 7, 8);

void store(char value);
//Funções extras
void numb();
void menu();
void lagr();
void disp();

//------------------------------TIMER PARA LEITURA DO TECLADO-----------------------------
ISR(TIMER2_OVF_vect){
    TCNT2=500;
    counter++;
    if(counter == 0x02){
       counter = 0x00;
       if(digitalRead(col_0) && control == 0x01){
         control = 0x02;
         digitalWrite(col_0,  LOW);
         digitalWrite(col_1, HIGH);
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3, HIGH);
         digitalWrite(col_4, HIGH);
         if     (digitalRead(row_A)==LOW)  store('1');
         else if(!digitalRead(row_B))  store('2');
         else if(!digitalRead(row_C))  store('3');
         else if(!digitalRead(row_D))  store('+');
      }else if(digitalRead(col_1) && control == 0x02){
         control = 0x03;
         digitalWrite(col_0, HIGH);
         digitalWrite(col_1,  LOW);
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3, HIGH);
         digitalWrite(col_4, HIGH);
         if     (!digitalRead(row_A))  store('4');
         else if(!digitalRead(row_B))  store('5');
         else if(!digitalRead(row_C))  store('6');
         else if(!digitalRead(row_D))  store('-');
      }else if(digitalRead(col_2) && control == 0x03){
         control = 0x04;
         digitalWrite(col_0, HIGH);
         digitalWrite(col_1, HIGH);
         digitalWrite(col_2,  LOW);
         digitalWrite(col_3, HIGH);
         digitalWrite(col_4, HIGH);
         if     (!digitalRead(row_A))  store('7');
         else if(!digitalRead(row_B))  store('8');
         else if(!digitalRead(row_C))  store('9');
         else if(!digitalRead(row_D))  store('*');
      }else if(digitalRead(col_3) && control == 0x04){
         control = 0x05;
         digitalWrite(col_0, HIGH);
         digitalWrite(col_1, HIGH);
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3,  LOW);
         digitalWrite(col_4, HIGH);
         if     (!digitalRead(row_A))  store('=');
         else if(!digitalRead(row_B))  store('0');
         else if(!digitalRead(row_C))  store('.');
         else if(!digitalRead(row_D))  store('/');
      }else if(digitalRead(col_4) && control == 0x05){
         control = 0x01;
         digitalWrite(col_0, HIGH);
         digitalWrite(col_1, HIGH);
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3, HIGH);
         digitalWrite(col_4,  LOW);
         if     (!digitalRead(row_A))  store('a');
         else if(!digitalRead(row_B))  store('b');
         else if(!digitalRead(row_C))  store('c');
         else if(!digitalRead(row_D))  store('E');
      }
    }
}

void setup() {
    lcd.begin(16, 2, LCD_5x8DOTS);
    TCCR2A = 0x00;   //Timer operando em modo normal
    TCCR2B = 0x07;   //Prescaler 1:1024
    TCNT2  = 10;    //10 ms overflow again
    TIMSK2 = 0x01;   //Habilita interrupção do Timer2
    
    pinMode(col_0, OUTPUT);
    pinMode(col_1, OUTPUT);
    pinMode(col_2, OUTPUT);
    pinMode(col_3, OUTPUT);
    pinMode(col_4, OUTPUT);
    pinMode(row_A,  INPUT);
    pinMode(row_B,  INPUT);
    pinMode(row_C,  INPUT);
    pinMode(row_D,  INPUT);
    //inicializar tudo em HIGH se não não inicializa a varredura
     digitalWrite(col_0, HIGH);
     digitalWrite(col_1, HIGH);
     digitalWrite(col_2, HIGH);
     digitalWrite(col_3, HIGH);
     digitalWrite(col_4, HIGH);

}

void loop(){
  //numb();
  if(num==11){
    menu();
  }
  
  
}

void store(char value){
   char i;                                //variável de iterações
   TIMSK2 = 0x00;                         //Desabilita interrupção do Timer2
   delay(10);
   num = value;                        //atualiza number
   numb();
   TIMSK2 = 0x01;   //Habilita interrupção do Timer2
}
void numb(){
  //-------------------------Leitura numerical e escreve em tela----------------
   if(num<=59 && num>=48 || num==46){//'.'==46, de '0' a '9' == 48 a 59
    if(m > 14){
      lcd.setCursor(0,0);
      lcd.print("Too big number");
    }else{
     n[m] = num;
    lcd.print(n[m]);
    }
    m++;
  }if(num==69){ //'E'==69
    x = atof(n);
      lcd.setCursor(0,1);
      lcd.print(x,7);
    }

  //----------------------------Prepara operandos----------------
/*  if(num==16 && shift==false && calcM1==0){//multiplação
    m=n;
    oper==0x01;
  }else if(num==20 && shift==false && calcM1==0){//divisão
    m=n;
    oper==0x02;
  }else if(num==12 && shift==false && calcM1==0){//adição
    m=n;
    oper==0x03;
  }else if(num==13 && shift==false && calcM1==0){//subtração
    m=n;
    oper==0x04;
  }
*/
  //-----------------------------Resultado-calc-mod-1----------------
  /*
  if(num==19 && shift==false && calcM1==0){
    switch(oper){
    case 0x01:
      n=m*n;
      lcd.setCursor(0,0);
      lcd.print(n);
    break;
    case 0x02:
      n=m/n;
      lcd.setCursor(0,0);
      lcd.print(n);
    break;
    case 0x03:
      n=m+n;
      lcd.setCursor(0,0);
      lcd.print(n);
    break;
    case 0x04:
      n=m-n;
      lcd.setCursor(0,0);
      lcd.print(n);
    break;
    }
  }
  */
}
void lagr(){
  //codigo para execução de interpolação de lagrange
}
void menu(){
  //codigo para execução menu
}
void disp(){
  //Código que armazena o numeral e mostra em tela


}
