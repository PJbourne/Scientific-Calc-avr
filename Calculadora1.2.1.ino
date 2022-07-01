/*
 * Autor: Pablo T. Monteiro
 * Versão 1.1.2
 * Data inicio: 22/06/2022 - 14h:41min
 * Data fim:    01/07/2022 - 14:53min
 * CACULADORA CIENTIFICA RPN
*/

//#include <LiquidCrystal.h>
#include "C:\Users\Monteiro\Downloads\LiquidCrystal-1.0.0\LiquidCrystal-1.0.0\src\LiquidCrystal.cpp"
#include <math.h>

#define  col_0   9                   //coluna 1 controlada pelo pino digital 09 (será usado como digital)
#define  col_1   10                   //coluna 2 controlada pelo pino digital 10 (será usado como digital)
#define  col_2   11                   //coluna 3 controlada pelo pino digital 11 (será usado como digital)
#define  col_3   12                   //coluna 3 controlada pelo pino digital 12 (será usado como digital)
#define  row_A   5//0                    //linha A  controlada pelo pino digital 10
#define  row_B   6//2                    //linha B  controlada pelo pino digital 11
#define  row_C   7//3                    //linha C  controlada pelo pino digital 12
#define  row_D   8//4                    //linha D  controlada pelo pino digital 13
/*
 * 
 * Constantes não utilizadas, mas que podem ser implementadas em um teclado de 32 teclas:
#define M_velLuz  2.99792458
#define M_cGrav   6.674210
#define M_kPer    8.987551787
#define M_grav    9.80665
#define M_atm     1.01325
#define eVolt     1.6021765314
#define M_uMasAtm 1.6605388628
#define M_cGas    8.31447215
#define M_Epsl    8.854187817
#define M_Boltz   1.3806505
#define M_Plnk    6.6260693
#define M_mElt    9.1093826
#define M_Avog    6.022141510

#define m_velLuz  "E10m/s"
#define m_cGrav   "E-11Km2/kg2"
#define m_kPer    "E9Nm2/C2"
#define m_grav    "E0m/s2"
#define m_atm     "E5Pa"
#define m_eVolt   "E-19J"
#define m_uMasAtm "E-27kg"
#define m_cGas    "EJ/molK"
#define m_Epsl    "E-12C2/Nm2"
#define m_Boltz   "E-23J/K"
#define m_Plnk    "E-34Js"
#define m_mElt    "E-31kg"
#define m_Avog    "E23mole/mol"
*/
/*
 * Descrição das variáveis:
 * 
 * char counter = 0x00;      Numero de ciclos de estouro so timer sem executar nada
 * char  control = 0x01;     Numero de controle da varredura do teclado
 * float Num[20];            Estrutura de memoria da calculadora (estilo pilha, fila ou lista)
 * float Buffer = 0;         Buffer de teclado numerico (ultima tecla pressionada - valor numerico)
 * float fator = 1;          Numero que inverte o sinal do numero na tela (Num[0])
 * float divisor = 0;        Numero que determina as casas apos virgula enquanto digita (apos pressionar o '.')
 * boolean shift = 0;        Fator booelano do shift (botao de operacoes auxiliares e constantes numerica)
*/

void media();                   //Calcula a media aritmetica dos valores (diferentes de !=0) na memoria
void somatorio();               //Calcula juros composto de aplicacao financeira continua
void ordem();                   //Organiza a memoria em ordem crescente e mostra o ultimo valor (o maior)
void rollthrough();             //Avanca a memoria
void rollback();                //Recua a memoria
void printa();                  //Printa na tela o 1º numero da memoria Num[0]
void oper(char op);             //Funcao com as operacoes
void simbol(char Op, float a);  //Funcao de outras operacoes
void keyboard(float a, char b); //Funcao que ler e interpreta o que foi digitado no teclado


//------------------------------DECLARACAO DO LCD 16X2-----------------------------
LiquidCrystal lcd(A0, /*13,*/ A1, /*8, 7, 6, 5,*/ A2, A3, A4, A5);
// 13, pino WR do LCD (caso fosse utilizado);
// 8, 7, 6, 5, pinos 1,2,3,4 do LCD (caso fosse utilizados);
//----------------------------------------------------------------------------------

