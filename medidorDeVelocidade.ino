// Sensor de distância Ultrasônico HC - SR04

int PinTrigger = 5; // Pino usado para pulso do Sensor.
int PinEcho = 4; // Pino usado para ler a saida do sensor.

float TempoEcho = 0; //Variavel tempo do echo
float distanciaAnterior = 0; // Armazena a distância anterior para cálculo da velocidade
float distanciaAtual = 0; // Armazena a distância atual
float velocidade = 0; // Velocidade calculada
unsigned long tempoAnterior = 0; // Armazena o tempo da última medição

const float velocidadeSom_mps = 340; // Velocidade do som em metros por segundo.
const float velocidadeSom_mpus = 0.000340; // Velocidade do som em microsegundos.

void setup() {
    pinMode(PinTrigger, OUTPUT); // Configura trigger como saida
    digitalWrite(PinTrigger, LOW); // Pino do trigger em nivel baixo
    pinMode(PinEcho, INPUT); // Configura pino do echo cmo entrada.
    Serial.begin(9600); // Inicializa monitor serial 9600 bps
    delay(100); // Atraso de 100 milisegundos.
    tempoAnterior = millis(); // Inicializa o tempo anterior
}

void loop(){
    DisparaPulsoUltrassonico(); // Dispara Pulso ultrassonico
    TempoEcho = pulseIn(PinEcho, HIGH);// Mede duração do pulso HIGH
    
    distanciaAtual = CalculoDistancia(TempoEcho); // Calcula distância atual
    
    // Calcula a velocidade
    CalcularVelocidade();
    
    // Atualiza para próxima medição
    distanciaAnterior = distanciaAtual;
    tempoAnterior = millis();
    
    // Exibe resultados no monitor serial
    Serial.print("Distância em metros: "); //mostra no monitor serial
    Serial.println(distanciaAtual); // Mostra calculo da distancia
    
    Serial.print("Distância em centimetros: "); //Mostra no monitor serial
    Serial.println(distanciaAtual * 100); //Mostra calculo em centimetros.
    
    Serial.print("Velocidade: "); // Mostra velocidade
    Serial.print(velocidade); // Valor da velocidade
    Serial.println(" m/s"); // Unidade
    
    Serial.println("-----------------------"); // Separador
    
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

void CalcularVelocidade()
{
    unsigned long tempoAtual = millis(); // Tempo atual
    float deltaTempo = (tempoAtual - tempoAnterior) / 1000.0; // Tempo em segundos
    
    // Calcula a velocidade (variação da distância / variação do tempo)
    if (deltaTempo > 0) { // Evita divisão por zero
        velocidade = (distanciaAtual - distanciaAnterior) / deltaTempo;
    }
    
    // Filtro para evitar valores espúrios quando há pouca variação
    if (abs(velocidade) < 0.01) {
        velocidade = 0;
    }
}                
