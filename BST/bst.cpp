#include<iostream>
#include"BST.h"
int main()
{
	BinarySearchTree<int> test;
	test.insert(8);
	test.insert(6);
	test.insert(12);
	test.insert(2);
	test.insert(9);
	test.insert(10);
	test.insert(15);
	test.insert(16);
	std::cout<<"The initial Tree is:"<<std::endl;
	test.printTree();//打印初始二叉树
	
	test.remove(8);//删去根节点
	std::cout<<"After the first removing,the current Tree is:"<<std::endl;
	test.printTree();
	
	test.remove(6);//删去只有一个子节点的节点
	std::cout<<"After the second removing,the current Tree is:"<<std::endl;
	test.printTree();
	
	test.remove(16);//删去叶子节点
	std::cout<<"After the third removing,the current Tree is:"<<std::endl;
	test.printTree();
	
	test.makeEmpty();
	
	test.remove(10);//测试二叉树为空时的情况
	return 0;
	
 } 
