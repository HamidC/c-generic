run: clean compile
	./generic2

compile:
	gcc generic.c -o generic.exe
	gcc generic2.c -o generic2.exe
	
clean:
	del generic.exe generic2.exe
	
.PHONY: run compile clean