// ========== CONFIGURACIÓN DE PINES ==========
// Define el pin 16 como RX para comunicación serial con el módulo SIM800
#define RXD2 16
// Define el pin 17 como TX para comunicación serial con el módulo SIM800
#define TXD2 17

// ========== SENSOR DE GAS ==========
// Define el pin analógico 12 para leer el valor analógico del sensor de gas
const int sensorPinao = 12;
// Define el pin digital 14 para leer el estado digital (encendido/apagado) del
// sensor de gas
const int sensorpindo = 14;

// ========== AJUSTE DE UMBRAL ==========
// Define el valor umbral de gas (2000). Si el sensor detecta un valor mayor, se
// activará la alerta
const int UMBRAL_GAS = 2000;

// ========== VARIABLES GLOBALES ==========
// Crea un objeto de comunicación serial (UART2) para comunicarse con el módulo
// SIM800
HardwareSerial simSerial(2);
// Variable de tipo String para almacenar el comando AT de envío de SMS con el
// número de teléfono
String phonenumber;
// Variable booleana para rastrear si ya se envió una alerta (evita envíos
// múltiples)
bool alertaEnviada = false;

// Declaración anticipada de la función enviarSMS
void enviarSMS();
// Declaración anticipada de la función comunicacion
void comunicacion();

//========== FUNCIÓN PARA comunicacion de sim800l ==========

void comunicacion(){
   // Si hay datos disponibles en el puerto serial USB (desde la computadora)
    delay(1000);
    while (Serial.available()) {
    // Lee los datos del USB y los envía al módulo SIM800
    simSerial.write(Serial.read());
    }
        
    // Si hay datos disponibles desde el módulo SIM800
    while (simSerial.available()) {
    // Lee los datos del SIM800 y los envía al monitor serial USB
    Serial.write(simSerial.read());
    }
    
  }

// ========== FUNCIÓN PARA ENVIAR SMS ==========
void enviarSMS() {

  // Inicializa la comunicación serial con el módulo SIM800 a 9600 baudios
  // usando los pines definidos
  simSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  // Imprime en el monitor serial que se está enviando un SMS
  Serial.println("Enviando SMS...");

  // Espera 10 segundos para que el módulo SIM800 se estabilice
  delay(5000);
  // Envía el comando AT para configurar el módulo en modo texto (necesario para
  // enviar SMS)
  simSerial.println("AT+CMGF=1");
  comunicacion();
  // Espera 1 segundo para que el módulo procese el comando
  delay(1000);

  // Construye el comando AT para especificar el número de teléfono destinatario
  phonenumber = String("AT+CMGS="); // Inicia el comando AT de envío de SMS
  phonenumber += String('"');       // Agrega comilla de apertura
  phonenumber +=
      String("2302488481");   // Agrega el número de teléfono destinatario
  phonenumber += String('"'); // Agrega comilla de cierre

  // Envía el comando completo al módulo SIM800 con el número de teléfono
  simSerial.println(phonenumber);
  comunicacion();
  // Espera 1 segundo para que el módulo procese el comando
  delay(1000);

  // Envía el texto del mensaje SMS
  simSerial.print("ALERTA: Gas detectado. ");
  comunicacion();
  // Espera 500 milisegundos antes de finalizar el mensaje
  delay(500);

  // Envía el carácter ASCII 26 (Ctrl+Z) que indica el fin del mensaje SMS
  simSerial.write(26);
  comunicacion();
  // Espera 5 segundos para que el módulo envíe el SMS
  delay(5000);

  // Imprime en el monitor serial que el SMS fue enviado
  Serial.println("SMS enviado");
}


// ========== CONFIGURACIÓN INICIAL (se ejecuta una sola vez) ==========
void setup() {
  // Inicializa la comunicación serial con la computadora a 115200 baudios
  Serial.begin(115200);
  // Configura el pin analógico del sensor de gas como entrada
  pinMode(sensorPinao, INPUT);
  // Configura el pin digital del sensor de gas como entrada
  pinMode(sensorpindo, INPUT);

  // Imprime en el monitor serial que el sistema se inició y muestra el umbral
  // configurado
  Serial.println("Sistema iniciado. Umbral: " + String(UMBRAL_GAS));
}

// ========== BUCLE PRINCIPAL (se ejecuta continuamente) ==========
void loop() {
  // Lee el valor analógico del sensor de gas (rango 0-4095 en ESP32)
  int valorGas = analogRead(sensorPinao);
  // Lee el estado digital del sensor de gas (0 o 1)
  int valorDigital = digitalRead(sensorpindo);

  // Imprime un separador en el monitor serial para organizar las lecturas
  Serial.println("\n--- Lectura ---");
  // Imprime el valor analógico leído del sensor
  Serial.println("Analogico: " + String(valorGas));
  // Imprime el valor digital leído del sensor
  Serial.println("Digital: " + String(valorDigital));

  // Verifica si el valor del gas supera el umbral establecido
  if (valorGas > UMBRAL_GAS) {
    // Imprime mensaje de alerta en el monitor serial
    Serial.println("¡ALERTA! Gas detectado");
    // Verifica si aún no se ha enviado la alerta
    if (!alertaEnviada) {
      // Llama a la función para enviar el SMS de alerta
      enviarSMS();
      // Marca que la alerta ya fue enviada para evitar envíos repetidos
      alertaEnviada = true;
    }
  } else {
    // Si el valor está por debajo del umbral, imprime "Normal"
    Serial.println("Normal");
    // Si ya se envió una alerta Y el valor bajó 200 unidades por debajo del
    // umbral
    if (alertaEnviada && valorGas < (UMBRAL_GAS - 200)) {
      // Resetea la bandera de alerta enviada (permite enviar nuevas alertas en
      // el futuro)
      alertaEnviada = false;
      // Imprime que el sistema fue reseteado
      Serial.println("Sistema reseteado");
    }
  }
  
    
  // Espera 15 segundos antes de realizar la siguiente lectura
  delay(15000);
}
