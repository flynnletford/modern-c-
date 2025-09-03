// csv-corrector.h
#ifndef CSV_CORRECTOR_H
#define CSV_CORRECTOR_H

#include <sstream>
#include <fstream>

#include "csv-writer.h"

template<typename T>
class CSVCorrector {

    private:
        static bool isDelimiter(const char& c) {
            return c == ' ' || c == ',';
        }

        static T convertFromString(const std::string& input) {
            // Convert val into T.
            std::istringstream fs(input);
            T value;
            fs >> value;

            return value;
        }

        void ingestRawValue(CSVWriter<T>& writer, std::string &val, int col) {

            if (val.empty()) return;

            const T valueParsed = convertFromString(val);
            writer.ingestValue(valueParsed, col);
            val.clear();
        }

    public:
        // correct sends parsed values to the csv writer, which in turn overwrites any zero values into the specified newFilePath.
        void correct(const std::string& filePath, const std::string& newFilePath) {
            
            std::ofstream outFile(newFilePath);
            CSVWriter<T> writer{};

            std::ifstream file(filePath);
            if (!file.is_open()) {
                throw std::runtime_error("failed to open file: " + filePath);
            }

            std::string line;
            while (std::getline(file, line)) {

                std::string val;

                int col = 0;
                for (const auto& c : line) {
                    if (isDelimiter(c)) {

                        if (val.empty()) {
                            continue;
                        }
                        ingestRawValue(writer, val, col);

                        col++;
                        continue;
                    }
                    
                    // Otherwise, keep appending to our string to build the number.
                    val += c;
                }

                // Ingest the last value in the line.
                ingestRawValue(writer, val, col);

                // We've finished ingesting this row - let the writer know.
                writer.writeRowToFile(outFile);
            }
        }
};

#endif // CSV_CORRECTOR_H
