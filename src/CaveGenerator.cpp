// Local includes
#include "Cave.h"
#include "Utils.h"

int main()
{

    // Initialize random seed.
    Utils::initRamdom();

    // Columns and rows.
    const int COLUMNS = 150;
    const int ROWS = 60;
    const int ROOMS = 0;

    // Create an empty cave.
    Cave cave(COLUMNS, ROWS, ROOMS);

    // Print the cave while generating it.
    // cave.generateCavePrinting();

    // Generate the cave, then print it.
    // cave.Generatecave();

    cave.printCave();
    return 0;
}
