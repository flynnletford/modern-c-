#### Summary:
- CSVCorrector reads in each line and passes in individual cell values to the CSVWriter.
- CSVWriter keeps track of the previous two rows so that any zero values found can then be corrected by taking the average of neighboring cells.
- The corrected values are then written to a new CSV file.
- In this way we avoid holding the entire CSV file content in memory, which is important for large files.
- We also encapsulate the logic for storing each line and correcting values inside the CSVWriter class, helping to avoid cluttering a single class with too much rsponsibility.
- Class templates used to allow for different data types.
- In production I would be adding unit tests as I code, ensuring each modular part of code works as expected.

#### Assumptions:
- Assume that no two bad values are adjacent to each other.
- Assume no special treatment at borders required.
- Unknown/inconsistent csv row sizes so vectors used.