/*
   Autor: Pablo T. Monteiro
   Versão 3.5.1
   Data inicio: 08/04/2023 - 09h:41min
   Data fim:    08/04/2023 - 23:45min
   CACULADORA CIENTIFICA RPN
*/

#include <LiquidCrystal.h>
#include <math.h>
#include <string.h>

#define MAX_BUFFER_SIZE 20
#define  col_0   9                   //coluna 1 controlada pelo pino digital 09 (será usado como digital)
#define  col_1   10                   //coluna 2 controlada pelo pino digital 10 (será usado como digital)
#define  col_2   11                   //coluna 3 controlada pelo pino digital 11 (será usado como digital)
#define  col_3   12                   //coluna 4 controlada pelo pino digital 12 (será usado como digital)
#define  col_4   13                   //coluna 5 controlada pelo pino digital 13 (será usado como digital)
#define  row_A   5//0                    //linha A  controlada pelo pino digital 10
#define  row_B   6//2                    //linha B  controlada pelo pino digital 11
#define  row_C   7//3                    //linha C  controlada pelo pino digital 12
#define  row_D   8//4                    //linha D  controlada pelo pino digital 13

LiquidCrystal lcd(A5, A4, A3, A2, A1, A0); //lcd(A5, /*13,*/ A4, /*8, 7, 6, 5,*/ A3, A2, A1, A0);

//---------------------------------------------------Rotina TIMER----------------------
unsigned char counter = 0x00, control = 0x01;
ISR(TIMER2_OVF_vect) {
  TCNT2 = 255;
  counter++;
  if (counter == 0xFF) {
    counter = 0x00;
    if (!digitalRead(col_0) & control == 0x01) {
      control = 0x02;
      digitalWrite(col_1, LOW);
      digitalWrite(col_2, LOW);
      digitalWrite(col_3, LOW);
      digitalWrite(col_4, LOW);
      digitalWrite(col_0, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x41); //1,8 'A'
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x46); //1,7 'F'
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D)) keyboard(0x4B); //1,6 'K'
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D)) keyboard(0x50); //1,5 'P'
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D)) keyboard(0x61); //1,4 'a'
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x62); //1,3 'b'
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x63); //1,2 'c'
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x64); //1,1 'd'
    } else if (!digitalRead(col_1) & control == 0x02) {
      control = 0x03;
      digitalWrite(col_0, LOW);
      digitalWrite(col_2, LOW);
      digitalWrite(col_3, LOW);
      digitalWrite(col_4, LOW);
      digitalWrite(col_1, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x42); //2,8
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x47); //2,7
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0x4C); //2,6
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x51); //2,5
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x37); //1,4
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x34); //2,3
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x31); //2,2
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x30); //2,1
    } else if (!digitalRead(col_2) & control == 0x03) {
      control = 0x04;
      digitalWrite(col_0, LOW);
      digitalWrite(col_1, LOW);
      digitalWrite(col_3, LOW);
      digitalWrite(col_4, LOW);
      digitalWrite(col_2, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x43); //3,8
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x48); //3,7
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0x4D); //3,6
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x52); //3,5
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x38); //1,4
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x35); //3,3
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x32); //3,2
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x2E); //3,1
    } else if (!digitalRead(col_3) & control == 0x04) {
      control = 0x05;
      digitalWrite(col_0, LOW);
      digitalWrite(col_1, LOW);
      digitalWrite(col_2, LOW);
      digitalWrite(col_4, LOW);
      digitalWrite(col_3, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x44); //4,8
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x49); //4,7
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0x4E); //4,6
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x53); //4,5
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x39); //1,4
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x36); //4,3
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x33); //4,2
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x65); //4,1
    } else if (!digitalRead(col_4) & control == 0x05) {
      control = 0x01;
      digitalWrite(col_0, LOW);
      digitalWrite(col_1, LOW);
      digitalWrite(col_2, LOW);
      digitalWrite(col_3, LOW);
      digitalWrite(col_4, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x45); //5,8
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x4A); //5,7
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0x4F); //5,6
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x54); //5,5
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x2F); //1,4
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x2A); //5,3
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x2D); //5,2
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x2B); //5,1
    }
  }
}
//-----------------------------------------------Fim Rotina TIMER----------------------

