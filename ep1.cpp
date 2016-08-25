#include <iostream>

#include <stdlib.h>
#include <string.h>

#include <omp.h>

void generate_N(int size, int* &list);
void sieve(int* &list, int size, int val, int threads);

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
	
	// get exec start time
	double exec_time = omp_get_wtime();

	generate_N(size, num_list);

	#ifdef DEBUG
	double t1 = omp_get_wtime() - exec_time;
	#pragma omp master
	#pragma omp critical
	std::cout << "[profile] generate time: " << t << std::endl;
	#endif

	// set all non-prime numbers the num_list tag 1
	for (int p=2; p<size; p++) {	
		if (num_list[p] == 0) {
			#ifdef DEBUG
			#pragma omp critical
			std::cout << "[main:" << omp_get_thread_num() << "] checking: " << p << std::endl;
			#endif
			sieve(num_list, size, p, threads);
		}
	}

	#ifdef DEBUG
	double t2 = omp_get_wtime() - exec_time - t1;
	#pragma omp master
	#pragma omp critical
	std::cout << "[profile] sieve time: " << t2 << std::endl;
	#endif

	// calculate the sum and get all prime numbers
	int* primes_list = new int[size];
	int last_prime = 0;
	int sum = 0;
	for (int p=2; p<size; p++) {
		if (num_list[p] == 0) {
			primes_list[last_prime++] = p;
			sum += p;
		}
	}

	#ifdef DEBUG
	double t3 = omp_get_wtime() - exec_time - t2 - t1;
	#pragma omp master
	#pragma omp critical
	std::cout << "[profile] sum time: " << t3 << std::endl;
	#endif

	// finishes time mesuring
	exec_time = omp_get_wtime() - exec_time;

	// list output
	if (t == r_list || t == r_all) {
		for (int i=0; i<last_prime; i++)
			std::cout << primes_list[i] << " ";
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
		num_list[i] = 0;

		#ifdef DEBUG
		#pragma omp critical
		std::cout << "[generate_N:" << omp_get_thread_num() << "] generated: " << num_list[i] << std::endl;
		#endif

	}
}

void sieve(int* &num_list, int size, int val, int threads) {
	
	int j=0;
	for (int i=val+1; i<size; i++) {
		#ifdef DEBUG
		#pragma omp critical
		std::cout << "[sieve:" << omp_get_thread_num() << "] checking: " << i << std::endl;
		#endif

		if (i%val == 0) {
			#ifdef DEBUG
			#pragma omp critical
			std::cout << "[sieve:" << omp_get_thread_num() << "] pruning: " << i << std::endl;
			#endif
			num_list[i] = 1;
		}
	}
}

