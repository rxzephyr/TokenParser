#include <gtest/gtest.h>
#include "../src/MultipurposeSequence.h"


constexpr int SEQUENCE_TEST_SIZE=100;

class SequenceTest:public testing::Test
{
protected:
	void SetUp() override
	{
		for(int i=0;i<SEQUENCE_TEST_SIZE;i++)
		{
			list.AddFinal(i);
		}
	}
	Sequence<int> list;
};

TEST_F(SequenceTest,testCopyConstructor)
{
	auto copy(list);
	ASSERT_TRUE(copy.getUsage()==list.getUsage());
	for(int i=0;i<copy.getUsage();i++)
	{
		EXPECT_TRUE(copy[i]==list[i]);
	}
	ASSERT_TRUE(copy==list);
}

TEST_F(SequenceTest,testDelete)
{
	list.Delete(27);
	ASSERT_EQ(list.getUsage(),SEQUENCE_TEST_SIZE-1);
	EXPECT_EQ(list.getSubscriptFromData(28),27);
}
int cmp(const int &a,const int &b)
{
	if(a<b)
		return 1;
	else
		return -1;
}

TEST_F(SequenceTest,testSort)
{
	ASSERT_EQ(list[0],0);
	ASSERT_EQ(list[list.getUsage()-1],SEQUENCE_TEST_SIZE-1);
	list.Sort(cmp);
	EXPECT_EQ(list[0],SEQUENCE_TEST_SIZE-1);
	EXPECT_EQ(list[list.getUsage()-1],0);
}

TEST_F(SequenceTest,testMakeUnique)
{
	list.Insert(32,98);
	list.Insert(59,2);
	list.Insert(76,39);
	EXPECT_EQ(list.getUsage(),SEQUENCE_TEST_SIZE+3);
	list.MakeUnique(cmp);
	EXPECT_EQ(list.getUsage(),SEQUENCE_TEST_SIZE);
	EXPECT_EQ(list[0],SEQUENCE_TEST_SIZE-1);
	EXPECT_EQ(list[list.getUsage()-1],0);
}

TEST_F(SequenceTest,testMerge)
{
	Sequence<int> tmp1,tmp2;
	for(int i=0;i<SEQUENCE_TEST_SIZE;i+=2)
	{
		tmp1.AddFinal(i);
		tmp2.AddFinal(SEQUENCE_TEST_SIZE-1-i);
	}
	ASSERT_EQ(tmp1.getUsage(),SEQUENCE_TEST_SIZE/2);
	ASSERT_EQ(tmp2.getUsage(),SEQUENCE_TEST_SIZE/2);
	tmp1.Merge(tmp2);
	EXPECT_EQ(tmp1.getUsage(),SEQUENCE_TEST_SIZE);
	tmp1.Sort(cmp);
	EXPECT_EQ(tmp1[0],SEQUENCE_TEST_SIZE-1);
	EXPECT_EQ(tmp1[tmp1.getUsage()-1],0);
}