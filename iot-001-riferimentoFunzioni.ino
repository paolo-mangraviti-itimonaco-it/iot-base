int tempoON = 1000;
int tempoOFF = 500;
int iterazione = 0;

// Predisponiamo le funzioni, alle funzioni è assegnato un indirizzo in memoria
String statoA(int p);
String statoB(int p);

// Si costruisce un array di puntantori: l'operatore prefisso * permette di indicare in modo esplicito il tipo puntatore
// Dalla tradizione C la scrittura, la presenza scrittura (*f)() indica in modo esplicito un puntatore a funzione. 
// (*f)(int) puntatore a funzione che ha parametro formale di tipo intero
String (*stati[2])(int) = {&statoA, &statoB};
// ogni elemento è un puntatore a funzione, il cui indirizzo è indicato in modo esplicito con l'operatore & (riferimento) prefisso
// le funzioni riferite hanno un solo parametro formale indicato nella scrittura (int). 
// L'array è inizializzato con gli indirizzi delle funzioni pre-dichiarate alle righe 6 e 7 e che quindi si trovano già assegnato un indirizzo fisico 
// stati[0](20) === statoA(20)
// stati[1](33) === statoB(33)

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

// Implementazione della funzione statoA(p)
String statoA(int p) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(p); 
  return "ON risolto"; 
}  

// Implementazione della funzione statoB(p)
String statoB(int p) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(p);  
  return "OFF risolto";
}

