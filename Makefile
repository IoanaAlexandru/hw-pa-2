build: minlexbfs disjcnt rtd revedges

minlexbfs:
	g++ -Wall -g utils.cpp minlexbfs.cpp -o minlexbfs

disjcnt:
	g++ -Wall -g utils.cpp disjcnt.cpp -o disjcnt

rtd:
	g++ -Wall -g utils.cpp rtd.cpp -o rtd

revedges:
	g++ -Wall -g utils.cpp revedges.cpp -o revedges

run-p1:
	./minlexbfs

run-p2:
	./disjcnt

run-p3:
	./rtd

run-p4:
	./revedges

clean:
	rm -f minlexbfs disjcnt rtd revedges
