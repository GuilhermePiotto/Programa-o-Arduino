#include <Wire.h>         // inclusão da biblioteca responsável por conter as funções necessárias para gerenciar a comunicação entre os dispositivos através do protocolo I2C.
#include <VL53L0X.h>      // inclusão da biblioteca do sensor de distância VL53LOX.
int rele = 8;             // criação da variável chamade de rele, localizada na porta 8 do Arduino.


VL53L0X sensor;

void setup()
{
  Serial.begin(9600);         // Configura a taxa de transferência em 9600 bits por segundo para transmissão serial. Para comunicação com um computador, através do Monitor Serial da IDE
  Wire.begin();               // Inicie a biblioteca Wire e junte-se ao barramento I2C como mestre ou escravo, nesse caso usado como mestre. 
  pinMode (rele, OUTPUT);     // definição do pino do rele como saida

  sensor.init();
  sensor.setTimeout(500);     // define 500 milissegundos para aguardar os dados seriais.
  sensor.startContinuous();   // Iniciar o modo contínuo back-to-back (fazer leituras o mais rápido possível).
}

void loop() {
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) {                     
    Serial.print(" TIMEOUT");                           // imprime no monitor serial a distância que o sensor está medindo em milímetro.
  }
  if (sensor.readRangeContinuousMillimeters()< 50) {
    digitalWrite(rele, HIGH);                          // verifica a distância do sensor, se a distância for menor que 50 milímetros, o Arduino manda sinal alto pata a porta 8 do rele.
   
  }
  if (sensor.readRangeContinuousMillimeters()> 50) {
    digitalWrite(rele,LOW);                             // verifica a distância do sensor, se a distância for maior que 50 milímetros, o Arduino manda sinal baixo pata a porta 8 do rele.
   
  }
  Serial.println();
}
