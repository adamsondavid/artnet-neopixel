#include "receiver.h"
#include "opcode.h"

void Artnet::Receiver::begin(uint8_t* mac, uint8_t* ip) {
    EthernetClass::begin(mac, ip);
    this->udp.begin(6454);
}

void Artnet::Receiver::begin(uint8_t *mac) {
    EthernetClass::begin(mac);
    this->udp.begin(6454);
}

void Artnet::Receiver::poll() {
    this->udp.parsePacket();

    uint8_t header[18];
    this->udp.read((uint8_t*) &header, sizeof(header));

    if (String(reinterpret_cast<char*>(header)) != "Art-Net") return;

    auto opCode = static_cast<OpCode>(header[8] | header[9] << 8);
    if (opCode == OpCode::DMX) {
        uint16_t universe = header[14] | header[15] << 8;
        uint16_t numPixels = (header[17] | header[16] << 8) / 3;

        for (uint16_t i = 0; i < numPixels; i++) {
            uint8_t data[3];
            this->udp.read(data, sizeof(data));
            this->dmxCallback(universe, Pixel{i, data[0], data[1], data[2]});
        }
    }

    this->udp.flush();
}

void Artnet::Receiver::setDmxCallback(void (*callback) (uint16_t, Pixel)) {
    this->dmxCallback = callback;
}
