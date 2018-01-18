SRCS = $(shell ls *.c)
all:
	@for i in $(SRCS); do j=`echo $$i | sed -n 's/\.c//p'`; if [ $$j = "sort_common" ]; then continue; fi;  gcc -g -o $$j sort_common.c $$i; done

clean:
	@find . -maxdepth 1 -executable -type f -exec rm -f {} \;
