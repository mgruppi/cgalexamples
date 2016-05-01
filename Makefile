all: one two three four five six

one: one.cpp
	g++ one.cpp -frounding-math -o one -lCGAL
two: two.cpp
	g++ -std=c++11 two.cpp -frounding-math -o two -lCGAL
three: three.cpp
	g++ three.cpp -frounding-math -o three -lCGAL -lgmpxx -lgmp
four: four.cpp
	g++ four.cpp -frounding-math -o four -lCGAL
five: five.cpp
	g++ five.cpp -frounding-math -o five -lCGAL -lboost_thread -lmpfr -lgmpxx -lgmp


clean:
	rm one two three four five
