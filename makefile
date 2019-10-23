prog: main.o fileReader.o linearRegression.o
	gcc -o prog main.o fileReader.o linearRegression.o

main.o: main.c
	gcc -c main.c

fileReader.o: input/fileReader.c
	gcc -c input/fileReader.c
	
linearRegression.o: linearRegression/linearRegression.c
	gcc -c linearRegression/linearRegression.c