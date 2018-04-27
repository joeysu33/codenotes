SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGETS = $(patsubst %.c, %, $(SRCS))

all: $(TARGETS)

$(TARGETS) : $(OBJS)
	gcc -o $@ $(join $@, .o)

$(OBJS):$(SRCS)
	gcc -c -o $@ $(patsubst %.o, %.c, $@)

clean:
	@rm -f *.o
	@find . -maxdepth 1 -type f -executable -print0 -exec rm -f {} \;
