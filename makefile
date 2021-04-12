# change application name here (executable output name)
TARGET=Curl

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O6
# warnings
WARN=-Wall

WEXTRA=-Wextra

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(WEXTRA)  $(PTHREAD) -pipe

CURL= -lcurl
MYSQL=`mysql_config --libs --cflags`
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(CURL)  $(MYSQL) -export-dynamic

OBJS=    main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(CURL) $(MYSQL) -o main.o

clean:
	rm -f *.o $(TARGET)

install:
	sudo apt install curl
	sudo apt install libcurl4-openssl-dev
	sudo apt install default-libmysqlclient-dev