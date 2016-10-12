AA: AA.o BB CC DD EE FF
	gcc -o AA AA.o
BB: BB.o
	gcc -o BB BB.o
CC: CC.o
	gcc -o CC CC.o
DD: DD.o CC
	gcc -o DD DD.o
EE: EE.o
	gcc -o EE EE.o
FF: FF.o
	gcc -o FF FF.o
AA.o : AA.c
	gcc -c AA.c
BB.o : BB.c
	gcc -c BB.c
CC.o : CC.c
	gcc -c CC.c
DD.o : DD.c
	gcc -c DD.c
EE.o : EE.c
	gcc -c EE.c
FF.o : FF.c
	gcc -c FF.c
clean : 
	rm AA BB CC DD EE FF AA.o BB.o CC.o DD.o EE.o FF.o

