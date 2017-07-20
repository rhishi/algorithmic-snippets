
CXX = g++-7
CXXFLAGS = -Wall

MAINS = sorting_main binarytree_main

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = sorting_test

all : $(MAINS) $(TESTS)

clean :
	rm -f *.o $(MAINS) $(TESTS)

################################################################################
# Google Test Boilerplate
# Builds gtest.a and gtest_main.a.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = googletest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
GTEST_CPPFLAGS = -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
GTEST_CXXFLAGS = -g -Wall -Wextra -pthread

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

################################################################################

%_test : %_test.o %.o gtest_main.a
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -o $@ $^

%_test.o : %_test.cc %.cc %.h
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -c $<

%_main : %_main.o %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o : %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<
