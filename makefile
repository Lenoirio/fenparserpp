CC              = g++
CFLAGS          = -c -Wall -std=c++17
#COPT            = -O3
COPT            = -g -O0
LIBS			= -lgtest -lgtest_main
TARGET          = ./target/

all:	$(TARGET)fentest

$(TARGET)fentest: $(TARGET)fentest.o parsertest.cpp
	mkdir -p $(TARGET)
	$(CC) $(COPT) -o $(TARGET)fentest $(TARGET)fenparserpp.o parsertest.cpp $(LIBS)

$(TARGET)fentest.o:	fenparserpp.h fenparserpp.cpp
	mkdir -p $(TARGET)
	$(CC) $(CFLAGS) $(COPT) -o $(TARGET)fenparserpp.o fenparserpp.cpp

clean:
	rm -rf $(TARGET)
