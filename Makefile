CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -L/usr/X11R6/lib -lSDL -lSDLmain -lSDL_image
INCLUDES = -I/usr/X11R6/include -framework Cocoa -framework OpenGL

OBJ      = minimal.o basicShapes.o player.o
RM       = rm -f
BIN      = minimal
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES)  -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

minimal.o : minimal.c player.c basicShapes.c
	@echo "compile minimal"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

player.o : player.c
	@echo "compile player"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

basicShapes.o : basicShapes.c
	@echo "compile basicShapes"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN) 

tar : clean 
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)


#gcc -Wall -framework OpenGL -lSDL -lSDLmain -framework cocoa -o exo5 exo5.c