void setup() {
  //lcd.display();
  lcd.begin(16, 2/*, LCD_5x8DOTS8*/);
  lcd.noAutoscroll();
  lcd.setCursor(0, 0);
  lcd.cursor();
  lcd.blink();
  lcd.print("RPN Calc v3.5.1");
  pinMode(col_0, OUTPUT);
  pinMode(col_1, OUTPUT);
  pinMode(col_2, OUTPUT);
  pinMode(col_3, OUTPUT);
  pinMode(col_4, OUTPUT);
  pinMode(row_A,  INPUT);
  pinMode(row_B,  INPUT);
  pinMode(row_C,  INPUT);
  pinMode(row_D,  INPUT);
  //inicializar tudo em LOW
  digitalWrite(col_0, LOW);
  digitalWrite(col_1, LOW);
  digitalWrite(col_2, LOW);
  digitalWrite(col_3, LOW);
  digitalWrite(col_4, LOW);
  digitalWrite(row_A, LOW);
  digitalWrite(row_B, LOW);
  digitalWrite(row_C, LOW);
  digitalWrite(row_D, LOW);
  delay(50);
  //lcd.clear();
  //-----------------------------------------SET DO TIMER2 E INTERRUPCAO----------------------------------------
  TCCR2A = 0x00;   //Timer operando em modo normal
  TCCR2B = 0x07;   //Prescaler 1:1024
  TCNT2  = 255;    //10 ms overflow again
  TIMSK2 = 0x01;   //Habilita interrupção do Timer2
  //----------------------------------------------------------------------------------
}

char MODE_type = 0x01;
char lastMODE;
char mod = 0x00;
char tri = 0x00;
char notation = 0x00;
char n = 0x00;
bool type_flag = false;
bool SHIFT = false, polar = false;
double Num[20], lastX;//pilha do sistema RPN
char keybuffer[MAX_BUFFER_SIZE + 1]; //buffer de entrada
int buffer_size = 0;//initial size do buffer de entrada
double float_buffer = 0.0;//variavl aux do metodo de entrada
char complexo = 0x00;
//char *string_buffer;

//Funções para modo RPN
void type_number(char c);
void store_number(char c);
void operate_number(char c);
void rollthrough();
void rollback();
void clear_key();;

//Funções para modo Linear System
void gauss_elimination(double **A, double *B, char m);
void back_substitution(double **A, double *B, double *X, char m);

void menu();            //Menu de seleção do modo
void RPN();             //Modo 1
void linear_system();   //Modo 2
void equation_solver(); //Modo 3
void integral_solver(); //Modo 4
void derivator();       //Modo 5
void interpolation();   //Modo 6

