/*
 * Autor: Pablo T. Monteiro
 * Versão 1.0.5
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

#define A 20

char control = 0x01;
char counter = 0x00, dec = 0x00, num, shift=0x00, menuC=0x00;
char cntMem = 0x03, oper=0x00,  n[15], m=0x00;
float x[4];
    bool rep = 0;
    char ex;
    double X[A], Y[A], L[A], fx[A], NUM, DEN, x, FX;

LiquidCrystal lcd(2, 4, 5, 6, 7, 8);

void store(char value);
//Funções extras
void show();
void numb();
void menu();
void lagr();
void disp();
void lecture();
void lg();

//------------------------------TIMER PARA LEITURA DO TECLADO-----------------------------
ISR(TIMER2_OVF_vect){
    TCNT2=500;
    counter++;
    if(counter == 0x03){
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
  if((num<=59 && num>=48) || num==46){          //'.'==46, de '0' a '9' == 48 a 59
    if(m > 14){
      lcd.setCursor(0,0);
      lcd.print("OVRF");
    }else{
      n[m] = num;
      lcd.print(n[m]);
    }
    m++;
  }if(num==69){                               //'E'==69
      x[0]=x[1];
      x[1]=x[2];
      x[2]=x[3];
      x[3] = atof(n);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(x[3],7);
      for(m=0x00;m<14;m++){
        n[m]=0x00;
        //if(m<4){
        //  x[m]=0;
        //  }
      }
      m=0x00;
      lcd.setCursor(0,0);
    }
  if(menuC==0x00){
  //----------------------------Prepara operandos----------------
   switch(num){ 
      case '+':
        switch (shift){
        case 0x00://soma
          x[0]=x[1];
          x[1]=x[2];
          x[2]=x[3];
          x[3]=x[1]+x[2];
          oper==0x01;
          show();
        break;
        case 0x01://sen
          x[0]=x[1];
          x[1]=x[2];
          x[2]=x[3];
          x[3]=sin(x[2]);
          oper==0x05;
          show();
        break;
        case 0x02://asen
          x[0]=x[1];
          x[1]=x[2];
          x[2]=x[3];
          x[3]=asin(x[2]);
          oper==0x05;
          show();
        break;
      
   }break;
      case '-':
        switch (shift){
          case 0x00://sub
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=x[1]-x[2];
            oper==0x02;
            show();
          break;
          case 0x01://cos
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=cos(x[2]);
            oper==0x06;
            show();
          break;
          case 0x02://acos
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=acos(x[2]);
            oper==0x05;
            show();
          break;
      
   }break;
      case '*':
        switch(shift){
          case 0x00://mult
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=x[1]*x[2];
            oper==0x03;
            show();
          break;
          case 0x01://elev
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=pow(x[1],x[2]);
            oper==0x07;
            show();
          break;
          case 0x02://root
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=pow(x[1], 1/x[2]);
            oper==0x05;
            show();
          break;
        
      }break;
      case '/':
        switch (shift){ 
          case 0x00://div
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=x[1] / x[2];
            oper==0x04;
            show();
          break;
          case 0x01://1/x
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=1/x[2];
            oper==0x08;
            show();
          break;
          case 0x02://x!
            x[0]=x[1];
            x[1]=x[2];
            x[2]=x[3];
            x[3]=int(x[2]);
            for(int i = int(x[2])-1; i>0; i--){
              x[3]=int(x[3])*(int(x[2])-i);
            }
            oper==0x05;
            show();
          break;
        
      }break;
  //-----------------------------Menus----------------
      case 'a':
        menu();
        lcd.clear();
        lcd.setCursor(0,0);
      break;
  }
}
}
void show(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(x[3],7);
}
void lagr(){
  //codigo para execução de interpolação de lagrange

    while(rep == 0){
    lecture();
    lg();
    lcd.print(FX);
    lcd.print(" Deseja sair?(S/N");
    //cin >> ex;
    if(ex == 'N' || ex == 'n'){
        lcd.clear();
    }else{
        rep=1;
    }
    }
    //-------------------------------------
    
}
void lg(){
    for(i=0; i<n; i++){
        NUM = 1;
        DEN = 1;
            for(j=0; j<n; j++){
                if(i != j){

                    NUM *= x - X[j];
                    DEN *= X[i] - X[j];
                    lcd.print(NUM);
                    lcd.print(" \t ");
                    lcd.print(DEN);
                    lcd.print(" \t i ");
                    lcd.print(i);
                    lcd.print(" \t j ");
                    lcd.print(j);
                    
            }
        }
        L[i]= NUM / DEN;
        lcd.print(NUM);
        lcd.print("\t ");
        lcd.print(DEN);
    }
for(int m=0; m<n; m++){
    fx[m] = Y[m] * L[m];
    lcd.print(L[m]);
}
for(int l=0; l<n; l++){
    FX += fx[l];
}
//-----------------------------

//--------------------------------------
}
void lecture(){
    lcd.print("Entre o numero de pontos: ");
    //cin >> n;
    lcd.print("Entre com os valores X e Y separados por espaço e presse ENTER: ");
    for(i=0; i<n; i++){
        lcd.print(i);
        lcd.print(" º  \t");
        //cin >> X[i] >> Y[i];
    }
    lcd.print("Entre com o X desejado: ");
    //cin >> x;
}

void menu(){
  //codigo para execução menu
  
}
void disp(){
  //Código que armazena o numeral e mostra em tela
}
void menu1(){
  
}
void menu2(){
  
}
void menu3(){
  
}
void menu4(){
  
  }
