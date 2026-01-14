APPS = app1 app2
BINARIES = $(patsubst %,%.bin,$(APPS))
FAE_HOME = ~/agon/fab

all: $(APPS)
$(DIRS): $(BINARIES)

set_agondev:
	cd app1 ; rm makefile ; ln -s agondev_makefile makefile
	cd app2 ; rm makefile ; ln -s agondev_makefile makefile
	ln -t app1/src -sr src/util.c
	ln -t app1/src -sr include/util.h
	ln -t app2/src -sr src/util.c
	ln -t app2/src -sr include/util.h

set_agdev:
	cd app1 ; rm makefile ; ln -s agdev_makefile makefile
	cd app2 ; rm makefile ; ln -s agdev_makefile makefile
	rm -f app1/src/util.c
	rm -f app1/src/util.h
	rm -f app2/src/util.c
	rm -f app2/src/util.h

$(APPS):
	@echo ---------------------------
	@echo Compile : $@
	$(MAKE) -C $@ install

$(BINARIES): $(APPS)

install: $(BINARIES)
	cp app1.bin $(FAE_HOME)/sdcard
	cp app2.bin $(FAE_HOME)/sdcard
	
	
clean:
	rm -f $(BINARIES)
	cd app1; make clean
	cd app2; make clean

.PHONY: all clean $(APPS)