void keyboard(char c) {
  char i;                                //variável de iterações
  TIMSK2 = 0x00;                         //Desabilita interrupção do Timer2
  if(c == 0x41){
    MODE_type = 0x00;
    lcd.clear();
  }else if (c == 0x62) {
    SHIFT = !SHIFT;
    if (SHIFT) {
      lcd.setCursor(9, 1);
      lcd.print(" shift ");
    } else {
      lcd.setCursor(9, 1);
      lcd.print("       ");
    }
  }else if(c == 0x4C){
    lastMODE = MODE_type;
    MODE_type = 0x10;
  }else if(c == 0x63){
    char *trigo[] = {"RAD","DEG","GRAD"};
    char *mod[] = {"MENU","RPN","LIN","EQN","INT","DER"};
    char *notat[] = {"FIX","ENG","SCI"};
    char *pola[] = {"RET","POL"};
    lcd.clear();
    lcd.print("T:");
    lcd.print(trigo[(int)tri]);
    lcd.print(" N:");
    lcd.print(notat[(int)notation]);
    lcd.setCursor(0,1);    
    lcd.print(" M:");
    lcd.print(mod[(int)MODE_type]);
    lcd.print(" P:");
    lcd.print(pola[(int)polar]);
  }else if(c == 0x64){
    if(!SHIFT){    
      MODE_type = 0x01;
      tri = 0x00;
      notation = 0x00;
      SHIFT = false;
      polar = false;
      complexo = 0x00;
    }else{
      for(int j = 0; j < (sizeof(*Num)/sizeof(float)); j++){
        Num[j] = 0xFFFF;
      }      
    }
  }
  if (MODE_type == 0x00) {   //Menu
    if(c == 0x52){        //rola a tela & a seleção de modo
      n++;
      n = n%6;
    }else if(c == 0x50){                                                      //Seleciona o modo, de acordo com o que está na tela
      MODE_type = n+1;
      n = 0x00;
    }
    const char *menu_items[] = {"RPN MODE", "Linear System", "Equation Solver", "Integral Solver", "Derivator", "Interpolation"};
    lcd.setCursor(0,1);
    lcd.print(menu_items[((int)n)]);
  } else if (MODE_type == 0x01) {                                                 //RPN
    if ((c > 0x2F && c < 0x3A) || c == 0x2E || c == 0x65 || c == 0x54 || c == 0x53) {    //c[0_9+-e<=]
      type_number(c);
      SHIFT = false;
    } else if (c == 0x61) {        
      complexo = 0x00;
      refresh(c);
    } else if (c == 0x50) {                                          //[ENTER]
      store_number(c);
    } else if ((c > 0x41 && c < 0x53) || (c > 0x29 && c < 0x2E) || c == 0x2F) { //c[B_O+-*/] || c == 0x52
      operate_number(c);
      clear_key();
      SHIFT = false;
      refresh(c);
    }
  } else if (MODE_type == 0x02) { //Linear
    if((c > 0x2F && c < 0x3A) || c == 0x2E || c == 0x65 || c == 0x54 || c == 0x53) {
      type_number(c);
      SHIFT = false;
    }else if(c == 0x50){
      clear_key();
      n++;
    }
  } else if (MODE_type == 0x03) { //Equation
  } else if (MODE_type == 0x04) { //Integral
  } else if (MODE_type == 0x05) { //Derivator
  } else if (MODE_type == 0x06) { //Interpolation
  } else if (MODE_type == 0x10) {
    lcd.clear();
    lcd.print(" RAD  DEG  GRAD");
    if(c == 0x42){ //for RAD
      tri = 0x00;
      MODE_type = 0x01;
      lcd.print("RAD");
      delay(400);
      refresh(c);
    }else if(c == 0x43){ //for DEG
      tri = 0x01;
      MODE_type = 0x01;
      lcd.print("DEG");
      delay(400);
      refresh(c);
    }else if(c == 0x44){ //for GRAD
      tri = 0x02;
      MODE_type = 0x01;
      lcd.print("GRAD");
      delay(400);
      refresh(c);
    }else if(c == 0x52){
        MODE_type = 0x11;
        lcd.clear();
        lcd.print(" FIX  ENG  SCI");
    }
  }else if (MODE_type == 0x11) { //Representation (refresh, or lcd.print)
    lcd.clear();
    lcd.print(" FIX  ENG  SCI");
    if(c == 0x42){        //for FIX
      notation = 0x00;
      MODE_type = 0x01;
      lcd.print("FIX");
      delay(400);
      refresh(c);
    }else if(c == 0x43){ //for ENG
      notation = 0x01;
      MODE_type = 0x01;
      lcd.print("ENG");
      delay(400);
      refresh(c);
    }else if(c == 0x44){ //for SCI
      notation = 0x02;
      MODE_type = 0x01;
      lcd.print("SCI");
      delay(400);
      refresh(c);
    }else if(c == 0x52){
      MODE_type = 0x10;
      lcd.clear();
      lcd.print(" RAD  DEG  GRAD");
    }
    //refresh(c);
  }
  while (digitalRead(row_A) | digitalRead(row_B) | digitalRead(row_C) | digitalRead(row_D)) { //----------------------------------------impede o efeito boucing
  }
  delay(20);
  TIMSK2 = 0x01;   //Habilita interrupção do Timer2
}


