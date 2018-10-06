//
// Created by 星落_月残 on 2018/5/26.
//

#include "Initialize.h"

#define DEBUG 1
//!根据要求生成相应的DFA，并准备用于检验
TokenParser InitTokenParser()
{
	string keywords=string("")+LEFT_BRACE+
					LEFT_BRACE+"i"+CLUSTER+"n"+CLUSTER+"t"+RIGHT_BRACE+
					PARALLEL+LEFT_BRACE+"r"+CLUSTER+"e"+CLUSTER+"a"+CLUSTER+"l"+RIGHT_BRACE+
					PARALLEL+LEFT_BRACE+"i"+CLUSTER+"f"+RIGHT_BRACE+
					PARALLEL+LEFT_BRACE+"t"+CLUSTER+"h"+CLUSTER+"e"+CLUSTER+"n"+RIGHT_BRACE+
					PARALLEL+LEFT_BRACE+"e"+CLUSTER+"l"+CLUSTER+"s"+CLUSTER+"e"+RIGHT_BRACE+
					PARALLEL+LEFT_BRACE+"w"+CLUSTER+"h"+CLUSTER+"i"+CLUSTER+"l"+CLUSTER+"e"+RIGHT_BRACE+
					RIGHT_BRACE+
					CLUSTER+FINAL;

	string identifiers=LEFT_BRACE+RE_LowerCharSet+PARALLEL+RE_UpperCharSet+RIGHT_BRACE+CLUSTER+
					   LEFT_BRACE+RE_LowerCharSet+PARALLEL+RE_UpperCharSet+PARALLEL+RE_NumSet+RIGHT_BRACE+CLOSURE+
					   CLUSTER+FINAL;

	string operators=string("")+LEFT_BRACE+"+"+PARALLEL+"-"+PARALLEL+"/"+PARALLEL+"*"+PARALLEL+"="+PARALLEL+
					 LEFT_BRACE+"="+CLUSTER+"="+RIGHT_BRACE+PARALLEL+
					 LEFT_BRACE+"<"+CLUSTER+"="+RIGHT_BRACE+PARALLEL+
					 LEFT_BRACE+">"+CLUSTER+"="+RIGHT_BRACE+PARALLEL+
					 LEFT_BRACE+"!"+CLUSTER+"="+RIGHT_BRACE+PARALLEL+
					 "<"+PARALLEL+">"+RIGHT_BRACE+
					 CLUSTER+FINAL;

	string delimiters=string("")+LEFT_BRACE+"("+PARALLEL+")"+PARALLEL+
					  "{"+PARALLEL+"}"+PARALLEL+";"+PARALLEL+","+RIGHT_BRACE+
					  CLUSTER+FINAL;

	const string DIGIT_PLUS=LEFT_BRACE+RE_NumSet+CLUSTER+RE_NumSet+CLOSURE+RIGHT_BRACE;

	string intnumber=DIGIT_PLUS+CLUSTER+FINAL;
//
	const string EXPONENT=string("")+LEFT_BRACE+LEFT_BRACE+"E"+PARALLEL+"e"+RIGHT_BRACE+CLUSTER+LEFT_BRACE+"+"+PARALLEL+"-"+
						  PARALLEL+EPISILON+RIGHT_BRACE+CLUSTER+DIGIT_PLUS+RIGHT_BRACE;

	string exponent=EXPONENT+CLUSTER+FINAL;

	const string FRACTION=string("")+LEFT_BRACE+"."+CLUSTER+DIGIT_PLUS+RIGHT_BRACE;

	string fraction=FRACTION+CLUSTER+FINAL;

	string realnumber=string("")+LEFT_BRACE+LEFT_BRACE+DIGIT_PLUS+CLUSTER+EXPONENT+RIGHT_BRACE+PARALLEL+
					  LEFT_BRACE+DIGIT_PLUS+CLUSTER+FRACTION+CLUSTER+LEFT_BRACE+EXPONENT+PARALLEL+EPISILON+RIGHT_BRACE+RIGHT_BRACE+RIGHT_BRACE+
					  CLUSTER+FINAL;

	RegularExpressionParser parser1;
	parser1.AllProcess(keywords);
	RegularExpressionParser parser2;
	parser2.AllProcess(identifiers);
	RegularExpressionParser parser3;
	parser3.AllProcess(operators);
	RegularExpressionParser parser4;
	parser4.AllProcess(delimiters);
	RegularExpressionParser parser5;
	parser5.AllProcess(intnumber);
	RegularExpressionParser parser6;
	parser6.AllProcess(exponent);
	RegularExpressionParser parser7;
	parser7.AllProcess(fraction);
	RegularExpressionParser parser8;
	parser8.AllProcess(realnumber);


	TokenParser tokenParser;
	tokenParser.getDFATypeListR().AddFinal(make_pair("keywords",parser1.getFinalDFAR()));
	tokenParser.getDFATypeListR().AddFinal(make_pair("exponent",parser6.getFinalDFAR()));
	tokenParser.getDFATypeListR().AddFinal(make_pair("identifiers",parser2.getFinalDFAR()));
	tokenParser.getDFATypeListR().AddFinal(make_pair("operators",parser3.getFinalDFAR()));
	tokenParser.getDFATypeListR().AddFinal(make_pair("delimiters",parser4.getFinalDFAR()));
	tokenParser.getDFATypeListR().AddFinal(make_pair("intnumber",parser5.getFinalDFAR()));
	tokenParser.getDFATypeListR().AddFinal(make_pair("fraction",parser7.getFinalDFAR()));
	tokenParser.getDFATypeListR().AddFinal(make_pair("realnumber",parser8.getFinalDFAR()));

	return tokenParser;
}

