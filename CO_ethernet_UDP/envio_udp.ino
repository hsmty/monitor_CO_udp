  // Send a request for checkin status on our
  // UDP server
  
void envioUDP(IPAddress server, unsigned int port, char command[] )
  {
    Serial.println ("Sending request...");
    Serial.println (server, port);
    Udp.beginPacket(server, port);
    Udp.write(command);
    Udp.endPacket();
  } 
 
void recepcion(char recibido[],char command[]) 
  {
  int packetSize = Udp.parsePacket();
     
  if (packetSize){
    IPAddress remote = Udp.remoteIP();
    // Read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Recived: ");
    Serial.println(packetBuffer);
    recibido = packetBuffer; 
    if (recibido=command){
     Serial.println("Envio OK");
    }else{
     Serial.println("Envio Difiere");
    } 
  }
  else{
    Serial.println("no hubo respuesta");
  }
    
  }
