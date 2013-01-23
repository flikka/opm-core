# GNUmakefile is processed before Makefile, which is why we arrive here
# first; when we call the other makefile, then we must specify its real
# name with the -f parameter

# figure out the number of processors from the system, add one and round
# to nearest integer. this is the maximum number of processes we want running
# at the same time (one for each core and one stuck on I/O)
# if we are running this is a VM, then /proc won't be mounted and we revert
# to single CPU processing
CPUINFO:=/proc/cpuinfo
NUM_CPUS:=$(shell test -r $(CPUINFO) && grep -P -c '^processor\t:' $(CPUINFO) || echo 0)
PROCS:=$(shell echo "("$(NUM_CPUS)+1")"/1 | bc)

# use these utilities if they are available
IONICE:=$(shell test -x "$$(which ionice)" && echo ionice -c2 -n7)
NICE:=$(shell test -x "$$(which nice)" && echo nice)

# we do dependency management the right way; don't attempt to cache
export CCACHE_DISABLE:=1

# ignore that there may be files with these names, we are going to call
# the other make regardless
.PHONY: __everything $(MAKECMDGOALS)

# outsource the processing to the real makefile, running in parallel and
# in a nice environment so that it doesn't hog our workstation. if there
# is nothing else happening on the box, then it will run just as fast
__everything:
	@$(IONICE) $(NICE) $(MAKE) -f Makefile -j $(PROCS) $(MAKECMDGOALS)

# automatically generate all the goals we are asked to make and delegate
# processing of them to the real makefile through the dependency (since
# everything depends on the same thing, then we only call the other make
# once). the dummy command is just there to make sure that make doesn't
# show the "Nothing to do for `foo'" message after processing
$(MAKECMDGOALS): __everything
	@true
