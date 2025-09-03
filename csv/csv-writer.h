// csv-writer.h
#ifndef CSV_WRITER_H
#define CSV_WRITER_H

template <typename T>
class CSVWriter {

    private:
        std::vector<T> grandparentRow; // Two rows back from our current row.
        std::vector<T> parentRow; // One row back from our current row.
        std::vector<T> currentRow;
        int currentRowIndex;

        std::vector<int> zeroColsPrev; // Keep track of the col index for any zero values in the previous row.
        std::vector<int> zeroColsCurrent;

        static void writeRowToFile(std::ofstream& outFile, const std::vector<T>& row) {
            bool isStart = true;
            for (const auto& cell : row) {

                if (!isStart) {
                    outFile << ",";
                }
                isStart = false;

                outFile << cell;
            }
            outFile << "\n";
        }

        T getCorrectedValue(const int col) const {
            T sum = 0;

            // a, b, c - grandparent row.
            // d, e, f - parent row which we want to correct.
            // g, h, i - current row.
            // Since we now have the current row we can correct "e" which we have found is zero.
            // We average all of the values around e.

            // Sum a,b,c.
            for (int i = -1; i < 2; i++) {
                sum += grandparentRow[col+i];
            }

            // Sum d,f.
            sum += parentRow[col-1];
            sum += parentRow[col+1];

            // Sum g,h,i.
            for (int i = -1; i < 2; i++) {
                sum += currentRow[col+i];
            }

            return sum/8;
        }

        bool updatePreviousRowZeros() {

            if (zeroColsPrev.empty()) {
                return false;
            }

            for (const int col : zeroColsPrev) {
                const T newVal = getCorrectedValue(col);

                // Update parent.
                parentRow[col] = newVal;

                std::cout << "corrected zero val at [" << currentRowIndex << "," << col << "] to: " << newVal << std::endl;
            }

            return true;
        }

    public:

        void writeRowToFile(std::ofstream& outFile) {

            // First write our parent to file if any zeros needed to be updated.
            if (updatePreviousRowZeros()) {
                writeRowToFile(outFile, parentRow);
            }

            // Now we can write our current row to file, but only if we don't have any zeros.
            if (zeroColsCurrent.empty()) {
                writeRowToFile(outFile, currentRow);
            }

            // Now update our storage avoiding unnecessary copying.
            grandparentRow = std::move(parentRow);
            parentRow = std::move(currentRow);
            zeroColsPrev = std::move(zeroColsCurrent);
            zeroColsCurrent.clear();
            currentRow.clear();
            currentRowIndex++;
        }

        void ingestValue(const T value, const int col) {

            currentRow.push_back(value);

            // If we have a zero value, mark the column.
            // We will come back to this once we have parsed the next row so that we can calculate an average value.
            if (value == 0) {
                zeroColsCurrent.push_back(col);
            }
        }
};


#endif // CSV_WRITER_H
