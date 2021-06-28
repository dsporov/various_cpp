#include <iostream>
#include <queue>
#include <stack>

struct Node {
	int data{ 0 };

	Node(int value) : data(value) {};

	Node* left{ nullptr };
	Node* right{ nullptr };

	void print() const {
		std::cout << data << "\n";
	}
};


void print_depth(Node* node) {
	if (node == nullptr)
		return;

	node->print();

	print_depth(node->left);
	print_depth(node->right);
}

void print_depth2(Node* root) {
	std::stack<Node*> s;
	if (root != nullptr)
		s.push(root);

	while (!s.empty()) {
		Node* node = s.top();
		node->print();

		s.pop();

		if (node->right != nullptr)
			s.push(node->right);
		if (node->left != nullptr)
			s.push(node->left);
	}
}

void print_breadth(Node* root) {
	if (root == nullptr)
		return;

	std::queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* node = q.front();
		node->print();

		q.pop();

		if (node->left != nullptr)
			q.push(node->left);
		if (node->right != nullptr)
			q.push(node->right);
	}
}

void test_dfs_bfs() {
	Node* root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->right = new Node(5);

	root->right->left = new Node(77);
	root->right->right = new Node(6);

	print_breadth(root);
	std::cout << "----\n";
	print_depth(root);
	std::cout << "----\n";
	print_depth2(root);
}
