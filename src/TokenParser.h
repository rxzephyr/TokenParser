//
// Created by 星落_月残 on 2018/5/18.
//

#ifndef COMPILER_TOKENPARSER_H
#define COMPILER_TOKENPARSER_H

#include "MultipurposeSequence.h"
#include "BasicGraph.h"


class TokenInf
{
public:
	TokenInf();
	TokenInf(const std::string &tokenName,const std::string &tokenType,const std::string &dataName,long long int data,long long int row,long long int col);
	TokenInf(const TokenInf &another);
	const std::string &getTokenName() const;
	const std::string &getTokenType() const;
	const std::string &getDataName() const;
	long long int getData() const;
	long long int getRow() const;
	long long int getCol() const;
	void setTokenName(const std::string &tokenName);
	void setTokenType(const std::string &tokenType);
	void setDataName(const std::string &dataName);
	void setData(long long int data);
	void setRow(long long int row);
	void setCol(long long int col);

private:
	std::string tokenName;
	std::string tokenType;
	std::string dataName;
	long long data;
	long long row;
	long long col;
};

class TokenParser
{
public:
	TokenParser()=default;
	TokenParser(const TokenParser &another)=default;
	TokenParser &operator=(const TokenParser &another);
	Sequence<std::pair<std::string,Graph<long long int,char>>> &getDFATypeListR();
	TokenInf parse(std::string input);
private:
	bool isMatch(std::string input,Graph<long long,char> &DFA);
	Sequence<std::pair<std::string,Graph<long long,char>>> DFATypeList;//Token类型名，DFA

};

std::pair<long long,long long> getWordLineLocation(Sequence<std::pair<long long,long long>> &wordToLineList,long long wordLocation);
Sequence<TokenInf> GenerateTokenTable(Sequence<TokenInf> &tokenizedStmt);
TokenInf * getTokenAddress(std::string tokenName,Sequence<TokenInf> &tokenTable);


#endif //COMPILER_TOKENPARSER_H
