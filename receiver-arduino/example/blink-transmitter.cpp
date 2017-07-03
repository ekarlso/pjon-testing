#include <Arduino.h>
#include <SPI.h>

#define TS_RESPONSE_TIME_OUT 600000
#define TS_COLLISION_DELAY 3000

#define PJON_INCLUDE_TS true
//#define PJON_INCLUDE_ETHERNET false
#include <PJON.h>

// <Strategy name> bus(selected device id)
PJON<ThroughSerial> bus(2);


void setup() {
  pinMode(13, OUTPUT);
  bus.begin();
  Serial.begin(9600);

  bus.strategy.set_serial(&Serial); // Pass the Serial object you want to use for communication

  // Uncomment this if you use independant pins for rx / tx enable
  // bus.strategy.set_rx_RS485_pin(10);
  // bus.strategy.set_tx_RS485_pin(11);

  // Use this if you use the same rx / tx pin
  bus.strategy.set_tx_RS485_pin(10);

  bus.send_repeatedly(1, "B", 1, 1000000);
}

void loop() {
  bus.update();
};
