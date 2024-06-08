#pragma once
#include "../packet.h"
#include <string>

class LoginPacket : public Packet {
public:
    LoginPacket(const std::string& username);
    void serialize(std::vector<uint8_t>& buffer) const override;
    const std::string& getUsername() const;

private:
    std::string username;
};
