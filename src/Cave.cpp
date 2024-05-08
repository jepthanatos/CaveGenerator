// Local includes
#include "Cave.h"
#include "Color.h"
#include "Utils.h"
#include "SimplexNoise.h"

// System includes
#include <math.h>

Cave::Cave(const int _cols, const int _rows, const int _rooms) : cols{_cols}, rows{_rows}
{
    const SimplexNoise simplex(0.1f, 0.5f, 1.5f, 0.5f);

    for (int j = 0; j < rows; ++j)
    {
        for (int i = 0; i < cols; ++i)
        {
            Tile tile(i, j);
            if (j > 0 and j < rows - 1 and i > 0 and i < cols - 1)
                tile.setIsRoom(ceil(simplex.fractal(8, i, j)));
            // tile.setIsRoom(Utils::pickRandom(0,1));
            grid.push_back(tile);
        }
    }

    int rooms = _rooms;
    while (rooms > 0)
    {
        if (createRandomRoom())
        {
            --rooms;
        }
    }

    SmoothMap(1);
}

void Cave::SmoothMap(const int times)
{
    for (int k = 0; k < times; ++k)
    {
        for (int j = 0; j < rows; ++j)
        {
            for (int i = 0; i < cols; ++i)
            {
                int neighbourWallTiles = GetSurroundingWallCount(i, j);

                if (neighbourWallTiles >= 4)
                    grid[index(i, j)].setIsRoom(true);
                else
                    grid[index(i, j)].setIsRoom(false);
            }
        }
    }
}

int Cave::GetSurroundingWallCount(int col, int row)
{
    int wallCount = 0;

    for (int j = row - 1; j <= row + 1; ++j)
    {
        for (int i = col - 1; i <= col + 1; ++i)
        {
            if ((index(i, j) != -1) and (col != i or row != j))
            {
                // if (grid[index(i,j)].getIsRoom()) {
                wallCount += grid[index(i, j)].getIsRoom();
                //}
            }
        }
    }

    return wallCount;
}

bool Cave::createRandomRoom(void)
{
    int sizeCols =
        Utils::pickRandom((cols) / Utils::pickRandom(5, 10), (cols) / Utils::pickRandom(2, 4));
    int sizeRows =
        Utils::pickRandom((rows) / Utils::pickRandom(5, 10), (rows) / Utils::pickRandom(2, 4));

    Tile roomTopLeft(Utils::pickRandom(0, cols), Utils::pickRandom(0, rows));

    int topLeftIndex = index(roomTopLeft.getCol(), roomTopLeft.getRow());
    int topRightIndex = index(roomTopLeft.getCol() + sizeCols, roomTopLeft.getRow());
    int bottomLeftIndex = index(roomTopLeft.getCol(), roomTopLeft.getRow() + sizeRows);
    int bottomRigthIndex = index(roomTopLeft.getCol() + sizeCols, roomTopLeft.getRow() + sizeRows);

    if ((topLeftIndex != -1) and (bottomRigthIndex != -1) and
        !grid[topLeftIndex].getIsRoom() and !grid[topRightIndex].getIsRoom() and
        !grid[bottomLeftIndex].getIsRoom() and !grid[bottomRigthIndex].getIsRoom())
    {
        for (int j = roomTopLeft.getCol(); j < roomTopLeft.getCol() + sizeCols; ++j)
        {
            for (int i = roomTopLeft.getRow(); i < roomTopLeft.getRow() + sizeRows; ++i)
            {
                if (grid[index(j, i)].getIsRoom())
                {
                    return false;
                }
            }
        }
    }
    else
    {
        return false;
    }

    for (int j = roomTopLeft.getCol(); j < roomTopLeft.getCol() + sizeCols; ++j)
    {
        for (int i = roomTopLeft.getRow(); i < roomTopLeft.getRow() + sizeRows; ++i)
        {
            grid[index(j, i)].setIsRoom(true);
        }
    }

    return true;
}

int Cave::index(int col, int row)
{
    if (col < 0 or row < 0 or col >= cols or row >= rows)
    {
        return -1;
    }
    return col + row * cols;
}

int Cave::checkNeighbours(Tile &tile)
{
    std::vector<int> vectorIndex = {
        index(tile.getCol(), tile.getRow() - 1), // Top
        index(tile.getCol() + 1, tile.getRow()), // Right
        index(tile.getCol(), tile.getRow() + 1), // Bottom
        index(tile.getCol() - 1, tile.getRow())  // Left
    };

    tile.clearNeighbours();

    for (unsigned int i = 0; i < vectorIndex.size(); ++i)
    {
        int index = vectorIndex[i];
        if (index > -1 and !grid[index].isVisited() and !grid[index].getIsRoom())
        {
            tile.addNeighbour(index);
        }
    }
    if (tile.hasNeighbours())
    {
        return tile.getRandomNeighbour();
    }
    else
    {
        return -1;
    }
}

