all:
	@for i in $(shell ls *.c); do echo "compile:$$i...";target=`echo $$i |sed -n 's/\.c//p'`;gcc -o $$target $$i; done
clean:
	find . -maxdepth 1 -type f -executable -exec rm -f {} \;
