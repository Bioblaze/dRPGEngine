#include <iostream>
#include <cstdio>
#include "core/map/worldmap.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>
#ifdef __unix__ 

#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/sinks/systemd_sink.h>

#endif
#include <spdlog/fmt/ostr.h>
#include <spdlog/cfg/env.h>
#include "core/networking/gameserver.h"

int main() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("drpgserver.log", true);

#ifdef __unix__ 

    auto syslog_sink = std::make_shared<spdlog::sinks::syslog_sink_mt>("syslog", "drpgserver_logger");
    auto systemd_sink = std::make_shared<spdlog::sinks::systemd_sink_st>();
    std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink, syslog_sink, systemd_sink };

#elif defined(_WIN32) || defined(WIN32)

    std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };

#endif

    auto logger = std::make_shared<spdlog::async_logger>("drpgserver_logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    spdlog::register_logger(logger);
    //spdlog::set_default_logger(logger);

    // TEST MAP SYSTEM
    WorldMap map(10, 10);

    map.addCell(2, 3, CellType::Ground); // Add ground at (2, 3)
    map.addCell(5, 5, CellType::Wall); // Add wall at (5, 5)

    std::cout << "Cell (2, 3) type: " << static_cast<int>(map.getCellType(2, 3)) << std::endl;
    std::cout << "Cell (5, 5) type: " << static_cast<int>(map.getCellType(5, 5)) << std::endl;

    map.changeCellType(2, 3, CellType::Empty); // Change (2, 3) to empty
    std::cout << "Cell (2, 3) type after change: " << static_cast<int>(map.getCellType(2, 3)) << std::endl;

    map.saveMap("drpg.map");
    map.loadMap("drpg.map");

    map.saveJsonMap("drpg.json");

    // TEST SERVER START
    spdlog::info("Initiating Server...");

    GameServer server;

    if (!server.initServer(53945)) {
        spdlog::error("Failed to initialize server.");
        return EXIT_FAILURE;
    }

    spdlog::info("Server started. Waiting for connections...");
    server.process();

    return 0;
}