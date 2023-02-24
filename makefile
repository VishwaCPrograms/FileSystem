# Vishwa V

#compiles the lab, zips it up, and then removes the uneeded .o files
all: fileSystem clean lab3.zip
#findMemLeak 

fileSystem: fileSystem.o helpManual.o
	gcc $^ -o $@

#Compiles lab3 main file
#lab3: fileSystem.o
#	gcc -g -o $@ $^

#zips all source files, as well as readme and makefile into one nice zip for Rob.
lab3.zip: makefile *.c *.h lab3readme
	zip lab3.zip makefile *.c *.h lab3readme

#Compiles any required .c files into .o files
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@

#removes all intermediate files (eg: .o files)
clean:
	rm -rf *.o

#Removes all test files except the input (.mid and .out)
cleantests:
	rm -rf *.mid *.out

#Removes all "non-source" files (eg: executables and other products)
cleanall: clean
	rm -rf exec_encode exec_decode exec_encodeObfs exec_decodeObfs *.mid *.out

findMemLeak: fileSystem
	valgrind --tool=memcheck $<
