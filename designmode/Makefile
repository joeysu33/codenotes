SRCS=$(shell ls *.cpp)

all:
	@for i in $(SRCS); do j=`echo $$i | sed -n 's/\.cpp//p'`; g++ -std=c++11 -g -o $$j $$i; done

clean:
	@find . -executable -type f -exec rm -f {} \;


