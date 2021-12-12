#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DFPlayerMini_Fast.h>

#define BEGIN_DELAY 2000
#define LED         2

// Prototipos de las funciones desarrolladas.
void mainPage      (void);
void listarRedWiFi (void);
void cargarRedWiFi (void);

// Credenciales SSID y pass necesarias para definir al access point.
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Declaración de un objeto llamado servidor de la clase WebServer.
WebServer servidor (80);

DFPlayerMini_Fast audio;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  
  // Definición del modo de operación de los pines digitales que se utilizarán en el desarrollo
  pinMode(LED     , OUTPUT);
  
  Serial.print("ESP32 empleado en modo de access point");
  WiFi.mode(WIFI_AP_STA);       // Estoy empleando el microcontrolador ESP32 en modo AP y STA.
  WiFi.softAP(ssid, password);  // Se realiza el setup del AP con el ssid y pass antes definidos.

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Dirección IP del Access Point: ");
  Serial.println(IP);

  servidor.begin();
  // Utilización del método on asociado a objetos de la clase WebServer
  servidor.on("/", mainPage);

  audio.begin(Serial2, true);
  delay(BEGIN_DELAY);

  audio.volume(15);

  audio.play(1);
  // Serial.print("El tamaño es: ");
  // Serial.println(sizeof(data));
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial2.available() > 0)
  {
    data = Serial2.read();
    Serial.println(data, HEX);
  }
}