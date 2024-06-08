#pragma once
#include <vector>
#include <cstdint>

class Packet {
public:
    enum PacketType {
        LOGIN_REQUEST = 1,
        LOGIN = 2
    };

    Packet(PacketType type);
    virtual ~Packet() = default;

    PacketType getType() const;
    int getId() const;

    virtual void serialize(std::vector<uint8_t>& buffer) const = 0;

protected:
    PacketType type;
    int id;
    static int next_id;
};
