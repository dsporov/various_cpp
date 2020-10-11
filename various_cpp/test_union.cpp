#include <cassert>

#include "UnionFind.h"

UnionFindPtr get_quick_union(int size);
UnionFindPtr get_weighted_union(int size);
UnionFindPtr get_quick_union_with_path_compressoin(int size);
UnionFindPtr get_weighted_union_with_path_compressoin(int size);

static const int UF_SIZE = 5;

void test_union(UnionFindPtr unionFind) {
	assert(!unionFind->connected(0, 2));
	assert(!unionFind->connected(1, 3));

	unionFind->unite(1, 2);
	assert(unionFind->connected(1, 2));
	assert(!unionFind->connected(1, 3));

	unionFind->unite(0, 3);
	assert(unionFind->connected(0, 3));
	assert(!unionFind->connected(0, 1));

	unionFind->unite(0, 1);
	assert(unionFind->connected(3, 2));
	assert(unionFind->connected(0, 1));

	unionFind->unite(0, 4);
	assert(unionFind->connected(2, 4));
}

void test_union() {
	test_union(get_quick_union(UF_SIZE));
	test_union(get_weighted_union(UF_SIZE));
	test_union(get_quick_union_with_path_compressoin(UF_SIZE));
	test_union(get_weighted_union_with_path_compressoin(UF_SIZE));
}
