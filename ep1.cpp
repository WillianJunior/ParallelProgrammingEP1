#include <iostream>
#include <list>

#include <stdlib.h>
#include <string.h>

void generate_N(int size, int* &list);
int sieve(int* list, int size, int val, int* &ret_list);

enum run_type {
	r_list, r_time, r_sum, r_all
};

// sieve of eratosthenes implementation
int main(int argc, char **argv) {
	
	// get input arguments
	if (argc != 4) {
		std::cout << "usage: ./ep1 {size} {list|time|sum|all} {threads}" << std::endl;
		return 0;
	}

	int size = atoi(argv[1]);
	char* c_type = argv[2];
	run_type t;

	if (strcmp(c_type, "list") == 0)
		t = r_list;
	else if (strcmp(c_type, "time") == 0)
		t = r_time;
	else if (strcmp(c_type, "sum") == 0)
		t = r_sum;
	else if (strcmp(c_type, "all") == 0)
		t = r_all;
	else {
		std::cout << "usage: ./ep1 {size} {list|time|sum|all} {threads}" << std::endl;
		return 0;	
	}

	int threads = atoi(argv[3]);

	int* num_list = new int[size];
	std::list<int> prime;
	int* temp_list;

	generate_N(size, num_list);

	int p = 2;
	int s = size;
	while (s > 0) {
		std::cout << "[main] prime: " << p << std::endl;
		prime.emplace_back(p);
		s = sieve(num_list, s, p, temp_list);
		std::cout << "[main] s: " << s << std::endl;
		delete[] num_list;
		num_list = temp_list;
		p = num_list[0];
	}

	for (int i : prime)
		std::cout << i << std::endl;

	return 0;
}

void generate_N(int size, int* &num_list) {
	for (int i=0; i<size; i++) {
		num_list[i] = 2+i;
		std::cout << "[generate_N] generated: " << num_list[i] << std::endl;
	}
}

int sieve(int* num_list, int size, int val, int* &ret_list) {
	ret_list = new int[size];
	int j=0;
	for (int i=0; i<size; i++) {
		std::cout << "[sieve] checking: " << num_list[i] << std::endl;
		if (num_list[i]%val == 0) {
			std::cout << "[sieve] pruning: " << num_list[i] << std::endl;
		} else {
			ret_list[j++] = num_list[i];
		}
	}
	return j;
}

