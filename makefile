# change application name here (executable output name)
TARGET=Mysql

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
MYSQL=`mysql_config --libs --cflags`

CURL=-lcurl
# linker
LD=gcc
LDFLAGS=$(PTHREAD)  -export-dynamic  $(CURL) $(MYSQL)

OBJS=    main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c  $(CURL) $(MYSQL) -o main.o

clean:
	rm -f *.o $(TARGET)
install:
	apt install gcc
	apt install curl
	apt install default-libmysqlclient-dev 
	apt install libcurl4-openssl-dev