void loop() {
  if(MODE_type == 0x00){
    //menu();
  }else if(MODE_type == 0x02){
    linear_system();
  }
}

//Funções Gerais
//=============================================================MENU
/*void menu(){
  const char *menu_items[] = {"RPN MODE", "Linear System", "Equation Solver", "Integral Solver", "Derivator", "Interpolation"};
  char m = n;
  lcd.clear();
  lcd.print("Set mode: ");
  while(n==m){
  }
  lcd.setCursor(0,1);
  lcd.print(menu_items[((int)n)]);
}
*/
//=============================================================MENU                                     void RPN();             //Modo 1
//=============================================================LINEAR SYSTEM
/*
extern unsigned int __heap_start;
extern void *__brkval;

int freeMemory() {
  int free_memory;
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__heap_start);
  } else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
  }
  return free_memory;
}*/
//------------------------------To see resources consume

void linear_system(){
  char m = 0x00;
  n = 0x00;
  int z = 0;
  lcd.setCursor(0, 0);
  lcd.print("MATRIX ORDER:   ");
  lcd.setCursor(0, 1);
  while(!n){//Loop to enter the order matrix
    z++;
    if(z > 16384){
      lcd.print(".");
      z=0;
    }
  }
  m = map((int) float_buffer, 0, 255, 0x00, 0xFF);
  lcd.setCursor(0, 0);
  //lcd.print("Order: ");
  //lcd.print((int)m);
  double **A = (double **)malloc(m * sizeof(double *));
  for (int i = 0; i < m; i++) {
      A[i] = (double *)malloc(m * sizeof(double));
  }
  /*if(A == NULL){
    lcd.clear();
    lcd.print("A allocate fail");
    delay(512);
  }else{
    lcd.clear();
    lcd.print((unsigned int)&A[0][0]);
    lcd.print(" - ");
    lcd.print((unsigned int)&A[m][m]);
    delay(255);
  }*/
  double *B = (double *)malloc(m * sizeof(double));
  double *X = (double *)malloc(m * sizeof(double));
  lcd.clear();
  lcd.print("MATRIX ENTERING:");
  n = 0x00;
  for(int i = 0; i<m; i++){//Loop to insert the matrix
    for(int j = 0; j<m; j++){
      lcd.setCursor(0, 1);
      while(!n){
        z++;
        if(z > 16384){
          lcd.print(".");
          z=0;
        }
      }
      A[i][j] = float_buffer;
      lcd.clear();
      lcd.print(i+1);
      lcd.print("A[");
      lcd.print(j+1);
      lcd.print("]<-");
      lcd.print(float_buffer,6);
      n=0x00;
    }
  }
  
  lcd.clear();
  lcd.print("RIGHT VECTOR:   ");
  for(int i = 0; i<m; i++){//Loop to insert the matrix
    lcd.setCursor(0, 1);
    while(!n){
      z++;
      if(z > 16384){
        lcd.print(".");
        z=0;
      }
    }
    B[i] = float_buffer;
    lcd.setCursor(0,0);
    lcd.print("x[");
    lcd.print(i+1);
    lcd.print("]<-");
    lcd.print(float_buffer,6);
    n=0x00;
  }
  TIMSK2 = 0x00;
  gauss_elimination(A, B, m);
  back_substitution(A, B, X, m);
  for(int i = 0; i < m; i++) {
      Num[i] = X[i];
  }
  free(B);
  free(X);
  for (int i = 0; i < m; i++) {
      free(A[i]);
  }
  free(A);
  lcd.clear();
  lcd.print("RESULT STORED   ");
  MODE_type = 0x01;
  TIMSK2 = 0x01;
  delay(500);
  refresh(n);
}
//=============================================================LINEAR SYSTEM

