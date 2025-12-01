 // Define the RX and TX pins for Serial 2
#define RXD2 16
#define TXD2 17

#define GPS_BAUD 9600

// Create an instance of the HardwareSerial class for Serial 2
HardwareSerial simSerial(2);
String phonenumber;
 
void setup(){
  
  // Serial Monitor
  Serial.begin(115200);
  
  // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
  simSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial 2 started at 9600 baud rate");

  delay(10000);
  
  simSerial.println("AT+CMGF=1");
  delay(50);
 
  phonenumber = String("AT+CMGS=");
  phonenumber+= String ('"');
  phonenumber+=String("2302488481");
  phonenumber+= String ('"');

  simSerial.println(phonenumber);
  delay(50);
  simSerial.println("alerta... detecion de gas nocivo");
  delay(50);
  simSerial.write(26);
    
}

void loop(){
  
 if (Serial.available()) {      // If anything comes in Serial (USB),
    simSerial.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
  }

  if (simSerial.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(simSerial.read());   // read it and send it out Serial (USB)
  }


}
