#pragma once
#include <enet/enet.h>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "connectedclient.h"
#include "packets/loginrequestpacket.h"
#include "packets/loginpacket.h"

#include "../../defs.h"

#include <libenvpp/env.hpp>
#include <spdlog/spdlog.h>

class GameServer {
public:
    GameServer();
    ~GameServer();

    bool initServer(uint16_t port);
    void process();

private:
    void handlePacket(ENetEvent& event);
    void sendLoginRequest(ENetPeer* peer);
    void disconnectClient(ENetPeer* peer);

    ENetHost* server;
    std::unordered_map<ENetPeer*, ConnectedClient> clients;
    int maxConnections;
};
