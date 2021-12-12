#include <HW437.h>

char formato_serial[10] = {
    /*START BYTE*/ 0x7E,
    /*VERS. BYTE*/ 0xFF,

    /*  LENGTH  */ 0x06,
    /*  COMMAND */ 0x03,
    /*FB.COMMAND*/ 0x00,
    /* QUERY P1 */ 0x00,
    /* QUERY P2 */ 0x01,

    /* CHECKSUM */ 0xFF,
    /* CHECKSUM */ 0xE6,
    /* END BYTE */ 0xEF};

/*
 * Función para levantar el mensaje de inicialización del módulo HW437 y comprobar que la tarjeta SD
 * se encuentra conectada de manera correcta.
 */
void inicializacion_HW437(void)
{
    // Coloco el comando para el reseteo del dispositivo
    /*formato_serial[3] = PLAY;
    Serial.print("El comando es: ");
    Serial.println(formato_serial[3], HEX);*/

    int sendBytes = Serial2.write(formato_serial[0]);

    sendBytes = sendBytes + Serial2.write(formato_serial[1]);
    sendBytes = sendBytes + Serial2.write(formato_serial[2]);
    sendBytes = sendBytes + Serial2.write(formato_serial[3]);
    sendBytes = sendBytes + Serial2.write(formato_serial[4]);
    sendBytes = sendBytes + Serial2.write(formato_serial[5]);
    sendBytes = sendBytes + Serial2.write(formato_serial[6]);
    sendBytes = sendBytes + Serial2.write(formato_serial[7]);
    sendBytes = sendBytes + Serial2.write(formato_serial[8]);
    sendBytes = sendBytes + Serial2.write(formato_serial[9]);

    Serial.println(sendBytes);

    /*if (Serial2.available())
    {
        data = Serial2.read();
        Serial.println(data, HEX);
    }*/
}