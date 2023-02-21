#ifndef CSV_EDITOR_INCLUDE_CSV_EDITOR_H
#define CSV_EDITOR_INCLUDE_CSV_EDITOR_H
#include "util.h"
namespace csv{

void outputTableToFile(const Table& table, const std::string& file_name){
  std::ofstream input(file_name);
  // assuming all lines are of the same length
  for(int i = 0; i < table[0].size(); i++){
    for(int j = 0; j < table.size(); j++){
      input << table[j][i].getValueInString() << ", ";
    }
    input << "\n";
  }
  input.close();
}
std::optional<double> getAvgInColumn(const Table& table, int column){
  if(column < 0 || column > table.size() || table[column].size() < 2)
    return {};
  if(table[column][1].getDataType() != TableCellDataType::kInt && table[column][1].getDataType() != TableCellDataType::kDouble){
    return {};
  }
  double avg = 0;
  int i;
  for(i = 1; i < table[column].size(); i++){
    avg += atof(table[column][i].getValueInString().c_str());
  }
  avg /= i-1;
  return avg;
}
}
#endif