#
# OMNeT++/OMNEST Makefile for routing
#
# This file was generated with the command:
#  opp_makemake -f --deep -L/home/daniel/git/inet/out/$$\(CONFIGNAME\)/src -lINET -DINET_IMPORT -KINET_PROJ=/home/daniel/git/inet
#

# Name of target to be created (-o option)
TARGET = routing$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Ibase \
    -Ie01random \
    -Ie02flooding \
    -Ie03discovery \
    -Ie04dv

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(INET_PROJ)/out/$(CONFIGNAME)/src  -lINET
LIBS += -Wl,-rpath,`abspath $(INET_PROJ)/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/base/NodeDiscoveryBase.o \
    $O/base/NodeBase.o \
    $O/e01random/NodeRandom2.o \
    $O/e01random/NodeRandom.o \
    $O/e02flooding/NodeFlooding.o \
    $O/e03discovery/NodeSimpleDiscovery.o \
    $O/e03discovery/NodeSimpleDiscovery2.o \
    $O/e03discovery/NodeSimpleDiscovery2ext.o \
    $O/e04dv/NodeDistanceVector.o \
    $O/base/discovery_m.o \
    $O/base/vector_m.o \
    $O/base/Packet_m.o

# Message files
MSGFILES = \
    base/discovery.msg \
    base/vector.msg \
    base/Packet.msg

# Other makefile variables (-K)
INET_PROJ=/home/daniel/git/inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f routing routing.exe librouting.so librouting.a librouting.dll librouting.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f base/*_m.cc base/*_m.h
	$(Q)-rm -f e01random/*_m.cc e01random/*_m.h
	$(Q)-rm -f e02flooding/*_m.cc e02flooding/*_m.h
	$(Q)-rm -f e03discovery/*_m.cc e03discovery/*_m.h
	$(Q)-rm -f e04dv/*_m.cc e04dv/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc base/*.cc e01random/*.cc e02flooding/*.cc e03discovery/*.cc e04dv/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/base/NodeBase.o: base/NodeBase.cc \
	base/NodeBase.h \
	base/Packet_m.h
$O/base/NodeDiscoveryBase.o: base/NodeDiscoveryBase.cc \
	base/NodeBase.h \
	base/NodeDiscoveryBase.h \
	base/Packet_m.h \
	base/discovery_m.h
$O/base/Packet_m.o: base/Packet_m.cc \
	base/Packet_m.h
$O/base/discovery_m.o: base/discovery_m.cc \
	base/discovery_m.h
$O/base/vector_m.o: base/vector_m.cc \
	base/vector_m.h
$O/e01random/NodeRandom.o: e01random/NodeRandom.cc \
	base/NodeBase.h \
	base/Packet_m.h \
	e01random/NodeRandom.h
$O/e01random/NodeRandom2.o: e01random/NodeRandom2.cc \
	base/NodeBase.h \
	base/Packet_m.h \
	e01random/NodeRandom2.h
$O/e02flooding/NodeFlooding.o: e02flooding/NodeFlooding.cc \
	base/NodeBase.h \
	base/Packet_m.h \
	e02flooding/NodeFlooding.h
$O/e03discovery/NodeSimpleDiscovery.o: e03discovery/NodeSimpleDiscovery.cc \
	base/NodeBase.h \
	base/NodeDiscoveryBase.h \
	base/Packet_m.h \
	base/discovery_m.h \
	e03discovery/NodeSimpleDiscovery.h
$O/e03discovery/NodeSimpleDiscovery2.o: e03discovery/NodeSimpleDiscovery2.cc \
	base/NodeBase.h \
	base/NodeDiscoveryBase.h \
	base/Packet_m.h \
	base/discovery_m.h \
	e03discovery/NodeSimpleDiscovery2.h
$O/e03discovery/NodeSimpleDiscovery2ext.o: e03discovery/NodeSimpleDiscovery2ext.cc \
	base/NodeBase.h \
	base/NodeDiscoveryBase.h \
	base/Packet_m.h \
	base/discovery_m.h \
	e03discovery/NodeSimpleDiscovery2.h \
	e03discovery/NodeSimpleDiscovery2ext.h
$O/e04dv/NodeDistanceVector.o: e04dv/NodeDistanceVector.cc \
	base/NodeBase.h \
	base/NodeDiscoveryBase.h \
	base/Packet_m.h \
	base/discovery_m.h \
	base/vector_m.h \
	e04dv/NodeDistanceVector.h

