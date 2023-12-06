#include <fstream>
#include <vector>
#include <sstream>
#include "DataReader.h"

std::unordered_map<std::string, EntityStats> DataReader::readStatsFromCSV(const std::string& filename) {
    std::unordered_map<std::string, EntityStats> statsMap;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::getline(file, line); // Read the header line and ignore it

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> rowData;

        while (std::getline(ss, cell, ',')) {
            rowData.push_back(cell);
        }

        if (rowData.size() == 4) {
            EntityStats stat;
            stat.name = rowData[0];
            stat.health = std::stof(rowData[1]);
            stat.damage = std::stof(rowData[2]);
            stat.speed = std::stof(rowData[3]);
            statsMap[stat.name] = stat;
        }
    }

    return statsMap;
}