all: ejudge
	g++ main.cpp -Wall -Wextra -o cmp
ejudge:
	python2.7 ~/PycharmProjects/SourceMerger/source_merger.py main.cpp -o ejudge.cpp
clean:
	rm cmp ejudge.cpp
