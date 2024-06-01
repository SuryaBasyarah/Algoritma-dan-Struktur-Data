#include <iostream>
#include <vector>

using namespace std;

// Node Struct
struct Node {
    int key;
    vector<Node*> children;

    Node(int data) : key(data) {}
};

// Tree Struct
struct Tree {
    Node* root;

    Tree(int data) : root(new Node(data)) {}

    // Add child to a parent node
    void addChild(Node* parent, int childData) {
        Node* child = new Node(childData);
        parent->children.push_back(child);
    }

    // Print children of a node
    void printChildren(Node* node) {
        cout << "Children of Node " << node->key << ": ";
        for (const auto& child : node->children) {
            cout << child->key << " ";
        }
        cout << endl;
    }
};

int main() {
    // Create a tree with root node 1
    Tree myTree(1);

    // Add children to the root
    myTree.addChild(myTree.root, 2);
    myTree.addChild(myTree.root, 3);
    myTree.addChild(myTree.root, 4);

    // Add children to node 2
    myTree.addChild(myTree.root->children[0], 5);
    myTree.addChild(myTree.root->children[0], 6);

    // Add children to node 3
    myTree.addChild(myTree.root->children[1], 7);

    // Print children of the root
    myTree.printChildren(myTree.root);

    // Print children of node 2
    myTree.printChildren(myTree.root->children[0]);

    // Print children of node 3
    myTree.printChildren(myTree.root->children[1]);

    return 0;
}