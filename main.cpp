
// For printf used below
#include <stdio.h>
// PJON library
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
// RPI serial interface
#include <wiringPi.h>
#include <wiringSerial.h>

#ifndef RPI
  #define RPI true
#endif

#define PJON_INCLUDE_ASYNC_ACK true
#define PJON_INCLUDE_TS true
#define TS_RESPONSE_TIMEOUT 0

#include "PJON/PJON.h"

int main() {
  printf("PJON instantiation... \n");
  PJON<ThroughSerial> bus(1);


  printf("Opening serial... \n");
  int s = serialOpen("/dev/ttyAMA0", 9600);
  if(s < 0) printf("Serial open fail!");
  if(wiringPiSetup() == -1) printf("WiringPi setup fail");
  printf("Setting serial... \n");
  bus.strategy.set_serial(s);

  //bus.strategy.set_enable_RS485_pin(0);
  //bus.set_synchronous_acknowledge(true);
  //bus.set_asynchronous_acknowledge(false);

  printf("Opening bus... \n");
  bus.begin();

  printf("Attempting to send a packet... \n");
  int packet = bus.send_repeatedly(2, "B", 1, 2000000);
  //int packet = bus.send(2, "B", 1);

  for(int i = 0; i < bus.packets[packet].length; i++) {
  printf("%i", (char)bus.packets[packet].content[i]);
  printf(" - ");
}
  /*printf("Attempting to roll bus... \n");
  bus.update();
  printf("Attempting to receive from bus... \n");
  bus.receive();
  printf("Success! \n");
*/
  while(true) {
    bus.update();
    bus.receive();
  }

  return 0;

};
