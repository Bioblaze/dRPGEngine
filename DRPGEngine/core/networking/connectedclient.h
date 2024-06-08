#pragma once
#include <enet/enet.h>
#include <string>

struct ConnectedClient {
    ENetPeer* peer;
    bool loggedIn;
    std::string username;
    uint32_t lastPacketTime;  // Timestamp of the last received packet
};
