.PHONY: all OMSimulator OMSimulatorLua clean

all: OMSimulator OMSimulatorLua

OMSimulator:
	@$(MAKE) -C OMSimulator > OMSimulator.log
	@grep == OMSimulator.log

OMSimulatorLua:
	@$(MAKE) -C OMSimulatorLua > OMSimulatorLua.log
	@grep == OMSimulatorLua.log

clean:
	@$(MAKE) -C OMSimulator clean
	@$(MAKE) -C OMSimulatorLua clean
	@rm -f *.log
