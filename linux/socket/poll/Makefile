SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGETS = $(patsubst %.o, %, $(OBJS))

all: $(TARGETS)
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(TARGETS)

$(TARGETS) : $(OBJS)
	gcc -o $@ $(join $@, .o)

$(OBJS) : $(SRCS)
	gcc -c -o $@ $(patsubst %.o, %.c, $@)

clean:
	@rm -f *.o
	@find . -maxdepth 1 -type f -print0 -executable -exec rm -f {} \;
