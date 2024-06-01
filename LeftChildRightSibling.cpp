#include <iostream>
using namespace std;

struct Node
{
	int data;
	struct Node *next;
	struct Node *child;
};

// Creating new Node
Node* newNode(int data)
{
	Node *newNode = new Node;
	newNode->next = newNode->child = NULL;
	newNode->data = data;
	return newNode;
}

// Adds a sibling to a list with starting with n
Node *addSibling(Node *n, int data)
{
	if (n == NULL)
		return NULL;

	while (n->next)
		n = n->next;

	return (n->next = newNode(data));
}

// Add child Node to a Node
Node *addChild(Node * n, int data)
{
	if (n == NULL)
		return NULL;

	// Check if child list is not empty.
	if (n->child)
		return addSibling(n->child, data);
	else
		return (n->child = newNode(data));
}

// Traverses tree in depth first order
void traverseTree(Node * root)
{
	if (root == NULL)
		return;

	while (root)
	{
		cout << " " << root->data;
		if (root->child)
			traverseTree(root->child);
		root = root->next;
	}
}

//Driver code

int main()
{
	/* Let us create below tree
	*	   10
	*	 / / \ \
	*   2 3	  4 5
	*		  | / | \
	*		  6 7 8 9 */

	// Left child right sibling
	/* 10
	* |
	* 2 -> 3 -> 4 -> 5
	*			 | |
	*			 6 7 -> 8 -> 9 */
	Node *root = newNode(10);
	Node *n1 = addChild(root, 2);
	Node *n2 = addChild(root, 3);
	Node *n3 = addChild(root, 4);
	Node *n4 = addChild(n3, 6);
	Node *n5 = addChild(root, 5);
	Node *n6 = addChild(n5, 7);
	Node *n7 = addChild(n5, 8);
	Node *n8 = addChild(n5, 9);
	traverseTree(root);
	return 0;
}