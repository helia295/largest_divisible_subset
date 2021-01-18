all:
	g++ -std=c++11 -Wall largest_divisible_pairs.cpp -o ldp
	g++ -std=c++11 -Wall largest_divisible_NonRecursive.cpp -o nr

	
run:
	./ldp
	
try: all run
