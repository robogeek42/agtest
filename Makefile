APPS = app1 app2
BINARIES = $(patsubst %,%.bin,$(APPS))

all: $(APPS)
$(DIRS): $(BINARIES)

set_agondev:
	cd app1 ; rm makefile ; ln -s agondev_makefile makefile
	cd app2 ; rm makefile ; ln -s agondev_makefile makefile

set_agdev:
	cd app1 ; rm makefile ; ln -s agdev_makefile makefile
	cd app2 ; rm makefile ; ln -s agdev_makefile makefile

$(APPS):
	@echo ---------------------------
	@echo Compile : $@
	$(MAKE) -C $@ install

clean:
	rm -f $(BINARIES)
	cd app1; make clean
	cd app2; make clean

.PHONY: all clean $(APPS)

