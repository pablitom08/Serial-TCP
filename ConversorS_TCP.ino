#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

#define RXp2 16
#define TXp2 17
String inputString = "";         // Una cadena para almacenar los datos entrantes
bool stringComplete = false;     // Indica si la cadena está completa
String cadena ="";
float dato = 0.00;
float dato1 = 0.00;

WiFiServer server(5001);  // Puerto del servidor
WiFiClient client;

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  inputString.reserve(200);

  // Conectar a la red WiFi
  WiFi.begin("Tecnipeso", "wf12tecni");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }

  Serial.println("Conexión WiFi establecida");
  Serial.println(WiFi.localIP());

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  // Esperar la conexión de un cliente si no hay uno conectado actualmente
  if (!client || !client.connected()) {
    client = server.available();
    if (client) {
      Serial.println("Cliente conectado");
    }
  }

  // Leer los datos del puerto serial
  if (Serial2.available()) {
    char inChar = (char)Serial2.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }

  // Enviar los datos al cliente si la cadena está completa
  if (stringComplete && client && client.connected()) {
    cadena = inputString.substring(0,14);
    Serial.println("peso: " + cadena);
    //client.print(cadena+'\n');
    client.print(cadena);
    inputString = "";
    stringComplete = false;
  }
}

