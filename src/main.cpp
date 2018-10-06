#include <iostream>
#include <ctime>
#include "Initialize.h"


int main(int argc,char *argv[])
{
//	cout<<"Enter the filename:"<<endl;
//	string filename;
//	cin>>filename;
//	cout<<"Processing."<<endl;
	TokenParser parser=InitTokenParser();
	auto input=ReformatInput("correctTest.txt","//");
	Sequence<pair<long long,long long>> wordToLineList=input.first;
	Sequence<TokenInf> tokenizedStmt;
	string forSyntaxParse=GenerateForSyntaxParser(parser,input.second.second,wordToLineList,tokenizedStmt);
	Sequence<TokenInf> tokenTable=GenerateTokenTable(tokenizedStmt);



	return 0;
}
