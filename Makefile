.PHONY : all me cs clean

all: me cs

me:
	@$(MAKE) -C me > me.log
	@grep == me.log

cs:
	@$(MAKE) -C cs > cs.log
	@grep == cs.log

clean:
	@$(MAKE) -C me clean
	@$(MAKE) -C cs clean
	@rm *.log
