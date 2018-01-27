# *** MACROS
CXXFLAGS=-g -ansi -pedantic -Wall -Wconversion
CXX=g++

INC_PATH=./
CXXFLAGS += -I$(INC_PATH)

# *** TARGETS
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

TARGET=parser

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

all: $(TARGET)

include depends

depends:
	$(CXX) -MM -I$(INC_PATH) $(SRCS) > depends

# *** COMMANDS
clean:
	-rm $(TARGET)
	-rm *.o
	-rm depends

run:
	./$(TARGET) Parser.qq qqq TestFile1.txt
	
gdb:
	gdb $(TARGET)
##################################

