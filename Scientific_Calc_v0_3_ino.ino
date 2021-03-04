#include <SoftwareSerial.h>
#include <avr/eeprom.h>                                   //Biblioteca para uso da EEPROM para armazenar e utilizar valores lidos
#include <LiquidCrystal.h>                              //Biblioteca para o display LCD
#include <math.h>
//----MACROS----
#define button0 A0
#define button1 A1
#define button2 2
#define button3 1
#define 	M_E   2.7182818284590452354
// --- Hardware do LCD ---
LiquidCrystal disp(3,  //RS no digital 3
4,  //RW no digital 4
5,  //EN no digital 5
6,  //D4 no digital 6
7,  //D5 no digital 7
8,  //D6 no digital 8
9); //D7 no digital 9
byte integral[9] = { //Simbolo integral
  B00010,
  B00101,
  B00100,
  B00100,
  B00100,
  B00100,
  B10100,
  B01000,
};
byte realoc[9] = {  //Simbolo de setas right-left, usado para a troca em memoria de 'x' e 'y'
  B00000,
  B00010,
  B11111,
  B00010,
  B01000,
  B11111,
  B01000,
  B00000,
};
byte up[9] = { //Seta UP
  B00000,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00000,
};
byte down[9] = { //Seta DOWN
  B00000,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000,
};/*
byte bigInteg0[9] = {
 B00010,
 B00101,
 B00101,
 B00100,
 B00100,
 B00100,
 B00100,
 B00100,
 };
 byte bigInteg1[9] = {
 B00100,
 B00100,
 B00100,
 B00100,
 B00100,
 B10100,
 B10100,
 B01000,
 };*/
float number, x, y, z, t, lastx;
int leng, but0, but1, i=0;
boolean bt0, bt1, bt2, bt3, bt4,
bt5, bt6, bt7, bt8, bt9,
bt10, bt11, bt12, bt13, bt14,
bt15, bt16, bt17, bt18, bt19,
pilha = true, equa = false, sft, sft1, sh0, sh1;
char bnum, num[8]="", num0[]="";// power[] = (char(235), char(232), 'y'), rot[] = ('y', char(235)), ex[] = ('10', char(235)), inv[] = ('x', char(233)), xtoy[] = ('x', (byte(1)), 'y'), rup[] = ('R', (byte(2))), rdown[] = ('R',(byte(3)));


void shift(); //Funçao teclas shift
void RPN(); //Funçao RPN
void EQN(); //Funçao Equaçao
void key(); //Funçao de leitura do teclado

void mov();
void rt(); //Funçao de raiz quadrada
void xrt(); //Funçao de raiz x de y
void pw(); //Funçao de potencia quadrada
void xpw(); //Funçao de potencia x de y
void ex(); //Funçao de 10^x
void eex(); //Funçao de e^x
void lg(); //Funçao de logaritimo
void ln(); //Funçao de LN
void xf(); //Funçao de fatorial - x!
void inv(); //Funçao de inverso ^-1
void asn(); //Funçao de asin
void sn(); //Funçao de sin
void acs(); //Funçao de acos
void cs(); //Funçao de cos
void at(); //Funçao de atg
void tg(); //Funçao de tg
void pr(); //Funçao de porcentagem
void cpr(); //Funçao de mudança porcentagem
void sum0(); //Funçao de Somatorio -
void sum1(); //Funçao de Somatorio +

