#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>

struct Product {
    int id;
    std::string name;      
    int barcode;  
    int price;          
};

struct Cell {
    std::string name; 
    int count;     
    int price;          
};

std::vector<Product> readCSV(const std::string& filename);

#endif