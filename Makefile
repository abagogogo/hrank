#LATEST_CPP = $(shell find . -type f -name "*.cpp" | xargs stat --format '%Y:%n' | sort -nr | awk -F: '{print $$2}' | head -n1)
LATEST_CPP = $(shell find . -type f -name "*.cc" | xargs stat --format '%Y:%n' | sort -nr | awk -F: '{print $$2}' | head -n1)
LATEST_EXE = ./a.out

default: run

$(LATEST_EXE): $(LATEST_CPP)
	@echo "---- Compiling $< ----"	
	g++ -std=c++0x -o $@ $<
	@echo "---- Output: $@ ----"	

run: $(LATEST_EXE)
	@echo "---- running $(LATEST_EXE) ----"	
	$(LATEST_EXE)

edit:
	gvim $(LATEST_CPP)

clean:
	rm -f *~
	rm -f a.out
	rm -f core
