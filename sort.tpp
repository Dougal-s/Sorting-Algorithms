#include <type_traits>
#include <utility>

template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
bool is_sorted(Iterator first, Iterator last) {
	for (Iterator it = first;;) {
		Iterator prev = it++;
		if (it == last) {return true;}
		if (*it < *prev) {return false;}
	}
}

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
bool is_sorted(Iterator first, Iterator last, Compare comp) {
	for (Iterator it = first;;) {
		Iterator prev = it++;
		if (it == last) {return true;}
		if (comp(*it, *prev)) {return false;}
	}
}
