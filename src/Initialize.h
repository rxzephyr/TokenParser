//
// Created by 星落_月残 on 2018/5/26.
//

#ifndef COMPILER_GUI_INITIALIZE_H
#define COMPILER_GUI_INITIALIZE_H

#include "TokenParser.h"
#include "RegularExpressionParser.h"


TokenParser InitTokenParser();
string GenerateForSyntaxParser(TokenParser &tokenParser,Sequence<string> &input,Sequence<pair<long long,long long>> &wordToLineList,Sequence<TokenInf> &tokenList);
pair<Sequence<pair<long long,long long>>,pair<string,Sequence<string>>> ReformatInput(const string &inputFileName,const string annotationMark);
Sequence<string> splitInput(string &input,Sequence<char> delimiterList);
Sequence<string> getErrorStmts(Sequence<long long> errorLocationList,const char &endMark);
#endif //COMPILER_GUI_INITIALIZE_H
