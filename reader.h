#ifndef CSV_READER_INCLUDE_CSV_READER_H
#define CSV_READER_INCLUDE_CSV_READER_H
#include <fstream>
#include <string_view>
#include <regex>
#include <optional>
#include "util.h"
namespace csv {
constexpr bool kDebugModeActivated = 1;
std::optional<csv::Table> ReadCSVFile(std::string m_file_name, char delim){
		std::ifstream input(m_file_name);
		if (!input.is_open()) {
			return {};
		}
		std::vector<std::vector<TableCell>> m_data;
		std::string line, data;
		int column = 0, max = 0;
		bool first = 0, last = 0;
		while (std::getline(input, line)) {
			while(!last) {
				if (!first) {
					m_data.push_back(std::vector<TableCell>());
				}
				if(line[0] == '"'){
					int after_second_quote_index = line.substr(1, line.length()-1).find('"');
					int isTheEnd = line.substr(after_second_quote_index, line.length()-after_second_quote_index).find(',');
					if(isTheEnd == -1){
						max = -1;
					}
					else{
						max = line.find('"')+1;
					}
				}
				else
					max = line.find(delim);
				if (max == -1) {
					last = 1;
					max = line.length();
				}
				int index = line.find_first_not_of(' ');
				data = line.substr(index, max - index);
				if (max == index) {
					m_data[column].push_back(TableCell(TableCellDataType::kBlank, TableCellMetaType::kData, ""));
				}
        else if (util::is_integer(data)) {
					m_data[column].push_back(TableCell(TableCellDataType::kInt, TableCellMetaType::kData, data));
				}
				else if (util::is_double(data)) {
					m_data[column].push_back(TableCell(TableCellDataType::kDouble, TableCellMetaType::kData, data));
        }
				else {
						m_data[column].push_back(TableCell(TableCellDataType::kText, TableCellMetaType::kData, data));
				}
				if(!last){
					line = line.substr(max+1);
					column += 1;
					max = 0;
				}
				
			}
		first = 1;
		last = 0;
		column = 0;
	}
	input.close();
	return m_data;
}
}
#endif