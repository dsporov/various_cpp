#include "UnionFind.h"

class WightedQuickUnion : public UnionFind {
public:
	WightedQuickUnion(int size)
		: UnionFind(size)
	{
		sizes_.resize(size);
		for (int i = 0; i < size; ++i)
			sizes_[i] = 1;
	};

	virtual void unite(int p1, int p2) override {
		int idx1 = root(p1);
		int idx2 = root(p2);

		if (idx1 == idx2)
			return;

		int childIdx = idx1;
		int parentIdx = idx2;

		if (size(childIdx) > size(parentIdx)) {
			std::swap(childIdx, parentIdx);
		}

		parent(childIdx) = parentIdx;
		size(parentIdx) += size(childIdx);
	}

	virtual bool connected(int p1, int p2) const override {
		return root(p1) == root(p2);
	}

	int& size(int i) {
		return sizes_[i];
	}
	int size(int i) const {
		return sizes_[i];
	}

private:
	std::vector<int> sizes_;

	int root(int i) const {
		while (i != parent(i)) {
			i = parent(i);
		}

		return i;
	}
};

using WightedQuickUnionWithPathCompression = AddPathCompression<WightedQuickUnion>;


UnionFindPtr get_weighted_union(int size) {
	return UnionFindPtr(new WightedQuickUnion(size));
}

UnionFindPtr get_weighted_union_with_path_compressoin(int size) {
	return UnionFindPtr(new WightedQuickUnionWithPathCompression(size));
}
