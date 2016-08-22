#include <iostream>
#include <list>

void generate_N(int size, int* &list);
int sieve(int* list, int size, int val, int* &ret_list);


// sieve of eratosthenes implementation
int main(int argc, char **argv) {
	int size = 200;
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

