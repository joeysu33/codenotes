#编译所有的.c文件 
SOURCES = $(shell ls *.c)
TARNAMES = $(basename $(SOURCES))
CFLAGS += -g

all: $(TARNAMES)

$(TARNAMES): $(SOURCES)

clean:
	@rm -f *.o
	@find . -maxdepth 1 -type f -executable -exec rm -f {} \;
