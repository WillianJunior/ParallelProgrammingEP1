all:
	g++ -ggdb -gdwarf-2 -std=c++11 -fopenmp ep1.cpp -o ep1
debug:
	g++ -D DEBUG -g -ggdb -gdwarf-2 -fopenmp -std=c++11 ep1.cpp -o ep1
test:
	@g++ -std=c++11 -D OMMIT_TIME -fopenmp ep1.cpp -o ep1
	@./ep1 10 list 1 > t.tmp
	@echo "2 3 5 7 " > c.tmp
	@diff t.tmp c.tmp

	@./ep1 42 all 8 > t.tmp;
	@echo "2 3 5 7 11 13 17 19 23 29 31 37 41 \n238" > c.tmp
	@diff t.tmp c.tmp

	@./ep1 1000000 time 8

	@./ep1 1000 sum 4 > t.tmp
	@echo "76127" > c.tmp
	@diff t.tmp c.tmp

	@./ep1 8968 sum 10 > t.tmp
	@echo "4646851" > c.tmp
	@diff t.tmp c.tmp
all_csv: csv0 csv1 csv2 csv3 csv4 csv5
csv0:
	@g++ -std=c++11 -D OMMIT_TIME -D BASELINE -D CSV_NAME="test0.csv" -fopenmp ep1.cpp -o ep1
	@./ep1 100000 time 2 static 10 csv 5
	@./ep1 500000 time 2 static 10 csv 5
	@./ep1 1000000 time 2 static 10 csv 5
csv1:
	@g++ -std=c++11 -D OMMIT_TIME -D CSV_NAME="test1.csv" -fopenmp ep1.cpp -o ep1
	@./ep1 100000 time 2 static 10 csv 5
	@./ep1 100000 time 2 static 100 csv 5
	@./ep1 100000 time 2 static 1000 csv 5
	@./ep1 100000 time 2 static 10000 csv 5
	@./ep1 100000 time 2 static 100000 csv 5
	@./ep1 100000 time 2 dynamic 10 csv 5
	@./ep1 100000 time 2 dynamic 100 csv 5
	@./ep1 100000 time 2 dynamic 1000 csv 5
	@./ep1 100000 time 2 dynamic 10000 csv 5
	@./ep1 100000 time 2 dynamic 100000 csv 5
	@./ep1 100000 time 2 guided 10 csv 5
	@./ep1 100000 time 2 guided 100 csv 5
	@./ep1 100000 time 2 guided 1000 csv 5
	@./ep1 100000 time 2 guided 10000 csv 5
	@./ep1 100000 time 2 guided 100000 csv 5
csv2:
	@g++ -std=c++11 -D OMMIT_TIME -D CSV_NAME="test2.csv" -fopenmp ep1.cpp -o ep1
	@./ep1 500000 time 2 static 10 csv 5
	@./ep1 500000 time 2 static 100 csv 5
	@./ep1 500000 time 2 static 1000 csv 5
	@./ep1 500000 time 2 static 10000 csv 5
	@./ep1 500000 time 2 static 100000 csv 5
	@./ep1 500000 time 2 dynamic 10 csv 5
	@./ep1 500000 time 2 dynamic 100 csv 5
	@./ep1 500000 time 2 dynamic 1000 csv 5
	@./ep1 500000 time 2 dynamic 10000 csv 5
	@./ep1 500000 time 2 dynamic 100000 csv 5
	@./ep1 500000 time 2 guided 10 csv 5
	@./ep1 500000 time 2 guided 100 csv 5
	@./ep1 500000 time 2 guided 1000 csv 5
	@./ep1 500000 time 2 guided 10000 csv 5
	@./ep1 500000 time 2 guided 100000 csv 5
