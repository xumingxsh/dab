ROOT_PATH=../../../../../
OPTION := -lgtest -std=c++14 -g -pthread -I../ -I../../ -I$(ROOT_PATH)/include

.cpp.o:
	g++ -c $< $(OPTION)
TEST_CPP_SRC :=  telemetryTaskTest.o

CPP_SRC := $(TEST_CPP_SRC) ../telemetriesProxy.o ../telemetryTask.o \
            $(ROOT_PATH)/src/utils/hi_log.o   $(ROOT_PATH)/src/utils/hi_time.o

all: clean $(CPP_SRC)
	g++ -o test.out *.o $(OPTION)
	rm -f *.o
clean:
	rm -f *.o *.out