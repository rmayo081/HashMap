
#Link the compenents and compile the executable
driver: input.o map.o integer.o text.o driver.o
	gcc -g -Wall input.o map.o integer.o text.o driver.o -o driver

#Compile the input component
input.o: input.c input.h
	gcc -g -Wall -std=c99 -c input.c -o input.o

#Compile the map component
map.o: vtype.h map.h map.c
	gcc -g -Wall -std=c99 -c map.c -o map.o

#Compile the integer subclass component
integer.o: vtype.h integer.h integer.c
	gcc -g -Wall -std=c99 -c integer.c -o integer.o

#Compile the text subclass component
text.o: vtype.h text.h text.c
	gcc -g -Wall -std=c99 -c text.c -o text.o

#Compile the driver component
driver.o: input.h map.h integer.h text.h driver.c
	gcc -g -Wall -std=c99 -c driver.c -o driver.o

#Clean the directory of the executable, object files, and output files.
clean:
	rm -f input.o map.o integer.o text.o driver.o
	rm -f driver
	rm -f textTest
	rm -f mapTest
	rm -f stderr.txt
	rm -f output.txt