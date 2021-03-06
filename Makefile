CCX=g++-7
CCXFLAGS = -std=c++17 -O3

SRCDIR  = ./src
OBJSDIR = ./build
DEPDIR	= ./include
VPATH = $(SRCDIR)

HEADERS = $(wildcard $(DEPDIR)/*.h)
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS  = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJSDIR)/%.o)

compiler: $(OBJECTS)
	$(CCX) $(CCXFLAGS) $(OBJECTS) -o compiler

$(OBJECTS): $(OBJSDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CCX) $(CCXFLAGS) -c $< -o $@

clean:
	rm -f compiler 
	find $(OBJSDIR)/ -name '*.o' -delete
	find $(DEPDIR)/ -name '*.h.gch' -delete
	rm -r compiler.dSYM