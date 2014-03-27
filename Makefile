CPP=g++
FILES=
OUTPUT=project
OUTPUTS= project1 project2 project3


compile:	
	$(CPP) $(OUTPUT)1.cpp -o $(OUTPUT)1.out
	$(CPP) $(OUTPUT)2.cpp -o $(OUTPUT)2.out
	@echo "Now launch the executable with ./projectX.out > textfile"

install: clean compile

clean:
	rm $(OUTPUTS)