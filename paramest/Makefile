TEST = root -l -q -e 'gSystem->Load("../../3rdParty/FMIL/install/linux/lib/libfmilib_shared.so"); gSystem->Load("../../install/lib/libOMSimulatorLib.so");'

FILES = \
test_cfunc_HelloWorld.C \
test_cs_HelloWorld.C \
test_simbin_HelloWorld.C \

# test_cs_HelloWorld_withoutReset_SLOW.C \

FAILINGFILES = \


# Dependency files that are not .mo .mos or Makefile
# Add them here or they will be cleaned.
DEPENDENCIES = \
*.C \
*.sh \
models \
Makefile \
CMakeLists.txt \
README.MD \

CLEAN = `ls | grep -w -v -f deps.tmp`

.PHONY : all clean getdeps

all:
	@echo
	@echo Executing tests...
	@echo
	@for file in $(FILES); do $(TEST) $$file ; done
	@$(MAKE) clean

# Cleans all files that are not listed as dependencies
clean:
	@echo $(DEPENDENCIES) | sed 's/ /\\\|/g' > deps.tmp
	@rm -rf $(CLEAN)

# Run this if you want to list out the files (dependencies).
# do it after cleaning and updating the folder
# then you can get a list of file names (which must be dependencies
# since you got them from repository + your own new files)
# then add them to the DEPENDENCIES. You can find the
# list in deps.txt
getdeps:
	@echo $(DEPENDENCIES) | sed 's/ /\\\|/g' > deps.tmp
	@echo $(CLEAN) | sed -r 's/deps.txt|deps.tmp//g' | sed 's/ / \\\n/g' > deps.txt
	@echo Dependency list saved in deps.txt.
	@echo Copy the list from deps.txt and add it to the Makefile @DEPENDENCIES
