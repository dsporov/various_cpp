#include "UnionFind.h"

class QuickUnion : public UnionFind {
public:
	QuickUnion(int size) : UnionFind(size) {};

	using UnionFind::unite;

	virtual void unite(int p1, int p2) override {
		int idx1 = root(p1);
		int idx2 = root(p2);

		parent(idx1) = idx2;
	}

	virtual bool connected(int p1, int p2) const override {
		return root(p1) == root(p2);
	}


private:
	virtual int root(int i) const {
		while (i != parent(i)) {
			i = parent(i);
		}

		return i;
	}
};


using QuickUnionWithPathCompression = AddPathCompression<QuickUnion>;


static const int UF_SIZE = 10;
Connection union_find_connections[] = {
	{4, 3},
	{3, 8},
	{6, 5},
	{9, 4},
	{2, 1},
	{8, 9},
	{5, 0},
	{7, 2},
	{6, 1},
	{1, 0},
	{6, 7}
};

UnionFindPtr get_quick_union(int size) {
	return UnionFindPtr(new QuickUnion(size));
}

UnionFindPtr get_quick_union_with_path_compressoin(int size) {
	return UnionFindPtr(new QuickUnionWithPathCompression(size));
}
