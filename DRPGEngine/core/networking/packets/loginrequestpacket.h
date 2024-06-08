#pragma once
#include "../packet.h"

class LoginRequestPacket : public Packet {
public:
    LoginRequestPacket();
    void serialize(std::vector<uint8_t>& buffer) const override;
};
