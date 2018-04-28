SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGETS = $(patsubst %.o, %, $(OBJS))

all: $(TARGETS)

#不会一一对应的，需要自己来实现
$(TARGETS):$(OBJS)
	gcc -o $@ $(join $@, .o)

#模式匹配可以自动一一对应
%.o : %.c
	gcc -c -o $@ $<

clean:
	@$(RM) -f *.o
	@find . -maxdepth 1 -type f  -executable -print0 -exec rm -f {} \;
