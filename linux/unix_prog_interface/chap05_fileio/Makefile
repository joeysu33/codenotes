BIN= ../bin
SRCS= $(shell ls *.c)
all:
	@for i in $(SRCS); do j=`echo $$i | sed -n 's/\.c//p'`; gcc -o $(BIN)/$$j $$i; done
clean:
	@for i in $(SRCS); do j=`echo $$i| sed -n 's/\.c//p'`; rm -f $(BIN)/$$j; done
