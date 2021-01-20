
/* Part 2 - HW4: To answer TIME COMPLEXITY question:
 * 
 * The time complexity for my Dynamic Programming version of the code is
 * O(n.logn + n^2 + n). 
 * The time complexity for my Recursive version of the code is
 * O(n^n).
 * 
 * I think O(n^n) is always bigger than O(n.logn + n^2 + n) (i even plugged
 * in some random numbers and calculated them to be sure). 
 * So the time complexity of the dynamic programming code is smaller than
 * that of recursive code version.
 *  */


#include <iostream>
#include <vector>
#include <algorithm>    // sort
#include <stdexcept>


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


void checkConditions(vector<int> input) {
	
	//to check if there is any NEGATIVE argument in the input, throw exception
	for (unsigned int i = 0; i < input.size(); i++) {
		
		if (input.at(i) < 0) {
			
			throw invalid_argument("Negative arguments not allowed: " + to_string(input.at(i)));
		}
	}
	
	//to check if there is any DUPLICATE argument in the input, throw exception
	for (unsigned int i = 0; i < input.size(); i++) {
		for (unsigned int j = i + 1; j < input.size(); j++) {
			if (input.at(i) == input.at(j)) {
				throw invalid_argument("Duplicate arguments not allowed: " + to_string(input.at(i)));
			}
		}
	}
}


//DYNAMIC PROGRAMMING APPROACH
/* Time complexity: O(n.logn) + O(n^2) + O(n)
 * 
 * The idea is to find the element in the vector with which we can create the 
 * largest LDP subset (largest in size) and backtrack from that element to 
 * find THE subset. */
 
vector<int> largest_divisible_pairs(vector<int> input) {
	
	int sz = input.size();
	
	//if input vector size is 0, return empty vector
	if (input.size() == 0) { 	
		return vector<int>();
	}
	
	/* Time complexity: O(n.logn) --at best.
	 * We sort the vector in increasing order so that we only have to check 
	 * if the current element is divisible by the previous one (which is supposed
	 * to be smaller than current). */
	sort( input.begin() , input.end() ); 		
	//cout << "sorted vector: " << vec_to_string(input) << endl;
	
	int maxSize = 1; 	//to store the max possible size of the result vector
	
	/* This is where the dynamic programming happens.
	 * This vector will store the largest possible size of a largest divisible
	 * subset that includes the current element as the last element of subset */
	vector<int> currMaxSize(sz, 1);
	
	// Time complexity: O(n^2) 
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
	
	// Time complexity: O(n)
	for (int k = sz - 1; k >= 0; k--) { 	//go backward in the sorted input vector
		
		/* if the max possible size of a LD subset created with the current
		 * element k == the max possible size of a LD subset of the input 
		 * AND (current element is divisible by element at k OR curr == -1) 
		 * 
		 * Note: since the 2nd condition checks if the 2 number are divisible
		 * by each other, the code cannot push other number with the same currMaxSize
		 * value (for exp: it cannot push 24 instead of 28 in the original example 
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


int main() {
	
	vector<int> digitsVector{2, 3, 8, 14, 22, 24, 28, 44, 56, 12, 1};
	//vector<int> digitsVector{22, 1, 44, 52, 6, 39, 14, 28, 88};
	try {
		checkConditions(digitsVector);
		
		vector<int> LDPvec = largest_divisible_pairs(digitsVector);
	
		cout << "Input: " << vec_to_string(digitsVector) << endl;
		cout << "Answer: " << vec_to_string(LDPvec) << endl;
		
	} catch (invalid_argument &excpt) {
		
		cout << excpt.what() << endl;
	}
}










/* RECURSIVE APPROACH
 * This function will help find the LDP subset using recursion method.
 * 
 * Params:
 * @ vector<int> input
 * @ vector<int>& result: store the result
 * @ vector<int> currSubset: store the current possible LDP subset
 * @ vector<int>& sizeSubset: store the size of the largest divisible subset
 * 							including the element(s) before it in the sorted vector,
 * 							that the element at same index can become a part of
 * 							(by being divisible by the last element of that subset.
 * 							Value -1 means Not part of any possible LDP subset.
 * @ int startIdx: the index of the current element
 * @ int prevNum: store the previous number that was just added to currSubset 
 * */
 /*
void  FindLDPsubset(vector<int> input, vector<int>& result, vector<int> currSubset, vector<int>& sizeSubset, int startIdx, int prevNum) {
	
	//if currSubset is bigger than the old result --> make result = currSubset
	if (static_cast<int>(currSubset.size()) > static_cast<int>(result.size())) {
		
		result = currSubset;
	}
	
	for (unsigned int i = startIdx; i < input.size(); i++) {
		
		//check if the current number is divisible by prevNum (just been added to currSubset)
		//also if the size of currSubset > the size of the largest LDP subset that the current 
		//number can be a part of with some elements before it in the sorted vector.
		if (static_cast<int>(currSubset.size()) > sizeSubset.at(i) && input.at(i) % prevNum == 0) {
			
			//update that current number's sizeSubset value into the size of currSubset
			sizeSubset.at(i) = static_cast<int>(currSubset.size());
			
			//add the current number to currSubset because it could possibly form a LDP subset
			currSubset.push_back(input.at(i));
			
			
			//make a recursive call on the next number after the current one
			FindLDPsubset(input, result, currSubset, sizeSubset, i+1, input.at(i));
			
			//pop the currSubset so we can move on to form currSubset with another number
			//because the last number added might not be the correct one
			currSubset.pop_back();
		}
	}
	
}


vector<int> largest_divisible_pairs(vector<int> digitsVector) {
	
	sort( digitsVector.begin() , digitsVector.end() );
	checkConditions(digitsVector); 	
	
	vector<int> sizeSubset(digitsVector.size(), -1);
	vector<int> result;
	vector<int> currSubset;
	
	FindLDPsubset(digitsVector, result, currSubset, sizeSubset, 0, 1);
	
	return result;
}*/

