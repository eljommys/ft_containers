/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:12:25 by jserrano          #+#    #+#             */
/*   Updated: 2021/10/21 17:49:17 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
template <typename T>
struct v_list
{
	struct v_list	*prev;
	T				val;
	struct v_list	*next;
};

template <typename T>
class	vector{

	private:
		struct v_list *vector;
		int n;

	public:
		vector(): vector(NULL), n(0) {}
		vector(unsigned int n):vector(new T[n]), n(n){}
		vector(vector &obj):n(obj.size()){

			this->vector = new T[this->n];

			for (int i = 0; i < this->n; i++)
				this->vector[i] = obj[i];
		}
		~vector(){
			if (this->vector)
				delete[] this->vector;
		}

		int size(){
			return this->n;
		}

		class OutOfLimits: public std::exception{
			public:
				const char	*what() const throw(){
					return "Error: Out of limits";
				}
		};

		vector	&operator=(vector &arr){

			this->n = arr.size();

			if (this->vector)
				delete[] this->vector;
			this->vector = new T[this->n];

			for (int i = 0; i < this->n; i++)
				this->vector[i] = arr[i];

			return *this;
		}

		T	&operator[](int i) const{

			try{
				if (i < 0 || i >= this->n)
					throw OutOfLimits();
			}catch(std::exception &e){
				std::cout << std::endl << e.what() << std::endl;
			}

			return this->vector[i];
		}
};