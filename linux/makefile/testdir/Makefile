#test project Makefile

lib_codec := lib/codec
lib_db := lib/db
lib_ui := lib/ui
libraries := $(lib_codec) $(lib_db) $(lib_ui)
player := app/player

.PHONY: all $(player) $(libraries)

all: $(player)

#决定player和libries的依赖关系
$(player) : $(libraries)

$(player) $(libraries):
	@#$(MAKE) --directory=$@
	@#与上面的 --directory等价，递归编译
	$(MAKE) -C $@

