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

	// convert string to the data type that it is, 
	// which is written in the dataTypeInField variable
	// in this case [0][2] is already a string
	// so we don't have to do any casting
	csv::removeQuotesInTable(table);
	std::cout << "Value at [0][2] is: " << col1row3.getValueInString() << std::endl;
	// Value at [0][2] is: FEB
	return 0;
}
```