csv3:
	@g++ -std=c++11 -D OMMIT_TIME -D CSV_NAME="test3.csv" -fopenmp ep1.cpp -o ep1
	@./ep1 1000000 time 2 static 10 csv 5
	@./ep1 1000000 time 2 static 100 csv 5
	@./ep1 1000000 time 2 static 1000 csv 5
	@./ep1 1000000 time 2 static 10000 csv 5
	@./ep1 1000000 time 2 static 100000 csv 5
	@./ep1 1000000 time 2 dynamic 10 csv 5
	@./ep1 1000000 time 2 dynamic 100 csv 5
	@./ep1 1000000 time 2 dynamic 1000 csv 5
	@./ep1 1000000 time 2 dynamic 10000 csv 5
	@./ep1 1000000 time 2 dynamic 100000 csv 5
	@./ep1 1000000 time 2 guided 10 csv 5
	@./ep1 1000000 time 2 guided 100 csv 5
	@./ep1 1000000 time 2 guided 1000 csv 5
	@./ep1 1000000 time 2 guided 10000 csv 5
	@./ep1 1000000 time 2 guided 100000 csv 5
csv4:
	@g++ -std=c++11 -D OMMIT_TIME -D BASELINE -D CSV_NAME="test4.csv" -fopenmp ep1.cpp -o ep1
	@./ep1 100000 time 1 static 2000 csv 5
	@./ep1 100000 time 2 static 2000 csv 5
	@./ep1 100000 time 3 static 2000 csv 5
	@./ep1 100000 time 4 static 2000 csv 5
	@./ep1 100000 time 5 static 2000 csv 5
	@./ep1 100000 time 6 static 2000 csv 5
	@./ep1 100000 time 7 static 2000 csv 5
	@./ep1 100000 time 8 static 10000 csv 5
	@./ep1 100000 time 9 static 10000 csv 5
	@./ep1 500000 time 1 static 10000 csv 5
	@./ep1 500000 time 2 static 10000 csv 5
	@./ep1 500000 time 3 static 10000 csv 5
	@./ep1 500000 time 4 static 10000 csv 5
	@./ep1 500000 time 5 static 10000 csv 5
	@./ep1 500000 time 6 static 10000 csv 5
	@./ep1 500000 time 7 static 10000 csv 5
	@./ep1 500000 time 8 static 10000 csv 5
	@./ep1 500000 time 9 static 10000 csv 5
	@./ep1 1000000 time 1 static 20000 csv 5
	@./ep1 1000000 time 2 static 20000 csv 5
	@./ep1 1000000 time 3 static 20000 csv 5
	@./ep1 1000000 time 4 static 20000 csv 5
	@./ep1 1000000 time 5 static 20000 csv 5
	@./ep1 1000000 time 6 static 20000 csv 5
	@./ep1 1000000 time 7 static 20000 csv 5
	@./ep1 1000000 time 8 static 20000 csv 5
	@./ep1 1000000 time 9 static 20000 csv 5
