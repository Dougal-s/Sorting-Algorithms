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

	namespace cocktail_shaker {
		template <class Iterator>
		void cocktail_shaker_sort(Iterator first, Iterator last, std::bidirectional_iterator_tag) {
			bool sorted = true;
			int size = 0;
			Iterator it = first;
			// one iteration to find the size of the input
			for (;;++size) {
				Iterator prev = it++;
				if (it == last) {break;}
				if (*it < *prev) {
					std::swap(*it, *prev);
					sorted = false;
				}
			}
			--it;

			while(!sorted) {
				sorted = true;
				for (int i = 0; i < size; ++i) {
					Iterator prev = it--;
					if (*prev < *it) {
						std::swap(*it, *prev);
						sorted = false;
					}
				}
				if (sorted) {return;}
				sorted = true;
				--size;
				for (int i = 0; i < size; ++i) {
					Iterator prev = it++;
					if (*it < *prev) {
						std::swap(*it, *prev);
						sorted = false;
					}
				}
				--size;
			}
		}

		template <class Iterator>
		void cocktail_shaker_sort(Iterator first, Iterator last, std::random_access_iterator_tag) {
			bool sorted;
			int lower_bound = 0;
			int upper_bound = std::distance(first, last)-1;
			do {
				sorted = true;
				for (int i = lower_bound; i < upper_bound; ++i) {
					if (first[i+1] < first[i]) {
						std::swap(first[i], first[i+1]);
						sorted = false;
					}
				}
				--upper_bound;
				if (sorted) {return;}
				sorted = true;
				for (int i = upper_bound; i > lower_bound; --i) {
					if (first[i] < first[i-1]) {
						std::swap(first[i-1], first[i]);
						sorted = false;
					}
				}
				++lower_bound;
			} while(!sorted);
		}

		template <class Iterator, class Compare>
		void cocktail_shaker_sort(Iterator first, Iterator last, Compare comp, std::bidirectional_iterator_tag) {
			bool sorted = true;
			int size = 0;
			Iterator it = first;
			// one iteration to find the size of the input
			for (;;++size) {
				Iterator prev = it++;
				if (it == last) {break;}
				if (comp(*it, *prev)) {
					std::swap(*it, *prev);
					sorted = false;
				}
			}
			--it;

			while(!sorted) {
				sorted = true;
				for (int i = 0; i < size; ++i) {
					Iterator prev = it--;
					if (comp(*prev, *it)) {
						std::swap(*it, *prev);
						sorted = false;
					}
				}
				if (sorted) {return;}
				sorted = true;
				--size;
				for (int i = 0; i < size; ++i) {
					Iterator prev = it++;
					if (comp(*it, *prev)) {
						std::swap(*it, *prev);
						sorted = false;
					}
				}
				--size;
			}
		}

		template <class Iterator, class Compare>
		void cocktail_shaker_sort(Iterator first, Iterator last, Compare comp, std::random_access_iterator_tag) {
			bool sorted;
			int lower_bound = 0;
			int upper_bound = std::distance(first, last)-1;
			do {
				sorted = true;
				for (int i = lower_bound; i < upper_bound; ++i) {
					if (comp(first[i+1], first[i])) {
						std::swap(first[i], first[i+1]);
						sorted = false;
					}
				}
				--upper_bound;
				if (sorted) {return;}
				sorted = true;
				for (int i = upper_bound; i > lower_bound; --i) {
					if (comp(first[i], first[i-1])) {
						std::swap(first[i-1], first[i]);
						sorted = false;
					}
				}
				++lower_bound;
			} while(!sorted);
		}
	}

	namespace comb {
		constexpr float shrink_factor = 1.3f;

		template <class Iterator>
		bool bubble_sort(Iterator first, Iterator last, int gap, int size) {
			bool sorted = true;
			for (int i = 0; i+gap < size; ++i) {
				if (first[i+gap] < first[i]) {
					std::swap(first[i], first[i+gap]);
					sorted = false;
				}
			}
			return sorted;
		}

		template <class Iterator, class Compare>
		bool bubble_sort(Iterator first, Iterator last, Compare comp, int gap, int size) {
			bool sorted = true;
			for (int i = 0; i+gap < size; ++i) {
				if (comp(first[i+gap], first[i])) {
					std::swap(first[i], first[i+gap]);
					sorted = false;
				}
			}
			return sorted;
		}

		template <class Iterator>
		void comb_sort(Iterator first, Iterator last, std::random_access_iterator_tag) {
			int size = std::distance(first, last);
			int gap_size = size;
			do {
				gap_size /= shrink_factor;
				bubble_sort(first, last, gap_size, size);
			} while (gap_size > 1);
			while(!bubble_sort(first, last, 1, size)) {}
		}

		template <class Iterator, class Compare>
		void comb_sort(Iterator first, Iterator last, Compare comp, std::random_access_iterator_tag) {
			int size = std::distance(first, last);
			int gap_size = size;
			do {
				gap_size /= shrink_factor;
				bubble_sort(first, last, comp, gap_size, size);
			} while (gap_size > 1);
			while(!bubble_sort(first, last, comp, 1, size)) {}
		}
	}

	namespace gnome {
		template <class Iterator>
		void gnome_sort(Iterator first, Iterator last, std::bidirectional_iterator_tag) {
			for (Iterator it = first; it != last; ++it) {
				for (Iterator sortedIt = it; sortedIt != first;) {
					Iterator element = sortedIt--;
					if (!(*element < *sortedIt)) {break;}
					std::swap(*element, *sortedIt);
				}
			}
		}

		template <class Iterator, class Compare>
		void gnome_sort(Iterator first, Iterator last, Compare comp, std::bidirectional_iterator_tag) {
			for (Iterator it = first; it != last; ++it) {
				for (Iterator sortedIt = it; sortedIt != first;) {
					Iterator element = sortedIt--;
					if (!comp(*element, *sortedIt)) {break;}
					std::swap(*element, *sortedIt);
				}
			}
		}
	}

	namespace shell {
		template <class Iterator>
		void gnome_sort(Iterator first, int offset, int gap) {
			for (int i = offset; i >= gap && first[i] < first[i-gap]; i -= gap) {
				std::swap(first[i], first[i-gap]);
			}
		}

		template <class Iterator, class Compare>
		void gnome_sort(Iterator first, int offset, int gap, Compare comp) {
			for (int i = offset; i >= gap && comp(first[i], first[i-gap]); i -= gap) {
				std::swap(first[i], first[i-gap]);
			}
		}

		template <class Iterator>
		void shell_sort(Iterator first, Iterator last, std::random_access_iterator_tag) {
			int size = std::distance(first, last);

			int k = logf((5.f*size+4.f)/9.f)/logf(2.25f);
			for (float gap = 1.8f*powf(2.25f, k)-0.8f; gap > 0.0f; gap = (gap-1.f)/2.25f) {
				for (int j = std::ceil(gap); j < size; ++j) {
					gnome_sort(first, j, std::ceil(gap));
				}
			}
		}

		template <class Iterator, class Compare>
		void shell_sort(Iterator first, Iterator last, Compare comp, std::random_access_iterator_tag) {
			int size = std::distance(first, last);

			int k = logf((5.f*size+4.f)/9.f)/logf(2.25f);
			for (float gap = std::ceil(1.8f*powf(2.25f, k)-0.8f); gap > 0.0f; gap = (gap-1.f)/2.25f) {
				for (int j = gap; j < size; ++j) {
					gnome_sort(first, j, gap, comp);
				}
			}
		}
	}

	namespace selection {
		template <class Iterator>
		void selection_sort(Iterator first, Iterator last, std::forward_iterator_tag) {
			for (Iterator it = first; it != last; ++it) {
				Iterator minElem = it;
				for (Iterator it2 = it; it2 != last; ++it2) {
					if (*it2 < *minElem) {
						minElem = it2;
					}
				}
				std::swap(*minElem, *it);
			}
		}

		template <class Iterator, class Compare>
		void selection_sort(Iterator first, Iterator last, Compare comp, std::forward_iterator_tag) {
			for (Iterator it = first; it != last; ++it) {
				Iterator minElem = it;
				for (Iterator it2 = it; it2 != last; ++it2) {
					if (comp(*it2, *minElem)) {
						minElem = it2;
					}
				}
				std::swap(*minElem, *it);
			}
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


template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void cocktail_shaker_sort(Iterator first, Iterator last) {
	helper::cocktail_shaker::cocktail_shaker_sort(first, last, typename std::iterator_traits<Iterator>::iterator_category());
}

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void cocktail_shaker_sort(Iterator first, Iterator last, Compare comp) {
	helper::cocktail_shaker::cocktail_shaker_sort(first, last, comp, typename std::iterator_traits<Iterator>::iterator_category());
}


template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void comb_sort(Iterator first, Iterator last) {
	helper::comb::comb_sort(first, last, typename std::iterator_traits<Iterator>::iterator_category());
}

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void comb_sort(Iterator first, Iterator last, Compare comp) {
	helper::comb::comb_sort(first, last, comp, typename std::iterator_traits<Iterator>::iterator_category());
}

template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void gnome_sort(Iterator first, Iterator last) {
	helper::gnome::gnome_sort(first, last, typename std::iterator_traits<Iterator>::iterator_category());
}

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void gnome_sort(Iterator first, Iterator last, Compare comp) {
	helper::gnome::gnome_sort(first, last, comp, typename std::iterator_traits<Iterator>::iterator_category());
}


template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void shell_sort(Iterator first, Iterator last) {
	helper::shell::shell_sort(first, last, typename std::iterator_traits<Iterator>::iterator_category());
}

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void shell_sort(Iterator first, Iterator last, Compare comp) {
	helper::shell::shell_sort(first, last, comp, typename std::iterator_traits<Iterator>::iterator_category());
}



template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void selection_sort(Iterator first, Iterator last) {
	helper::selection::selection_sort(first, last, typename std::iterator_traits<Iterator>::iterator_category());
}

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void selection_sort(Iterator first, Iterator last, Compare comp) {
	helper::selection::selection_sort(first, last, comp, typename std::iterator_traits<Iterator>::iterator_category());
}
