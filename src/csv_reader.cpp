#include "csv_reader.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Product> readCSV(const std::string& filename) {
    std::vector<Product> data;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        
        Product product;

        product.id = std::stoi(row[0]);
        product.name = row[1];
        product.barcode = std::stoi(row[2]);
        product.price = std::stoi(row[3]);

        data.push_back(product);
    }

    file.close();
    return data;
}