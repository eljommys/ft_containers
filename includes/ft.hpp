#pragma once

#include <cstddef>
#include <type_traits>
#include <algorithm>
#include <memory>
#include <iterator>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <iterator>

#include <stdio.h>

#include "nullptr.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "conditional.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include "random_access_iterator.hpp"
#include "pair.hpp"
#include "bidirectional_iterator_traits.hpp"
#include "bidirectional_iterator.hpp"
#include "less_more.hpp"
#include "tree_iterator.hpp"
#include "tree.hpp"

namespace ft {
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	struct contiguous_iterator_tag: public random_access_iterator_tag { };
};
