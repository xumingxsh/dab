ROOT_PATH=../../../
OPTION := -lgtest -std=c++14 -g -pthread -I../ -I$(ROOT_PATH)/include

.cpp.o:
	g++ -c $< $(OPTION)
TEST_CPP_SRC :=  hi_img_test.o

CPP_SRC := $(TEST_CPP_SRC) ../hi_img.o ../hi_log.o

all: clean $(CPP_SRC)
	g++ -o test.out *.o $(OPTION)
	rm -f *.o
clean:
	rm -f *.o *.out