//------------------------------------VARIAVEIS GLOBAIS-------------------------------------
char counter = 0x00, control = 0x01;
float Num[20], Buffer = 0, divisor = 0, fator = 1;
boolean shift = 0;
//----------------------------------------------------------------------------------
//------------------------------INTERRUPCAO DO TIMER2 PARA LEITURA DO TECLADO-----------------------------
ISR(TIMER2_OVF_vect){
    TCNT2=1000;
    counter++;
    if(counter == 0x03){
       counter = 0x00;
       if(!digitalRead(col_0) & control == 0x01){
         control = 0x02;
         digitalWrite(col_1, LOW);
         digitalWrite(col_2, LOW);
         digitalWrite(col_3, LOW);
         digitalWrite(col_0, HIGH);
         delay(1);
         if(digitalRead(row_A)&!digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '1');//1,1
         else if(digitalRead(row_A)&digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '(');//1,2
         else if(!digitalRead(row_A)&digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, ',');//1,3
         else if(!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C)&!digitalRead(row_D))  keyboard(7, 0x00);//1,4
         else if(!digitalRead(row_A)&!digitalRead(row_B)&digitalRead(row_C)&!digitalRead(row_D))  keyboard(4, 0x00);//1,5
         else if(!digitalRead(row_A)&!digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(1, 0x00);//1,6
         else if(!digitalRead(row_A)&!digitalRead(row_B)&!digitalRead(row_C)&digitalRead(row_D))  keyboard(0, '<');//1,7
      }else if(!digitalRead(col_1) & control == 0x02){
         control = 0x03;
         digitalWrite(col_0, LOW);
         digitalWrite(col_2, LOW);
         digitalWrite(col_3, LOW);
         digitalWrite(col_1, HIGH);
         delay(1);
         if(digitalRead(row_A)&!digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '2');//2,1
         else if(digitalRead(row_A)&digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, ')');//2,2
         else if(!digitalRead(row_A)&digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '\'');//2,3
         else if(!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C)&!digitalRead(row_D))  keyboard(8, 0x00);//2,4
         else if(!digitalRead(row_A)&!digitalRead(row_B)&digitalRead(row_C)&!digitalRead(row_D))  keyboard(5, 0x00);//2,5
         else if(!digitalRead(row_A)&!digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(2, 0x00);//2,6
         else if(!digitalRead(row_A)&!digitalRead(row_B)&!digitalRead(row_C)&digitalRead(row_D))  keyboard(0, 0x00);//2,7
      }else if(!digitalRead(col_2) & control == 0x03){
         control = 0x04;
         digitalWrite(col_0, LOW);
         digitalWrite(col_1, LOW);
         digitalWrite(col_3, LOW);
         digitalWrite(col_2, HIGH);
         delay(1);
         if(digitalRead(row_A)&!digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '3');//3,1
         else if(digitalRead(row_A)&digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '#');//3,2
         else if(!digitalRead(row_A)&digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '&');//3,3
         else if(!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C)&!digitalRead(row_D))  keyboard(9, 0x00);//3,4
         else if(!digitalRead(row_A)&!digitalRead(row_B)&digitalRead(row_C)&!digitalRead(row_D))  keyboard(6, 0x00);//3,5
         else if(!digitalRead(row_A)&!digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(3, 0x00);//3,6
         else if(!digitalRead(row_A)&!digitalRead(row_B)&!digitalRead(row_C)&digitalRead(row_D))  keyboard(0, '.');//3,7
      }else if(!digitalRead(col_3) & control == 0x04){
         control = 0x01;
         digitalWrite(col_0, LOW);
         digitalWrite(col_1, LOW);
         digitalWrite(col_2, LOW);
         digitalWrite(col_3, HIGH);
         delay(1);
         if(digitalRead(row_A)&!digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D)) keyboard(0, '4');//4,1
         else if(digitalRead(row_A)&digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '%');//4,2
         else if(!digitalRead(row_A)&digitalRead(row_B)&!digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '=');//4,3
         else if(!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '+');//4,4
         else if(!digitalRead(row_A)&!digitalRead(row_B)&digitalRead(row_C)&!digitalRead(row_D))  keyboard(0, '-');//4,5
         else if(!digitalRead(row_A)&!digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0, '*');//4,6
         else if(!digitalRead(row_A)&!digitalRead(row_B)&!digitalRead(row_C)&digitalRead(row_D))  keyboard(0, '/');//4,7
      }
    }
}
//----------------------------------------------------------------------------------
//--------------------------------------SETUP INICIAL--------------------------------------------
void setup() {
    lcd.display();
    lcd.begin(16, 2/*, LCD_5x8DOTS8*/);
    lcd.noAutoscroll();
    lcd.setCursor(0,0);
    lcd.cursor();
    lcd.blink();
    lcd.print("RPN Calculator");
    lcd.setCursor(0,1);
    delay(1000);
    lcd.print("by P. Monteiro");
    pinMode(col_0, OUTPUT);
    pinMode(col_1, OUTPUT);
    pinMode(col_2, OUTPUT);
    pinMode(col_3, OUTPUT);
    pinMode(row_A,  INPUT);
    pinMode(row_B,  INPUT);
    pinMode(row_C,  INPUT);
    pinMode(row_D,  INPUT);
    //inicializar tudo em LOW
     digitalWrite(col_0, LOW);
     digitalWrite(col_1, LOW);
     digitalWrite(col_2, LOW);
     digitalWrite(col_3, LOW);
     digitalWrite(row_A, LOW);
     digitalWrite(row_B, LOW);
     digitalWrite(row_C, LOW);
     digitalWrite(row_D, LOW);
     delay(1000);
     //-----------------------------------------SET DO TIMER2 E INTERRUPCAO----------------------------------------
    TCCR2A = 0x00;   //Timer operando em modo normal
    TCCR2B = 0x07;   //Prescaler 1:1024
    TCNT2  = 100;    //10 ms overflow again
    TIMSK2 = 0x01;   //Habilita interrupção do Timer2
    //----------------------------------------------------------------------------------
}
//------------------------------------FUNCAO MAIN EM DESUSO----------------------------------------------
void loop(){

}
//----------------------------------------------------------------------------------

