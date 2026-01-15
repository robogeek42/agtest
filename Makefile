APPS = app1 app2
BINARIES = $(patsubst %,%.bin,$(APPS))
MYLIBS = util
FAE_HOME = ~/agon/fab

all: $(APPS)
$(DIRS): $(BINARIES)

set_agondev:
	cd app1 ; rm makefile ; ln -s agondev_makefile makefile
	cd app2 ; rm makefile ; ln -s agondev_makefile makefile
	echo "agondev" > compiler
	mkdir -p app1/include
	cp -f include/* app1/include/
	mkdir -p app2/include
	cp -f include/* app2/include/

set_agdev:
	cd app1 ; rm makefile ; ln -s agdev_makefile makefile
	cd app2 ; rm makefile ; ln -s agdev_makefile makefile
	echo "agdev" > compiler

COMPILER = $(shell cat compiler)

ifeq ($(COMPILER),agondev)
$(MYLIBS): 
	@echo ---------------------------
	@echo "Make Library $@"
	cd $@ ; make lib
	
	@echo "Copy library $@ to app1"
	mkdir -p app1/lib
	cp $@/bin/lib$@.a app1/lib
	
	@echo "Copy library $@ to app2"
	mkdir -p app2/lib
	cp $@/bin/lib$@.a app2/lib
endif

$(APPS): $(MYLIBS)
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

.PHONY: all clean $(MYLIBS) $(APPS)

