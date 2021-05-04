#include "source.cpp"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

using namespace std;

string branchInfo(const Branch& b) {
	string out = "";
	std::stringstream sstm;
	sstm << b.getFruitsTotal() << ".";
	sstm << b.getWeightsTotal() << ".";
	sstm << b.getHeight() << ".";
	sstm << b.getLength();
	out = sstm.str();
	return out;
}

string treeInfo(const Tree& t) { 
	string out = "";
	std::stringstream s;
	s << t.getBranchesTotal() << ".";
	s << t.getFruitsTotal() << ".";
	s << t.getWeightsTotal() << ".";
	s << t.getNumber() << ".";
	s << t.getHeight();
	out = s.str();
	return out;
}

string gardenInfo(const Garden& g) { 
	string out = "";
	std::stringstream s;
	s << g.getTreesTotal() << ".";
	s << g.getBranchesTotal() << ".";
	s << g.getFruitsTotal() << ".";
	s << g.getWeightsTotal();
	out = s.str();
	return out;
}

void printBranchList(const Tree* t) {
	for (Branch* it = t->getFirst(); it != NULL; it = it->getNext()) {
		cout << it << "->" << it->getNext() << endl;
	}
}

TEST(Branch, CopyConstructor) {
	Branch b;
	Branch b1 = b;
	EXPECT_EQ(branchInfo(b), "0.0.0.0");
	EXPECT_EQ(branchInfo(b1), "0.0.0.0");

	b.growthBranch();
	Branch b2 = b;
	EXPECT_EQ(branchInfo(b), "0.0.0.1");
	EXPECT_EQ(branchInfo(b2), "0.0.0.1");

	b.growthBranch();
	Branch b3 = b;
	EXPECT_EQ(branchInfo(b), "1.0.0.2");
	EXPECT_EQ(branchInfo(b3), "1.0.0.2");

	b.growthBranch();
	Branch b4 = b;
	EXPECT_EQ(branchInfo(b), "1.1.0.3");
	EXPECT_EQ(branchInfo(b4), "1.1.0.3");

	b.growthBranch();
	Branch b5 = b;
	EXPECT_EQ(branchInfo(b), "2.2.0.4");
	EXPECT_EQ(branchInfo(b5), "2.2.0.4");

	b.growthBranch();
	Branch b6 = b;
	EXPECT_EQ(branchInfo(b), "2.4.0.5");
	EXPECT_EQ(branchInfo(b6), "2.4.0.5");

	for (int i = 0; i < 5; i++) {
		b6.fadeBranch();
	}
	EXPECT_EQ(branchInfo(b6), "0.0.0.0");

	Branch b7 = b;
	b7.harvestBranch(1);
	EXPECT_EQ(branchInfo(b7), "2.0.0.5");

	Branch b8 = b;
	b8.cutBranch(2);
	EXPECT_EQ(branchInfo(b8), "1.3.0.2");

	EXPECT_EQ(branchInfo(b1), "0.0.0.0");
	EXPECT_EQ(branchInfo(b2), "0.0.0.1");
	EXPECT_EQ(branchInfo(b3), "1.0.0.2");
	EXPECT_EQ(branchInfo(b4), "1.1.0.3");
	EXPECT_EQ(branchInfo(b5), "2.2.0.4");
	EXPECT_EQ(branchInfo(b6), "0.0.0.0");
	EXPECT_EQ(branchInfo(b7), "2.0.0.5");
	EXPECT_EQ(branchInfo(b8), "1.3.0.2");
}

