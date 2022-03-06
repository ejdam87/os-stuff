
CFLAGS += -Wall -std=c99 -MD -MP

all: math

SRClib = fib.c factorial.c
OBJlib = ${SRClib:.c=.o}
DEPlib = ${SRClib:.c=.d}
SRCm = math.c
OBJm = ${SRCm:.c=.o}
DEPm = ${SRCm:.c=.d} 

libmath.a: $(OBJlib)
	ar r libmath.a $(OBJlib)

math: $(OBJm) libmath.a
	cc -o math $(OBJm) libmath.a

-include $(DEPlib)
-include $(DEPm)

clean: rm -f $(DEPm) $(DEPlib) $(OBJlib) $(OBJm)
