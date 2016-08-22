all:
	g++ -ggdb -gdwarf-2 -std=c++11 ep1.cpp -o ep1
debug:
	g++ -D DEBUG -g -ggdb -gdwarf-2 -std=c++11 ep1.cpp -o ep1
test:
	@g++ -std=c++11 ep1.cpp -o ep1;
	@./ep1 10 list 1 > t.tmp;
	@echo "2 3 5 7 " > c.tmp;
	@diff t.tmp c.tmp

	@#./ep1 42 all 8 > t.tmp;
	@#echo "2 3 5 7 11 13 17 19 23 29 31 37 41\n238\n0.002387" > c.tmp;
	@#diff t.tmp c.tmp

	@#./ep1 1000000 time 8 > t.tmp;
	@#echo "0.75472" > c.tmp;
	@#diff t.tmp c.tmp

	@./ep1 1000 sum 4 > t.tmp;
	@echo "76127" > c.tmp;
	@diff t.tmp c.tmp

	@./ep1 8968 sum 10 > t.tmp;
	@echo "4646851" > c.tmp;
	@diff t.tmp c.tmp