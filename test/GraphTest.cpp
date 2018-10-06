#include <gtest/gtest.h>
#include "../src/BasicGraph.h"


constexpr int GRAPH_TEST_SIZE=10;

class GraphTest:public testing::Test
{
protected:
	GraphTest():Test(),graph(Graph<int,int>(GRAPH_TEST_SIZE))
	{
	}
	void SetUp() override
	{
		for(int i=0;i<GRAPH_TEST_SIZE;i++)
			graph.getVertexPointerFromPosition(i)->setData(i);
		graph.addEdgeSymmetrical(0,3,1);
		graph.addEdgeSymmetrical(0,2,2);
		graph.addEdgeSymmetrical(1,5,3);
		graph.addEdgeSymmetrical(1,7,4);
		graph.addEdgeSymmetrical(2,9,5);
		graph.addEdgeSymmetrical(2,6,6);
		graph.addEdgeSymmetrical(3,6,7);
		graph.addEdgeSymmetrical(3,4,8);
		graph.addEdgeSymmetrical(4,5,9);
		graph.addEdgeSymmetrical(4,8,10);
		graph.addEdgeSymmetrical(5,6,11);
		graph.addEdgeSymmetrical(6,7,12);
	}
	Graph<int,int> graph;
};

TEST_F(GraphTest,testCopyConstructor)
{
	auto copy(graph);
	EXPECT_EQ(copy.getEdgeFromPosition(1,7).getConstituent().getUsage(),1);
	EXPECT_EQ(copy.getEdgeFromPosition(1,7).getConstituent()[0],4);
	EXPECT_EQ(copy.getEdgeFromPosition(4,8).getConstituent().getUsage(),1);
	EXPECT_EQ(copy.getEdgeFromPosition(4,8).getConstituent()[0],10);
}
TEST_F(GraphTest,testGetEdgeFromPosition)
{
	graph.getEdgeFromPosition(1,5).getConstituent()[0]=-1;
	EXPECT_EQ(graph.getEdgeFromPosition(1,5).getConstituent()[0],-1);
	graph.getEdgeFromPosition(1,5).Clear();
	EXPECT_EQ(graph.getEdgeFromPosition(1,5).getConstituent().getUsage(),0);
}