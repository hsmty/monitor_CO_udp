#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>     // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORT 2323
#define WAIT 1000
#define METER 0
#define DEVICE 0
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(66, 228, 50, 204);
IPAddress address(192, 168, 1, 201);

EthernetUDP udp; //Ethernet UDP interface

int lastRead = -1; // Used to only update when the reading changes

void setup() 
{
  Serial.begin(9600);
  Serial.println("Requestin IP address...");
  // Request DHCP for address or use default
  if (Ethernet.begin(mac)) {
    Serial.print("Got IP address: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("DHCP failed, assigning static address: ");
    Ethernet.begin(mac, address);
    Serial.println(address);
  }
    
  udp.begin(PORT);  
}

void loop()
{
  int packeSize = 0; 
  char* command = (char*) malloc(sizeof(char) * 12);
  int reading = analogRead(METER);

  if (reading != lastRead) {
    sprintf(command, "%03d:%03d:store", reading, DEVICE);
    udpSend(server, PORT, command);
    lastRead = reading;
  } else {
    Serial.println("Reading has not changed");
  }
  delay(WAIT);
}
