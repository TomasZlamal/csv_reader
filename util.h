#ifndef CSV_INCLUDE_UTIL_H
#define CSV_INCLUDE_UTIL_H
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <optional>
namespace csv{
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
	std::string getValueInString() const {
		return m_string_value;
	}
	TableCellDataType getDataType() const {
		return m_field_data_type;
	}
	TableCellMetaType getMetaType() const {
		return m_field_meta_type;
  }
  void changeToStringValue(const std::string& str){
    m_string_value = str;
  }
};
namespace util{
inline bool is_integer(const std::string& s) {
	return std::regex_match(s, std::regex("[(-|+)|][0-9]+"));
}

bool is_double(const std::string& s) {
	char* end = nullptr;
	double val = strtod(s.c_str(), &end);
	return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}
}
using Table = std::vector<std::vector<TableCell>>;
}
#endif