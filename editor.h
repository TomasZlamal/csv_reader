#ifndef CSV_EDITOR_INCLUDE_CSV_EDITOR_H
#define CSV_EDITOR_INCLUDE_CSV_EDITOR_H
#include "util.h"
namespace csv{

void removeQuotesInTable(Table& table){
  for(int i = 0; i < table.size(); i++){
    for(int j = 0; j < table[i].size(); j++){
      std::string temp;
      for (const auto c: table[i][j].getValueInString()){

        if(!ispunct(c)){

        temp.push_back(c);
        }
      }
      table[i][j].changeToStringValue(temp);
    }
  }
}

}
#endif