#include "DataReader.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

std::unordered_map<std::string, EntityAttributes> DataReader::readStatsFromCSV(const std::string& filename) {
    std::unordered_map<std::string, EntityAttributes> statsMap;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::getline(file, line); // Read the header line

    std::stringstream headerSS(line);
    std::string columnName;
    std::vector<std::string> columnNames;
    while (std::getline(headerSS, columnName, ',')) {
        columnNames.push_back(columnName);
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        EntityAttributes attributes;
        std::string entityName;

        for (size_t i = 0; std::getline(ss, cell, ',') && i < columnNames.size(); ++i) {
            if (i == 0) {
                entityName = cell;
            } else {
                attributes.attributes[columnNames[i]] = std::stof(cell);
            }
        }

        statsMap[entityName] = attributes;
    }

    return statsMap;
}