TEST(Branch, Branch) {
	//GTEST_SKIP();
	Branch b;
	EXPECT_EQ(branchInfo(b), "0.0.0.0");
	for (int i = 0; i < 8; i++) {
		b.growthBranch();
		//cout << branchInfo(b) << endl;
	}
	EXPECT_EQ(branchInfo(b), "4.12.0.8");
	for (int i = 0; i < 12; i++) {
		b.fadeBranch();
		//cout << branchInfo(b) << endl;
	}
	EXPECT_EQ(branchInfo(b), "0.0.0.0");
	for (int i = 0; i < 8; i++) {
		b.growthBranch();
		//cout << branchInfo(b) << endl;
	}
	EXPECT_EQ(branchInfo(b), "4.12.0.8");
	b.harvestBranch(8);
	b.harvestBranch(7);
	EXPECT_EQ(branchInfo(b), "4.12.0.8");
	b.harvestBranch(6);
	EXPECT_EQ(branchInfo(b), "4.6.0.8");
	b.harvestBranch(6);
	b.harvestBranch(6);
	b.harvestBranch(5);
	EXPECT_EQ(branchInfo(b), "4.6.0.8");
	b.harvestBranch(0);
	EXPECT_EQ(branchInfo(b), "4.0.0.8");
	b.fadeBranch();
	EXPECT_EQ(branchInfo(b), "3.0.0.7");
	for (int i = 0; i < 7; i++) {
		b.fadeBranch();
	}
	EXPECT_EQ(branchInfo(b), "0.0.0.0");
	for (int i = 0; i < 8; i++) {
		b.growthBranch();
	}
	EXPECT_EQ(branchInfo(b), "4.12.0.8");
	b.cutBranch(8);
	EXPECT_EQ(branchInfo(b), "4.12.0.8");
	b.cutBranch(7);
	EXPECT_EQ(branchInfo(b), "3.12.0.7");
	b.cutBranch(3);
	EXPECT_EQ(branchInfo(b), "1.6.0.3");
	b.cutBranch(0);
	EXPECT_EQ(branchInfo(b), "0.0.0.0");


	for (int i = 0; i < 8; i++) {
		b.growthBranch();
	}
	EXPECT_EQ(branchInfo(b), "4.12.0.8");
	Branch b1 = b;
	EXPECT_EQ(branchInfo(b1), "4.12.0.8");
	b1.fadeBranch();
	EXPECT_EQ(branchInfo(b), "4.12.0.8");
	//cout << branchInfo(copy) << endl;
	EXPECT_EQ(branchInfo(b1), "3.9.0.7");
	b1.harvestBranch(2);
	EXPECT_EQ(branchInfo(b1), "3.1.0.7");
	EXPECT_EQ(branchInfo(b), "4.12.0.8");
	b1.growthBranch();
	EXPECT_EQ(branchInfo(b1), "4.4.0.8");
	Branch b2 = b1;
	Branch b3 = b1;
	b1.cutBranch(2);
	EXPECT_EQ(branchInfo(b1), "1.1.0.2");
	b1.harvestBranch(1);
	EXPECT_EQ(branchInfo(b1), "1.0.0.2");
	b1.harvestBranch(0);
	EXPECT_EQ(branchInfo(b1), "1.0.0.2");

	b2.cutBranch(1);
	EXPECT_EQ(branchInfo(b2), "0.0.0.1");
	b2.harvestBranch(1);
	EXPECT_EQ(branchInfo(b2), "0.0.0.1");
	b2.harvestBranch(0);
	EXPECT_EQ(branchInfo(b2), "0.0.0.1");

	b3.cutBranch(0);
	EXPECT_EQ(branchInfo(b3), "0.0.0.0");
	b3.harvestBranch(1);
	EXPECT_EQ(branchInfo(b3), "0.0.0.0");
	b3.harvestBranch(0);
	EXPECT_EQ(branchInfo(b3), "0.0.0.0");
	// TODO można spróbować je porozrastać
}

TEST(Tree, cloneBranch) {
	GTEST_SKIP();
	Tree t;
	for (int i = 0; i < 9; i++) {
		t.growthTree();
	}
	EXPECT_EQ(treeInfo(t), "3.4.7.0.9");
	Branch* tb6 = t.getBranchPointer(6);
	EXPECT_EQ(branchInfo(*tb6), "1.1.6.3");
	t.cloneBranch(tb6);
	EXPECT_EQ(branchInfo(*tb6), "1.1.6.3");
	Branch* tb9 = t.getBranchPointer(9);
	//cout << tb9->getLength() << endl;
	//cout << "tb9=" << tb9 << endl;
	//cout << tb9->getLength() << endl;
	EXPECT_EQ(branchInfo(*tb9), "1.1.9.3");
	EXPECT_EQ(treeInfo(t), "4.5.8.0.9");
	//cout << "a" << endl;
	//t.cutTree(2);
	//EXPECT_EQ(treeInfo(t), "0.0.0.0.2");
	//for (int i = 0; i < 7; i++) {
	//	t.growthTree();
	//}
	//EXPECT_EQ(treeInfo(t), "3.4.7.0.9");

}

