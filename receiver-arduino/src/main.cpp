#define PJON_INCLUDE_ASYNC_ACK true
#define PJON_INCLUDE_TS true
#define TS_RESPONSE_TIMEOUT 0


#include <PJON.h>

// <Strategy name> bus(selected device id)
PJON<ThroughSerial> bus(2);

void receiver_function(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  /* Make use of the payload before sending something, the buffer where payload points to is
     overwritten when a new message is dispatched */
     if (payload[0] == 'B') {
     digitalWrite(13, HIGH);
     delay(20);
     digitalWrite(13, LOW);
   }

};

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); // Initialize LED 13 to be off

  Serial.begin(9600);
  bus.strategy.set_serial(&Serial);

  bus.begin();

  bus.set_receiver(receiver_function);
  //bus.send_repeatedly(45, "B", 1, 1000000);
};

void loop() {
  bus.update();
  bus.receive();
};
