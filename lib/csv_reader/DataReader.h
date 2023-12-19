


#include <string>
#include <unordered_map>

struct EntityAttributes {
    std::unordered_map<std::string, float> attributes;
};

class DataReader {
public:
    static std::unordered_map<std::string, EntityAttributes> readStatsFromCSV(const std::string& filename);
};
