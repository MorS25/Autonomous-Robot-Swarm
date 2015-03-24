#include <VirtualWire.h>

#define TRANSMIT_PIN         A0
#define RECEIVE_PIN          A1
#define TRANSMIT_ENABLE_PIN  3

bool startOfData = false;
bool endOfData = false;

char input;
char dataToSend[20];
int index = 0;

void setup(void)
{
  Serial.begin(9600);

  vw_set_tx_pin(TRANSMIT_PIN);
  vw_set_rx_pin(RECEIVE_PIN);
  vw_set_ptt_pin(TRANSMIT_ENABLE_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(4000);
}

void loop(void)
{
  while (Serial.available()) {
    input = Serial.read();

    if (input == '[') {
      dataToSend[index++] = input;
      startOfData = true;
    }
    if (input == ']' && startOfData) {
      dataToSend[index++] = input;
      endOfData = true;
    }
    if (startOfData && !endOfData && input != '[' && input != ']' ) {
      dataToSend[index++] = input;
    }

    //Send Data Over
    if (startOfData && endOfData) {
      //Reset
      startOfData = false;
      endOfData = false;
      index = 0;

      //Send Data
      vw_send((uint8_t *)dataToSend, strlen(dataToSend));
      vw_wait_tx();
      
      //Printing for debugging
      Serial.println(dataToSend);

      //Reset Data Array
      for (int i = 0; i < strlen(dataToSend); dataToSend[i++] = 0)
        ;
    }
  } //End of outer if-statement
}
