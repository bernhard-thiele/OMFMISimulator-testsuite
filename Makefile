.PHONY : all OMSimulator lua clean

all: OMSimulator

OMSimulator:
	@$(MAKE) -C OMSimulator > OMSimulator.log
	@grep == OMSimulator.log

lua:
	@$(MAKE) -C lua | tee lua.log

clean:
	@$(MAKE) -C OMSimulator clean
	@$(MAKE) -C lua clean
	@rm -f *.log
