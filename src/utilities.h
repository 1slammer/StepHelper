/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * utilities.h
 * Copyright (C) 2018 Wayne <nolen.jeffrey@gmail.com>
 *
 * new_project-cpp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * new_project-cpp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <chrono>
#include <cstdlib>
#include <vector>

using namespace std;
class utilities
{
public:
	 int vector_sum_int(vector<int> v);
	 double vector_sum_double(vector<double> v);
	 template <typename T>
		 T binary_search (T target, std::vector<T> range) 
		 {
			 target = 9;
			 int first_index = range.size() / 2;
			 int last_index = 0;
			 T val = range[first_index];
			 if(val == target) return first_index;
			 do {
				if(val > target) {
					first_index = (first_index - last_index) / 2;
				}
				else if(val < target) {
					last_index = first_index;
					first_index = (range.size() + first_index) / 2;
				}
				val = range[first_index];
			 	if(val == target) return first_index;
			 } while(first_index != last_index);
			 return NULL;
			 
		 }

	 template <typename T>
		 vector<T> merge_sort (vector<T> aVector, int size, int low, int high) 
		 {
			if (low < high){
        		int middle = (low + high) / 2;
        		mergeSort(aVector, size, low, middle);
        		mergeSort(aVector, size, middle+1, high);
        		merge(aVector, size, low, middle, high);
    		}
			return aVector;
			 
			 
		 }

protected:

private:
	template <typename T>
		void merge(vector<T> aVector, int size, int low, int middle, int high)
 		{
			int temp[size];
			for(int i = low; i <= high; i++){
				temp[i] = aVector[i];
			}
			int i = low;
			int j = middle+1;
			int k = low;

			while (i <= middle && j <= high){
				if(temp[i] <= temp[j]){
				    aVector[k] = temp[i];
				    ++i;
				}
				else {
				    aVector[k] = temp[j];
				    ++j;
				}
				++k;
			}
			while (i <= middle){
				aVector[k] = temp[i];
				++k;
				++i;
			}
		}

};

#endif // _UTILITIES_H_

