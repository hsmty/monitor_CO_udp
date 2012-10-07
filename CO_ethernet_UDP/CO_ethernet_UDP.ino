#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>     // UDP library from: bjoern@cs.stanford.edu 12/30/2008

int analogPin = 0;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(66, 228, 50, 204);
IPAddress address(192, 168, 1, 201);
unsigned int port = 2323, packetSize, secs = 5000; // UDP port on server, removi la variable chackin

unsigned int device = 0; // variable para diferenciar los distintos dispositivos

int regLectura; // registro para monitoreo del valor de la lectura


/* Buffer to hold incoming packet, utilizo recibido y command globales para poder obtener
 un char array como resultado de las funciones recepcion() y hacerString()*/
char packetBuffer[UDP_TX_PACKET_MAX_SIZE],recibido[7],command[7];


// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Iniciando DHCOP...");
  // Request DHCP for address or use default
  if (Ethernet.begin(mac)) {
    Serial.print("Obtenida IP: ");
    Serial.println(Ethernet.localIP());
  } 
  else {
    Serial.print("DHCP fallo, asignando statica: ");
    Ethernet.begin(mac, address);
    delay(500);
    Serial.println(address);
  }
    
  Udp.begin(port);
 
  
}

/* en loop creamos una variable que sirve de registro del valor de lectura,
de esta forma solo hacemos posts cuando hay cambio en el valor*/

void loop()
{
  
  int lectura = lecturaCO();
  if (lectura != regLectura){
    Serial.println("Cambio en la lectura");
    Serial.print("Lectura ahora es: ");
    Serial.println(lectura);
    hacerString(lectura, device, command);
    Serial.println("Creando String");
    Serial.print("String a enviar:");
    Serial.println(command);
    delay(1000);
    Serial.println("Actualizando valores a servidor");
    envioUDP(server,port,command);
    recepcion(recibido,command);     
  }
  else{
    Serial.print("Lectura sin cambio");
    delay(1000);
}
}