csv5:
	@g++ -std=c++11 -D OMMIT_TIME -D CSV_NAME="test5.csv" -fopenmp ep1.cpp -o ep1
	@./ep1 100000 time 1 static 2000 csv 5
	@./ep1 100000 time 2 static 2000 csv 5
	@./ep1 100000 time 3 static 2000 csv 5
	@./ep1 100000 time 4 static 2000 csv 5
	@./ep1 100000 time 5 static 2000 csv 5
	@./ep1 100000 time 6 static 2000 csv 5
	@./ep1 100000 time 7 static 2000 csv 5
	@./ep1 100000 time 8 static 10000 csv 5
	@./ep1 100000 time 9 static 10000 csv 5
	@./ep1 500000 time 1 static 10000 csv 5
	@./ep1 500000 time 2 static 10000 csv 5
	@./ep1 500000 time 3 static 10000 csv 5
	@./ep1 500000 time 4 static 10000 csv 5
	@./ep1 500000 time 5 static 10000 csv 5
	@./ep1 500000 time 6 static 10000 csv 5
	@./ep1 500000 time 7 static 10000 csv 5
	@./ep1 500000 time 8 static 10000 csv 5
	@./ep1 500000 time 9 static 10000 csv 5
	@./ep1 1000000 time 1 static 20000 csv 5
	@./ep1 1000000 time 2 static 20000 csv 5
	@./ep1 1000000 time 3 static 20000 csv 5
	@./ep1 1000000 time 4 static 20000 csv 5
	@./ep1 1000000 time 5 static 20000 csv 5
	@./ep1 1000000 time 6 static 20000 csv 5
	@./ep1 1000000 time 7 static 20000 csv 5
	@./ep1 1000000 time 8 static 20000 csv 5
	@./ep1 1000000 time 9 static 20000 csv 5
	@./ep1 100000 time 1 dynamic 2000 csv 5
	@./ep1 100000 time 2 dynamic 2000 csv 5
	@./ep1 100000 time 3 dynamic 2000 csv 5
	@./ep1 100000 time 4 dynamic 2000 csv 5
	@./ep1 100000 time 5 dynamic 2000 csv 5
	@./ep1 100000 time 6 dynamic 2000 csv 5
	@./ep1 100000 time 7 dynamic 2000 csv 5
	@./ep1 100000 time 8 dynamic 10000 csv 5
	@./ep1 100000 time 9 dynamic 10000 csv 5
	@./ep1 500000 time 1 dynamic 10000 csv 5
	@./ep1 500000 time 2 dynamic 10000 csv 5
	@./ep1 500000 time 3 dynamic 10000 csv 5
	@./ep1 500000 time 4 dynamic 10000 csv 5
	@./ep1 500000 time 5 dynamic 10000 csv 5
	@./ep1 500000 time 6 dynamic 10000 csv 5
	@./ep1 500000 time 7 dynamic 10000 csv 5
	@./ep1 500000 time 8 dynamic 10000 csv 5
	@./ep1 500000 time 9 dynamic 10000 csv 5
	@./ep1 1000000 time 1 dynamic 20000 csv 5
	@./ep1 1000000 time 2 dynamic 20000 csv 5
	@./ep1 1000000 time 3 dynamic 20000 csv 5
	@./ep1 1000000 time 4 dynamic 20000 csv 5
	@./ep1 1000000 time 5 dynamic 20000 csv 5
	@./ep1 1000000 time 6 dynamic 20000 csv 5
	@./ep1 1000000 time 7 dynamic 20000 csv 5
	@./ep1 1000000 time 8 dynamic 20000 csv 5
	@./ep1 1000000 time 9 dynamic 20000 csv 5
	@./ep1 100000 time 1 guided 2000 csv 5
	@./ep1 100000 time 2 guided 2000 csv 5
	@./ep1 100000 time 3 guided 2000 csv 5
	@./ep1 100000 time 4 guided 2000 csv 5
	@./ep1 100000 time 5 guided 2000 csv 5
	@./ep1 100000 time 6 guided 2000 csv 5
	@./ep1 100000 time 7 guided 2000 csv 5
	@./ep1 100000 time 8 guided 10000 csv 5
	@./ep1 100000 time 9 guided 10000 csv 5
	@./ep1 500000 time 1 guided 10000 csv 5
	@./ep1 500000 time 2 guided 10000 csv 5
	@./ep1 500000 time 3 guided 10000 csv 5
	@./ep1 500000 time 4 guided 10000 csv 5
	@./ep1 500000 time 5 guided 10000 csv 5
	@./ep1 500000 time 6 guided 10000 csv 5
	@./ep1 500000 time 7 guided 10000 csv 5
	@./ep1 500000 time 8 guided 10000 csv 5
	@./ep1 500000 time 9 guided 10000 csv 5
	@./ep1 1000000 time 1 guided 20000 csv 5
	@./ep1 1000000 time 2 guided 20000 csv 5
	@./ep1 1000000 time 3 guided 20000 csv 5
	@./ep1 1000000 time 4 guided 20000 csv 5
	@./ep1 1000000 time 5 guided 20000 csv 5
	@./ep1 1000000 time 6 guided 20000 csv 5
	@./ep1 1000000 time 7 guided 20000 csv 5
	@./ep1 1000000 time 8 guided 20000 csv 5
	@./ep1 1000000 time 9 guided 20000 csv 5
	