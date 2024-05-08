#ifndef CAVE_H_
#define CAVE_H_

// System includes
#include <vector>
#include <stack>

// Local includes
#include "Tile.h"
#include "Img.h"

class Cave
{
public:
    Cave(const int _cols, const int _rows, const int _rooms);
    ~Cave(void) {}

    void generateCave(void);
    void generateCavePrinting(void);
    void printCave(void);

    std::vector<Tile> getGrid(void)
    {
        return grid;
    }

private:
    void SmoothMap(const int times);
    int GetSurroundingWallCount(int gridX, int gridY);
    bool createRandomRoom(void);
    int index(int i, int j);
    int checkNeighbours(Tile &c);
    void removeWalls(Tile &a, Tile &b);
    void printWalls(int i, int j, const Tile &tile, Img &img);

    int cols, rows;
    std::vector<Tile> grid;
    std::stack<int> visited;
};

#endif /* CAVE_H_ */
