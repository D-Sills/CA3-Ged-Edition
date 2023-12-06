


#include <string>
#include <unordered_map>

struct EntityStats {
    std::string name;
    float health;
    float damage;
    float speed;
};

class DataReader {
public:
    static std::unordered_map<std::string, EntityStats> readStatsFromCSV(const std::string& filename);

};

class GameData {
public:
    static void loadEntityStats(const std::string& filename);

    static EntityStats getEntityStats(const std::string& name);

private:
    static std::unordered_map<std::string, EntityStats> entityStats;
};
