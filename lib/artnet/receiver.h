#pragma once

#include <Ethernet.h>
#include "pixel.h"

namespace Artnet {
    class Receiver {
    private:
        EthernetUDP udp;
        void (*dmxCallback) (uint16_t, Pixel);
    public:
        void begin(uint8_t* mac, uint8_t* ip);
        void begin(uint8_t* mac);
        void poll();
        void setDmxCallback(void (*callback) (uint16_t universe, Pixel pixel));
    };
}
