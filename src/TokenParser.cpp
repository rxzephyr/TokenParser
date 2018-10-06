//
// Created by 星落_月残 on 2018/5/18.
//

#include "TokenParser.h"


TokenInf::TokenInf()
		:tokenName(""),tokenType(""),data(0)
{
}
TokenInf::TokenInf(const std::string &tokenName,const std::string &tokenType,const std::string &dataName,long long int data,long long int row,long long int col)
		:tokenName(tokenName),tokenType(tokenType),dataName(dataName),data(data),row(row),col(col)
{
}
TokenInf::TokenInf(const TokenInf &another)
		:tokenName(another.tokenName),tokenType(another.tokenType),dataName(another.dataName),data(another.data),row(another.row),col(another.col)
{
}
const std::string &TokenInf::getTokenName() const
{
	return tokenName;
}
const std::string &TokenInf::getTokenType() const
{
	return tokenType;
}
const std::string &TokenInf::getDataName() const
{
	return dataName;
}
long long int TokenInf::getData() const
{
	return data;
}
long long int TokenInf::getRow() const
{
	return row;
}
long long int TokenInf::getCol() const
{
	return col;
}
void TokenInf::setTokenName(const std::string &tokenName)
{
	TokenInf::tokenName=tokenName;
}
void TokenInf::setTokenType(const std::string &tokenType)
{
	TokenInf::tokenType=tokenType;
}
void TokenInf::setDataName(const std::string &dataName)
{
	TokenInf::dataName=dataName;
}
void TokenInf::setData(long long int data)
{
	TokenInf::data=data;
}
void TokenInf::setRow(long long int row)
{
	TokenInf::row=row;
}
void TokenInf::setCol(long long int col)
{
	TokenInf::col=col;
}


TokenParser &TokenParser::operator=(const TokenParser &another)
{
	TokenParser parser(another);
	Swap(this->DFATypeList,parser.DFATypeList);
	return *this;
}

//! 判定输入是否满足DFA
//! \param input 输入字符串
//! \param DFA 用于检验的DFA
//! \return 是否通过
bool TokenParser::isMatch(std::string input,Graph<long long,char> &DFA)
{
	long long currentIndex=0;
	bool flag=false;
	for(int i=0;i<input.size();i++)//循环完整个输入
	{
		for(long long j=0;j<DFA.getSize();j++)
		{
			if(DFA.hasEgdeData(currentIndex,j,input[i]))
			{
				currentIndex=j;
				flag=true;
				break;
			}
		}
		if(flag)
			flag=false;
		else
			return false;
	}
	//此处判断currentIndex是否为终止状态
	return DFA.getSpecialVertexListR().hasData(currentIndex);

}
//! 逐个DFA检查是否接受
//! \param input 输入字符串
//! \return 检查后的Token信息
TokenInf TokenParser::parse(std::string input)
{
	std::string typeName,tokenName;
	for(long long i=0;i<DFATypeList.getSize();i++)
	{
		if(isMatch(input,DFATypeList[i].second))
		{
			typeName=DFATypeList[i].first;
			tokenName=input;
			break;
		}
	}
	if(typeName.empty())
	{
		typeName="ERROR";
		tokenName=input;
	}
	return TokenInf(tokenName,typeName,tokenName,0,-1,-1);

}
Sequence<std::pair<std::string,Graph<long long int,char>>> &TokenParser::getDFATypeListR()
{
	return DFATypeList;
}


//!
//! \param wordToLineList 转换表
//! \param wordLocation 字符在总文件中的序数
//! \return 返回行数，列数对
std::pair<long long,long long> getWordLineLocation(Sequence<std::pair<long long,long long>> &wordToLineList,long long wordLocation)
{
	long long rowResult=-1;
	long long colResult=-1;
	for(long long i=0;i<wordToLineList.getUsage();i++)
	{
		if(wordLocation<=wordToLineList[i].second)
		{
			if(i==0)
			{
				rowResult=wordToLineList[i].first;
				colResult=wordLocation;
			}
			else
			{
				rowResult=wordToLineList[i].first;
				colResult=wordLocation-wordToLineList[i-1].second;
			}
			break;
		}
	}
	return std::make_pair(rowResult,colResult);
}

//!
//! \param tokenizedStmt 所有token的列表
//! \return 去重，且只有变量的符号表
Sequence<TokenInf> GenerateTokenTable(Sequence<TokenInf> &tokenizedStmt)
{
	Sequence<TokenInf> tokenTable;//记录最初出现的位置
	Sequence<std::string> tokenNameList;
	for(long long i=0;i<tokenizedStmt.getUsage();i++)
	{
		if(tokenizedStmt[i].getDataName()=="ID")
		{
			if(!tokenNameList.hasData(tokenizedStmt[i].getTokenName()))
			{
				tokenNameList.AddFinal(tokenizedStmt[i].getTokenName());
				tokenTable.AddFinal(tokenizedStmt[i]);
			}
		}
	}
	return tokenTable;
}

TokenInf *getTokenAddress(std::string tokenName,Sequence<TokenInf> &tokenTable)
{
	for(long long i=0;i<tokenTable.getUsage();i++)
	{
		if(tokenTable[i].getTokenName()==tokenName)
			return &tokenTable[i];
	}
	return nullptr;
}