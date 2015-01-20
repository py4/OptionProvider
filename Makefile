all: a.out

clean:
	rm -rf *o a.out

a.out: main.o feature.o parser.o product.o product_manager.o
	g++ main.o feature.o parser.o product.o product_manager.o -o a.out

product_manager.o: product_manager.cpp product_manager.h product.h 
	g++ -c product_manager.cpp

product.o: product.cpp product.h feature.h parser.h
	g++ -c product.cpp

feature.o: feature.cpp feature.h parser.h
	g++ -c feature.cpp

parser.o: parser.cpp parser.h type.h
	g++ -c parser.cpp
