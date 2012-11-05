
# config variables
CC := g++
CXXFLAGS := -Wall -Wextra -ansi -pedantic -std=c++0x -x c++ -O3 -g
LDFLAGS :=
TARGETS := nuclient nuserver testrunner
nuclient_OBJS :=
nuserver_OBJS := $(patsubst %.cc,%.o,$(filter-out test%,$(wildcard *.cc))) 
testrunner_OBJS := $(patsubst %.cc,%.o,$(wildcard test*.cc)) $(nuserver_OBJS)
testrunner_LIBS := dl cppunit

# functions
define rule_t
$1: $2
	$3
endef
compile = $(CC) $(CXXFLAGS) -c $< -o $@ -MMD -MF $(*).d
link = $(CC) $(LDFLAGS) -o $@ $^ $(patsubst %,-l%,$1)

.DEFAULT_GOAL := all
.PHONY: all depend test clean

all: $(TARGETS)

# generate target link rules
$(foreach t,$(TARGETS),$(eval $(call rule_t,$t,$($t_OBJS),$$(call link,$($t_LIBS)))))

%.o: %.cc
	$(compile)

# todo 
test: testrunner
	./testrunner

clean:
	rm -rf *.o *.d $(TARGETS)

ifneq ($(MAKECMDGOALS),clean)
include $(wildcard *.d)
endif

