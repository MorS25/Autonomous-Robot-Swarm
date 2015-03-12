#include <VirtualWire.h>

const int led_pin = A1;
const int transmit_pin = A0;
const int receive_pin = 2;
const int transmit_en_pin = 3;

void setup(void)
{
  Serial.begin(115200);
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(8000);	 // Bits per sec
  
  pinMode(led_pin, OUTPUT);
}

void loop(void)
{  
  while (Serial.available() < 1)
    ;
  
  char a[] = {Serial.read()};
  Serial.println(a);
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)a, strlen(a));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
}