void setup(){
  disp.begin(16,2);
  disp.blink();
  disp.setCursor(0,0);
  disp.leftToRight();
  disp.createChar(0, integral);
  disp.createChar(1, realoc);
  disp.createChar(2, up);
  disp.createChar(3, down);
}
void loop(){
  while(pilha == true){
    but0 = (analogRead(button0));
    but1 = (analogRead(button1));
    key();
    RPN();
    if(equa){
      pilha = false;
    }
  }
  while(equa == true){
    EQN();
    if(pilha){
      equa = false;
    }
  }
}
void RPN(){
  sft1 = (but0 || but1);
  if(sft1){
    delay(20);
    int j=0;
    i++;
    key();
    strcat(num, ""); //Concatena valor NULL ao array
      leng = i-1;
    num[leng] = bnum;  //adiciona 'bnum' ao array na localidade 'leng'
    number = atof(num); //converte bnum (char) para number (float)
    disp.setCursor(0,0);
    disp.print(number,12);
    disp.setCursor(0,1);
    disp.print(num);
    disp.setCursor(12,0);
    disp.print(but1);
    disp.setCursor(12,1);
    disp.print(but0);
    delay(20);
    int tik=0;
    if(i==16){ //Se o numero alcançar 16 digitos, incluso o '.'
    for(; j<=strlen(num); j++){ //Limpa o buffer de 'bnum'
      num[j]=NULL;
    }for(; tik<=15;tik++){ //Limpa a tela. O uso do disp.clear apaga o buffer do LCD, e por isso ligeiramente mais.
//      disp.setCursor(tik,0);
//      disp.write(byte(254));
        disp.clear();
    }
    j=0;
    i=0;
  }
}
  sft=false;
  bnum=0x00;
}
void EQN(){ //funçao de equaçao ainda nao criada

}
void shift(){
  if(sh0==false && sh1==false){
    sft=0;
  }
  else if(sh0==true && sh1==false){
    sft=1;
  }
  else if(sh0==false && sh1==true){
    sft=2;
  }
  else if(sh0==true && sh1==true){
    sft=3;
  }
}
void key(){
  if(but0){
    if(but0 > 50 && but0 < 130){
      switch(sft){
      case 0:
        bnum='0';
        break;
      case 1:
        //  bnum="sin";
        break;
      case 2:
        // bnum="asin";
        break;
      }
    }
    else if(but0 > 130 && but0 < 215){
      switch(sft){
      case 0:
        bnum='1';
        break;
      case 1:
        // bnum="cos";
        break;
      case 2:
        // bnum="acos";
        break;
      }
    }
    else if(but0 > 215 && but0 < 300){
      switch(sft){
      case 0:
        bnum='2';
        break;
      case 1:
        // bnum="tg";
        break;
      case 2:
        // bnum="atg";
        break;
      }
    }
    else if(but0 > 300 && but0 < 370){
      switch(sft){
      case 0:
        bnum='3';
        break;
      case 1:
        // bnum='rot';
        break;
      case 2:
        //  bnum='pow';
        break;
      }
    }
    else if(but0 > 370 && but0 < 455){
      switch(sft){
      case 0:
        bnum='4';
        break;
      case 1:
  //      bnum='A';
        break;
      case 2:
        // bnum="ln";
        break;
      }
    }
    else if(but0 > 455 && but0 < 545){
      switch(sft){
      case 0:
        bnum='5';
        break;
      case 1:
    //    bnum='B';
        break;
      case 2:
        //  bnum="log";
        break;
      }
    }
    else if(but0 > 545 && but0 < 650){
      switch(sft){
      case 0:
        bnum='6';
        break;
      case 1:
    //    bnum='C';
        break;
      case 2:
 //       bnum=(byte(0));
        break;
      }
    }
    else if(but0 > 650 && but0 < 770){
      switch(sft){
      case 0:
        bnum='7';
        break;
      case 1:
    //    bnum='D';
        break;
      case 2:
        //  bnum="d/dx";
        break;
      }
    }
    else if(but0 > 770 && but0 < 920){
      switch(sft){
      case 0:
        bnum='8';
        break;
      case 1:
    //    bnum='E';
        break;
      case 2:
    //    bnum='.';
        break;
      }
    }
    else if(but0 > 920 && but0 < 1024){
      switch(sft){
      case 0:
       bnum='9';
        break;
      case 1:
     //   bnum='F';
        break;
      case 2:
        //  bnum="x!";
        break;
      }
    }

  }
  if(but1){
    if(but1 > 50 && but1 < 130){
      switch(sft){
      case 0:
        bnum='.';
        break;
      case 1:
        //   bnum="RPN";
        break;
      case 2:
        //  bnum="EQN";
        break;
      }
    }
    else if(but1 > 130 && but1 < 215){
      switch(sft){
      case 0:
        bnum='e';
        break;
        //    case 1:
        //    bnum=String(char(247));
        //    break;
      case 2:
    //    bnum='*';
        break;
      }
    }
    else if(but1 > 215 && but1 < 300){
      switch(sft){
      case 0:
    //    bnum='/';
        break;
      case 1:
        //  bnum='exp';
        break;
      case 2:
        //bnum='inv';
        break;
      }
    }
    else if(but1 > 300 && but1 < 370){
      switch(sft){
      case 0:
    //    bnum='+';
        break;
      case 1:
   //     bnum='x';
        break;
      case 2:
    //    bnum='y';
        break;
      }
    }
    else if(but1 > 370 && but1 < 455){
      switch(sft){
      case 0:
   //     bnum='-';
        break;
      case 1:
    //    bnum='(';
        break;
      case 2:
    //    bnum=')';
        break;
      }
    }
    else if(but1 > 455 && but1 < 545){
      switch(sft){
      case 0:
    //    bnum='5';
        break;
      case 1:
        //  bnum="cls";
        break;
      case 2:
      //  bnum='=';
        break;
      }
    }
    else if(but1 > 545 && but1 < 650){
      switch(sft){
      case 0:
        //   bnum='x-y';
        break;
      case 1:
        //   bnum='Rup';
        break;
      case 2:
        //   bnum='Rdn';
        break;
      }
    }else if(but1 > 650 && but1 < 770){
     switch(sft){
     case 0:
     bnum;
     break;
     case 1:
     bnum;
     break;
     case 2:
     bnum;
     break;
     }
     }
    else if(but0 > 770 && but1 < 920){
      switch(sft){
      case 0:
        sh0=1;
        disp.setCursor(12,0);
        disp.write(byte(1));
        break;
      case 1:
        sh0=0;
        disp.setCursor(12,0);
        disp.write(byte(0));
        break;
      case 2:
        sh0=1;
        disp.setCursor(12,0);
        disp.write(byte(1));
        break;
      }
    }
    else if(but0 > 920 && but1 < 1024){
      switch(sft){
      case 0:
        sh1=1;
        disp.setCursor(12,0);
        disp.write(byte(3));
        break;
      case 1:
        sh1=1;
        disp.setCursor(12,0);
        disp.write(byte(3));
        break;
      case 2:
        sh1=0;
        disp.setCursor(12,0);
        disp.write(byte(1));
        break;
      }
    }

  }

}
void mov(){
  t=z;
  z=y;
  y=x;
  x=number;
}
void rt(){ //Funçao de raiz quadrada
x=number;
  lastx=number;
  number=sqrt(x);
    mov();
  }
