#include <gtest/gtest.h>
#include "../src/TokenParser.h"
#include "../src/RegularExpressionParser.h"


class TokenParserTest:public testing::Test
{
protected:
	void SetUp() override
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

		RegularExpressionParser regularExpressionParser1;
		regularExpressionParser1.AllProcess(keywords);
		RegularExpressionParser regularExpressionParser2;
		regularExpressionParser2.AllProcess(identifiers);

		parser.getDFATypeListR().AddFinal(make_pair("keywords",regularExpressionParser1.getFinalDFAR()));
		parser.getDFATypeListR().AddFinal(make_pair("identifiers",regularExpressionParser2.getFinalDFAR()));
	}
	TokenParser parser;
};

TEST_F(TokenParserTest,testParse1)
{
	auto token=parser.parse("else");
	ASSERT_EQ(token.getTokenType(),"keywords");
}

TEST_F(TokenParserTest,testParse2)
{
	auto token=parser.parse("temp");
	ASSERT_EQ(token.getTokenType(),"identifiers");
}

TEST_F(TokenParserTest,testParse3)
{
	auto token=parser.parse("ui23");
	ASSERT_EQ(token.getTokenType(),"identifiers");
}

TEST_F(TokenParserTest,testParse4)
{
	auto token=parser.parse("command");
	ASSERT_EQ(token.getTokenType(),"identifiers");
}

TEST_F(TokenParserTest,testParse5)
{
	auto token=parser.parse("while");
	ASSERT_EQ(token.getTokenType(),"keywords");
}

TEST_F(TokenParserTest,testParse6)
{
	auto token=parser.parse("if");
	ASSERT_EQ(token.getTokenType(),"keywords");
}

TEST_F(TokenParserTest,testParse7)
{
	auto token=parser.parse("part");
	ASSERT_EQ(token.getTokenType(),"identifiers");
}

TEST_F(TokenParserTest,testParse8)
{
	auto token=parser.parse("then");
	ASSERT_EQ(token.getTokenType(),"keywords");
}