#include "worldmap.h"
#include <fstream>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

WorldMap::WorldMap(int width, int height) : width(width), height(height) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            grid[x][y] = Cell(x, y, CellType::Empty); // Initialize all cells as empty
        }
    }
}

void WorldMap::addCell(int x, int y, CellType cellType) {
    grid[x][y] = Cell(x, y, cellType);
}

bool WorldMap::isOccupied(int x, int y) const {
    auto it = grid.find(x);
    if (it != grid.end() && it->second.find(y) != it->second.end()) {
        return it->second.at(y).cellType != CellType::Empty;
    }
    return false;
}

CellType WorldMap::getCellType(int x, int y) const {
    auto it = grid.find(x);
    if (it != grid.end() && it->second.find(y) != it->second.end()) {
        return it->second.at(y).cellType;
    }
    return CellType::Empty; // Indicate cell does not exist
}

void WorldMap::changeCellType(int x, int y, CellType newType) {
    if (grid.find(x) != grid.end() && grid[x].find(y) != grid[x].end()) {
        grid[x][y].cellType = newType;
    }
}

void WorldMap::saveMap(const std::string& filename) const {
    spdlog::info("Saving map to binary file: {}", filename);
    std::ofstream os(filename, std::ios::binary);
    cereal::BinaryOutputArchive archive(os);
    archive(width, height, grid);
    spdlog::info("Map successfully saved to binary file: {}", filename);
}

void WorldMap::saveMap(const std::string& filename, const std::string& directory) const {
    saveMap(directory + "/" + filename);
}

void WorldMap::loadMap(const std::string& filename) {
    spdlog::info("Loading map from binary file: {}", filename);
    std::ifstream is(filename, std::ios::binary);
    cereal::BinaryInputArchive archive(is);
    archive(width, height, grid);
    spdlog::info("Map successfully loaded from binary file: {}", filename);
}

void WorldMap::loadMap(const std::string& filename, const std::string& directory) {
    loadMap(directory + "/" + filename);
}

void WorldMap::saveJsonMap(const std::string& filename) const {
    spdlog::info("Saving map to JSON file: {}", filename);
    std::ofstream os(filename);
    cereal::JSONOutputArchive archive(os);
    archive(width, height, grid);
    spdlog::info("Map successfully saved to JSON file: {}", filename);
}

void WorldMap::saveJsonMap(const std::string& filename, const std::string& directory) const {
    saveJsonMap(directory + "/" + filename);
}
