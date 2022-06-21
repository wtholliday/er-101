firmware: 
	+$(MAKE) -f scripts/firmware.mk

clean:
	+$(MAKE) -f scripts/firmware.mk clean
	rm -f test/test

dist-clean:
	rm -rf release debug testing

check:
	+$(MAKE) -f scripts/check.mk