void xrt(){ //Funçao de raiz x de y
x=number;
  lastx=number;
  number=pow(y, (1/x));
    mov();
  }
void pw(){ //Funçao de potencia quadrada
x=number;
  lastx=number;
  number=pow(x, 2);
    mov();
  }
void xpw(){ //Funçao de potencia x de y
x=number;
  lastx=number;
  number=pow(y, x);
    mov();
  }
void ex(){ //Funçao de 10^x
x=number;
  lastx=number;
  number=pow(10, x);
    mov();
  }
void eex(){ //Funçao de e^x
x=number;
  lastx=number;
  number=pow(M_E, x);
    mov();
  }
void lg(){ //Funçao de logaritimo
x=number;
  lastx=number;
  number=log10(x);
    mov();
  }
void ln(){ //Funçao de LN
x=number;
  lastx=number;
  number=log(x);
    mov();
  }
void xf(){ //Funçao de fatorial - x!
x=number;
  lastx=number;
  for(int ft=1; ft <= (x-1); ft++){
    x=x*(x-ft);
  } 
  number=x;
    mov();
  }
void inv(){ //Funçao de inverso ^-1
x=number;
  lastx=number;
  number=1/x;
    mov();
}
void asn(){ //Funçao de asin
x=number;
  lastx=number;
  number=asin(number);
    mov();
}
void sn(){ //Funçao de sin
x=number;
  lastx=number;
  number=sin(x);
    mov();
}
void acs(){ //Funçao de acos
x=number;
  lastx=number;
  number=acos(x);
    mov();
}
void cs(){ //Funçao de cos
x=number;
  lastx=number;
  number=cos(x);
    mov();
}
void at(){ //Funçao de atg
x=number;
  lastx=number;
  number=atan(x);
    mov();
} 
void tg(){ //Funçao de tg
x=number;
  lastx=number;
  number=tan(x);
    mov();
}  
void pr(){ //Funçao de porcentagem
x=number;
  lastx=number;
  number=y*(x/100);
    mov();
}
void cpr(){ //Funçao de diferença percentual
x=number;
  lastx=number;
  number=y+y*(x/100);
    mov();
}
void sum0(){ //Funçao de Somatorio -
x=number;
  lastx=number;
  number=pow((z-y), x);
    mov();
}
void sum1(){ //Funçao de Somatorio +
x=number;
  lastx=number;
  number=pow((z+y), x);
    mov();
}
