#include "gameserver.h"
#include <iostream>
#include <chrono>
#include <libenvpp/env.hpp>
#include <spdlog/spdlog.h>

GameServer::GameServer() : server(nullptr) {
    spdlog::info("Looking for Environment Variable DRPG_MAX_CONNECTIONS");
    // Read the environment variable or use the default value
    auto pre = env::prefix("DRPG");
    const auto max_connections_id = pre.register_variable<unsigned int>("MAX_CONNECTIONS");

    const auto parsed_and_validated_pre = pre.parse_and_validate();
    if (parsed_and_validated_pre.ok()) {
        const auto max_connections = parsed_and_validated_pre.get_or(max_connections_id, MAX_CONNECTED_CLIENTS);
        maxConnections = static_cast<int>(max_connections);
        spdlog::info("DRPG_MAX_CONNECTIONS found with value ({})", maxConnections);
    }
    else {
        spdlog::info("DRPG_MAX_CONNECTIONS was not found, loading with default ({})", MAX_CONNECTED_CLIENTS);
        // Use default value in case of error
        maxConnections = MAX_CONNECTED_CLIENTS;
    }

}

GameServer::~GameServer() {
    if (server != nullptr) {
        enet_host_destroy(server);
    }
    enet_deinitialize();
}

bool GameServer::initServer(uint16_t port) {
    if (enet_initialize() != 0) {
        spdlog::error("An error occurred while initializing ENet.");
        return false;
    }

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;

    server = enet_host_create(&address, maxConnections, 2, 0, 0);
    if (server == nullptr) {
        spdlog::error("An error occurred while trying to create an ENet server host.");
        return false;
    }

    return true;
}

void GameServer::process() {
    const uint32_t LOGIN_TIMEOUT_MS = 5 * 60 * 1000;  // 5 minutes in milliseconds
    uint32_t startTime = enet_time_get();

    ENetEvent event;
    while (enet_host_service(server, &event, 1000) >= 0) {
        uint32_t currentTime = enet_time_get();
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            spdlog::info("A new client connected from {}:{}", event.peer->address.host, event.peer->address.port);
            sendLoginRequest(event.peer);
            clients[event.peer] = { event.peer, false, "", currentTime };
            break;

        case ENET_EVENT_TYPE_RECEIVE:
            handlePacket(event);
            enet_packet_destroy(event.packet);
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            spdlog::info("Client disconnected.");
            clients.erase(event.peer);
            break;

        default:
            break;
        }

        // Check for login timeout
        for (auto it = clients.begin(); it != clients.end();) {
            if (!it->second.loggedIn && (currentTime - it->second.lastPacketTime > LOGIN_TIMEOUT_MS)) {
                spdlog::info("Client login timed out.");
                disconnectClient(it->second.peer);
                it = clients.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

void GameServer::handlePacket(ENetEvent& event) {
    std::vector<uint8_t> buffer(event.packet->data, event.packet->data + event.packet->dataLength);
    Packet::PacketType type = static_cast<Packet::PacketType>(buffer[0]);

    switch (type) {
    case Packet::LOGIN:
        if (!clients[event.peer].loggedIn) {
            std::string username(buffer.begin() + 1, buffer.end());
            clients[event.peer].loggedIn = true;
            clients[event.peer].username = username;
            spdlog::info("Client logged in as {}.", username);
        }
        break;

    default:
        spdlog::warn("Unknown packet type received.");
        break;
    }

    clients[event.peer].lastPacketTime = enet_time_get();
}

void GameServer::sendLoginRequest(ENetPeer* peer) {
    LoginRequestPacket packet;
    std::vector<uint8_t> buffer;
    packet.serialize(buffer);

    ENetPacket* enetPacket = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, enetPacket);
}

void GameServer::disconnectClient(ENetPeer* peer) {
    enet_peer_disconnect(peer, 0);
}