//=============================================================CLEAR KEY
void clear_key() {
  buffer_size = 0;
  for (int i = 0; i < MAX_BUFFER_SIZE; i++) {
    keybuffer[i] = 0x00;
  }
  lcd.noCursor();
}
//=============================================================CLEAR KEY
//==============================================================type_number
//((c > 0x29 && c < 0x40) || c == 0x2E || c == 0x65 || c == 0x54 || c == 0x53)
void type_number(char c) {
  lcd.cursor();
  if ((c > 0x2F && c < 0x3A) || c == 0x2E || c == 0x65 || c == 0x53) {           // building the number
    if(c == 0x53){
      if(SHIFT == true){
        clear_key();
        dtostrf(float(lastX), 15, 14, keybuffer);
      }else{
        c = 0x2D;                           // c = '-' negativo
      }
      SHIFT = false;
    }
    if (buffer_size < MAX_BUFFER_SIZE) {
      keybuffer[buffer_size] = c;
      buffer_size++;
    }
    keybuffer[buffer_size + 1] = '\0';    // Null-terminate buffer
  } else if (c == 0x54 && buffer_size > 0) {                         // backspace the number
    if (c == 0x54 && SHIFT) {
      clear_key();                        // Limpa o buffer
    }else{
      buffer_size--;
      keybuffer[buffer_size] = 0x00;        // Null-terminate buffer
    }
  }
  float_buffer = double(atof(keybuffer));  // Numero em STRING e double
  if(MODE_type == 0x01){
    if(type_flag == true){
      rollthrough();
      type_flag = false;
    }
    Num[0] = float_buffer;
    refresh(c);
  }else if(MODE_type == 0x02){
    lcd.setCursor(0,0);
    lcd.print(float_buffer);
  }
}

