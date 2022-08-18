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
-10.58, 6.41,-10.46, 6.50,-10.35, 6.55,-10.24, 6.59,-10.13, 6.63,-10.02, 6.66,-9.91, 6.69,-9.80, 6.72,-9.69, 6.75,-9.57, 6.78,
-9.46, 6.82,-9.35, 6.85,-9.24, 6.88,-9.13, 6.91,-9.02, 6.93,-8.91, 6.94,-8.80, 6.95,-8.69, 6.96,-8.58, 6.97,-8.46, 6.98,
-8.35, 6.98,-8.24, 6.99,-8.13, 7.00,-8.02, 7.01,-7.91, 7.02,-7.80, 7.03,-7.69, 7.06,-7.58, 7.07,-7.47, 7.09,-7.35, 7.09,
-7.24, 7.08,-7.13, 7.08,-7.02, 7.10,-6.91, 7.11,-6.80, 7.17,-6.69, 7.26,-6.58, 7.35,-6.47, 7.45,-6.35, 7.53,-6.24, 7.59,
-6.13, 7.64,-6.02, 7.70,-5.91, 7.75,-5.80, 7.78,-5.69, 7.79,-5.58, 7.76,-5.59, 7.64,-5.66, 7.52,-5.72, 7.41,-5.78, 7.29,
-5.83, 7.13,-5.79, 6.97,-5.68, 6.90,-5.57, 6.85,-5.46, 6.79,-5.35, 6.73,-5.24, 6.66,-5.13, 6.61,-5.02, 6.54,-4.91, 6.48,
-4.79, 6.42,-4.68, 6.36,-4.57, 6.30,-4.46, 6.24,-4.35, 6.18,-4.24, 6.12,-4.13, 6.06,-4.02, 6.00,-3.91, 5.96,-3.80, 5.93,
-3.69, 5.89,-3.58, 5.88,-3.46, 5.88,-3.35, 5.95,-3.24, 6.03,-3.13, 6.09,-3.02, 6.15,-2.91, 6.22,-2.80, 6.28,-2.69, 6.34,
-2.58, 6.40,-2.46, 6.43,-2.35, 6.46,-2.24, 6.49,-2.13, 6.51,-2.02, 6.54,-1.91, 6.52,-1.99, 6.40,-2.10, 6.31,-2.21, 6.20,
-2.32, 6.10,-2.43, 5.99,-2.49, 5.87,-2.56, 5.75,-2.63, 5.62,-2.72, 5.47,-2.67, 5.30,-2.61, 5.17,-2.55, 5.06,-2.49, 4.95,
-2.42, 4.84,-2.36, 4.73,-2.30, 4.62,-2.25, 4.53,-2.23, 4.41,-2.15, 4.41,-2.35, 4.42,-2.46, 4.46,-2.57, 4.52,-2.68, 4.61,
-2.79, 4.69,-2.90, 4.79,-2.99, 4.90,-3.08, 5.00,-3.17, 5.11,-3.26, 5.22,-3.36, 5.33,-3.47, 5.41,-3.58, 5.43,-3.69, 5.43,
-3.80, 5.42,-3.91, 5.40,-4.02, 5.38,-4.13, 5.36,-4.24, 5.34,-4.35, 5.32,-4.46, 5.29,-4.58, 5.26,-4.69, 5.24,-4.80, 5.21,
-4.91, 5.14,-4.93, 5.04,-5.00, 4.96,-4.89, 4.91-4.82, 4.87,-5.11, 5.04,-5.22, 5.13,-5.33, 5.11,-5.33, 4.94,-5.41, 4.94,
-5.30, 4.86,-5.52, 5.02,-5.64, 5.13,-5.75, 5.16,-5.86, 5.15,-5.97, 5.13,-6.08, 5.12,-6.19, 5.10,-6.30, 5.09,-6.41, 5.09,
-6.52, 5.08,-6.64, 5.05,-6.60, 4.92,-6.54, 4.80,-6.49, 4.68,-6.44, 4.57,-6.39, 4.46,-6.36, 4.31,-6.30, 4.31,-6.47, 4.31,
-6.59, 4.35,-6.70, 4.42,-6.81, 4.49,-6.92, 4.57,-7.03, 4.66,-7.14, 4.76,-7.25, 4.86,-7.36, 4.97,-7.47, 5.04,-7.58, 5.05,
-7.69, 5.04,-7.73, 4.93,-7.75, 4.82,-7.78, 4.71,-7.83, 4.61,-7.88, 4.48,-7.88, 4.33,-7.94, 4.33,-8.06, 4.36,-8.16, 4.42,
-8.24, 4.52,-8.30, 4.63,-8.35, 4.74,-8.39, 4.86,-8.42, 4.98,-8.42, 5.12,-8.52, 5.15,-8.63, 5.16,-8.74, 5.18,-8.85, 5.19,
-8.96, 5.20,-9.07, 5.22,-9.19, 5.25,-9.30, 5.27,-9.41, 5.30,-9.52, 5.33,-9.63, 5.36,-9.74, 5.43,-9.85, 5.50,-9.96, 5.56,
-10.03, 5.67,-9.92, 5.73,-9.81, 5.76,-9.70, 5.78,-9.59, 5.80,-9.51, 5.89,-9.47, 5.84,-9.37, 5.86,-9.26, 5.87,-9.63, 5.92,
-9.74, 5.92,-9.85, 5.91,-9.96, 5.91,-10.07, 5.91,-10.18, 5.97,-10.29, 6.06,-10.40, 6.17,-10.51, 6.28
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
    if (pontoX >= 217 && pontoY >= 218) {
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
