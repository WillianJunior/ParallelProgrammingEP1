#include <iostream>
#include <list>

#include <stdlib.h>
#include <string.h>

#include <omp.h>

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

	int size = atoi(argv[1])-1;
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
	
	// get exec start time
	double exec_time = omp_get_wtime();

	generate_N(size, num_list);

	int sum = 2;

	int p = 2;
	int s = size;
	while (true) {
		#ifdef DEBUG
		std::cout << "[main] prime: " << p << std::endl;
		#endif

		prime.emplace_back(p);
		s = sieve(num_list, s, p, temp_list);
		
		#ifdef DEBUG
		std::cout << "[main] s: " << s << std::endl;
		#endif

		// Break if the returning list reaches size 0
		// This comparison is here to avoid the sum of an
		// inexistent last prime number: 'sum +=p;'
		if (s == 0)
			break;

		delete[] num_list;
		num_list = temp_list;
		p = num_list[0];
		sum +=p;
	}

	// finishes time mesuring
	exec_time = omp_get_wtime() - exec_time;

	// list output
	if (t == r_list || t == r_all) {
		for (int i : prime)
			std::cout << i << " ";
		std::cout << std::endl;
	}

	// sum output
	if (t == r_sum || t == r_all) {
		std::cout << sum << std::endl;
	}

	// time output
	if (t == r_time || t == r_all) {
		#ifndef OMMIT_TIME
		std::cout << exec_time << std::endl;
		#endif
	}

	return 0;
}

void generate_N(int size, int* &num_list) {
	for (int i=0; i<size; i++) {
		num_list[i] = 2+i;

		#ifdef DEBUG
		std::cout << "[generate_N] generated: " << num_list[i] << std::endl;
		#endif

	}
}

int sieve(int* num_list, int size, int val, int* &ret_list) {
	ret_list = new int[size];
	int j=0;
	for (int i=0; i<size; i++) {
		#ifdef DEBUG
		std::cout << "[sieve] checking: " << num_list[i] << std::endl;
		#endif

		if (num_list[i]%val == 0) {
			#ifdef DEBUG
			std::cout << "[sieve] pruning: " << num_list[i] << std::endl;
			#endif
		} else {
			ret_list[j++] = num_list[i];
		}
	}
	return j;
}

