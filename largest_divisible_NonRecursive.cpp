
#include <iostream>
#include <vector>
#include <algorithm>    // sort


using namespace std;


string vec_to_string(vector<int> v) {
	
	string vecString = "[";
	
	for (unsigned int i = 0; i < v.size()-1; ++i) {
		//to_string() turns int into string -- from <string>
		vecString += to_string(v.at(i)) + ", ";
	}
	
	vecString += to_string(v.at(v.size()-1)) + "]";
	
	return vecString;
	
}


//NON-RECURSIVE APPROACH
/* The idea is to find the element in the vector with which we can create the 
 * largest LDP subset (largest in size) and backtrack from that element to 
 * find THE subset. */
 
vector<int> largest_divisible_pairs(vector<int> input) {
	
	int sz = input.size();
	
	//if input vector size is 0, return empty vector
	if (input.size() == 0) { 	
		return vector<int>();
	}
	
	/* We sort the vector in increasing order so that we only have to check 
	 * if the curr element is divisible by the previous one instead of both 
	 * cases. */
	sort( input.begin() , input.end() ); 	
	//cout << "sorted vector: " << vec_to_string(input) << endl;
	
	int maxSize = 1; 	//to store the max possible size of the result vector
	
	/* This vector will store the largest possible size of a largest divisible
	 * subset that includes the current element while looping */
	vector<int> currMaxSize(sz, 1);
	
	for (int i = 1; i < sz; i++) { 		//loop from element 1 to sz
		for (int j = 0; j < i; j++) { 	//loop from element 0 to sz-1
			
			/* if element at i is divisible by element at j and this can 
			 * increase the size of the possible largest divisible subset
			 * (since size of subset including element i < size of subset
			 * including both j and i) */
			if (input.at(i) % input.at(j)==0 && currMaxSize.at(j) + 1 > currMaxSize.at(i)) {
				
				currMaxSize.at(i) = currMaxSize.at(j) + 1;
				
				if (maxSize < currMaxSize.at(i)) {
					maxSize = currMaxSize.at(i);
				}
			}
		}
	}
	
	//cout << "size vector: " << vec_to_string(currMaxSize) << endl;
	//create a result vector and push values to it
	vector<int> result;
	int curr = -1;
	
	for (int k = sz - 1; k >= 0; k--) { 	//go backward in the size vector
		
		/* if the max possible size of a LD subset created with the current
		 * element k == the max possible size of a LD subset of the input 
		 * AND (current element is divisible by element at k OR curr == -1) 
		 * 
		 * Note: since the 2nd condition checks if the 2 number are divisible
		 * by each other, the code cannot push other number with the same currMaxSize
		 * value (ex: it cannot push 24 instead of 28 in the original example 
		 * because 56 is not divisible by 24) */
		if (currMaxSize.at(k) == maxSize && (curr % input.at(k) == 0 || curr == -1)) {
			
			//push the current element at k to result
			result.push_back(input.at(k));
			
			//decrement maxSize because we just added 1 element to result so now
			//we need to find the element with the next most currMaxSize value
			maxSize--;
			
			//assign the curr value to input element at k to continue our search
			curr = input.at(k);
		}
	}
	
	return result;
}


void checkConditions(vector<int> input) {
	
	//to check if there is any NEGATIVE argument, throw exception
	for (unsigned int i = 0; i < input.size(); i++) {
		
		if (input.at(i) < 0) {
			
			throw invalid_argument("Negative arguments not allowed!!!");
		}
	}
	
	//to check if there is any DUPLICATE argument, throw exception
	for (unsigned int i = 0; i < input.size(); i++) {
		for (unsigned int j = i + 1; j < input.size(); j++) {
			if (input.at(i) == input.at(j)) {
				throw invalid_argument("Duplicate arguments not allowed: " + to_string(input.at(i)));
			}
		}
	}
}


int main() {
	
	//vector<int> digitsVector{2, 7, 8, 14, 22, 24, 28, 44, 56};
	vector<int> digitsVector{2, 1, 4, 5, 6, 4};
	checkConditions(digitsVector);
	
	vector<int> LDPvec = largest_divisible_pairs(digitsVector);
	
	cout << "Input: " << vec_to_string(digitsVector) << endl;
	cout << "Answer: " << vec_to_string(LDPvec) << endl;
	
}
