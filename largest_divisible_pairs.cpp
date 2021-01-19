
/* This is the RECURSIVE version that I wrote to solve this 
 * problem.
 * 
 * There is a Non-Recursive version of this assignment in
 * another file named largest_divisible_NonRecursive.cpp. */


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


/* This function will help find the LDP subset using recursion method.
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
 * 
 * EXPLANATION with example [1, 2, 5, 6]: start at 1, currSubset.size is not > result.size, 
 * check 0 > -1 && 1 % 1==0 --> true, make sizeSubset = [0,-1,-1,-1], currSubset = [1], call
 * ^^^^ so sizeSubset.at(0) = 0 because size of LDP subset before it is 0, there's no element 
 * ^^^^ before it, and currSubset was added by the current number that we are looking at: 1 
 * recursion on the next which is 2, currSubset.size is > result.size --> make result = [1], 
 * check 1 > -1 && 2 % 1==0 --> true, make sizeSubset = [0,1,-1,-1], currSubset = [1,2], call
 * recursion on the next which is 5, currSubset.size is > result.size --> make result = [1,2],
 * check 2 > -1 && 5 % 2==0 --> false, go to check with the next 6 (now, prev is still = 2), 
 * currSubset.size is > result.size --> make result = [1,2], 
 * check 2 > -1 && 6 % 2==0 --> true, make sizeSubset = [0,1,-1,2], currSubset = [1,2,6], call
 * recursion on the next which is Nothing, currSubset.size >result.size-->make result =[1,2,6],
 * now going back to pop currSubset 3 times. */
void  FindLDPsubset(vector<int> input, vector<int>& result, vector<int> currSubset, vector<int>& sizeSubset, int startIdx, int prevNum) {
	
	//if currSubset is bigger than the old result --> make result = currSubset
	if (static_cast<int>(currSubset.size()) > static_cast<int>(result.size())) {
		
		result = currSubset;
	}
	
	for (unsigned int i = startIdx; i < input.size(); i++) {
		
		//check if the current number is divisible by prevNum (just been added to currSubset
		//also if the size of currSubset > the size of the largest LDP subset that the current 
		//number can be a part of with the elements before it in the sorted vector.
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


vector<int> largest_divisible_pairs(vector<int> digitsVector) {
	
	/* We sort the vector in increasing order so that we only have to check 
	 * if the curr element is divisible by the previous one instead of both 
	 * cases. */
	sort( digitsVector.begin() , digitsVector.end() );
	checkConditions(digitsVector); 	
	
	vector<int> sizeSubset(digitsVector.size(), -1);
	vector<int> result;
	vector<int> currSubset;
	
	FindLDPsubset(digitsVector, result, currSubset, sizeSubset, 0, 1);
	
	return result;
}


int main() {
	
	vector<int> digitsVector{2, 3, 8, 14, 22, 24, 28, 44, 56};
	//vector<int> digitsVector{22, 1, 44, 52, 6, 39, 14, 28, 88};
	
	vector<int> LDPvec = largest_divisible_pairs(digitsVector);
	
	cout << "Input: " << vec_to_string(digitsVector) << endl;
	cout << "Answer: " << vec_to_string(LDPvec) << endl;
	
}
