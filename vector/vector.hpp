/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:12:25 by jserrano          #+#    #+#             */
/*   Updated: 2021/10/21 17:27:29 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T>
class	Array{

	private:
		T *array;
		int n;

	public:
		Array(): array(NULL), n(0) {}
		Array(unsigned int n):array(new T[n]), n(n){}
		Array(Array &obj):n(obj.size()){

			this->array = new T[this->n];

			for (int i = 0; i < this->n; i++)
				this->array[i] = obj[i];
		}
		~Array(){
			if (this->array)
				delete[] this->array;
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

		Array	&operator=(Array &arr){

			this->n = arr.size();

			if (this->array)
				delete[] this->array;
			this->array = new T[this->n];

			for (int i = 0; i < this->n; i++)
				this->array[i] = arr[i];

			return *this;
		}

		T	&operator[](int i) const{

			try{
				if (i < 0 || i >= this->n)
					throw OutOfLimits();
			}catch(std::exception &e){
				std::cout << std::endl << e.what() << std::endl;
			}

			return this->array[i];
		}
};