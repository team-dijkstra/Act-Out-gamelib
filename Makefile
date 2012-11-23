
PROJECT_NAME := Act-Out!
PROJECT_VERSION := $(shell git describe)
PROJECT_BRIEF := A turn based strategy game library

# user config variables
CXX := g++
INCLUDE := include test test/util
CXXFLAGS := -Wall -Wextra -ansi -pedantic -std=c++0x -O3 -g
CPPFLAGS := $(addprefix -I,$(INCLUDE))
LDFLAGS :=
OBJDIR := obj
BINDIR := bin
DOCDIR := doc
MSDIR := .msdir
LOGDIR := log
# defines what <error> severity attibutes will trigger a build error.
CPPCHECK_SEVERITY_ERR := error warning style

PROGS := testrunner driver 
LIBS := actout
PRECOMPILED_HEADER := precompile.h
driver_SRC := src/driver.cc
actout_SRC := $(filter-out $(driver_SRC),$(wildcard src/*.cc))
testutil_SRC := $(wildcard test/util/*.cc)
test_SRC := $(wildcard test/*.cc)
driver_OBJS := $(patsubst %.cc,%.o,$(notdir $(driver_SRC) $(actout_SRC)))
actout_OBJS := $(patsubst %.cc,%.o,$(notdir $(actout_SRC)))
testutil_OBJS := $(patsubst %.cc,%.o,$(notdir $(testutil_SRC)))
testrunner_OBJS := $(patsubst %.cc,%.o,$(notdir $(test_SRC))) $(testutil_OBJS) $(actout_OBJS)
testrunner_LIBS := dl cppunit

# computed config variables
have_dot := $(if $(shell which dot 2> /dev/null),YES,NO)
basedir := $(abspath .)

check_PROGS := cppunit cppcheck valgrind cppncss
milestones := $(check_PROGS) doxygen latex

# add scripts to the path
export PATH := $(PATH):$(realpath scripts)
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

#
# Creates links to all files in directory $1, in directory $2, that don't
# already exist in directory $2
#
# $1 - the name of the source directory.
# $2 - the name of the destination directory.
#
define create-links
$(foreach hook,\
$(filter-out $(shell ls $2),$(shell ls $1)),\
$(shell ln -s -t $2 $(realpath $1/$(hook)))$(info installed $(hook) hook.)) 
endef

# automagically install git-hooks.
$(call create-links,hooks,.git/hooks)

# the library path searched by the compiler
cclibpath := $(patsubst =%,%,$(word 6,$(shell $(CXX) -print-search-dirs)))

pchcompile = $(CXX) $(CPPFLAGS) $(CXXFLAGS) -x c++-header $< -o $@
compile = $(CXX) $(CPPFLAGS) $(CXXFLAGS) -include $(PRECOMPILED_HEADER) -Winvalid-pch -c -x c++ $< -o $@ -MMD -MF $(@:.o=.d)
link = $(CXX) $(LDFLAGS) -o $@ $^ $(patsubst %,-l%,$1)

# install search paths
vpath %.cc src:test:test/util
vpath %.o $(OBJDIR)
vpath %.d $(OBJDIR)
$(foreach milestone,$(milestones),$(eval vpath %.$(milestone) $(MSDIR)))
vpath % $(BINDIR)

.DEFAULT_GOAL := all
.PHONY: all depend test check docs clean clean-commit clean-all
.INTERMEDIATE: include/$(PRECOMPILED_HEADER).gch

all: $(addprefix $(BINDIR)/,$(PROGS))

# generate target link rules
$(foreach t,$(PROGS),$(eval $(call rule_t,$(BINDIR)/$t,$(addprefix $(OBJDIR)/,$($t_OBJS)) | $(BINDIR),$$(call link,$($t_LIBS)))))

# generate directory rules
$(foreach d,$(BINDIR) $(OBJDIR) $(LOGDIR) $(MSDIR) $(DOCDIR),$(eval $(call rule_t,$d,,mkdir -p $d)))

%.h.gch : %.h
	$(pchcompile)

$(OBJDIR)/%.o: %.cc include/$(PRECOMPILED_HEADER).gch | $(OBJDIR)
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
	cppcheck $(addprefix -I ,$(INCLUDE)) -i test --template gcc --xml-version=2 --error-exitcode=0 --inline-suppr --enable=all . 2> $(LOGDIR)/$(@F).log.xml
	@if [ $$CI ]; then cat $(LOGDIR)/$(@F).log.xml; fi
	@cppcheck-severity $(LOGDIR)/$(@F).log.xml $(CPPCHECK_SEVERITY_ERR)
	@touch $@

$(MSDIR)/%.cppncss: % | $(MSDIR) $(LOGDIR)
	cppncss -xml -f=$(LOGDIR)/$(@F).log.xml src include test test/util
	@if [ $$CI ]; then cat $(LOGDIR)/$(@F).log.xml; fi
	@touch $@

$(MSDIR)/%.doxygen: %/Doxyfile Doxyfile | $(MSDIR) $(LOGDIR) $(DOCDIR)
	doxygen $< > $(LOGDIR)/$(@F).log
	@if [ $$CI ]; then cat $(LOGDIR)/$(@F).log; fi
	@touch $@

$(MSDIR)/%.latex: %.doxygen | $(MSDIR) $(LOGDIR) $(DOCDIR)
	make -C $(DOCDIR)/$*/latex
	@cp -f $(DOCDIR)/$*/latex/refman.log $(LOGDIR)/$*-manual.log
	@ln -f -s $(DOCDIR)/$*/latex/refman.pdf $*-manual.pdf
	@touch $@

ifeq ($(MAKECMDGOALS),check)
check: $(addprefix $(MSDIR)/testrunner.,$(call available_checks,$(check_PROGS),$(call unpack,$(PATH)))) ;
endif

# variable exports needed for doxygen
export basedir have_dot DOCDIR INCLUDE PROJECT_NAME PROJECT_VERSION PROJECT_BRIEF

$(MSDIR)/test.doxygen: $(MSDIR)/src.doxygen $(test_SRC) $(testutil_SRC) $(wildcard test/*.h) $(wildcard test/util/*.h)
$(MSDIR)/src.doxygen: $(actout_SRC) $(wildcard include/*.h)
$(MSDIR)/msic.doxygen: $(actout_SRC) $(test_SRC) $(testutil_SRC) $(wildcard include/*.h) $(wildcard test/*.h) $(wildcard test/util/*.h)

html: $(MSDIR)/src.doxygen $(MSDIR)/test.doxygen
	@echo HTML documentation was built successfully. See the logs in the $(LOGDIR) directory.

latex: $(MSDIR)/src.latex $(MSDIR)/test.latex
	@echo LaTeX documentation was built successfully. See the logs in the $(LOGDIR) directory.

all-doc: $(MSDIR)/misc.doxygen $(MSDIR)/misc.latex
	@echo Combined documentation HTML, and LaTeX documentaiton was built successfully. See the logs in the $(LOGDIR) directory.

test: $(MSDIR)/testrunner.cppunit
	@echo Testing ran successfully. See the logs in the $(LOGDIR) directory.

clean:
	rm -rf *.pdf *~ $(OBJDIR)/*.o $(BINDIR)/*

# TODO: this could use a better name
clean-commit: clean
	rm -rf $(OBJDIR)/*.d $(DOCDIR)/* 

clean-all: clean-commit
	rm -rf $(MSDIR)/* $(LOGDIR)/*

decimate: clean-all
	rm -rf include/*.gch


ifneq ($(MAKECMDGOALS),clean)
include $(wildcard $(OBJDIR)/*.d)
endif

