#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
    char data;
    int left;
    int right;
    int depth;  
};

class BiTree {
private:
    TreeNode nodes[10100];  
    int root;

public:
    BiTree() : root(-1) {}

    void input(int nodeCount) {
        int isChild[10100] = { 0 };  

        for (int i = 0; i < nodeCount; i++) {
            char data;
            string left, right;
            cin >> data >> left >> right;
            nodes[i].data = data;
            if (left != "-") {
                nodes[i].left = stoi(left);
                isChild[nodes[i].left] = 1;
            }
            else {
                nodes[i].left = -1;
            }
            if (right != "-") {
                nodes[i].right = stoi(right);
                isChild[nodes[i].right] = 1;
            }
            else {
                nodes[i].right = -1;
            }
        }

        for (int i = 0; i < nodeCount; i++) {
            if (!isChild[i]) {
                root = i;
                break;
            }
        }
    }

    int Depth(int node) {
        if (node == -1) return 0;

        int leftDepth = Depth(nodes[node].left);
        int rightDepth = Depth(nodes[node].right);

        int currentDepth = max(leftDepth, rightDepth) + 1;
        nodes[node].depth = currentDepth;  

        return currentDepth;
    }

    bool isIsomorphic(const BiTree& other, int node1, int node2) {
        if (node1 == -1 && node2 == -1) {
            return true;
        }
        if ((node1 == -1 && node2 != -1) || (node1 != -1 && node2 == -1)) {
            return false;
        }
        if (nodes[node1].data != other.nodes[node2].data) {
            return false;
        }
        return (isIsomorphic(other, nodes[node1].left, other.nodes[node2].left) &&
            isIsomorphic(other, nodes[node1].right, other.nodes[node2].right)) ||
            (isIsomorphic(other, nodes[node1].left, other.nodes[node2].right) &&
                isIsomorphic(other, nodes[node1].right, other.nodes[node2].left));
    }

    int getRoot() const {
        return root;
    }

    int getDepth(int node) const {
        return nodes[node].depth;  
    }
};

int main() {
    int N1, N2;
    cin >> N1;
    BiTree tree1, tree2;
    tree1.input(N1);
    cin >> N2;
    tree2.input(N2);

    tree1.Depth(tree1.getRoot());
    tree2.Depth(tree2.getRoot());

    bool isIsomorphic = tree1.isIsomorphic(tree2, tree1.getRoot(), tree2.getRoot());
    cout << (isIsomorphic ? "Yes" : "No") << endl;
    cout << tree1.getDepth(tree1.getRoot()) << endl;
    cout << tree2.getDepth(tree2.getRoot()) << endl;

    return 0;
}
