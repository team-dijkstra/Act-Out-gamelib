
# config variables
CXX := g++
INCLUDE := include test test/util
CXXFLAGS := -Wall -Wextra -ansi -pedantic -std=c++0x -x c++ -O3 -g
LDFLAGS :=
OBJDIR := obj
BINDIR := bin
DOCDIR := doc
MSDIR := .msdir
LOGDIR := log

PROGS := testrunner # nuclient nuserver
nuclient_OBJS :=
nuserver_OBJS := $(patsubst %.cc,%.o,$(notdir $(wildcard src/*.cc)))
testutil_OBJS := $(patsubst %.cc,%.o,$(notdir $(wildcard test/util/*.cc)))
testrunner_OBJS := $(patsubst %.cc,%.o,$(notdir $(wildcard test/*.cc))) $(testutil_OBJS) $(nuserver_OBJS)
testrunner_LIBS := dl cppunit

check_PROGS := cppunit cppcheck valgrind cppncss

# functions

space :=
space +=

define pack
$(subst $(space),:,$1)
endef

define unpack
$(subst :,$(space),$1)
endef

define eq
$(filter $1,$2)
endef

#
# $1 - the file to find
# $2 - the list of paths to search
#
# returns the set of paths the file was found on, nothing otherwise.
#
define path_find 
$(strip $(foreach path,$2,$(wildcard $(abspath $(path))/*$1*)))
endef

#
# Generates check targets for all of the tools in $2 that can be found on
# the path. Generated targets look like <program>.<check>. The check is
# also expected to be the same as the name of the tool that performs it.
#
# $1 - the list of checks to try to determine the availability of.
# $2 - a list of paths to search
#
define available_checks 
$(strip $(foreach check,$1,\
$(if $(call path_find,$(check),$2),\
$(check),\
$(warning $(check) not available. check skipped.))))
endef

define rule_t
$1: $2
	$3
endef

# the library path searched by the compiler
cclibpath := $(patsubst =%,%,$(word 6,$(shell $(CXX) -print-search-dirs)))

compile = $(CXX) $(addprefix -I,$(INCLUDE)) $(CXXFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)
link = $(CXX) $(LDFLAGS) -o $@ $^ $(patsubst %,-l%,$1)

# install search paths
vpath %.cc src:test:test/util
vpath %.o $(OBJDIR)
vpath %.d $(OBJDIR)
$(foreach milestone,$(check_PROGS),$(eval vpath %.$(milestone) $(MSDIR)))
vpath % $(BINDIR)

.DEFAULT_GOAL := all
.PHONY: all depend test check clean clean-all

all: $(addprefix $(BINDIR)/,$(PROGS))

# generate target link rules
$(foreach t,$(PROGS),$(eval $(call rule_t,$(BINDIR)/$t,$(addprefix $(OBJDIR)/,$($t_OBJS)) | $(BINDIR),$$(call link,$($t_LIBS)))))

# generate directory rules
$(foreach d,$(BINDIR) $(OBJDIR) $(LOGDIR) $(MSDIR) $(DOCDIR),$(eval $(call rule_t,$d,,mkdir -p $d)))

$(OBJDIR)/%.o: %.cc | $(OBJDIR)
	$(compile)

$(MSDIR)/%.cppunit: % | $(MSDIR) $(LOGDIR)
	$< > $(LOGDIR)/$(@F).log
	@if [ $$CI ]; then cat $(LOGDIR)/$(@F).log; fi
	@touch $@

$(MSDIR)/%.valgrind: % | $(MSDIR) $(LOGDIR)
	valgrind --xml-file=$(LOGDIR)/$(@F).err.xml --log-file=$(LOGDIR)/$(@F).log --tool=memcheck $<
	@if [ $$CI ]; then cat $(LOGDIR)/$(@F).log; fi
	@touch $@

# TODO: does cppcheck actually need to build? or does it just use the source?
$(MSDIR)/%.cppcheck: % | $(MSDIR) $(LOGDIR)
	cppcheck $(addprefix -I ,$(INCLUDE)) --template gcc --xml-version=2 --error-exitcode=0 --inline-suppr --enable=all . 2> $(LOGDIR)/$(@F).log.xml
	@if [ $$CI ]; then cat $(LOGDIR)/$(@F).log.xml; fi
	@touch $@

$(MSDIR)/%.cppncss: % | $(MSDIR) $(LOGDIR)
	cppncss -xml -f=$(LOGDIR)/$(@F).log.xml src include test test/util
	@ if [ $$CI ]; then cat $(LOGDIR)/$(@F).log.xml; fi
	@ touch $@

ifeq ($(MAKECMDGOALS),check)
check: $(addprefix $(MSDIR)/testrunner.,$(call available_checks,$(check_PROGS),$(call unpack,$(PATH)))) ;
endif

test: $(MSDIR)/testrunner.cppunit
	@echo Testing ran successfully. See the logs in the $(LOGDIR) directory.

clean:
	rm -rf *~ $(OBJDIR)/*.o $(BINDIR)/*

clean-all: clean
	rm -rf $(OBJDIR)/*.d $(MSDIR)/* $(LOGDIR)/* $(DOCDIR)/*

ifneq ($(MAKECMDGOALS),clean)
include $(wildcard $(OBJDIR)/*.d)
endif

