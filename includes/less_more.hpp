namespace ft
{
	template < typename T >
	struct less : std::binary_function<T, T, bool> {
		bool operator()( const T & lhs, const T & rhs ) const {
			return lhs < rhs ;
		}
	};

	template< typename value_type >
	bool less_than( const value_type & lhs , const value_type & rhs ) {
		return lhs < rhs ;
	}

	template< typename value_type >
	bool more_than( const value_type & lhs , const value_type & rhs ) {
		return lhs > rhs ;
	}

}
