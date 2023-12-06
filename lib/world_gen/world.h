#include <vector>
#include <unordered_map>
#include <random>

enum class TileType { Empty, Road, Building, Water, Forest, Mountain, Grass, Sand, Rock, Snow };

struct Tile {
    TileType type;
    // Additional properties like resources, etc.

};

class World {
public:
    World(int width, int height);
    void generateWorld();

private:
    std::vector<std::vector<Tile>> grid;
    int width, height;

    void generateRoads();
    void placeBuildings();
    void placeResources();
    void placeEnemies();
    void placePlayer();
    void placeItems();
    void placeDecorations();
    void placeWater();
    void placeForests();
    void placeMountains();

};

// Constructor implementation, etc.
