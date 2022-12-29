CC=g++

EXE=jsnake.app

CFLAGS= -c -I ./inc 
LFLAGS=-lcurses

OBJDIR=obj

OBJS= $(OBJDIR)/main.o \
	$(OBJDIR)/Game.o \
	$(OBJDIR)/Debug.o \
	$(OBJDIR)/Snake.o \
	$(OBJDIR)/Display.o \
	$(OBJDIR)/Random.o \
	$(OBJDIR)/InputKeys.o \
	$(OBJDIR)/GameData.o \
	$(OBJDIR)/Menu.o \
	$(OBJDIR)/MenuItem.o \
	$(OBJDIR)/MenuPanel.o \
	$(OBJDIR)/Score.o


$(EXE):$(OBJS)
	mkdir -p $(OBJDIR)
	$(CC) -o $(EXE) $(OBJS) $(LFLAGS)

$(OBJDIR)/%.o : src/%.cpp	
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJDIR)
	rm -rf $(EXE)
