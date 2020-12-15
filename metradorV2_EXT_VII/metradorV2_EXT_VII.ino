// --- Variáveis Globais ---
#define input1 4
#define input2 5
#define input3 6
#define input4 7
volatile byte cmd;
unsigned long pulsos2;
unsigned long pulsos1;
unsigned long timeold;
unsigned long durationHigh;
unsigned long durationLow;
unsigned int countStopP1;
boolean p1;
boolean paradaDetectada;

//---Constantes -----
const byte interruptPin1 = 2;
const byte interruptPin2 = 3;
const unsigned long timeUpdate=500000; //microsegundos = 
const int stopDetectP1=2;


// --- ISR ---
void contador1(){
  detachInterrupt(0);
//  Serial.print("Disparo de PULSO: ");
//  Serial.println(durationHigh);
//  if(durationHigh >= 12000){
//    Serial.println("PULSO VALIDO");
    pulsos1=pulsos1+1;
    countStopP1=0;
    p1=true;
//    delay(385);
//  }  
  attachInterrupt(digitalPinToInterrupt(interruptPin1), contador1, RISING );
}

void contador2(){
  pulsos2++;
}

void setup() {
//  Serial.begin(38400);
//  Serial.println("Iniciando metrador");
  
//  Serial.println("Metrador iniciado");
  // Parametros serial
 
  Serial3.begin(38400);
  //Serial.println("Iniciando metrador");
  //configurando entradas digitais
  pinMode(input1,INPUT_PULLUP);
  pinMode(input2,INPUT_PULLUP);
  pinMode(input3,INPUT_PULLUP);
  pinMode(input4,INPUT_PULLUP);
  pinMode(interruptPin1,INPUT_PULLUP); //alterado de INPUT para INPUT_PULLUP
  pinMode(interruptPin2,INPUT_PULLUP); //alterado de INPUT para INPUT_PULLUP
  delay(60000);
  //Limpeza de variaveis  
  pulsos1= 0;
  pulsos2= 0;
  timeold=0;
  cmd=0;
  countStopP1=0;
  p1=false;
  durationHigh=0;
  durationLow=0;
  //Acionamento de interrupção
  attachInterrupt(digitalPinToInterrupt(interruptPin1), contador1, RISING );
  attachInterrupt(digitalPinToInterrupt(interruptPin2), contador2, RISING );
  
}

void loop() {
//  Serial.println("Entrou no loop");
  
//  if(Serial.available()>0){
//    cmd = Serial.read();    
//    if(cmd==49){ // comando 1
//      pulsos1 = 0;
//    }
//    if(cmd==50){ // comando 2
//      pulsos2 = 0;
//    }
//    if(cmd==51){ // comando 3
//      pulsos1 = 0;
//      pulsos2 = 0;
//    }
//  }
  if(Serial3.available()>0){
    cmd = Serial3.read();    
    if(cmd==49){ // comando 1
      pulsos1 = 0;
    }
    if(cmd==50){ // comando 2
      pulsos2 = 0;
    }
    if(cmd==51){ // comando 3
      pulsos1 = 0;
      pulsos2 = 0;
    }
  }  
  long tempo = micros() - timeold;
//  Serial.println(micros());
//  Serial.println(timeold);
//  Serial.println(tempo);
   
  if (tempo >= timeUpdate){   
    timeold = micros();
    
    if(p1==false){
      countStopP1++;      
      }
//    Serial.println(countStopP1);
    if(countStopP1<=stopDetectP1 && p1==false){
//      Serial.println("Aguardando Parada");      
      return;
    }
    //Desabilita interrupcao durante o calculo
    detachInterrupt(0);
    detachInterrupt(1);
//    Serial.print("Pulsos1:");
//    Serial.print(pulsos1);
//    Serial.print(";Pulsos2:");
//    Serial.print(pulsos2);
//    Serial.print(";");
//    //verifica estado entradas digitais
//    if(digitalRead(input1)){
//      Serial.print("Digital1:1;");
//    }else{
//      Serial.print("Digital1:0;");
//    }
//    if(digitalRead(input2)){
//      Serial.print("Digital2:1;");
//    }else{
//      Serial.print("Digital2:0;");
//    }
//    if(digitalRead(input3)){
//      Serial.print("Digital3:1;");
//    }else{
//      Serial.print("Digital3:0;");
//    }
//    if(digitalRead(input4)){
//      Serial.println("Digital4:1;");
//    }else{
//      Serial.println("Digital4:0;");
//    }
    //Comunicaão com Sistema Monitor
    Serial3.print("Pulsos1:");
    Serial3.print(pulsos1);
    Serial3.print(";Pulsos2:");
    Serial3.print(pulsos2);
    Serial3.print(";");
    //verifica estado entradas digitais
    if(digitalRead(input1)){
      Serial3.print("Digital1:1;");
    }else{
      Serial3.print("Digital1:0;");
    }
    if(digitalRead(input2)){
      Serial3.print("Digital2:1;");
    }else{
      Serial3.print("Digital2:0;");
    }
    if(digitalRead(input3)){
      Serial3.print("Digital3:1;");
    }else{
      Serial3.print("Digital3:0;");
    }
    if(digitalRead(input4)){
      Serial3.println("Digital4:1;");
    }else{
      Serial3.println("Digital4:0;");
    }
    p1=false;
    
    //Habilita interrupcao
    attachInterrupt(digitalPinToInterrupt(interruptPin1), contador1, RISING); // alterado de High para low
    attachInterrupt(digitalPinToInterrupt(interruptPin2), contador2, RISING); // alterado de High para low   
  }  

//  durationHigh = pulseIn(interruptPin1,HIGH,5000000);
  //durationLow = pulseIn(interruptPin1,LOW,10000000);
//  Serial.print("Pulso 1 Duração em alta: ");    
//  Serial.println(durationHigh);
//  Serial.print("Pulso 1 Duração em baixa: ");    
//  Serial.println(durationLow);   
}
