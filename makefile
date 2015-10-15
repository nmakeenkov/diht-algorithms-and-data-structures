all: ejudge
	g++ main.cpp -Wall -Wextra -o cmp
ejudge:
	python2.7 SourceMerger.py main.cpp -o ejudge.cpp
clean:
	rm cmp ejudge.cpp
