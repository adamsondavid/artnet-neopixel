#include <Arduino.h>
#include <Artnet.h>
#include <Adafruit_NeoPixel.h>

// Config --------------------------------------------------------------------------------------------------------------
int16_t  LED_COUNT      = 216;
int16_t  LED_PIN        = 6;
uint8_t  ETHERNET_IP[]  = {169, 254, 254, 12};
uint8_t  ETHERNET_MAC[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};
uint16_t START_UNIVERSE = 0;
// ---------------------------------------------------------------------------------------------------------------------

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Artnet::Receiver artnetReceiver;

void onDmx(uint16_t universe, Artnet::Pixel pixel) {
    uint16_t index = pixel.index + (universe - START_UNIVERSE) * 512;
    leds.setPixelColor(index, pixel.red, pixel.green, pixel.blue);
}

void setup() {
    leds.begin();
    artnetReceiver.begin(ETHERNET_MAC, ETHERNET_IP);
    artnetReceiver.setDmxCallback(onDmx);
}

void loop() {
    artnetReceiver.poll();
    leds.show();
}
