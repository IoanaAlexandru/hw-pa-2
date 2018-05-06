build: minlexbfs disjcnt rtd revedges

minlexbfs:
	g++ -Wall minlexbfs.cpp -o minlexbfs

disjcnt:
	g++ -Wall disjcnt.cpp -o disjcnt

rtd:
	g++ -Wall rtd.cpp -o rtd

revedges:
	g++ -Wall revedges.cpp -o revedges

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
