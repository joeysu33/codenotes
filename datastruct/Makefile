SRCS = $(shell ls *.c)
all:
	@for i in $(SRCS) ;do j=`echo $$i | sed -n 's/\.c//p'`; gcc -g -o $$j $$i; done

clean:
	@find . -maxdepth 1 -executable -type f -exec rm -f {} \;

