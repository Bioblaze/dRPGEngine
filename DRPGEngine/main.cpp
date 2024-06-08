#include <iostream>
#include "core/map/worldmap.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

int main() {
    auto logger = spdlog::basic_logger_mt("worldmap_logger", "worldmap.log");
    spdlog::set_default_logger(logger);

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

    return 0;
}