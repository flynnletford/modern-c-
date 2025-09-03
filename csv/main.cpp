#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "csv-corrector.h"
#include "csv-writer.h"

int main() {

    try {

        const std::string inputFile = "testFiles/test.csv";
        const std::string outputFile = "testFiles/corrected.csv";

        std::cout << "correcting csv file: " << inputFile << std::endl;

        CSVCorrector<int> corrector{};
        corrector.correct(inputFile, outputFile);

        std::cout << "wrote corrected csv file to: " << outputFile << std::endl;

    } catch (const std::runtime_error& e) {
        std::cout << "runtime error caught: " << e.what() << std::endl;
    }
}