#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <unordered_map>
#include <string>
#include "cell.h"
#include <cereal/types/vector.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

class WorldMap {
public:
    WorldMap() = default;
    WorldMap(int width, int height);

    void addCell(int x, int y, CellType cellType);
    bool isOccupied(int x, int y) const;
    CellType getCellType(int x, int y) const;
    void changeCellType(int x, int y, CellType newType);

    void saveMap(const std::string& filename) const;
    void saveMap(const std::string& filename, const std::string& directory) const;
    void loadMap(const std::string& filename);
    void loadMap(const std::string& filename, const std::string& directory);

    void saveJsonMap(const std::string& filename) const;
    void saveJsonMap(const std::string& filename, const std::string& directory) const;

private:
    int width = 0, height = 0;
    std::unordered_map<int, std::unordered_map<int, Cell>> grid;

    template<class Archive>
    void serialize(Archive& archive) {
        archive(width, height, grid);
    }
};

#endif // WORLDMAP_H
