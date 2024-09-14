all: a.out

a.out: main.o ident.o lex.o tabl_ident.o  scanner.o parcer.o poliz.o interpritator.o executer.o
	g++ main.o ident.o lex.o  tabl_ident.o  scanner.o parcer.o poliz.o interpritator.o executer.o 

main.o: main.cpp
	g++ -c main.cpp

ident.o: ident.cpp
	g++ -c ident.cpp

lex.o: lex.cpp
	g++ -c lex.cpp

tabl_ident.o: tabl_ident.cpp
	g++ -c tabl_ident.cpp

scanner.o: scanner.cpp
	g++ -c scanner.cpp

parcer.o: parcer.cpp
	g++ -c parcer.cpp

poliz.o: poliz.cpp
	g++ -c poliz.cpp

interpritator.o: interpritator.cpp
	g++ -c interpritator.cpp

executer.o: executer.cpp
	g++ -c executer.cpp

clean:
	rm *.o ./a.out