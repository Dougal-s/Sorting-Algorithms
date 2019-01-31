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

namespace helper {

	namespace bubble {
		template <class Iterator>
		void bubble_sort(Iterator first, Iterator last, std::forward_iterator_tag) {
			bool sorted = true;
			int upper_bound = 0;
			// one iteration to find the size of the input
			for (Iterator it = first;; ++upper_bound) {
				Iterator prev = it++;
				if (it == last) {break;}
				if (*it < *prev) {
					std::swap(*it, *prev);
					sorted = false;
				}
			}
			while (!sorted) {
				sorted = true;
				Iterator it = first;
				for (int i = 0; i < upper_bound; ++i) {
					Iterator prev = it++;
					if (*it < *prev) {
						std::swap(*it, *prev);
						sorted = false;
					}
				}
				--upper_bound;
			}
		}

		template <class Iterator>
		void bubble_sort(Iterator first, Iterator last, std::random_access_iterator_tag) {
			bool sorted;
			int upper_bound = std::distance(first, last)-1;
			do {
				sorted = true;
				for (int i = 0; i < upper_bound; ++i) {
					if (first[i+1] < first[i]) {
						std::swap(first[i], first[i+1]);
						sorted = false;
					}
				}
				--upper_bound;
			} while(!sorted);
		}

		template <class Iterator, class Compare>
		void bubble_sort(Iterator first, Iterator last, Compare comp, std::forward_iterator_tag) {
			bool sorted = true;
			int upper_bound = 0;
			// one iteration to find the size of the input
			for (Iterator it = first;; ++upper_bound) {
				Iterator prev = it++;
				if (it == last) {break;}
				if (comp(*it, *prev)) {
					std::swap(*it, *prev);
					sorted = false;
				}
			}
			while (!sorted) {
				sorted = true;
				Iterator it = first;
				for (int i = 0; i < upper_bound; ++i) {
					Iterator prev = it++;
					if (comp(*it, *prev)) {
						std::swap(*it, *prev);
						sorted = false;
					}
				}
				--upper_bound;
			}
		}

		template <class Iterator, class Compare>
		void bubble_sort(Iterator first, Iterator last, Compare comp, std::random_access_iterator_tag) {
			bool sorted;
			int upper_bound = std::distance(first, last)-1;
			do {
				sorted = true;
				for (int i = 0; i < upper_bound; ++i) {
					if (comp(first[i+1], first[i])) {
						std::swap(first[i], first[i+1]);
						sorted = false;
					}
				}
				--upper_bound;
			} while(!sorted);
		}
	}
}

template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void bubble_sort(Iterator first, Iterator last) {
	helper::bubble::bubble_sort(first, last, typename std::iterator_traits<Iterator>::iterator_category());
}

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void bubble_sort(Iterator first, Iterator last, Compare comp) {
	helper::bubble::bubble_sort(first, last, comp, typename std::iterator_traits<Iterator>::iterator_category());
}
