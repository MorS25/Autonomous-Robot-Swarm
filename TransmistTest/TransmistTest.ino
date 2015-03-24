#include <VirtualWire.h>

#define TRANSMIT_PIN         A0
#define RECEIVE_PIN          A1
#define TRANSMIT_ENABLE_PIN  3

byte input;

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
  if (Serial.available()) {
    input = Serial.read();
    Serial.write(input);
  }
}


/*
vw_send((uint8_t *)a, strlen(a));
vw_wait_tx(); // Wait until the whole message is gone
*/
