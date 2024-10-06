int tempoON = 1000;
int tempoOFF = 500;
int iterazione = 0;

// Predisponiamo le funzioni, alle funzioni è assegnato un indirizzo in memoria
String statoA(int p);
String statoB(int p);

// Si costruisce un array di puntantori: l'operatore prefisso * permette di indicare in modo esplicito il tipo puntatore
// Dalla tradizione C la scrittura, la presenza di () postfisso in (*f)() indica in modo esplicito un puntatore a funzione 
// ogni elemento è un puntatore a funzione, il cui indirizzo è indicato in modo esplicito con l'operatore & (riferimento) prefisso
// le funzioni riferite hanno un solo parametro formale. 
// L'array è inizializzato con gli indirizzi delle funzioni pre-dichiarate alle righe 5 e 6 alle quali è già assegnato un indirizzo
String (*stati[2])(int) = {&statoA, &statoB};

void setup() {
  Serial.begin(9600);
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.println(stati[(iterazione++)%2](tempoON));
  Serial.print(iterazione);Serial.print(" -> ");
  Serial.println(stati[(iterazione++)%2](tempoOFF));
  Serial.print(iterazione); Serial.print(" -> ");
}

String statoA(int p) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(p); 
  return "ON risolto"; 
}  

String statoB(int p) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(p);  
  return "OFF risolto";
}

