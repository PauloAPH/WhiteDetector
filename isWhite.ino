#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define sensorOut 12
#define RELE 4

// Stores frequency read by the photodiodes
int freqVermelho = 0;
int freqVerde = 0;
int freqAzul = 0;
int freqSemFiltro = 0;

int difVermelho = 0;
int difVerde = 0;
int difAzul = 0;

int media = 0;
float desvio_padrao;

bool isWhite = false;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(RELE, OUTPUT);
  pinMode(sensorOut, INPUT);
    
  digitalWrite(S0,LOW);
  digitalWrite(S1,HIGH);
  
  Serial.begin(9600);
}

void idColor(int *vermelho, int *azul, int *verde){

  //sem filtro
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  freqSemFiltro = pulseIn(sensorOut, LOW);

  //vermelho
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  freqVermelho = pulseIn(sensorOut, LOW);

  //verde
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  freqVerde = pulseIn(sensorOut, LOW);
 
  // azul
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  freqAzul = pulseIn(sensorOut, LOW);

  *vermelho = freqVermelho - freqSemFiltro;
  *verde = freqVerde - freqSemFiltro;
  *azul = freqAzul - freqSemFiltro;

  /*
  Serial.print("R=");
  Serial.print(difVermelho);
  Serial.print(" G=");
  Serial.print(difVerde);
  Serial.print(" B=");
  Serial.println(difAzul);*/
}

void loop() {
  delay(10);
  idColor(&difVermelho, &difAzul, &difVerde);
  media = (difVermelho + difVerde + difAzul)/3;
  desvio_padrao = sqrt(   (pow(difVermelho - media,2) + pow(difVerde - media,2) + pow(difAzul - media,2)) / 3);
  
  Serial.println(desvio_padrao);

  if(desvio_padrao < 100){
    digitalWrite(RELE, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(RELE, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }
}