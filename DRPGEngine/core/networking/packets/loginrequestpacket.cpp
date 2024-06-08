#include "loginrequestpacket.h"

LoginRequestPacket::LoginRequestPacket() : Packet(LOGIN_REQUEST) {}

void LoginRequestPacket::serialize(std::vector<uint8_t>& buffer) const {
    buffer.push_back(static_cast<uint8_t>(type));
}