//------------------------------------LEITURA E INTERPRETACAO DO TECLADO----------------------------------------------
void keyboard(float a, char b){
  char i;                                //variável de iterações
  TIMSK2 = 0x00;                         //Desabilita interrupção do Timer2
  if(b == 0x00  & !shift){//----------------------------------------------------------------------------------
    Buffer = a;
    if(divisor == 0){
      Num[0] = fator * fabsf(Num[0]) * 10 + a;
    }else{
      Num[0] = fator * fabsf(fabsf(Num[0]) + a/powf(10,divisor));
      divisor++;
    }
    printa();
  }else if(b == 0x00 & shift){//----------------------------------------------------------------------------------
    if(a == 0){
      Num[0] = M_LOG2E;//
    }else if(a == 1){
      Num[0] = M_2_SQRTPI;//
    }else if(a == 2){
      Num[0] = M_E;//
    }else if(a == 3){
      Num[0] = M_PI;//
    }else if(a == 4){
      Num[0] = M_SQRT2;//
    }else if(a == 5){
      Num[0] = M_1_PI;//
    }else if(a == 6){
      Num[0] = M_PI_2;//
    }else if(a == 7){
      Num[0] = M_SQRT1_2;//
    }else if(a == 8){
      Num[0] = M_2_PI;//
    }else if(a == 9){
      Num[0] = M_PI_4;//
    }
  }else if(b){//----------------------------------------------------------------------------------
    if(b == '.' & !divisor){//--------------------------char '.' to do: decimal
      divisor = 1;
    }else if(b == '.' & shift){
      ordem();
    }else if(b > '!' & b < '1'){//-------operações basicas
      oper(b);
    }else if(b > '0' & b < '5'){//1-4
      if(b == '4'){
        if(!shift){
          Num[0] = NULL;
        }else{
          for(int j=19; j>-1; j--){
            Num[j] = NULL;
          }
          shift = !shift;
        }
        lcd.clear();
        divisor = 0;
      }else if(b == '1' & !shift){
        float c = Num[0];
        rollback();
        Num[19] = c;
      }else if(b == '1' & shift){
        Num[0] = M_LN2;//
      }else if(b == '2' & !shift){
        float c = Num[19];
        rollthrough();
        Num[0] = c;
      }else if(b == '2' & shift){
        Num[0] = M_LN10;//
      }else if(b == '3' & !shift){
        float c = Num[0];
        Num[0] = Num[1];
        Num[1] = c;
      }else if(b == '3' & shift){
        Num[0] = M_LOG10E;//
      }
      fator = 1;
    }else{//-------------------------------demais operacoes
      simbol(b, a);
    }
    printa();
  }else{//--------------------------------------------------------erro?--------------------------
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Erro no teclado");
    delay(2500);
  }
  while(digitalRead(row_A)|digitalRead(row_B)|digitalRead(row_C)|digitalRead(row_D)){//----------------------------------------impede o efeito boucing
  }
  TIMSK2 = 0x01;   //Habilita interrupção do Timer2
}

