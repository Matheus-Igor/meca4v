#include <Servo.h>

Servo servo1, servo2, caneta; // servo 1, 2 e caneta de acordo com a biblioteca <Servo.h>
int tamanhoDoElo1 = 5; // tamanho do servo 1
int tamanhoDoElo2 = 8; // tamanho do servo 2
float atualAnguloDoServo1 = 0; // atual angulo do servo 1
float resultadoDaCinematicaInversaDoServo1 = 0; // resultado da cinematica do servo 1 que varia de 0 a 180
float angulosNecessariosParaOServo1AlcancarOResultadoDaCinematicaInversa = 0; // angulos necessarios para o servo 1 terminar o movimento
float atualAnguloDoServo2 = 0; // atual angulo do servo 2
float resultadoDaCinematicaInversaDoServo2 = 0; // resultado da cinematica do servo 2 que varia de 0 a 180
float angulosNecessariosParaOServo2AlcancarOResultadoDaCinematicaInversa = 0; // angulos necessarios para o servo 1 terminar o movimento
int delayDoMonitorSerial = 2500; // delay do monitor serial
float fatorDeCorrecaoDoServo2 = 0.965; // fator de correcao do servo 2. use 1 em caso de normalidade na montagem do robo
bool canetaNoPapel = false; // status da caneta
float pontosDoDesenho[]={
2.45,19.36,2.50,19.25,2.55,19.42,2.56,19.17,2.64,19.47,2.65,19.10,2.73,19.51,2.74,19.02,
2.82,19.55,2.83,18.94,2.91,19.57,2.92,18.87,3.00,19.60,3.00,18.63,3.01,18.85,3.04,18.53,
3.09,19.62,3.09,18.67,3.10,18.85,3.13,18.48,3.18,19.65,3.18,18.69,3.19,18.86,3.22,18.42,
3.27,19.68,3.27,18.71,3.28,18.86,3.31,18.37,3.36,19.70,3.36,18.73,3.37,18.86,3.40,18.31,
3.45,19.73,3.45,18.75,3.46,18.86,3.49,18.28,3.54,19.75,3.54,18.77,3.55,18.86,3.58,18.26,
3.63,19.78,3.64,18.80,3.65,18.83,3.67,18.24,3.72,19.80,3.73,18.81,3.77,18.22,3.81,19.83,
3.80,18.81,3.86,18.19,3.90,19.85,3.95,18.17,3.99,19.87,4.04,18.15,4.08,19.89,4.13,18.14,
4.18,19.89,4.22,18.13,4.27,19.90,4.31,18.12,4.36,19.91,4.40,18.11,4.45,19.91,4.49,18.11,
4.54,19.92,4.58,18.09,4.63,19.93,4.63,18.00,4.63,17.86,4.67,17.76,4.69,17.67,4.72,19.94,
4.74,17.58,4.80,17.49,4.81,19.94,4.86,17.39,4.90,19.95,4.92,17.33,4.99,19.96,5.01,17.30,
5.08,19.96,5.11,17.28,5.16,17.42,5.17,19.97,5.17,17.28,5.20,17.54,5.24,17.63,5.26,19.99,
5.28,17.73,5.29,17.84,5.32,17.96,5.35,20.00,5.39,18.01,5.44,20.02,5.49,18.00,5.53,20.04,
5.58,17.99,5.62,20.04,5.67,17.93,5.71,20.03,5.76,17.84,5.80,20.03,5.85,17.76,5.89,20.04,
5.94,17.68,5.99,20.05,6.03,17.60,6.08,20.05,6.12,17.53,6.17,20.08,6.21,17.46,6.26,20.15,
6.30,17.40,6.35,20.22,6.39,18.01,6.39,17.34,6.42,17.91,6.44,20.30,6.47,17.82,6.48,18.04,
6.48,17.29,6.51,17.72,6.53,20.37,6.55,17.63,6.57,18.04,6.57,17.26,6.60,17.53,6.62,20.45,
6.65,17.42,6.66,18.05,6.67,17.24,6.70,17.33,6.71,20.51,6.75,18.05,6.72,17.23,6.80,20.55,
6.84,18.06,6.89,20.60,6.93,18.07,6.98,20.64,7.02,18.08,7.07,20.69,7.11,18.10,7.16,20.72,
7.18,20.08,7.20,18.11,7.21,19.96,7.23,20.21,7.25,20.74,7.27,20.31,7.27,19.89,7.30,18.12,
7.32,20.41,7.34,20.75,7.36,19.85,7.37,20.50,7.38,18.09,7.43,20.73,7.43,20.60,7.45,18.02,
7.45,19.80,7.49,20.66,7.54,17.95,7.54,19.75,7.63,17.90,7.63,19.71,7.68,18.07,7.70,17.97,
7.71,17.85,7.73,19.66,7.73,17.81,7.78,18.09,7.82,19.60,7.87,18.05,7.91,19.56,7.96,17.97,
8.00,19.51,8.05,17.90,8.09,19.46,8.11,18.10,8.14,17.94,8.14,17.85,8.18,19.41,8.20,18.16,
8.20,17.83,8.27,19.36,8.29,18.19,8.36,19.31,8.38,18.21,8.45,19.26,8.47,18.23,8.54,19.21,
8.56,18.25,8.63,19.16,8.65,18.27,8.72,19.11,8.74,18.29,8.81,19.06,8.83,18.31,8.90,19.01,
8.92,18.33,8.99,18.96,9.01,18.34,9.08,18.93,9.11,18.36,9.17,18.91,9.20,18.38,9.27,18.88,
9.29,18.39,9.36,18.85,9.38,18.39,9.45,18.84,9.47,18.39,9.54,18.84,9.56,18.38,9.63,18.88,
9.65,18.31,9.72,18.95,9.73,18.23,9.77,18.15,9.81,19.01,9.84,18.07,9.90,19.06,9.91,17.98,
9.99,19.11,9.99,17.89,10.08,19.16,10.07,17.81,10.12,17.73,10.17,19.21,10.21,17.67,10.26,19.27,
10.29,18.43,10.30,17.60,10.34,18.30,10.35,19.32,10.36,18.55,10.39,18.20,10.39,17.54,10.41,18.65,
10.44,19.36,10.44,18.10,10.47,18.74,10.48,17.47,10.49,18.00,10.52,18.84,10.53,19.39,10.54,17.91,
10.57,17.43,10.58,18.93,10.59,17.82,10.62,19.41,10.65,17.74,10.65,19.03,10.67,17.39,10.70,17.64,
10.71,19.44,10.74,19.11,10.76,17.54,10.76,17.37,10.80,19.46,10.81,17.45,10.83,19.19,10.84,17.36,
10.89,19.48,10.92,19.28,10.91,17.38,10.98,19.50,11.02,19.37,11.08,19.49,11.09,19.43,11.14,19.52
}; // pontos (x, y) do desenho que o robo deve alcançar
int pontoX = 0; // posicao do array que representa o atual ponto x do desenho
int pontoY = 1; // posicao do array que representa o atual ponto y do desenho
int i = 0; // contador usado para criar loops temporarios

