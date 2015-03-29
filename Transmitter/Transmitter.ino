// [4043.5715N 07400.2783W]

// [ 4 0 4 3 . 5 7 1 5 N   0 7 4 0 0 . 2 7 8 3 W ]
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3

#include <VirtualWire.h>

#define TRANSMIT_PIN         A0
#define RECEIVE_PIN          A1
#define TRANSMIT_ENABLE_PIN  3

bool startOfData = false;
bool endOfData = false;

char input;
char dataToSend[23];
int index = 0;

void setup(void)
{
  Serial.begin(115200);

  vw_set_tx_pin(TRANSMIT_PIN);
  vw_set_rx_pin(RECEIVE_PIN);
  vw_set_ptt_pin(TRANSMIT_ENABLE_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(4000);

  Serial.println("Format: [DDMM.MMMM(N/S) DDDMM.MMMM(E/W)]\n");

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
      //Write function to check for correct format
      //This is a very basic test
      if (dataToSend[11] == ' ' && dataToSend[23] == ']') {
        vw_send((uint8_t *)dataToSend, strlen(dataToSend));
        vw_wait_tx();
        vw_send((uint8_t *)dataToSend, strlen(dataToSend));
        vw_wait_tx();
        Serial.println(dataToSend);
        Serial.println();
      }
      else
        Serial.println("INCORRECT FORMAT...\n");

      //Reset Data Array
      for (int i = 0; i <= 20; i++)
        dataToSend[i] = ' ';
    }
  } //End of outer if-statement
}