TEST(Tree, CopyConstructor) {
//GTEST_SKIP();
	Tree t;
	t.growthTree();
	Tree t1 = t;
	EXPECT_EQ(treeInfo(t), "0.0.0.0.1");
	EXPECT_EQ(treeInfo(t1), "0.0.0.0.1");
	t.growthTree();
	Tree t2 = t;
	EXPECT_EQ(treeInfo(t), "0.0.0.0.2");
	EXPECT_EQ(treeInfo(t2), "0.0.0.0.2");
	t.growthTree();
	Tree t3 = t;
	EXPECT_EQ(treeInfo(t), "1.0.0.0.3");
	EXPECT_EQ(treeInfo(t3), "1.0.0.0.3");
	t.growthTree();
	Tree t4 = t;
	EXPECT_EQ(treeInfo(t),  "1.0.0.0.4");
	EXPECT_EQ(treeInfo(t4), "1.0.0.0.4");

	EXPECT_EQ(treeInfo(t1), "0.0.0.0.1");
	EXPECT_EQ(treeInfo(t2), "0.0.0.0.2");
	EXPECT_EQ(treeInfo(t3), "1.0.0.0.3");
	EXPECT_EQ(treeInfo(t4), "1.0.0.0.4");

	t.growthTree();
	cout<<endl;

	Tree t5 = t;
	EXPECT_EQ(treeInfo(t), "1.1.0.0.5");
	EXPECT_EQ(treeInfo(t5), "1.1.0.0.5");
	t.growthTree();
	Tree t6 = t;
	EXPECT_EQ(treeInfo(t), "2.1.1.0.6");
	EXPECT_EQ(treeInfo(t6), "2.1.1.0.6");

	t.growthTree();
	Tree t7 = t;
	EXPECT_EQ(treeInfo(t), "2.2.2.0.7");
	EXPECT_EQ(treeInfo(t7), "2.2.2.0.7");
	Tree tc2 = t;
	EXPECT_EQ(treeInfo(t), "2.2.2.0.7");
	tc2.cutTree(2);
	EXPECT_EQ(treeInfo(tc2), "0.0.0.0.2");
	EXPECT_EQ(treeInfo(t), "2.2.2.0.7");
	for (int i = 0; i < 9; i++) {
		tc2.growthTree();
	}
	EXPECT_EQ(treeInfo(tc2), "3.4.7.0.9");
	Tree t0 = t;
	EXPECT_EQ(treeInfo(t), "2.2.2.0.7");
	t0.cutTree(0);
	EXPECT_EQ(treeInfo(t0), "0.0.0.0.0");
	for (int i = 0; i < 9; i++) {
		t0.growthTree();
	}
	EXPECT_EQ(treeInfo(t0), "3.4.7.0.9");
	Tree t9 = t;
	EXPECT_EQ(treeInfo(t), "2.2.2.0.7");
	EXPECT_EQ(treeInfo(t9), "2.2.2.0.7");
	//EXPECT_EQ(treeInfo(t), "3.4.7.0.9");
	//EXPECT_EQ(treeInfo(t1), "3.4.7.0.9");
}

