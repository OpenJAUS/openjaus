BINDIR	=	./bin/
SRC		=	./src/
BUILD	=	./Build/
LIB		=	./lib/
INC		=	./include/
LIBS	=	-lm -lcimar
LIBRARY	=	libjausC.so

all:
	@cd $(SRC); make;
	gcc -shared -o $(LIB)$(LIBRARY) $(BUILD)*.o $(LIBS)

clean:
	rm -fv $(BUILD)*.o
	rm -fv $(BINDIR)$(EXE)
	rm -fv $(LIB)libjausC.*

install:
	./Install
	
uninstall:
	./Uninstall
