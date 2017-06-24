
CXX = g++-7
CXXFLAGS = -Wall

MAINS = sorting_main

all : $(MAINS)

clean :
	rm -f *.o $(MAINS)

%_main : %_main.o %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o : %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<
