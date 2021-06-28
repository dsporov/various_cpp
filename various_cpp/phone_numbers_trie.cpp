#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>

#include <cassert>

namespace {

static std::unordered_map<int, std::string> digitLetters = {
	{2, "abc"},
	{3, "def"},
	{4, "ghi"},
	{5, "jkl"},
	{6, "mno"},
	{7, "pqrs"},
	{8, "tuv"},
	{9, "wxyz"}
};


struct Node {
	std::string const* origString = nullptr;
	std::unordered_map<char, Node*> next;

	bool contains(char letter) const {
		return next.find(letter) != next.end();
	}
};

Node* dictToTrie() {
	static std::unordered_set<std::string> dictionary = {
		"a",
		"flower",
		"flowers",
	};

	Node *root = new Node();
	for (std::string const& s : dictionary) {
		Node *node = root;

		for (char c : s) {
			if (!node->contains(c))
				node->next[c] = new Node();
			node = node->next[c];
		}
		node->origString = &s;
	}

	return root;
}

Node *dictTrie = dictToTrie();

std::string getWord(std::string const& digits) {
	std::queue<Node*> paths;

	paths.push(dictTrie);

	for (char digit : digits) {
		auto key = digitLetters[digit - '0'];
		std::queue<Node*> newPaths;

		while (!paths.empty()) {
			Node* node = paths.front();
			paths.pop();

			for (char letter : key) {
				if (node->contains(letter)) {
					newPaths.push(node->next[letter]);
				}
			}
		}

		std::swap(paths, newPaths);
	}

	while (!paths.empty()) {
		Node *node = paths.front();
		paths.pop();

		if (node->origString != nullptr)
			return *node->origString;
	}

	return "";
}

}

void test_phone_numbers_trie() {
	assert(getWord("3569377") == "flowers");
}
