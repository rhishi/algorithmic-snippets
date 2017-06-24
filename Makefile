
CXX = g++-7

MAINS = sorting_main

all : $(MAINS)

clean :
	rm -f *.o $(MAINS)

%_main : %_main.o %.o
	$(CXX) -o $@ $^

%.o : %.cc %.h
	$(CXX) -c $<
