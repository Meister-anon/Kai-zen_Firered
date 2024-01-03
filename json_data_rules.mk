# JSON files are run through jsonproc, which is a tool that converts JSON data to an output file
# based on an Inja template. https://github.com/pantor/inja

#AUTO_GEN_TARGETS += $(DATA_C_SUBDIR)/items.h

#$(DATA_C_SUBDIR)/items.h: $(DATA_C_SUBDIR)/items.json $(DATA_C_SUBDIR)/items.json.txt
#	$(JSONPROC) $^ $@

#$(C_BUILDDIR)/item.o: c_dep += $(DATA_C_SUBDIR)/items.h

#i think the json.txt file is the source fo json stuff think its the inja file? so I need to remove the items.json.txt before I can get rid of json for items?
#confirmed removed json.txt which was instruction file, and renamed items.json to items.h and works
#also required removal of generated items.h in data file beforehand, to prevent duplicate

AUTO_GEN_TARGETS += $(DATA_C_SUBDIR)/wild_encounters.h
$(DATA_C_SUBDIR)/wild_encounters.h: $(DATA_C_SUBDIR)/wild_encounters.json $(DATA_C_SUBDIR)/wild_encounters.json.txt
	$(JSONPROC) $^ $@

$(C_BUILDDIR)/wild_encounter.o: c_dep += $(DATA_C_SUBDIR)/wild_encounters.h
