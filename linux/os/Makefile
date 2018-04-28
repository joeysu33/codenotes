SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS)
TARS = $(patsubst %.c, %, $(SRCS))

all:$(TARS)


$(TARGS): $(OBJS)
	gcc -o $@ $(join $@,.o)

%.o : %.c
	gcc -c -o $@ $(patsubst %.o, %.c, $@)

clean:
	@rm -f *.o
	@find . -maxdepth 1 -type f -executable -print0 -exec rm -f {} \;
	@echo ""