TEST(Tree, Tree) {
	Tree t;
	EXPECT_EQ(treeInfo(t), "0.0.0.0.0");
	t.growthTree();
	EXPECT_EQ(treeInfo(t), "0.0.0.0.1");
	t.growthTree();
	t.growthTree();
	EXPECT_EQ(treeInfo(t), "1.0.0.0.3");
	t.growthTree();
	t.growthTree();
	EXPECT_EQ(treeInfo(t), "1.1.0.0.5");
	t.growthTree();
	EXPECT_EQ(treeInfo(t), "2.1.1.0.6");
	Branch* tb = t.getBranchPointer(3);
	EXPECT_EQ(branchInfo(*tb), "1.1.3.3");
	tb->growthBranch();
	EXPECT_EQ(branchInfo(*tb), "2.2.3.4");
	EXPECT_EQ(treeInfo(t), "2.2.2.0.6");
	tb->growthBranch();
	EXPECT_EQ(treeInfo(t), "2.2.4.0.6");
	EXPECT_EQ(branchInfo(*tb), "2.4.3.5");
	tb->growthBranch();
	tb->growthBranch();
	EXPECT_EQ(branchInfo(*tb), "3.9.3.7");
	EXPECT_EQ(treeInfo(t), "2.3.9.0.6");
	Branch* tb6 = t.getBranchPointer(6);
	for (int i = 0; i < 6; i++) {
		tb6->growthBranch();
	}
	EXPECT_EQ(branchInfo(*tb6), "3.6.6.6");
	EXPECT_EQ(treeInfo(t), "2.6.15.0.6");
	t.growthTree();
	EXPECT_EQ(treeInfo(t), "2.7.21.0.7");
	t.fadeTree();
	EXPECT_EQ(treeInfo(t), "2.6.15.0.6");
	t.growthTree();
	EXPECT_EQ(treeInfo(t), "2.7.21.0.7");
	t.cloneBranch(tb);
	EXPECT_EQ(treeInfo(t), "2.7.21.0.7");
	t.growthTree();
	t.growthTree();
	EXPECT_EQ(treeInfo(t), "3.9.36.0.9");
	/*cout << "c" << endl;
	Tree t2 = t;
	EXPECT_EQ(treeInfo(t), "3.14.36.0.9");
	cout << "d" << endl;
	t2.cloneBranch(tb);
	EXPECT_EQ(treeInfo(t), "3.14.36.0.9");
	cout << "e" << endl;
	EXPECT_EQ(treeInfo(t2), "3.14.56.0.9");
	cout << "f" << endl;*/

//	t.cutTree(2);
//	EXPECT_EQ(treeInfo(t), "0.0.0.0.2");
//
//	t.harvestTree(5);
//	EXPECT_EQ(treeInfo(t), "0.0.0.0.2");
//
//	t.growthTree();
//	EXPECT_EQ(treeInfo(t), "1.0.0.0.3");


	//t.harvestTree(5);
	//EXPECT_EQ(treeInfo(t), "3.14.16.0.9");
//	EXPECT_EQ(treeInfo(t), "3.14.56.0.9");
//	cout << "a" << endl;
//	Tree t2 = t;
//	EXPECT_EQ(treeInfo(t), "3.14.56.0.9");
//	cout << "b" << endl;
//	EXPECT_EQ(treeInfo(t2), "3.14.56.0.9");
//	t2.harvestTree(5);
//	EXPECT_EQ(treeInfo(t), "3.14.56.0.9");
	//EXPECT_EQ(treeInfo(t2), "3.14.16.0.9");

}

TEST(Graden, Garden) {
	//GTEST_SKIP();
	Garden g;
	EXPECT_EQ(gardenInfo(g), "0.0.0.0");
	g.plantTree();
	EXPECT_EQ(gardenInfo(g), "1.0.0.0");
	g.growthGarden();
	EXPECT_EQ(gardenInfo(g), "1.0.0.0");
	g.growthGarden();
	EXPECT_EQ(gardenInfo(g), "1.0.0.0");
	g.growthGarden();
	EXPECT_EQ(gardenInfo(g), "1.1.0.0");
	g.growthGarden();
	EXPECT_EQ(gardenInfo(g), "1.1.0.0");
	g.growthGarden();
	EXPECT_EQ(gardenInfo(g), "1.1.1.0");
	g.growthGarden();
	EXPECT_EQ(gardenInfo(g), "1.2.1.1");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
	//cout << "getFruitsTotal . getWeightsTotal . getHeight . setLength" << endl;
}

