#ifndef CSV_READER_INCLUDE_CSV_READER_H
#define CSV_READER_INCLUDE_CSV_READER_H
#include <string>
#include <vector>
#include <fstream>
#include <string_view>
#include <regex>
#include <cassert>
namespace csv {
constexpr bool kDebugModeActivated = 1;
enum class TableCellMetaType {
	kHeader,
	kData
};
enum class TableCellDataType {
	kText,
	kDouble,
	kInt,
	// TO-DO: Implement bool and date data types
	kBoolean,
	kDate,
	kBlank
};
class TableCell {
private:
	TableCellMetaType m_field_meta_type;
	TableCellDataType m_field_data_type;
	std::string m_string_value;
public:
	TableCell(TableCellDataType field_data_type, TableCellMetaType field_meta_type, std::string string_value)
		: m_field_data_type(field_data_type), m_field_meta_type(field_meta_type), m_string_value(string_value){}
	std::string getValueInString() {
		return m_string_value;
	}
	TableCellDataType getDataType() {
		return m_field_data_type;
	}
	TableCellMetaType getMetaType() {
		return m_field_meta_type;
	}
};
namespace util {
	bool is_integer(const std::string& s) {
		return std::regex_match(s, std::regex("[(-|+)|][0-9]+"));
	}

	bool is_double(const std::string& s) {
		char* end = nullptr;
		double val = strtod(s.c_str(), &end);
		return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
	}
}
std::vector<std::vector<TableCell>> ReadCSVFile(std::string m_file_name){
		std::ifstream input(m_file_name);
		std::vector<std::vector<TableCell>> m_data;
		std::string line, data;
		int column = 0, max = 0;
		bool first = 0, last = 0;
		if(kDebugModeActivated) assert(input.is_open());
		while (std::getline(input, line)) {
			while(!last) {
				if (!first) {
					m_data.push_back(std::vector<TableCell>());
				}
				max = line.find(',');
				if (max == -1) {
					last = 1;
					max = line.length() - 1;
				}
				int index = line.find_first_not_of(' ');
				data = line.substr(index, max - index);
				if (max == index) {
					if (!first)
						m_data[column].push_back(TableCell(TableCellDataType::kBlank, TableCellMetaType::kHeader, ""));
					else {
						m_data[column].push_back(TableCell(TableCellDataType::kBlank, TableCellMetaType::kData, ""));
					}
				}
				else if (util::is_double(data)) {
					if(!first)
						m_data[column].push_back(TableCell(TableCellDataType::kDouble, TableCellMetaType::kHeader, data));
					else {
						m_data[column].push_back(TableCell(TableCellDataType::kDouble, TableCellMetaType::kData, data));
					}
				}
				else if (util::is_integer(data)) {
					if (!first)
						m_data[column].push_back(TableCell(TableCellDataType::kInt, TableCellMetaType::kHeader, data));
					else {
						m_data[column].push_back(TableCell(TableCellDataType::kInt, TableCellMetaType::kData, data));
					}
				}
				else {
					if (!first)
						m_data[column].push_back(TableCell(TableCellDataType::kText, TableCellMetaType::kHeader, data));
					else {
						m_data[column].push_back(TableCell(TableCellDataType::kText, TableCellMetaType::kData, data));
					}
				}
				line = line.substr(max+1);
				column += 1;
				max = 0;
			}
			first = 1;
			last = 0;
		column = 0;
	}
	input.close();
	return m_data;
}
using Table = std::vector<std::vector<TableCell>>;
}
#endif