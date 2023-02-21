# csv_modif

This project is a simple csv modifier that allows you to read csv files and modify them.

An example of how you can use this class so far:
```c++
#include <iostream>
#include "reader.h"
#include "editor.h"

int main() {
	std::optional<csv::Table> tableOptional = csv::ReadCSVFile("industry.csv", ',');
	if (!tableOptional) {
		return EXIT_FAILURE;
	}
	csv::Table table = tableOptional.value();
	csv::TableCell col1row3 = table[0][2];
	
	csv::TableCellDataType dataTypeInField = col1row3.getDataType();
	csv::outputTableToFile(table, "out.csv");
	std::cout << "Value at [0][2] is: " << col1row3.getValueInString() << std::endl;
	std::cout << "Average in first column " << csv::getAvgInColumn(table, 0).value_or(0) << std::endl;
	return EXIT_SUCCESS;
}
```
