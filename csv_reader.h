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
enum class CsvFieldMetaType {
	kHeader,
	kData
};
enum class CsvFieldDataType {
	kText,
	kDouble,
	kInt,
	// TO-DO: Implement bool and date data types
	kBoolean,
	kDate,
	kBlank
};
class CsvField {
private:
	CsvFieldMetaType m_field_meta_type;
	CsvFieldDataType m_field_data_type;
	std::string m_string_value;
public:
	CsvField(CsvFieldDataType field_data_type, CsvFieldMetaType field_meta_type, std::string string_value)
		: m_field_data_type(field_data_type), m_field_meta_type(field_meta_type), m_string_value(string_value){}
	std::string getValueInString() {
		return m_string_value;
	}
	CsvFieldDataType getDataType() {
		return m_field_data_type;
	}
	CsvFieldMetaType getMetaType() {
		return m_field_meta_type;
	}
};
class CsvReader {
// Private Variables
private:
	std::vector<std::vector<CsvField>> m_data;
	std::string m_file_name;

// Scanning Functions
private:
	bool is_integer(const std::string& s) {
		return std::regex_match(s, std::regex("[(-|+)|][0-9]+"));
	}

	bool is_double(const std::string& s) {
		char* end = nullptr;
		double val = strtod(s.c_str(), &end);
		return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
	}
// Some other functions
private:

public:
	CsvReader(std::string file_name)
		: m_file_name(file_name){
		std::ifstream input(m_file_name);
		std::string line, data;
		int column = 0, max = 0;
		bool first = 0, last = 0;
		if(kDebugModeActivated) assert(input.is_open());
		while (std::getline(input, line)) {
			while(!last) {
				if (!first) {
					m_data.push_back(std::vector<CsvField>());
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
						m_data[column].push_back(CsvField(CsvFieldDataType::kBlank, CsvFieldMetaType::kHeader, ""));
					else {
						m_data[column].push_back(CsvField(CsvFieldDataType::kBlank, CsvFieldMetaType::kData, ""));
					}
				}
				else if (is_double(data)) {
					if(!first)
						m_data[column].push_back(CsvField(CsvFieldDataType::kDouble, CsvFieldMetaType::kHeader, data));
					else {
						m_data[column].push_back(CsvField(CsvFieldDataType::kDouble, CsvFieldMetaType::kData, data));
					}
				}
				else if (is_integer(data)) {
					if (!first)
						m_data[column].push_back(CsvField(CsvFieldDataType::kInt, CsvFieldMetaType::kHeader, data));
					else {
						m_data[column].push_back(CsvField(CsvFieldDataType::kInt, CsvFieldMetaType::kData, data));
					}
				}
				else {
					if (!first)
						m_data[column].push_back(CsvField(CsvFieldDataType::kText, CsvFieldMetaType::kHeader, data.substr(1, data.length()-2)));
					else {
						m_data[column].push_back(CsvField(CsvFieldDataType::kText, CsvFieldMetaType::kData, data.substr(1, data.length()-2)));
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
	}
	std::vector<CsvField> getVectorAtColumn(int index) {
		return m_data[index];
	}
	CsvField getDataAt(int column, int row) {
		return m_data[column][row];
	}
	std::vector<std::vector<CsvField>> getTable() {
		return m_data;
	}
};
using CsvFile = std::vector<std::vector<CsvField>>;
}
#endif