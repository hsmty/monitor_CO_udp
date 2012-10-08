// Send a request for checkin status on our
// UDP server
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
 
int udpSend(IPAddress server, unsigned int port, char command[])
{
  int ps = 0;// Packet size
  udp.beginPacket(server, port);
  udp.write(command);
  udp.endPacket();
  
  ps = udp.parsePacket();
  if (ps) {
    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    // If packetBuffer and command are equal
    if (strcmp(packetBuffer, command) == 0) {
      return 1;
    }
  } else {
    Serial.println("No response from server");
  }

  return 0;
}
