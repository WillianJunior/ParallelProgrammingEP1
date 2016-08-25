#include <iostream>
#include <fstream>
#include <string>

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
	std::string usage = "usage: ./ep1 {size} {list|time|sum|all} {threads}"
		"[{sched_strategy} {chunk_size} [csv {repetitions}]]";
	
	// get input arguments
	if (argc != 4 && argc != 6 && argc != 8) {
		std::cout << usage << std::endl;
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
		std::cout << usage << std::endl;
		return 0;	
	}

	int threads = atoi(argv[3]);
	int testing_rep = 1;
	int csv_testing = false;
	std::ofstream csv_file;

	// get sched args if they exist
	if (argc >= 6) {
		char* c_sched = argv[4];
		int chunk_size = atoi(argv[5]);
		if (strcmp(c_sched, "static") == 0)
			 omp_set_schedule(omp_sched_static, chunk_size);
		else if (strcmp(c_sched, "dynamic") == 0)
			 omp_set_schedule(omp_sched_dynamic, chunk_size);
		else if (strcmp(c_sched, "guided") == 0)
			 omp_set_schedule(omp_sched_guided, chunk_size);
		else {
			std::cout << usage << std::endl;
			return 0;
		}

		// get testing arguments
		if (argc == 8) {
			char* c_csv = argv[6];
			if (strcmp(c_csv, "csv") != 0) {
				std::cout << usage << std::endl;
				return 0;
			}
			testing_rep = atoi(argv[7]);
			csv_testing = true;
			
			// create csv header
			csv_file.open ("test.csv", std::ios::app);
			csv_file << std::endl << "scheduler;" << c_sched << std::endl;
			csv_file << "chunk_size;" << chunk_size << std::endl;
			csv_file << "size;" << size << std::endl;

			for (int i=0; i<testing_rep; i++)
				csv_file << "t" << i << ";";
			csv_file << "avr;stdev" << std::endl;
		}
	} else
		 omp_set_schedule(omp_sched_guided, 1000);

	int sum;
	int last_prime;
	double exec_time;
	int* primes_list_out = new int[1];

	// run the 
	for (int test=0; test<testing_rep; test++) {

		int* num_list = new int[size];
		int* primes_list = new int[size];
		sum = 0;
		last_prime = 0;
		
		// get exec start time
		exec_time = omp_get_wtime();

		generate_N(size, num_list);

		#ifdef PROFILE
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

		#ifdef PROFILE
		double t2 = omp_get_wtime() - exec_time - t1;
		#pragma omp master
		#pragma omp critical
		std::cout << "[profile] sieve time: " << t2 << std::endl;
		#endif

		// calculate the sum and get all prime numbers
		for (int p=2; p<size; p++) {
			if (num_list[p] == 0) {
				primes_list[last_prime++] = p;
				sum += p;
			}
		}

		#ifdef PROFILE
		double t3 = omp_get_wtime() - exec_time - t2 - t1;
		#pragma omp master
		#pragma omp critical
		std::cout << "[profile] sum time: " << t3 << std::endl;
		#endif

		// finishes time mesuring
		exec_time = omp_get_wtime() - exec_time;

		// output the test file
		if (csv_testing) {
			csv_file << exec_time << ";";
		}

		delete[] primes_list_out;
		delete[] num_list;
		primes_list_out = primes_list;
	}

	// add average time and stdev calc to csv
	csv_file << "=AVERAGE(OFFSET(INDIRECT(ADDRESS(ROW(), COLUMN()-" << testing_rep 
		<< ")),0,0):OFFSET(INDIRECT(ADDRESS(ROW(), COLUMN()-1)),0,0));";
	csv_file << "=STDEV(OFFSET(INDIRECT(ADDRESS(ROW(), COLUMN()-" << (testing_rep+1)
		<< ")),0,0):OFFSET(INDIRECT(ADDRESS(ROW(), COLUMN()-2)),0,0))" << std::endl;

	// close test file
	if (csv_testing)
		csv_file.close();

	// list output
	if (t == r_list || t == r_all) {
		for (int i=0; i<last_prime; i++)
			std::cout << primes_list_out[i] << " ";
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
	
	#pragma omp parallel for num_threads(threads) default(none) shared(num_list, size, val)
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

