CPP=g++
FILES=reading.cpp
OUTPUT=project

install: clean compile

compile:	
	$(CPP) $(OUTPUT)1.cpp -o $(OUTPUT)1
	@echo Now launch the executable with ./projectNO

clean:
	rm $(OUTPUT)