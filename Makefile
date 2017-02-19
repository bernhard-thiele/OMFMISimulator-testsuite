.PHONY : me clean

me:
	@$(MAKE) -C me
	@$(MAKE) -C cs

clean:
	@$(MAKE) -C me clean
	@$(MAKE) -C cs clean
