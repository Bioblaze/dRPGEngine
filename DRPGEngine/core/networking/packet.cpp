#include "packet.h"

int Packet::next_id = 1;

Packet::Packet(PacketType type) : type(type), id(next_id++) {}

Packet::PacketType Packet::getType() const {
    return type;
}

int Packet::getId() const {
    return id;
}
