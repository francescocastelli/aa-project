dirs := fill lexp lexm graphRandomCreation

all: test clean

test: $(dirs)

$(dirs):
	$(MAKE) -C $@ -f ../Makefile.test

.PHONY: test clean $(dirs)

clean:
	for i in $(dirs); do $(MAKE) -C $$i -f ../Makefile.test clean; done
