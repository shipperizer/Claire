CPP=g++
FILES=
OUTPUT=project
OUTPUTS= project1.out project2.out project3.out


compile:	
	$(CPP) $(OUTPUT)1.cpp -o $(OUTPUT)1.out
	$(CPP) $(OUTPUT)2.cpp -o $(OUTPUT)2.out
	$(CPP) $(OUTPUT)3.cpp -o $(OUTPUT)3.out
	@echo "Now launch the executable with ./projectX.out > textfile"

install: clean compile
	@echo "Done man"

clean:
	rm $(OUTPUTS)
