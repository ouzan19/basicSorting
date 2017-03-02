/*!
*	template implementation of basic sorting algorithms, namely Quick Sort, Bucket Sort, Shell Sort
*/
#include <iostream>
#include <vector>
#include<fstream>
#include <list>
#include <time.h>
#include <algorithm>

using namespace std;

//! median function
template <typename Iterator> Iterator medianT(Iterator a, Iterator b, Iterator c) { 

	if (*a > *b){
		if (*b > *c)
			return b;
		else if (*a > *c)
			return c;
		else
			return a;
	}
	else {
		if (*a > *c)
			return a;
		else if (*b > *c)
			return c;
		else
			return b;
	}
}

//! partition of quick sort
template <typename Iterator> int partitionT(Iterator begin, Iterator end, int p, int q){

	Iterator x = medianT(begin + p, begin + q, begin + ((p + q) / 2));		// find median of the first,middle and the last element

	auto med = *x;
	auto tmp = *x;
	*x = *(begin + p);
	*(begin + p) = tmp;
	int i = p;
	for (int j = p + 1; j <= q; j++)
	{
		if (*(begin + j) <= med)					// perform classic partition 
		{
			i++;
			tmp = *(begin + i);
			*(begin + i) = *(begin + j);
			*(begin + j) = tmp;

		}
	}

	tmp = *(begin + i);
	*(begin + i) = *(begin + p);
	*(begin + p) = tmp;
	return i;

}

//! main quick sort
template <typename Iterator> void quickSortT(Iterator begin, Iterator end, int p, int r){

	if ( p >= r) return;
	int q = partitionT(begin, end, p, r);
	quickSortT(begin, end, p, q - 1);
	quickSortT(begin, end, q +1, r);
}

//! quick sort
template <typename Iterator> void quickSortT(Iterator begin, Iterator end){ quickSortT(begin, end, 0, end - begin - 1); }

//! radix sort which works with only integers
void radixSort(vector<int> &list, int size) {
	int i, m = list[0], exp = 1;
	vector<int> output;
	for (i = 1; i < size; i++) //find max element of the array
	{
		if (list[i] > m)
			m = list[i];
	}
	for (int i = 0; i < size; i++) //set the out put as all 0
		output.push_back(0);
	while (m / exp > 0) // until the most significant digit is reached, it itaretes
	{
		vector<int> temp;
		for (int i = 0; i < 10; i++)		 //C
			temp.push_back(0); 		 		 //o
											//u
		for (int i = 0; i < size; i++)    	 //n
			temp[(list[i] / exp) % 10]++; 	 //t
											//
		for (int i = 1; i < 10; i++)    	 //s
			temp[i] += temp[i - 1]; 		 //o
											 //r
		for (int i = size - 1; i >= 0; i--)  //t
			output[--temp[(list[i] / exp) % 10]] = list[i];
		list = output;
		exp *= 10; // for passing to the next digit, exp should be multiplied by 10
	}
}

//! shell sort
template <typename Iterator> void shellSortT(Iterator begin, Iterator end) {

	int n = end - begin;
	int h = 1;
	while (h < (n / 2))
		h = 2 * h + 1; //set the h value
	while (h >= 1) {
		for (int i = h; i < n; i++) // until all shells are done
		{
			for (int j = i; j >= h && *(begin + j) < *(begin + j - h); j = j - h) { //insertion sort within a shell
				auto temp = *(begin + j);
				*(begin + j) = *(begin + j - h);
				*(begin + j - h) = temp;
			}
		}
		h = h / 2; // iterate shell
	}
}

//! bucket sort
template <typename Iterator> void bucketSortT(Iterator begin, Iterator end) {

	int size = end - begin;
	auto max = *begin;
	auto min = *begin;
	for (int i = 1; i < size; i++) {  // find max and min values
		if ( *(begin+i) > max)
			max = *(begin + i);
		else if (*(begin + i) < min)
			min = *(begin + i);
	}
	int b = size / 5; 	// 5 element per bucket
	int mod = ((max - min) / b) + 1; // to avoid very much empty bucket, not start the 0, but start the min	

	vector<list<std::iterator_traits<Iterator>::value_type> > lists;
	list<std::iterator_traits<Iterator>::value_type>::iterator it;
	list<std::iterator_traits<Iterator>::value_type>::iterator son;
	for (int i = 0; i < b; i++) {		// create buckets
		list<std::iterator_traits<Iterator>::value_type> temp;
		lists.push_back(temp);
	}
	for (int i = 0; i < size; i++) {
		int bucket = (*(begin + i) - min) / mod;	// for each element, find in which bucket it place 
		it = lists[bucket].begin();
		son = lists[bucket].end();
		while (it != son && (*it) <= *(begin + i))  // and put the correct place in the bucket with insertion sort
			it++;
		lists[bucket].insert(it, *(begin + i));
	}

	for (int i = 0, j = 0; i < b; i++) {		//after filling the buckets, put all the element in the resulting array
		son = lists[i].end();
		for (it = lists[i].begin(); it != son; it++)
			*(begin + j++) = *it;
	}
}

int main(int argc, char * argv[]) {
	

	srand(time(NULL));
	
	vector<float> array;
	int size = 20;
	for (int i = 0; i < size; i++){
		array.push_back(rand() % 100 / 100.);
	}

	for (int i = 0; i < size; i++)
		cout << array[i] << endl;

	cout << "---------------" << endl;

	quickSortT(array.begin(), array.end());
	//bucketSortT(array.begin(), array.end());
	//shellSortT(array.begin(), array.end());
	
	for (int i = 0; i < size; i++)
		cout << array[i] << endl;

	getchar();
	return 5;
}