void oper(char op){//-----------------------------------------OPERACOES GERAIS + - * / . & OPERACOES COM SHIFT-------------------------------------------------------------
  if(op > ')'){
    if(op == '-' & !shift){// char '-' to do: minus
      Num[1] = Num[1] - Num[0];
    }else if(op == '-' & shift){
      if(Num[0]==0){
        if(Num[1]==0){
          Num[1] = (float)random(2147483647)/100000;//------------------------gerador de numero de 0 a 21474--------------------------------------------------
        }else{
          Num[1] = (float)random(2147483647)/Num[1];//------------------------gerador de numero de 0 a 2147483647/Num[1]--------------------------------------------------
        }
      }else{
        Num[1] = (float)random(Num[1],Num[0])/100000;//-----------------------gerador de numero de Num[1] a Num[0]--------------------------------------------------
      }
    }else if(op == '+' & !shift){
      Num[1] = Num[1] + Num[0];// char '+' to do: plus
    }else if(op == '+' & shift){
      media();//-------------------------------------------------calcula media aritmetica dos valores != de ZERO ---------------------------------
    }else if(op == '*' & !shift){
      Num[1] = Num[1] * Num[0];// char '*' to do: mult
    }else if(op == '*' & shift){
      somatorio(); //--------------------------------------para aplicacao financeira mensal--------------------------------------------
    }else if(op == '/' & !shift){
      Num[1] = Num[1] / Num[0];// char '/' to do: div
    }else if(op == '/' & shift){
      Num[1] = Num[1] * Num[0]/100;
    }else if(op == ',' & !shift){
      Num[1] = powf(Num[1],Num[0]);
    }else if(op == ',' & shift){
      Num[1] = powf(Num[1],1/Num[0]);
    }
    rollback();//retorna a pilha
  }else{//--------------------------------------------------------OPERACOES E CONSTANTES NUMERICAS----------------------------------------------------------------------
    if(op == '\'' & !shift){
      Num[0] = expf(Num[0]);//e^x
    }else if(op == '\'' & shift){
      Num[0] = logf(Num[0]);//ln(x)
    }else if(op == '&' & !shift){
      Num[0] = sqrtf(Num[0]);//sqrt(x)
    }else if(op =='&' & shift){
      Num[0] = cbrtf(Num[0]);//cube(x)
    }else if(op =='(' & !shift){
      Num[0] = sinf(Num[0]);//sin(x)
    }else if(op =='(' & shift){
      Num[0] = asinf(Num[0]);//asin(x)
    }else if(op ==')' & !shift){
      Num[0] = cosf(Num[0]);//cos(x)
    }else if(op ==')' & shift){
      Num[0] = acosf(Num[0]);//acos(x)
    }else if(op =='#' & !shift){
      Num[0] = tanf(Num[0]);//tan(x)
    }else if(op =='#' & shift){
      Num[0] = atanf(Num[0]);//atan(x)
    }else if(op == '%'){//----------------------------------BOTAO SHIFT------------------------------------------------
      Shift();
    }
  }
  fator = 1;
  printa();
}

void simbol(char Op, float a){//-------------------------------------OPERACAO '=' E 'APAGAR' & OPERACAO COM SHIT---------------------------------------------
  if(Op == '=' & !shift){
    float c = Num[19];
    rollthrough();
    Num[0] = c;
    divisor = 0;
  }else if(Op == '=' & shift){
    Num[1] = hypotf(Num[1],Num[0]);
    rollback();
  }else if(Op == '<' & shift){//--------------------------char '<' to do: apagar
      Num[0] = -1 * Num[0];
      fator = -1 * fator;
  }else if(Op == '<' & !shift){//--------------------------char '<' to do: apagar
    if(divisor){
      divisor--;
      Num[0] = Num[0] - (Buffer * fator)/powf(10,divisor);
    }else{
      Num[0] = (Num[0] - Buffer * fator )/10;
    }
  }
  printa();
}

//----------------------------------------------------------------------------------FUNCOES-----------------------------------------------------------------------
void Shift(){
  shift = !shift;
  lcd.setCursor(0,1);
  if(shift){
    lcd.print("shift");
  }else{
    lcd.print("     ");
  }
}

void rollback(){
  for(int j=0; j<20;j++){
    Num[j] = Num[j+1];
  }
}

void rollthrough(){
  for(int j=19; j>-1;j--){
    Num[j] = Num[j-1];
  }
}

void printa(){
    lcd.setCursor(8,0);
  lcd.print("         ");
  lcd.setCursor(0,0);
  lcd.print(Num[0],6);
}

void ordem(){
  for(int i=0; i<20; i++){
        for(int j=i; j<20; j++){
            if(Num[i] >= Num[j]){
                float a = Num[i];
                Num[i] = Num[j];
                Num[j] = a;
                a = Num[i];
            }
        }
    }
    fator = 1;
}

void somatorio(){
  float soma = 0;
  for(float j = Num[1]; j>0; j--){
    soma = soma + Num[2] * powf(Num[0],(j));
  }
  Num[1] = soma;
}

void media(){
  float soma=0, n=0;
  for(int j = 0; j<20; j++){
    if(Num[j] != 0){
      soma = soma + Num[j];
      n++;
    }
  }
  Num[1] = soma / n;
}
