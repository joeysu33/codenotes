data  ="      a        b      c            "
data1 =       a        b      c           
dataprint:
	@echo $(data)
	@echo =$(strip $(data))=
	@echo $(data1)
	@echo $(strip $(data1))
