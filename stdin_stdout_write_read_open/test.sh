
cc -E write.c -o write.i
cc -S write.i -o write.s
cc -c write.s -o write.o
cc write.o

./a.out copy.c < write.c

./a.out /bin/tst.txt < write.c