void Cave::removeWalls(Tile &a, Tile &b)
{
    int x = a.getCol() - b.getCol();
    if (x == 1)
    {
        a.setWall(3, false);
        b.setWall(1, false);
    }
    else if (x == -1)
    {
        a.setWall(1, false);
        b.setWall(3, false);
    }

    int y = a.getRow() - b.getRow();
    if (y == 1)
    {
        a.setWall(0, false);
        b.setWall(2, false);
    }
    else if (y == -1)
    {
        a.setWall(2, false);
        b.setWall(0, false);
    }
}

void Cave::generateCave(void)
{
    int currentIndex = 0;

    do
    {
        int nextIndex = checkNeighbours(grid[currentIndex]);
        if (nextIndex > -1)
        {
            removeWalls(grid[currentIndex], grid[nextIndex]);
            visited.push(currentIndex);
            grid[nextIndex].setVisited(true);
            currentIndex = nextIndex;
        }
        else
        {
            currentIndex = visited.top();
            visited.pop();
        }
    } while (!visited.empty());
}

void Cave::generateCavePrinting(void)
{
    int currentIndex = 0;
    bool firstTime = true;
    bool completed = false;

    Img img(cols * 10, rows * 10, "Generating Cave");

    while (!img.isClosed())
    {
        // Print the grid at the start only one time.
        if (firstTime)
        {
            for (int j = 0; j < rows; ++j)
            {
                for (int i = 0; i < cols; ++i)
                {
                    const Tile tile = grid[index(i, j)];

                    // Print each tile yellow.
                    img.drawRectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10,
                                      (float *)&Color::yellow());

                    printWalls(i, j, tile, img);
                }
            }
            firstTime = false;
        }

        if (!completed)
        {
            do
            {
                int nextIndex = checkNeighbours(grid[currentIndex]);

                if (nextIndex > -1)
                {
                    removeWalls(grid[currentIndex], grid[nextIndex]);
                    visited.push(currentIndex);
                    grid[nextIndex].setVisited(true);
                    currentIndex = nextIndex;
                }
                else
                {
                    currentIndex = visited.top();
                    visited.pop();
                }

                for (int j = 0; j < rows; ++j)
                {
                    for (int i = 0; i < cols; ++i)
                    {
                        const Tile tile = grid[index(i, j)];

                        // Print the visited and actual tiles.
                        if (currentIndex == index(i, j))
                        {
                            img.drawRectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10,
                                              (float *)&Color::red());
                        }
                        else if (tile.isVisited())
                        {
                            img.drawRectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10,
                                              (float *)&Color::blue());
                        }

                        printWalls(i, j, tile, img);
                    }
                }

                img.display();

            } while (!visited.empty());
        }

        completed = visited.empty();

        img.display();
    }
}

void Cave::printCave(void)
{
    Img img(cols * 10, rows * 10, "Generated Cave");

    bool firstTime = true;

    while (!img.isClosed())
    {
        if (firstTime)
        {
            for (int j = 0; j < rows; ++j)
            {
                for (int i = 0; i < cols; ++i)
                {
                    const Tile tile = grid[index(i, j)];

                    // Print each tile.
                    if (tile.getIsRoom())
                    {
                        img.drawRectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10,
                                          (float *)&Color::yellow());
                    }
                    else
                    {
                        img.drawRectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10,
                                          (float *)&Color::black());
                    }

                    printWalls(i, j, tile, img);
                }
            }
            firstTime = false;
        }
        img.display();
    }
}

void Cave::printWalls(int i, int j, const Tile &tile, Img &img)
{
    // Top.
    if (tile.getWall(0))
    {
        img.drawLine(i * 10, j * 10, i * 10 + 10, j * 10,
                     (float *)&Color::black());
    }

    // Bottom.
    if (tile.getWall(2))
    {
        img.drawLine(i * 10, j * 10 + 10, i * 10 + 10, j * 10 + 10,
                     (float *)&Color::black());
    }

    // Right.
    if (tile.getWall(1))
    {
        img.drawLine(i * 10 + 10, j * 10, i * 10 + 10, j * 10 + 10,
                     (float *)&Color::black());
    }

    // Left.
    if (tile.getWall(3))
    {
        img.drawLine(i * 10, j * 10, i * 10, j * 10 + 10,
                     (float *)&Color::black());
    }
}
