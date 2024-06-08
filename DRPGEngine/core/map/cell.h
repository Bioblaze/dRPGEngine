#ifndef CELL_H
#define CELL_H

#include <cereal/types/unordered_map.hpp>
#include <cereal/archives/binary.hpp>

enum class CellType {
    Empty = 0,
    Ground = 1,
    Wall = 2
};

struct Cell {
    int x;
    int y;
    CellType cellType;

    Cell() : x(0), y(0), cellType(CellType::Empty) {}
    Cell(int x, int y, CellType type) : x(x), y(y), cellType(type) {}

    template<class Archive>
    void serialize(Archive& archive) {
        archive(
            cereal::make_nvp("x", x),
            cereal::make_nvp("y", y),
            cereal::make_nvp("cell_type", cellType)
        );
    }
};

#endif // CELL_H
