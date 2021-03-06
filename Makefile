# Makefile for ANN
#
# If this file is in the directory with your program, you can compile your
# program using the following command:
#
#   $ make
#
# When you are done with this assignment, delete all the files generated
# by the compiler (you can always recreate them if you need them)
#
#   $ make clean
#
# It is a good idea to understand how make works
#
# Commands all have the following format:
#    file_to_be_created: list_of_files_the_file_to_left_is_create_from
#    <tab>the command that generates this file
#
# Compiler options
#    the arguments after g++ specify specific options for the compiler
#    -Wall        ==> print all warnings
#    -pedantic    ==> print warnings when non-standard C++ is used
#    -g           ==> keep additional information to aid in debugging
#    -o           ==> specify the output filename
#    -c           ==> compile only (create a .o file)
main: main.o ANN.o Node.o Layer.o
	g++ -std=c++11 -Wall -pedantic -g -o main main.o ANN.o Layer.o Node.o

main.o: ANN.h main.cpp
	g++ -std=c++11 -Wall -pedantic -g -c main.cpp

ANN.o: ANN.h Layer.h Node.h ANN.cpp
	g++ -std=c++11 -Wall -pedantic -g -c ANN.cpp

Node.o: Node.h Layer.h Node.cpp
	g++ -std=c++11 -Wall -pedantic -g -c Node.cpp

Layer.o: Layer.h Node.h Layer.cpp
	g++ -std=c++11 -Wall -pedantic -g -c Layer.cpp
clean:
	rm -f *.o main