void setup(){
  servo1.attach(8); // setup do servo 1 na porta 8
  servo2.attach(9); // setup do servo 1 na porta 9
  caneta.attach(10); // setup da caneta na porta 10
  Serial.begin(9600); // setup do monitor serial para monitoramento das variaveis
  servo1.write(0); // setup do servo 1 com angulo padrao 0
  servo2.write((180*fatorDeCorrecaoDoServo2)-0); // setup do servo 2 com angulo padrao 0
  caneta.write(180-0); // setup da caneta com angulo padrao 0
  Serial.println("Programa iniciado com sucesso"); // alerta de que o programa comecou
  delay(1000);
}

void loop(){
    atualizeServos();
}

void atualizeServos(){
    if (canetaNoPapel == true) {
        caneta.write(180-90);
        delay(10);
        Serial.print("Status da caneta: ");
        Serial.println(canetaNoPapel);
        delay(delayDoMonitorSerial);
    }
    if (canetaNoPapel == false) {
        caneta.write(180-0);
        delay(10);
        Serial.print("Status da caneta: ");
        Serial.println(canetaNoPapel);
        delay(delayDoMonitorSerial);
    }
    float atualAnguloDoServo1 = resultadoDaCinematicaInversaDoServo1;
    float atualAnguloDoServo2 = resultadoDaCinematicaInversaDoServo2;
    Serial.print("Posicao do proximo ponto (x, y) do desenho no array: ");
    Serial.println((String)"["+pontoX+"] e ["+pontoY+"]");
    delay(delayDoMonitorSerial);
    calculeCinematicaInversa(); // chamada da funcao que realiza o calculo da cinematica inversa
    Serial.println("Cinematica inversa calculada com sucesso");
    delay(delayDoMonitorSerial);
    angulosNecessariosParaOServo1AlcancarOResultadoDaCinematicaInversa = resultadoDaCinematicaInversaDoServo1 - atualAnguloDoServo1;
    angulosNecessariosParaOServo2AlcancarOResultadoDaCinematicaInversa = resultadoDaCinematicaInversaDoServo2 - atualAnguloDoServo2;
    for (i = 0; i < 5; i++) { // suavizador do movimento da caneta que divide o avanço em 5 partes
        atualAnguloDoServo1 = atualAnguloDoServo1+(angulosNecessariosParaOServo1AlcancarOResultadoDaCinematicaInversa/5);
        atualAnguloDoServo2 = atualAnguloDoServo2+(angulosNecessariosParaOServo2AlcancarOResultadoDaCinematicaInversa/5);
        servo1.write(atualAnguloDoServo1);
        servo2.write((180*fatorDeCorrecaoDoServo2)-atualAnguloDoServo2);
    }
    delay(10);
    Serial.println((String)"Novo ponto (x, y) alcancado com sucesso atraves dos angulos "+atualAnguloDoServo1+" e "+atualAnguloDoServo2);
    delay(delayDoMonitorSerial);
    if (canetaNoPapel == false) {
      delay(1000);
      canetaNoPapel = true;
      }
    if (pontoX >= 860 && pontoY >= 861) {
        delay(1000);
        canetaNoPapel = false;
        pontoX = 0;
        pontoY = 1;
    } else {
        pontoX = pontoX + 2;
        pontoY = pontoY + 2;
      }   
}

void calculeCinematicaInversa(){ // calculo da cinematica inversa atraves do tamanho dos elos e atual ponto (x, y)
    float a = sqrt(pontosDoDesenho[pontoX]*pontosDoDesenho[pontoX]+pontosDoDesenho[pontoY]*pontosDoDesenho[pontoY]);
    float b = pontosDoDesenho[pontoX]*pontosDoDesenho[pontoX]+pontosDoDesenho[pontoY]*pontosDoDesenho[pontoY];
    float c = tamanhoDoElo1*tamanhoDoElo1;
    float d = tamanhoDoElo2*tamanhoDoElo2;
    resultadoDaCinematicaInversaDoServo1 = acos(pontosDoDesenho[pontoX]/a) - acos((b+c-d)/(2*tamanhoDoElo1*a));
    resultadoDaCinematicaInversaDoServo1 = resultadoDaCinematicaInversaDoServo1*(180/M_PI);
    resultadoDaCinematicaInversaDoServo2 = acos((c+d-b)/(2*tamanhoDoElo1*tamanhoDoElo2));
    resultadoDaCinematicaInversaDoServo2 = 180-(resultadoDaCinematicaInversaDoServo2*(180/M_PI));
}
