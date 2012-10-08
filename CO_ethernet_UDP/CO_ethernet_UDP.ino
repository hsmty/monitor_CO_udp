#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>     // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <string.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(66, 228, 50, 204);
IPAddress address(192, 168, 1, 201);
// UDP port on server
unsigned int port = 2323, packetSize, secs = 5000;
EthernetUDP udp; //Ethernet UDP interface

unsigned int device = 0; // Device id
int lastRead = -1; // Used to only update when the reading changes
int meterPin = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("running setup");
  Serial.println("Iniciando DHCP...");
  // Request DHCP for address or use default
  if (Ethernet.begin(mac)) {
    Serial.print("Obtenida IP: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("DHCP fallo, asignando statica: ");
    Ethernet.begin(mac, address);
    Serial.println(address);
  }
    
  udp.begin(port);  
}

/* en loop creamos una variable que sirve de registro del valor de lectura,
de esta forma solo hacemos posts cuando hay cambio en el valor*/

void loop()
{
  int packeSize = 0; 
  char* command = (char*) malloc(sizeof(char) * 12);
  int reading = analogRead(meterPin);

  if (reading != lastRead) {
    sprintf(command, "%03d:%03d:store", reading, device);
    udpSend(server, port, command);
    lastRead = reading;
  } else {
    Serial.println("Lectura sin cambio");
  }
  delay(1000);
}