//==============================================================type_number
//==============================================================operate_number
void operate_number(char c) {
  lastX = Num[0];
  type_flag = true;
  //double A = Num[0];
  //Num[0] = Num[1]; //y^x
  //Num[1] = A;
  if (c == 0x2D) { // char '-' to do: minus
    if(SHIFT){
      double Im  =  Num[3]  -  Num[1];//Posição Y = Im
      double Re  =  Num[2]  -  Num[0];//Posiçõa X = Re
      Num[2]  =  Im;
      Num[1]  =  Re;
      complexo = 0x01;
    }else{
      Num[1] = Num[1] - Num[0];
      complexo = 0x00;
    }
  } else if (c == 0x2B) { // char '+' to do: plus
    if(SHIFT){
      double Im  =  Num[3]  +  Num[1];//Posição Y = Im
      double Re  =  Num[2]  +  Num[0];//Posiçõa X = Re
      Num[2]  =  Im;
      Num[1]  =  Re;
      complexo = 0x01;
    }else{
      Num[1] = Num[1] + Num[0];
      complexo = 0x00;
    }
  } else if (c == 0x2A) { // char '*' to do: mult
    if(SHIFT){
      double Re  =  Num[2] * Num[0] + ( -1 * Num[1] * Num[3]); // Num[i].Re = Num[1].Re * Num[0].Re + ( -1 * Num[0].Im * Num[1].Im);
      double Im  =  Num[0] * Num[3] + Num[2] * Num[1]; //Num[1].Im = Num[0].Re * Num[1].Im + Num[1].Re * Num[0].Im;
      Num[1]  =  Re;
      Num[2]  =  Im;
      complexo = 0x01;
    }else{
      Num[1] = Num[1] * Num[0];
      complexo = 0x00;
    }
  } else if (c == 0x2F) { // char '/' to do: div
    if(SHIFT){
      double Re  =  Num[2] * Num[0] + (Num[3] * Num[1]);
      double Im  =  Num[0] * (Num[3]) + Num[2] * ( -1 * Num[1]);
      double a = Num[1];
      Num[1] = Re / ( pow(Num[0], 2) + pow(a, 2) );
      Num[2] = Im / ( pow(Num[0], 2) + pow(a, 2) );
      complexo = 0x01;
    }else{
      Num[1] = Num[1] / Num[0];
      complexo = 0x00;
    }
  } else if (c == 0x49) {
    if(SHIFT){
      double r = sqrt(Num[2] * Num[2] + Num[3] * Num[3]);
      double theta = atan2(Num[3], Num[2]);
      double x = pow(r, Num[0]) * exp(-Num[1] * theta);
      double y = Num[0] * theta + 0.5 * Num[1] * log(r * r);
      Num[1] = x * cos(y);
      Num[2] = x * sin(y);
      complexo = 0x01;
    }else{
      Num[1] = pow(Num[1], Num[0]);//y^x)
      complexo = 0x00;
    }
  } else if (c == 0x48) {
    Num[1] = pow(Num[1], (1 / Num[0])); //y^-x
    complexo = 0x00;
  }else{
    if (c == 0x4A) {
      if(SHIFT){
        if(tri == 0x01){
            Num[1] = ((Num[1]*PI)/180);
        }else if(tri == 0x02){
            Num[1] = ((Num[1]*PI)/200);
        }
        if(polar){
          lcd.setCursor(0,1);
          lcd.print("To Rectangular  ");
          delay(400);
          polar = false;
          double a = Num[0] * cos(Num[1]);
          Num[1] = Num[0] * sin(Num[1]);
          Num[0] = a;
        }else{
          lcd.print("To Polar        ");
          delay(400);
          polar = true;
          double a = sqrt(Num[0]*Num[0] + Num[1]*Num[1]);
          Num[1] = atan2(Num[1], Num[0]);
          Num[0] = a;
        }
        //delay(50);
      }else{
        double b = Num[0];
        Num[0] = Num[1]; //y^x
        Num[1] = b;
        type_flag = false;
        //rollthrough();
      }
      return;
    } else if (c == 0x42) {
      if(SHIFT){
        Num[0] = log(Num[0]);//ln(x)
      }else{
        Num[0] = exp(Num[0]);//exp(x)
      }
      return;
    } else if (c == 0x43) {
      if(SHIFT){
        Num[0] = log10(Num[0]);//log(x)
      }else{
        Num[0] = 1/Num[0];//inverse(x)
      }
      return;
    } else if (c == 0x44) {
      if(SHIFT){
        //Num[0] = x!; //NOT IMPLEMENTED
      }else{
        Num[0] = Num[0] * Num[0];//square(x)
      }
      return;
    } else if (c == 0x45) {
      if(SHIFT){
        Num[0] = PI;//pi
      }else{
        Num[0] = pow(10,Num[0]);//10^x
      }
      return;
    } else if (c == 0x46) {// Convert to DEG or RAD or GRAD
      if(SHIFT){
        Num[0] = ((Num[0]*PI)/180);
      }else{
        Num[0] = ((Num[0]*180)/PI);
      }
      return;
    } else if (c == 0x47) {
      Num[0] = sqrt(Num[0]);//sqrt(x)
      return;
    } else if (c == 0x4B) {
      if(SHIFT){
      }else{
        polar = !polar;
      }
      return;
    } else if (c == 0x4D) {       //SIN
      if(SHIFT){
        if(tri == 0x01){                // DEG
          Num[0] = (Num[0]*PI)/180;      // DEG
        }else if(tri == 0x02){          // GRAD
          Num[0] = (Num[0]*PI)/200;      // GRAD
        }
        Num[0] = asin(Num[0]);
      }else{
        if(tri == 0x01){                 // RAD
          Num[0] = (Num[0]*PI)/180;      // DEG
        }else if(tri == 0x02){          // DEG
          Num[0] = (Num[0]*PI)/200;      // GRAD
        }
        Num[0] = sin(Num[0]);
      }
      return;
    } else if (c == 0x4E) {       //COS
      if(SHIFT){
        if(tri == 0x01){                 // RAD
          Num[0] = (Num[0]*PI)/180;      // DEG
        }else if(tri == 0x02){          // DEG
          Num[0] = (Num[0]*PI)/200;      // GRAD
        }
        Num[0] = acos(Num[0]);
      }else{
        if(tri == 0x01){                 // RAD
          Num[0] = (Num[0]*PI)/180;      // DEG
        }else if(tri == 0x02){          // DEG
          Num[0] = (Num[0]*PI)/200;      // GRAD
        }
        Num[0] = cos(Num[0]);
      }
      return;
    } else if (c == 0x4F) {       //TAN
      if(SHIFT){
        if(tri == 0x01){                 // RAD
          Num[0] = (Num[0]*PI)/180;      // DEG
        }else if(tri == 0x02){          // DEG
          Num[0] = (Num[0]*PI)/200;      // GRAD
        }
        Num[0] = atan(Num[0]);
      }else{
        if(tri == 0x01){                 // RAD
          Num[0] = (Num[0]*PI)/180;      // DEG
        }else if(tri == 0x02){          // DEG
          Num[0] = (Num[0]*PI)/200;      // GRAD
        }
        Num[0] = tan(Num[0]);
      }
      return;
    }else if(c == 0x52){
      type_flag = false;
      if(SHIFT){
        double p, q, delta, x1, x2, x3, a = Num[0], b = Num[1], c = Num[2], d = Num[3];
        double real1, imag1, real2, imag2, real3, imag3;
    
        // Calculate the coefficients p and q
        p = (3*a*c - b*b)/(3*a*a);
        q = (2*b*b*b - 9*a*b*c + 27*a*a*d)/(27*a*a*a);
    
        // Calculate the discriminant
        delta = q*q/4 + p*p*p/27;
    
        // Calculate the roots
        if (delta > 0) {
            double u = cbrt(-q/2 + sqrt(delta));
            double v = cbrt(-q/2 - sqrt(delta));
            x1 = u + v - b/(3*a);
            x2 = -0.5*(u + v) - b/(3*a);
            x3 = 0.5*sqrt(3)*(u - v);
            Num[0] = x1;
            Num[1] = x2;
            Num[2] = x3;
            complexo = 0x00;
        }
        else if (delta == 0) {
            double u = cbrt(-q/2);
            x1 = 2*u - b/(3*a);
            x2 = -u - b/(3*a);
            Num[0] = x1;
            Num[1] = x2;
            Num[2] = x2;
            complexo = 0x00;
        }
        else {
            double theta, cosTheta, sinTheta;
            theta = acos(-q/2/sqrt(-p*p*p/27));
            cosTheta = cos(theta/3);
            sinTheta = sin(theta/3);
            x1 = 2*sqrt(-p/3)*cosTheta - b/(3*a);
            x2 = 2*sqrt(-p/3)*cos(theta/3 + 2*PI/3) - b/(3*a);
            x3 = 2*sqrt(-p/3)*cos(theta/3 + 4*PI/3) - b/(3*a);
            Num[0] = x1;
            Num[1] = 0xFFFF;
            Num[2] = -sqrt(-p/3)*cosTheta - b/(3*a);
            Num[3] = sqrt(-p/3)*sinTheta;
            Num[4] = -sqrt(-p/3)*cosTheta - b/(3*a);
            Num[5] = -sqrt(-p/3)*sinTheta;
            complexo = 0x02;
        }
      }else{
        rollthrough();
      }
      return;
    }else if(c == 0x51){
      type_flag = false;
      if(SHIFT){
        double a = Num[0], b = Num[1], c = Num[3];
        double delta = (b * b) - (4 * a * c);
        double root1, root2;
        if (delta > 0) {
            root1 = (-b + sqrt(delta)) / (2 * a);
            root2 = (-b - sqrt(delta)) / (2 * a);
            Num[2] = root2;
            Num[1] = root1;
            complexo = 0x00;
        } else if (delta == 0) {
            root1 = -b / (2 * a);
            Num[1] = root1;
            complexo = 0x00;
        } else {
          root1 = -b/(2*a);
          root2 = sqrt(-delta)/(2*a);
          Num[3] = -root2;
          Num[2] = root1;
          Num[1] = root2;
          Num[0] = root1;
          complexo = 0x02;
        }
      }else{
        rollback();
      }
      return;
    }
  }
  rollback();
  Num[19] = 0;
}
//==============================================================operate_number
//=============================================================store_number
void store_number(char c) {
  clear_key();
  rollthrough();
  Num[0] = Num[1];
  refresh(c);
}
//=============================================================store_number
//=============================================================roll back
void rollback(){
  double temporario = Num[0];
  for(int j=0; j<19; j++){
    Num[j] = Num[j+1];
  }
  Num[19] = temporario;
}
//=============================================================roll back
//=============================================================roll through    
void rollthrough(){
  double temporario = Num[19];
  for(int j=19; j>0; j--){
    Num[j] = Num[j-1];
  }
  Num[0] = temporario;
}
//=============================================================roll through
//=============================================================refresh
void refresh(char c) {
  int i;
  //--------------------------------------------------------------------------------while(i > 1){
  if((c > 0x41 && c < 0x46) ||(c > 0x46 && c < 0x4A) ||(c > 0x4B && c < 0x51) || (c > 0x29 && c < 0x2E) || (c > 0x2E && c < 0x30)){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.noCursor();
    i = 8;
  }else{
    lcd.setCursor(0,0);
    lcd.cursor();
    i = 9;
  }
  if(notation == 0x00){
    lcd.print(Num[0], i);
    if(c==0x50){
      lcd.setCursor(0,0);
      lcd.print(Num[0], i);
    }
  }else if(notation == 0x01){
    //int exponent = floor(log10(Num[0])); // Determine the exponent
    //exponent -= (exponent%3);
    //double value = Num[0]*pow(10, exponent * -1);

    int exponent = floor(log10(abs(Num[0]))); // Determine the exponent
    exponent -= (exponent%3);
    double value = Num[0]*pow(10, exponent * -1);
    if(exponent < 0) {
        value *= pow(10, -3*(exponent/3));
        exponent -= (exponent%3);
    }

    lcd.print(value,5);
    lcd.print("E");
    lcd.print(exponent);
    if(c==0x50){
      lcd.setCursor(0,0);
      lcd.print(value,5);
      lcd.print("E");
      lcd.print(exponent);
    }
  }else if(notation == 0x02){ // To print in Scientific Notation
    int exponent = floor(log10(Num[0])); // Determine the exponent
    double value = Num[0]*pow(10, exponent * -1);
    lcd.print(value,5);
    lcd.print("E");
    lcd.print(exponent);
    if(c==0x50){
      lcd.setCursor(0,0);
      lcd.print(value,5);
      lcd.print("E");
      lcd.print(exponent);
    }
    //clear_key();
  }
  if(c == 0x53 && SHIFT == true){
    lcd.setCursor(0,0);
    lcd.print(lastX,11);
  }
  //--------------------------------------------------------------------------------}
  if(complexo != 0x00){
     lcd.setCursor(12,1);
    if(complexo == 0x01){
      lcd.print("2cpl");
    }else if(complexo == 0x02){
      lcd.print("3cpl");
    }else if(complexo == 0x03){
      lcd.print("4cpl");
    }
  }else{
    lcd.setCursor(12,1);
    lcd.print("    ");
  }
  lcd.setCursor(12,0);
  if(tri == 0x00){
    lcd.print(" rad");
  }else if(tri == 0x01){
    lcd.print(" deg");
  }else{
    lcd.print(" grd");
  }
  if(polar){
    lcd.setCursor(9,1);
    lcd.print("pol");
  }else{
    lcd.setCursor(9,1);
    lcd.print("ret");
  }
}
//=============================================================refresh
//=============================================================GAUSS
void gauss_elimination(double **A, double *B, char n) {
    int max_row;
    double max_val, factor;

    for (int i = 0; i < n - 1; i++) {
        // partial pivoting
        max_row = i;
        max_val = A[i][i];
        for (int j = i + 1; j < n; j++) {
            if (fabs(A[j][i]) > fabs(max_val)) {
                max_row = j;
                max_val = A[j][i];
            }
        }
        if (max_row != i) {
            // swap rows
            for (int j = i; j < n; j++) {
                double temp = A[i][j];
                A[i][j] = A[max_row][j];
                A[max_row][j] = temp;
            }
            double temp = B[i];
            B[i] = B[max_row];
            B[max_row] = temp;
        }

        // elimination
        for (int j = i + 1; j < n; j++) {
            factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            B[j] -= factor * B[i];
        }
    }
}

void back_substitution(double **A, double *B, double *X, char n) {
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * X[j];
        }
        X[i] = (B[i] - sum) / A[i][i];
    }
}
//=============================================================GAUSS
