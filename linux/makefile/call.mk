reverse = $(2) $(1)
example = $(call reverse, aa, bb)
all:
	@echo $(example)
	@echo $(call reverse, kk, jj)

