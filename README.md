# csv_reader

This project is a simple csv reader that allows you to read csv files.

It is usable standalone, although much of its use will be in the future
when csv_writer and csv_transformer classes are done. These three classes
will allow you to read a csv file, modify it and write some date to another
csv file.

An example of how you can use this class so far:
```c++
#include <iostream>
#include "include/csv_reader.h"

int main() {
	std::optional<csv::Table> tableOptional = csv::ReadCSVFile("test.csv");
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
	std::cout << "Value at [0][2] is: " << col1row3.getValueInString() << std::endl;
	// Value at [0][2] is: FEB
	return 0;
}
```