//! 通过已经生成的DFA将输入的字符转换为LLParser可以接受的格式
//! \param tokenParser 生成的DFA
//! \param input 分拆过的输入
//! \param tokenList 待写入的符号表
//! \return 适应于LLParser的字符串
string GenerateForSyntaxParser(TokenParser &tokenParser,Sequence<string> &input,Sequence<pair<long long,long long>> &wordToLineList,Sequence<TokenInf> &tokenList)
{
	string result;
	for(long long i=0;i<input.getUsage();i++)
	{
		string lexicalUnit=input[i];
		TokenInf tokenResult=tokenParser.parse(lexicalUnit);
		auto wordLoc=getWordLineLocation(wordToLineList,i+1);//行数，列数对
		tokenResult.setRow(wordLoc.first);
		tokenResult.setCol(wordLoc.second);
		if(tokenResult.getTokenType()=="intnumber"||tokenResult.getTokenType()=="realnumber")
		{
			tokenResult.setDataName("NUM");
			tokenResult.setData(stoll(tokenResult.getTokenName()));
		}
		else if(tokenResult.getTokenType()=="identifiers")
		{
			tokenResult.setDataName("ID");
		}


		tokenList.AddFinal(tokenResult);
#if DEBUG ==1
		cout<<endl<<lexicalUnit<<"/"<<tokenResult.getTokenType()<<endl;
#endif
//		if(tokenResult.getTokenType().empty());
//		else if(tokenResult.getTokenType()=="intnumber"||tokenResult.getTokenType()=="realnumber")
//		{
//			if(result.empty())
//			{
//				result+="NUM";
//			}
//			else
//			{
//				result+=string()+CLUSTER+"NUM";
//			}
//		}
//		else if(tokenResult.getTokenType()=="identifiers")
//		{
//			if(result.empty())
//			{
//				result+="ID";
//			}
//			else
//			{
//				result+=string()+CLUSTER+"ID";
//			}
//		}
//		else if(tokenResult.getTokenType()=="ERROR");
//		else
//		{
//			if(result.empty())
//			{
//				result+=tokenResult.getTokenName();
//			}
//			else
//			{
//				result+=string()+CLUSTER+tokenResult.getTokenName();
//			}
//		}
	}
	return result;
}

//! 分拆输入
//! \param inputFileName 输入文件名
//! \param annotationMark 需要忽略的注释标识符
//! \return 行数，该行起始字符数对的列表 原始文件内容 以及 分拆后的内容
pair<Sequence<pair<long long,long long>>,pair<string,Sequence<string>>> ReformatInput(const string &inputFileName,const string annotationMark)
{
	Sequence<char> delimiterList;
	Sequence<pair<long long,long long>> wordToLineList;//行数，该行起始字符数
	delimiterList.AddFinal(' ');
	delimiterList.AddFinal('\t');
	ifstream fin(inputFileName);
	string orginal;
	string inputLine;
	Sequence<string> result;
	long long wordCount=0;
	long long lineCount=0;
//	wordToLineList.AddFinal(make_pair(1,0));

	for(;!fin.eof();)
	{
		getline(fin,inputLine);
		lineCount++;

		orginal+=inputLine;
//		Sequence<string> lineResult=splitInput(inputLine,delimiterList);


		Sequence<string> lineResult;
		string element;
		for(long long i=0;i<inputLine.size();i++)
		{
			if(inputLine[i]==annotationMark[0])//判定注释
			{
				bool completeMark=false;
				for(long long j=i+1,k=1;j<inputLine.size()&&k<annotationMark.size();j++,k++)
				{
					if(inputLine[j]!=annotationMark[k])
						break;
					if(k==annotationMark.size()-1)
					{
						completeMark=true;
					}
				}
				if(completeMark)
				{
					break;
				}
			}
			if(!delimiterList.hasData(inputLine[i]))
			{
				element.push_back(inputLine[i]);
			}
			else
			{
				if(!element.empty())
				{
					lineResult.AddFinal(element);
					wordCount++;
				}
				element.clear();
			}
		}
		if(!element.empty())
		{
			lineResult.AddFinal(element);
			wordCount++;
		}
		wordToLineList.AddFinal(make_pair(lineCount,wordCount));


		result.Merge(lineResult);
	}
	fin.close();
	return make_pair(wordToLineList,make_pair(orginal,result));
}

//!用于拆分输入
Sequence<string> splitInput(string &input,Sequence<char> delimiterList)
{
	Sequence<string> result;
	string element;
	for(long long i=0;i<input.size();i++)
	{
		if(!delimiterList.hasData(input[i]))
		{
			element.push_back(input[i]);
		}
		else
		{
			if(!element.empty())
				result.AddFinal(element);
			element.clear();
		}
	}
	if(!element.empty())
		result.AddFinal(element);
	return result;
}




