#include "loginpacket.h"

LoginPacket::LoginPacket(const std::string& username) : Packet(LOGIN), username(username) {}

void LoginPacket::serialize(std::vector<uint8_t>& buffer) const {
    buffer.push_back(static_cast<uint8_t>(type));
    buffer.insert(buffer.end(), username.begin(), username.end());
}

const std::string& LoginPacket::getUsername() const {
    return username;
}
