#include "NodeSerial.h"

NodeSerial::NodeSerial(void) {
  vw_set_tx_pin(TRANSMIT_PIN);
  vw_set_rx_pin(RECIEVE_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(8000);
  vw_rx_start();
}
