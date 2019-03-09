#include <algorithm>

#include <map>
#include <set>
#include <vector>
#include <tuple>

#include <string>
#include <iostream>

static const std::string s_text = 
R"(Java SE 8 represents the single largest evolution of the Java language in its history.
A relatively small number of features - lambda expressions, method references, and
functional interfaces - combine to offer a programming model that fuses the objectoriented
and functional styles.Under the leadership of Brian Goetz, this fusion
has been accomplished in a way that encourages best practices - immutability,
statelessness, compositionality - while preserving "the feel of Java" - readability,
simplicity, universality.)";

class Tokenizer {
public:
	using Term = std::tuple<std::string, size_t>;

	Tokenizer(std::string const& text) : text_(text), offs_(0) {}

	static std::string getWord(std::string const& text, size_t pos) {
		size_t pos2 = pos;
		while (pos2 < text.length() && ::isalpha(text[pos2])) {
			pos2++;
		}

		return text.substr(pos, pos2 - pos);
	}

	Term next() {
		while (!finished() && !::isalpha(text_[offs_])) {
			offs_++;
		}

		size_t start = offs_;
		while (!finished() && isalpha(text_[offs_])) {
			offs_++;
		}

		std::string word(offs_ - start, 0);
		std::transform(&text_[start], &text_[offs_], word.begin(), ::tolower);
		return Term(word, start);
	}

private:
	bool finished() {
		return offs_ >= text_.length();
	}

	void static toLower(std::string &str) {
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	}

	std::string const& text_;
	size_t offs_;
};

class TextSearch {
public:
	using Positions = std::vector<size_t>;

	TextSearch(std::string const& text);

	Positions findNearest(std::set<std::string> const& words);

private:
	using Dict = std::map<std::string, Positions>;
	
	Dict dict_;

	void createDictionary(std::string const& text);
	size_t calcDist(std::vector<size_t> const& indexes, std::vector<TextSearch::Positions> const& wp);

	bool tryIncIndex(std::vector<size_t> &indexes, std::vector<TextSearch::Positions> const& wp);
	bool tryIncIndex(std::vector<size_t> &indexes, std::vector<TextSearch::Positions> const& wp, size_t idx);
};

TextSearch::TextSearch(std::string const& text) {
	createDictionary(text);
}

TextSearch::Positions TextSearch::findNearest(std::set<std::string> const& words) {
	std::vector<Positions> wp;

	for (std::string const& word : words) {
		auto it = dict_.find(word);
		if (it == dict_.end())
			return Positions();
		wp.push_back(it->second);
	}

	if (wp.size() == 1) {
		// just return the first occurance of the word
		return { wp.front().front() };
	}

	size_t opt_dist = std::numeric_limits<size_t>::max();
	
	Positions positions(wp.size(), 0);
	std::vector<size_t> indexes(wp.size(), 0);
	
	do {
		size_t dist = calcDist(indexes, wp);
		if (opt_dist > dist) {
			opt_dist = dist;
			for (size_t i = 0; i < indexes.size(); ++i) {
				positions[i] = wp[i].at(indexes[i]);
			}
		}
	} while (tryIncIndex(indexes, wp));

	return positions;
}

bool TextSearch::tryIncIndex(std::vector<size_t> &indexes, std::vector<TextSearch::Positions> const& wp) {
	return tryIncIndex(indexes, wp, 0);
}

bool TextSearch::tryIncIndex(std::vector<size_t> &indexes, std::vector<TextSearch::Positions> const& wp, size_t i) {
	if (i >= indexes.size())
		return false;

	if (indexes[i] >= wp[i].size() - 1) {
		indexes[i] = 0;
		return tryIncIndex(indexes, wp, i + 1);
	}

	indexes[i]++;
	return true;
}

size_t TextSearch::calcDist(std::vector<size_t> const& indexes, std::vector<TextSearch::Positions> const& wp) {
	size_t dist = 0;
	for (size_t i = 1; i < indexes.size(); ++i) {
		int dist_i = std::abs(
			static_cast<int>(wp[i].at(indexes[i]) - wp[i - 1].at(indexes[i - 1]))
		);
		dist += static_cast<size_t>(dist_i);
	}
	
	return dist;
}

void TextSearch::createDictionary(std::string const& text) {
	Tokenizer tokenizer(text);
	for (;;) {
		Tokenizer::Term term = tokenizer.next();

		std::string const& word = std::get<0>(term);
		if (word.empty())
			break;

		size_t const& pos = std::get<1>(term);

		auto &positions = dict_[word];
		positions.push_back(pos);
	}
}

void test_dict_search_text() {
	TextSearch textSearch(s_text);
	TextSearch::Positions positions = textSearch.findNearest({"the", "way", "that"});

	size_t dist = 0;
	for (size_t i = 1; i < positions.size(); ++i) {
		dist += std::abs((int)(positions[i] - positions[i-1]));
	}

	for (size_t p : positions) {
		std::cout << Tokenizer::getWord(s_text, p) << " ";
	}
	std::cout << "\n";

	std::cout << dist << std::endl;
}
