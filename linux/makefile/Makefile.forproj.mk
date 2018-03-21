#test project Makefile

lib_codec := lib/codec
lib_db := lib/db
lib_ui := lib/ui
libraries := $(lib_codec) $(lib_db) $(lib_codec)
player := app/player

.PHONY: all $(player) $(libraries)

all: $(player)

$(libraries) $(player):
	$(MAKE) --directory=$@

