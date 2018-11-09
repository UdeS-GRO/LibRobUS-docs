/*
  ID-12.ino
*/

#include <LibRobus.h> // Essentielle pour utiliser RobUS

char crecu, i, incoming=0;
char id_tag[20];

void setup()
{
  BoardInit();
  Serial2.begin(9600);
  Serial.println("Test du ID-12 sur UART2 (RX2/Digital 17)");
}

void loop()
{
  if( Serial2.available() )
  {
    crecu=Serial2.read();     // lit le ID-12
    switch( crecu )
    {
      case 0x02:
        // START OF TRANSMIT
        AX_BuzzerON();
        i=0;
        incoming=1;
        break;
      case 0x03:
        // END OF TRANSMIT
        AX_BuzzerOFF();
        incoming=0;
        // Affiche le code recu sans valider le checksum
        for( i=0 ; i<10 ; i++ )
          Serial.print(id_tag[i]);
        Serial.println("");
        break;
      default:
        if( incoming )
          id_tag[i++] = crecu;
        break;
    }
  }
}

/* fin du fichier */
