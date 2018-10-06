#include <gtest/gtest.h>
#include "../src/RegularExpressionParser.h"


class RegularExpressionParserTest:public testing::Test
{
protected:
	void SetUp() override
	{
		keywords=string("")+LEFT_BRACE+
				 LEFT_BRACE+"i"+CLUSTER+"n"+CLUSTER+"t"+RIGHT_BRACE+
				 PARALLEL+LEFT_BRACE+"r"+CLUSTER+"e"+CLUSTER+"a"+CLUSTER+"l"+RIGHT_BRACE+
				 PARALLEL+LEFT_BRACE+"i"+CLUSTER+"f"+RIGHT_BRACE+
				 PARALLEL+LEFT_BRACE+"t"+CLUSTER+"h"+CLUSTER+"e"+CLUSTER+"n"+RIGHT_BRACE+
				 PARALLEL+LEFT_BRACE+"e"+CLUSTER+"l"+CLUSTER+"s"+CLUSTER+"e"+RIGHT_BRACE+
				 PARALLEL+LEFT_BRACE+"w"+CLUSTER+"h"+CLUSTER+"i"+CLUSTER+"l"+CLUSTER+"e"+RIGHT_BRACE+
				 RIGHT_BRACE+CLUSTER+FINAL;
		for(char keyword:keywords)
		{
			if(isValidChar(keyword))
				toCompare+=keyword;
		}

	}

	RegularExpressionParser parser;
	string keywords;
	string toCompare;
};

TEST_F(RegularExpressionParserTest,testInitializeFromString)
{
	parser.InitializeFromString(keywords);
	auto postfixQueue=parser.getPostfixQueue();
	string join,compare;
	for(int i=0;i<postfixQueue.getUsage();i++)
	{
		if(isValidChar(postfixQueue[i]))
			join+=postfixQueue[i];
	}
	EXPECT_EQ(join,toCompare);
}

void visit(REBinaryClient<char> *pTraverse,void *ref)
{
	if(isValidChar(pTraverse->getData()))
		((string *)ref)->operator+=(pTraverse->getData());
}

TEST_F(RegularExpressionParserTest,testMakeParseTree)
{
	parser.InitializeFromString(keywords);
	parser.MakeParseTree();
	auto &parseTree=parser.getParseTree();
	string result;
	parseTree.PreorderTraverse(parseTree.getRERoot(),visit,&result);
	EXPECT_EQ(result,toCompare);
}

struct TransferDetails
{
	TransferDetails(long long fromIndex,char type,long long toIndex):fromIndex(fromIndex),type(type),toIndex(toIndex)
	{}
	bool operator==(const TransferDetails &rhs) const
	{
		return fromIndex==rhs.fromIndex&&
			   type==rhs.type&&
			   toIndex==rhs.toIndex;
	}

	long long fromIndex;
	char type;
	long long toIndex;
};

TEST_F(RegularExpressionParserTest,testMakeStateTransferList)
{
	parser.InitializeFromString(keywords);
	parser.MakeParseTree();
	parser.SetREClientProperties();
	parser.MakeStateTransferList();
	auto stateTransferList=parser.getStateTransferListR();
	vector<TransferDetails> compare{{0, 'e',1},
									{0, 'i',2},
									{0, 'r',3},
									{0, 't',4},
									{0, 'w',5},
									{1, 'l',6},
									{2, 'f',7},
									{2, 'n',8},
									{3, 'e',9},
									{4, 'h',10},
									{5, 'h',11},
									{6, 's',12},
									{8, 't',7},
									{9, 'a',13},
									{10,'e',14},
									{11,'i',15},
									{12,'e',7},
									{13,'l',7},
									{14,'n',7},
									{15,'l',16},
									{16,'e',7}};
	vector<TransferDetails> result;
	for(int i=0;i<stateTransferList.getUsage();i++)
	{
		for(int j=0;j<stateTransferList[i].second.getUsage();j++)
		{
			result.push_back(TransferDetails(stateTransferList[i].first,stateTransferList[i].second[j].first,stateTransferList[i].second[j].second));
		}
	}
	EXPECT_EQ(compare,result);
}
