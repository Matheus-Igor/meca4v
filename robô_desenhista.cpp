// TRIBUTO A DIEGO AUGUSTO E ERIVALDO JUNIOR QUE DERAM APOIO MORAL ENQUANTO EU FAZIA O CODIGO

#include <Servo.h>

Servo servo1, servo2, caneta; // servo 1, 2 e caneta de acordo com a biblioteca <Servo.h>
int tamanhoDoElo1 = 5; // tamanho do servo 1
int tamanhoDoElo2 = 8; // tamanho do servo 2
float atualAnguloDoServo1 = 0; // atual angulo do servo 1
float atualAnguloDoServo2 = 0; // atual angulo do servo 2
float resultadoDaCinematicaInversaDoServo1 = 0; // resultado da cinematica do servo 1 que varia de 0 a 180
float resultadoDaCinematicaInversaDoServo2 = 0; // resultado da cinematica do servo 2 que varia de 0 a 180
float pontosDoDesenho[]={
-8.00, 8.00,
-4.00, 8.00,
-4.00, 4.00,
-8.00, 4.00,
-8.00, 8.00, 
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
  delay(2500);
}

void loop(){
    atualizeServos();
}

void atualizeServos(){
    float angulosNecessariosParaOServo1AlcancarOResultadoDaCinematicaInversa = 0;
    float angulosNecessariosParaOServo2AlcancarOResultadoDaCinematicaInversa = 0;
    float atualAnguloDoServo1 = resultadoDaCinematicaInversaDoServo1;
    float atualAnguloDoServo2 = resultadoDaCinematicaInversaDoServo2;
    calculeCinematicaInversa();
    angulosNecessariosParaOServo1AlcancarOResultadoDaCinematicaInversa = resultadoDaCinematicaInversaDoServo1 - atualAnguloDoServo1;
    angulosNecessariosParaOServo2AlcancarOResultadoDaCinematicaInversa = resultadoDaCinematicaInversaDoServo2 - atualAnguloDoServo2;
    for (i = 0; i < 5; i++) { // suavizador do movimento da caneta que divide o avanço em 5 partes
        atualAnguloDoServo1 = atualAnguloDoServo1+(angulosNecessariosParaOServo1AlcancarOResultadoDaCinematicaInversa/5);
        atualAnguloDoServo2 = atualAnguloDoServo2+(angulosNecessariosParaOServo2AlcancarOResultadoDaCinematicaInversa/5);
        servo1.write(atualAnguloDoServo1);
        servo2.write(180-atualAnguloDoServo2);
    }
    delay(25);
    Serial.println((String)"Posicao do proximo ponto (x, y) do desenho no array: ["+pontoX+"] e ["+pontoY+"]");
    Serial.println((String)"Novo ponto (x, y) alcancado com sucesso atraves dos angulos: "+atualAnguloDoServo1+" e "+atualAnguloDoServo2);
    if (pontoX == 0 && pontoY == 1) { // abaixador da caneta no inicio do desenho
      delay(1000);
      caneta.write(180-90);
      Serial.println("---Primeiro ponto (x, y) do desenho terminado---");
      delay(1000);
    }
    if (pontoX == 8 && pontoY == 9) { // levantador da caneta no final do desenho
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
    resultadoDaCinematicaInversaDoServo1 = acos(pontosDoDesenho[pontoX]/a) - acos(((pontosDoDesenho[pontoX]*pontosDoDesenho[pontoX]+pontosDoDesenho[pontoY]*pontosDoDesenho[pontoY])+(tamanhoDoElo1*tamanhoDoElo1)-(tamanhoDoElo2*tamanhoDoElo2))/(2*tamanhoDoElo1*a));
    resultadoDaCinematicaInversaDoServo1 = resultadoDaCinematicaInversaDoServo1*(180/M_PI);
    resultadoDaCinematicaInversaDoServo2 = acos(((tamanhoDoElo1*tamanhoDoElo1)+(tamanhoDoElo2*tamanhoDoElo2)-(pontosDoDesenho[pontoX]*pontosDoDesenho[pontoX]+pontosDoDesenho[pontoY]*pontosDoDesenho[pontoY]))/(2*tamanhoDoElo1*tamanhoDoElo2));
    resultadoDaCinematicaInversaDoServo2 = 180-(resultadoDaCinematicaInversaDoServo2*(180/M_PI));
}
