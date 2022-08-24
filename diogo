#include <Servo.h>

Servo servo1, servo2, caneta; // servo 1, 2 e caneta de acordo com a biblioteca <Servo.h>
int tamanhoDoElo1 = 5; // tamanho do servo 1
int tamanhoDoElo2 = 8; // tamanho do servo 2
float anguloDoServo1 = 0; // angulo do servo 1
float anguloDoServo2 = 0; // angulo do servo 2

float pontosDoDesenho[]={
-9.49, 4.79
,-9.41, 5.11
,-9.23, 5.47
,-9.05, 5.75
,-8.83, 6.02
,-8.56, 6.25
,-8.30, 6.48
,-7.76, 6.84
,-7.28, 7.07
,-7.05, 6.61
,-6.88, 6.52
,-6.66, 6.48
,-6.34, 6.43
,-5.72, 6.29
,-5.59, 6.84
,-5.46, 6.48
,-5.19, 6.48
,-5.01, 6.80
,-4.88, 6.25
,-4.61, 6.34
,-4.35, 6.39
,-4.04, 6.48
,-3.55, 6.57
,-3.37, 7.02
,-3.15, 6.98
,-2.97, 6.89
,-2.75, 6.75
,-2.48, 6.57
,-2.26, 6.43
,-2.00, 6.25
,-1.77, 5.98
,-1.60, 5.79
,-1.42, 5.52
,-1.29, 5.29
,-1.20, 5.11
,-1.11, 4.79
,-1.38, 5.02
,-1.60, 5.20
,-1.77, 5.34
,-2.00, 5.43
,-2.17, 5.47
,-2.35, 5.47
,-2.53, 5.38
,-2.66, 5.25
,-2.80, 5.06
,-2.84, 4.88
,-3.06, 4.97
,-3.33, 5.06
,-3.55, 5.11
,-3.77, 5.11
,-4.04, 5.11
,-4.26, 5.06
,-4.48, 4.97
,-4.66, 4.79
,-4.84, 4.70
,-4.97, 4.47
,-5.06, 4.33
,-5.15, 4.15
,-5.24, 3.97
,-5.32, 3.74
,-5.41, 4.01
,-5.46, 4.15
,-5.55, 4.29
,-5.68, 4.52
,-5.86, 4.74
,-6.03, 4.88
,-6.12, 4.97
,-6.30, 5.06
,-6.48, 5.06
,-6.70, 5.11
,-6.88, 5.15
,-7.05, 5.11
,-7.28, 5.06
,-7.50, 5.02
,-7.72, 4.93
,-7.85, 5.11
,-7.99, 5.25
,-8.96, 5.25
,-9.18, 5.06
,-9.36, 4.93

}; // pontos (x, y) do desenho que o robo deve alcançar
int pontoX = 0; // posicao do array que representa o atual ponto x do desenho
int pontoY = 1; // posicao do array que representa o atual ponto y do desenho
int i = 0; // contador simples

void setup(){
  servo1.attach(8); // setup do servo 1 na porta 8
  servo2.attach(9); // setup do servo 1 na porta 9
  caneta.attach(10); // setup da caneta na porta 10
  Serial.begin(9600); // setup do monitor serial para monitoramento das variaveis
  servo1.write(0); // setup do servo 1 com angulo padrao 0
  servo2.write(180-0); // setup do servo 2 com angulo padrao 0
  caneta.write(180-0); // setup da caneta com angulo padrao 0
  Serial.println("---Programa iniciado com sucesso---"); // alerta de que o programa comecou
  delay(5000);
}

void loop(){
    atualizeServos();
}

void atualizeServos(){
    calculeCinematicaInversa();
    servo1.write(anguloDoServo1);
    servo2.write(180-anguloDoServo2);
    delay(25);
    Serial.println((String)"Posicao do proximo ponto (x, y) do desenho no array: ["+pontoX+"] e ["+pontoY+"]");
    Serial.println((String)"Novo ponto (x, y) alcancado com sucesso atraves dos angulos: "+anguloDoServo1+" e "+anguloDoServo2);
    if (pontoX == 0 && pontoY == 1) { // abaixador da caneta no inicio do desenho
      delay(1000);
      caneta.write(180-45);
      Serial.println("---Primeiro ponto (x, y) do desenho terminado---");
      delay(1000);
    }
    if (pontoX == 168 && pontoY == 169) { // levantador da caneta no final do desenho
      delay(1000);
      caneta.write(180-0);
      Serial.println("---Ultimo ponto (x, y) do desenho terminado---");
      delay(1000);
      pontoX = 0;
      pontoY = 1;
    } else {
      pontoX = pontoX + 2; //
      pontoY = pontoY + 2;
    }
}

void calculeCinematicaInversa(){ // cinematica inversa atraves do tamanho dos elos e atual ponto (x, y) do desenho
    float a = sqrt(pontosDoDesenho[pontoX]*pontosDoDesenho[pontoX]+pontosDoDesenho[pontoY]*pontosDoDesenho[pontoY]);
    anguloDoServo1 = acos(pontosDoDesenho[pontoX]/a) - acos(((pontosDoDesenho[pontoX]*pontosDoDesenho[pontoX]+pontosDoDesenho[pontoY]*pontosDoDesenho[pontoY])+(tamanhoDoElo1*tamanhoDoElo1)-(tamanhoDoElo2*tamanhoDoElo2))/(2*tamanhoDoElo1*a));
    anguloDoServo1 = anguloDoServo1*(180/M_PI);
    anguloDoServo2 = acos(((tamanhoDoElo1*tamanhoDoElo1)+(tamanhoDoElo2*tamanhoDoElo2)-(pontosDoDesenho[pontoX]*pontosDoDesenho[pontoX]+pontosDoDesenho[pontoY]*pontosDoDesenho[pontoY]))/(2*tamanhoDoElo1*tamanhoDoElo2));
    anguloDoServo2 = 180-(anguloDoServo2*(180/M_PI));
}
