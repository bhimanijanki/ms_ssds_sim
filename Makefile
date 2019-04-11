CC = gcc

CFLAGS  = -g -Wall

all: msssdsim

msssdsim: msssdsim.c detect.c hash.c
	$(CC) $(CFLAGS) -o msssdsim msssdsim.c detect.c hash.c

clean:
	$(RM) msssdsim
