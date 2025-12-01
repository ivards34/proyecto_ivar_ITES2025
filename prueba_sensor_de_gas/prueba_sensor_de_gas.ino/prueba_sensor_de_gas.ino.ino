const int sensorPinao = 22;  // Pin analógico conectado al AO del MQ
const int sensorpindo = 23; //pin analogico conectado al DO del MQ

void setup() {
  Serial.begin(9600);      // Inicializa la comunicación serial
  pinMode(sensorPinao, INPUT);
  pinMode(sensorpindo, INPUT);
}

void loop() {
  int lectura = analogRead(sensorPinao);  // Lee el valor analógico (0–4095)
  int lecturado = analogRead(sensorpindo);
  Serial.print("Valor del sensor MQ: ");
  Serial.println(lectura);
  Serial.println(lecturado);

  delay(2000);  // Espera 2 segundo entre lecturas
}
