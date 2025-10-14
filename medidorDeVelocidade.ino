// Sensor de distância Ultrasônico HC - SR04

int PinTrigger = 5; // Pino usado para pulso do Sensor.
int PinEcho = 4; // Pino usado para ler a saida do sensor.

float TempoEcho = 0; //Variavel tempo do echo

const float velocidadeSom_mps = 340; // Velocidade do som em metros por segundo.
const float velocidadeSom_mpus = 0.000340; // Velocidade do som em microsegundos.

void setup() {
    pinMode(PinTrigger, OUTPUT); // Configura trigger como saida
    digitalWrite(PinTrigger, LOW); // Pino do trigger em nivel baixo
    pinMode(PinEcho, INPUT); // Configura pino do echo cmo entrada.
    Serial.begin(9600); // Inicializa monitor serial 9600 bps
    delay(100); // Atraso de 100 milisegundos.
}

void loop(){
    DisparaPulsoUltrassonico(); // Dispara Pulso ultrassonico
    TempoEcho = pulseIn(PinEcho, HIGH);// Mede duração do pulso HIGH
    Serial.print("Distância em metros: "); //mostra no monitor serial
    Serial.println(CalculoDistancia(TempoEcho)); // Mostra calculo da distancia
    Serial.print("Distância em centimetros: "); //Mostra no monitor serial
    Serial.println(CalculoDistancia(TempoEcho) * 100); //Mostra calculo em centimetros.
    delay(200);
}

void DisparaPulsoUltrassonico()
{
  digitalWrite(PinTrigger, HIGH); // Pulso alto disparato
  delayMicroseconds(10);          // Atraso entre os disparos
  digitalWrite(PinTrigger, LOW);  // Pulso baixo disparado.
}

float CalculoDistancia(float tempo_us)
{
  return(tempo_us * velocidadeSom_mpus / 2); // Calcula a distancia em metros.
}
