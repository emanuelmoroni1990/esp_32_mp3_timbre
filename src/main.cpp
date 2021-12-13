/*
 * 1. https://github.com/PowerBroker2/DFPlayerMini_Fast
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DFPlayerMini_Fast.h>
#include <mainPage.h>

#define BEGIN_DELAY 2000
#define LED         2
#define TIMEOUT     30000

// Prototipos de las funciones desarrolladas.
void mainPage      (void);
void playSong      (void);
void stopSong      (void);
void volumeUp      (void);
void volumeDown    (void);
void selectSong    (void);

// Credenciales SSID y pass necesarias para definir al access point.
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Declaración de un objeto llamado servidor de la clase WebServer.
WebServer servidor (80);
// Declaración de un array de objetos llamado listado_redes de la clase String.
String listado_redes [50];

DFPlayerMini_Fast audio;
int cantidadTracks;
int contadorTracks = 1;
// Preseteo el valor inicial para evitar la condición inicial de que no exista una canción seleccionada. emoroni.
int seleccionTrack = -1;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  
  // Definición del modo de operación de los pines digitales que se utilizarán en el desarrollo
  pinMode(LED     , OUTPUT);
  
  Serial.println("ESP32 empleado en modo STA y access point");
  WiFi.mode(WIFI_AP_STA);       // Estoy empleando el microcontrolador ESP32 en modo AP y STA.
  WiFi.softAP(ssid, password);  // Se realiza el setup del AP con el ssid y pass antes definidos.

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Dirección IP del Access Point: ");
  Serial.println(IP);

  servidor.begin();
  // Utilización del método on asociado a objetos de la clase WebServer
  servidor.on("/", mainPage);
  servidor.on("/reproducirCancion" , playSong);
  servidor.on("/detenerCancion"    , stopSong);
  servidor.on("/subirVolumen"      , volumeUp);
  servidor.on("/bajarVolumen"      , volumeDown);
  servidor.on("/seleccionarCancion", selectSong);

  // Es necesario que este timeout sea grande. Si no es así, no llega a correr todas las querys. emoroni.
  // En el segundo de los parámetros puedo colocar false para no ver todo el handshake de la comuniacion. emoroni.
  audio.begin(Serial2, false, TIMEOUT);
  delay(BEGIN_DELAY);

  // Seteo un volumen inicial de 15. emoroni.
  audio.volume(15);

  cantidadTracks = audio.numSdTracks();
  if(cantidadTracks != -1){
    Serial.print("La cantidad de tracks es: ");
    Serial.println(cantidadTracks);
  }
  else{
    Serial.print("El error es: ");
    audio.printError();
  }

  // Serial.print("El tamaño es: ");
  // Serial.println(sizeof(data));
}

void loop()
{
  // put your main code here, to run repeatedly:
  servidor.handleClient();
}

void mainPage (void){
  // El servidor envía al cliente el código de estado, el tipo y el contenido en si mismo.
  servidor.send(200, "text.html", webcode(listado_redes, 0));
  //playSong();
}

void playSong (void){

  if(contadorTracks <= cantidadTracks)
  { 
    Serial.print("La cancion que se está reproduciendo es: ");
    Serial.println(contadorTracks);

    audio.play(contadorTracks);
    contadorTracks++;
  }
  else
  {
    contadorTracks = 1;

    Serial.print("La cancion que se está reproduciendo es: ");
    Serial.println(contadorTracks);

    audio.play(contadorTracks);
    contadorTracks++;
  }

  servidor.send(200, "text.html", webcode(listado_redes, 0));
}

void stopSong (void)
{
  audio.stop();

  servidor.send(200, "text.html", webcode(listado_redes, 0));
}

void volumeDown (void)
{
  audio.decVolume();
  Serial.print("Volumen: ");
  Serial.println(audio.currentVolume());

  servidor.send(200, "text.html", webcode(listado_redes, 0));
}

void volumeUp (void)
{
  audio.incVolume();  
  Serial.print("Volumen: ");
  Serial.println(audio.currentVolume());

  servidor.send(200, "text.html", webcode(listado_redes, 0));
}

void selectSong (void)
{
  seleccionTrack = contadorTracks;
  Serial.print("Timbre seleccionado: ");
  Serial.println(seleccionTrack);

  servidor.send(200, "text.html", mensajeCarga());
}