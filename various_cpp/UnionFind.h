#pragma once

#include <vector>
#include <map>
#include <memory>

using Connection = std::pair<int, int>;

struct UnionFind {
	UnionFind(int size) {
		id_.resize(size);

		for (int i = 0; i < size; ++i) {
			id_[i] = i;
		}
	};

	virtual void unite(int p1, int p2) abstract;
	virtual bool connected(int p1, int p2) const abstract;

	void unite(Connection const& connection) {
		unite(connection.first, connection.second);
	};

	size_t getSize() const {
		return id_.size();
	}

	int parent(int i) const {
		return id_.at(i);
	}

	int& parent(int i) {
		return id_.at(i);
	}

private:
	std::vector<int> id_;
};

template<class Base>
class AddPathCompression : public Base {
public:
	AddPathCompression(int size) : Base(size) {};


private:
	virtual int root(int i) const {
		while (i != Base::parent(i)) {
			int up1 = Base::parent(i);
			int up2 = Base::parent(up1);
			const_cast<AddPathCompression*>(this)->parent(i) = up2;

			i = Base::parent(i);
		}

		return i;
	}
};


using UnionFindPtr = std::unique_ptr<UnionFind>;
