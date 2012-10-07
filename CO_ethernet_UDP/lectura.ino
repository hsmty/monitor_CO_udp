int lecturaCO() 
{
  int lecturaRaw=analogRead(analogPin);
  int voltajeRaw=lecturaRaw*5/1024;
  return lecturaRaw; //
}

//armando el string para enviar
void hacerString(int  lectura, int device, char command[]){
  Serial.println(lectura);
  char strDato[7]="";
  char strBuffera[7]="";
  char strBufferb[7]="";
  char puntos[]=":"; 
  Serial.println(strDato);
  itoa(device,strBuffera,7);
  strcat(strDato, strBuffera);
  Serial.println(strDato);
  strcat(strDato, puntos);
  Serial.println(strDato);
  itoa(lectura,strBufferb,7);
  strcat(strDato, strBufferb);  
  Serial.println(strDato);
  strncpy(command, strDato,7);
  Serial.println(command);
}
  
