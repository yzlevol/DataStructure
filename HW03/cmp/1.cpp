#include <iostream>
#include <string.h>
using namespace std;

const int MAX_NODES = 10;

// 定义二叉树节点
struct BiNode
{
	char data;
	int left;
	int right;
	int depth;
};

struct BinaryTree
{
	BiNode nodes[MAX_NODES];
	int nodeCount;
	int treeHeight;
	int root;

	BinaryTree()
	{
		for (int i = 0; i < MAX_NODES; i++)
		{
			nodes[i].depth = 0;
			nodes[i].data = 0;
			nodes[i].left = -1;
			nodes[i].right = -1;
		}
		treeHeight = 0;
		nodeCount = 0;
		root = -1;
	};

	void input()
	{
		cin >> nodeCount;
		for (int i = 0; i < nodeCount; i++)
		{
			char left, right;
			cin >> nodes[i].data >> left >> right;
			if (left != '-')
				nodes[i].left = left - 48;
			if (right != '-')
				nodes[i].right = right - 48;
		}
	};

	void updateDepth(const int i, const int newDepth)
	{
		nodes[i].depth = newDepth;
		if (newDepth == 1)
			root = i;
		treeHeight = (treeHeight > newDepth ? treeHeight : newDepth);
		int left = nodes[i].left;
		if (left >= 0 && left < nodeCount)
			updateDepth(left, newDepth + 1);
		int right = nodes[i].right;
		if (right >= 0 && right < nodeCount)
			updateDepth(right, newDepth + 1);
	};
};

bool isSame(const BinaryTree &tree1, const BinaryTree &tree2, int root1, int root2)
{
	if (root1 == -1 && root2 == -1)
	{
		// 如果两棵树都是空树，则它们同构
		return true;
	}

	if ((root1 == -1 && root2 != -1) || (root1 != -1 && root2 == -1))
	{
		// 如果一棵树为空，而另一棵树不为空，它们不同构
		return false;
	}

	// 获取两棵树的根节点
	BiNode node1 = tree1.nodes[root1];
	BiNode node2 = tree2.nodes[root2];

	// 比较当前节点的值
	if (node1.data != node2.data)
	{
		return false;
	}

	// 递归比较左子树和右子树
	return (isSame(tree1, tree2, node1.left, node2.left) && isSame(tree1, tree2, node1.right, node2.right)) ||
		   (isSame(tree1, tree2, node1.left, node2.right) && isSame(tree1, tree2, node1.right, node2.left));
}

int main()
{
	BinaryTree tree1, tree2;
	tree1.input();
	tree2.input();
	for (int i = 0; i < tree1.nodeCount; i++)
	{
		if (tree1.nodes[i].depth == 0)
			tree1.updateDepth(i, 1);
	}
	for (int i = 0; i < tree2.nodeCount; i++)
	{
		if (tree2.nodes[i].depth == 0)
			tree2.updateDepth(i, 1);
	}
	int result = isSame(tree1, tree2, tree1.root, tree2.root);
	if (result)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	cout << tree1.treeHeight << endl;
	cout << tree2.treeHeight << endl;
	return 0;
}
