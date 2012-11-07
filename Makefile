
# config variables
CC := g++
CXXFLAGS := -Wall -Wextra -ansi -pedantic -std=c++0x -x c++ -O3 -g
LDFLAGS :=
TARGETS := nuclient nuserver testrunner
nuclient_OBJS :=
nuserver_OBJS := $(patsubst %.cc,%.o,$(filter-out test%,$(wildcard *.cc))) 
testrunner_OBJS := $(patsubst %.cc,%.o,$(wildcard test*.cc)) $(nuserver_OBJS)
testrunner_LIBS := dl cppunit

CHECKS := cppcheck valgrind

# functions

space :=
space +=

define unpack
$(subst :,$(space),$1)
endef
#
# $1 - the file to find
# $2 - the list of paths to search
#
# returns the set of paths the file was found on, nothing otherwise.
#
define path_find 
$(strip $(foreach path,$2,$(wildcard $(path)/$1)))
endef

#
# Generates check targets for all of the tools in $2 that can be found on
# the path. Generated targets look like <program>.<check>. The check is
# also expected to be the same as the name of the tool that performs it.
#
# $1 - the name of the program to add checks to.
# $2 - the list of checks to add to the specified program.
#
define available_checks 
$(strip $(foreach check,$2,\
$(if $(call path_find,$(check),\
$(call unpack,$(PATH))),$1.$(check),\
$(warning $(check) not available. check skipped.))))
endef

define rule_t
$1: $2
	$3
endef

compile = $(CC) $(CXXFLAGS) -c $< -o $@ -MMD -MF $(*).d
link = $(CC) $(LDFLAGS) -o $@ $^ $(patsubst %,-l%,$1)

.DEFAULT_GOAL := all
.PHONY: all depend test check clean

all: $(TARGETS)

# generate target link rules
$(foreach t,$(TARGETS),$(eval $(call rule_t,$t,$($t_OBJS),$$(call link,$($t_LIBS)))))

%.o: %.cc
	$(compile)

%.valgrind: %
	valgrind --xml-file=$@.err.xml --log-file=$@.log --tool=memcheck $<
	touch $@

%.cppcheck: %
	cppcheck --template=gcc --xml-version=2 --enable all . > $@.log.xml
	touch $@

check: $(call available_checks,testrunner,$(CHECKS)) ;

test: testrunner
	./testrunner

clean:
	rm -rf *~ *.o *.d $(TARGETS) $(patsubst %,*.%*,$(CHECKS))

ifneq ($(MAKECMDGOALS),clean)
include $(wildcard *.d)
endif

