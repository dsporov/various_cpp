#include <vector>
#include <random> 
#include <algorithm>

#include <cassert>

void merge_sort(std::vector<int> &a);
void quick_sort(std::vector<int> &a);

void verify_is_sorted(std::vector<int> const& a) {
	for (size_t i = 1; i < a.size(); ++i) {
		assert(a[i-1] <= a[i]);
	}
}

void sort_and_verify(std::vector<int>& a) {
	merge_sort(a);
	//quick_sort(a);

	verify_is_sorted(a);
}

void test_sort() {
	std::vector<int> arr = { 1, 21, 5, 3, 2, 8, 17, 40, 6 };
	sort_and_verify(arr);

	std::vector<int> arr0 = {};
	sort_and_verify(arr0);

	std::vector<int> arr1 = {1};
	sort_and_verify(arr1);

	std::vector<int> arr_dup = { 1, 2, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2 };
	sort_and_verify(arr_dup);

	std::vector<int> arr_sorted;
	for (int i = 1; i < 12; ++i)
		arr_sorted.push_back(i);
	sort_and_verify(arr_sorted);

	std::vector<int> arr_unsorted;
	for (int i = 11; i > 0; --i)
		arr_sorted.push_back(i);
	sort_and_verify(arr_unsorted);

	std::mt19937 gen{ std::random_device()() };
	std::uniform_int_distribution<int> uid(-1000, 1000);
	std::vector<int> arr_random(100);
	std::generate(arr_random.begin(), arr_random.end(), [&uid, &gen]() -> int
		{ return uid(gen); });
	sort_and_verify(arr_random);
}
