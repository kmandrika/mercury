CXX = clang++
CXXFLAGS = -Wall -O0 -std=c++11 -stdlib=libc++ -Wno-unused-local-typedefs
LDFLAGS = 

NAME = mercuryd

LIBS = -L/usr/local/Cellar/boost/1.58.0/lib -lboost_program_options-mt
INCS = -Iinclude -I/usr/local/include -I/usr/local/Cellar/boost/1.58.0/include
SRCS = $(shell find src -name '*.cxx')
DIRS = $(shell find src -type d | sed 's/src//./g')
OBJS = $(patsubst src/%.cxx,obj/%.o,$(SRCS))

bin/$(NAME): build $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) $(INCS) -o $@

obj/%.o: src/%.cxx
	$(CXX) $(CXXFLAGS) -c $< $(INCS) -o $@

build:
	mkdir -p bin
	mkdir -p obj
	for dir in $(DIRS); do mkdir -p obj/$$dir; done
