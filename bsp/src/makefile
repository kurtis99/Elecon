#makefile

#  scmRTOS avr-gcc port
#
#  project-dependent makefile for samples
#

#Select controller type
#CONTROLLER_TYPE = MRTP3
#CONTROLLER_TYPE = MRTP4
CONTROLLER_TYPE = MRTP4_MORE_RAM
#CONTROLLER_TYPE = MK035
#CONTROLLER_TYPE = MK035NORAM

SUBSYSTEM_TYPE = PDZ
#SUBSYSTEM_TYPE = BOIL
#SUBSYSTEM_TYPE = TEPLO
#SUBSYSTEM_TYPE = COND
#SUBSYSTEM_TYPE = VENT

# Y/N - !!! N for gcc < 4.x
MAKE_SMALLEST_HEX = Y

# point to start of project sources subtree,
PROJ_SRCTOP := .

#put the name of the target file here (without extension)
TRG	= Project
TRG_NAME = ЩПЗ
TRG_CPY = $(TRG_NAME)_$(MCU)

# project modules (directories with source files)
# "current" directory (.) included automatically in gcc-avr.make
MODULES += ../board
ifeq ($(CONTROLLER_TYPE), MK035)
MODULES += ../board/mk035
endif
ifeq ($(CONTROLLER_TYPE), MRPT3) 
MODULES += ../board/mrtp3
endif
ifeq ($(CONTROLLER_TYPE), MRPT4) 
MODULES += ../board/mrtp4
endif
ifeq ($(CONTROLLER_TYPE), MRTP4_MORE_RAM) 
MODULES += ../board/mrtp4
endif
MODULES += ../board/scmRTOS/AVR
MODULES += ../board/scmRTOS/Common
MODULES += ../board/lib/strings
MODULES += ../board/lib
MODULES += ../board/lib/i2c
MODULES += ../board/lib/lcd
MODULES += ../board/lib/menu
MODULES += ../board/lib/misc
MODULES += ../net_pack
MODULES += ../subsys
MODULES += ../subsys/devs
ifeq ($(SUBSYSTEM_TYPE), BOIL)
MODULES += ../subsys/boil
endif
ifeq ($(SUBSYSTEM_TYPE), COND)
MODULES += ../subsys/cond
endif
ifeq ($(SUBSYSTEM_TYPE), PDZ)
MODULES += ../subsys/pdz
endif
ifeq ($(SUBSYSTEM_TYPE), VENT)
MODULES += ../subsys/vent
endif
ifeq ($(SUBSYSTEM_TYPE), TEPLO)
MODULES += ../subsys/teplo
endif  
MODULES += ./ 

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency. You can then use this symbol in your source code to
#     calculate timings. Упячка следит за тобой, Do NOT tack on a 'UL' at the
#     end, this will be done automatically to create a 32-bit value in your
#     source code.
#     Реально используемые значения 
#         F_CPU =  7372800
#         F_CPU = 11059200
#         F_CPU = 14745600

ifeq ($(CONTROLLER_TYPE),MK035)
    MCU := atmega1280
    I_HAVE_NORAM = 0
    F_CPU = 14745600
endif

ifeq ($(CONTROLLER_TYPE),MK035noram)
    MCU := atmega1280
    I_HAVE_NORAM = 1
    F_CPU = 14745600
endif

ifeq ($(CONTROLLER_TYPE),MRTP4)
    MCU := atmega128
    I_HAVE_NORAM = 1
    F_CPU = 11059200
endif

ifeq ($(CONTROLLER_TYPE),MRTP4_MORE_RAM)
    MCU := atmega1281
    I_HAVE_NORAM = 1
    F_CPU = 11059200
endif

ifeq ($(CONTROLLER_TYPE),MRTP3)
    MCU := atmega32
    I_HAVE_NORAM = 1
    F_CPU = 7372800
endif

TRGPGMEXT := hex
#eep

# additional libraries and object files to link
LIB =

# assembler flags
ASFLAGS =

OPT = -Os  -mcall-prologues

# compiler flags
CSTD = # -std=c++98 --pedantic

# additional flags transmit to programm
ADD_COMPILE_FLAGS  = -DF_CPU=$(F_CPU)UL
ADD_COMPILE_FLAGS += -DI_HAVE_NORAM=$(I_HAVE_NORAM)

CWARN += -Wextra
#CWARN += -Wstrict-prototypes -Wno-main
CWARN += -Wall
CFLAGS  = -g3 -s $(OPT) $(CSTD) $(CWARN) $(ADD_COMPILE_FLAGS) \
 -fno-exceptions -fno-rtti \
 -funsigned-bitfields -fshort-enums

# linker flags
#---------------- Library Options ----------------
#LDFLAGS =
ifeq ($(CONTROLLER_TYPE),MK035)
    LDFLAGS = -T ../board/lib/scripts/linker.ld
endif

ifeq "$(MAKE_SMALLEST_HEX)" "Y"
    CFLAGS += -ffunction-sections -fdata-sections
    LDFLAGS += -Wl,--gc-sections
    LDFLAGS += -Wl,--relax
endif

#-----------------------------------------------------------------------
#
#  This makefile add avr-gcc directory at start of PATH for easy changing
#  of avr-gcc version by changing (or overriding in project makefile)
#  only one variable AVRGCC.
#
#  avr-gcc.mak assume that directories organised as
#
#  proj/obj -.
#  proj/lst -+- working and output directories
#  proj/exe -'
#  proj/src - sources base directory
#
# Externally defined variables:
#
#  AVRGCC = Path to avr-gcc base directory (can contain spaces,
#       '/' must be used instead of '\', no slash at the end).
#
#  MCU = Target processor name
#  TRG = Target name (project name)
#  LIB = Additional libraries
#  CFLAGS  = C  project-dependent flags
#  ASFLAGS = AS project-dependent flags
#  LDFLAGS = LD project-dependent flags
#
#  PROJ_SRCTOP = Base directory of source files subtree. Must point to
#       proj/src and can be relative from makefile location.
#       For example, when main project makefile located at
#       proj/src/proj_main/  you can set PROJ_SRCTOP=..
#       For "simple" project with all sources and makefile placed to
#       proj/src you can set PROJ_SRCTOP=.
#
#  MODULES = Space separated source directories list (from PROJ_SRCTOP point)
#       All .c and .S files in this directories will be compiled and linked.
#

# do not print any commands
.SILENT :

#-----------------------------------------------------------------------
#
CC		:= avr-gcc
AS		:= avr-gcc -x assembler-with-cpp
OBJTOOL := objtool
BIN		:= avr-objcopy
OBJCOPY := avr-objcopy
OBJDUMP := avr-objdump
SIZE	:= avr-size
COPY    := cp
NM      := avr-nm
PROG	:= avrdude
CTAGS_EX := ctags-exuberant

ELFSIZE = avr-mem.sh $(TRGELF) $(MCU)

#-----------------------------------------------------------------------
#
OBJDIR := ./obj
LSTDIR := ./lst
EXEDIR := ./exe

SRCDIRS := $(MODULES)
INCDIRS := $(SRCDIRS)

CSRC	:= $(wildcard $(addsuffix /*.c,$(SRCDIRS)))
CPPSRC	:= $(wildcard $(addsuffix /*.cpp,$(SRCDIRS)))
ASRC    := $(wildcard $(addsuffix /*.S,$(SRCDIRS)))
BAK      = $(wildcard $(addsuffix /*.*~*,$(SRCDIRS)))
OBJ	:= $(addprefix $(OBJDIR)/,$(notdir $(CSRC:.c=.o) $(CPPSRC:.cpp=.o) $(ASRC:.S=.o) ))
LST	:= $(addprefix $(LSTDIR)/,$(notdir $(CSRC:.c=.lst) $(CPSRC:.cpp=.o) $(ASRC:.S=.lst) ))

TRGELF := $(EXEDIR)/$(TRG).elf
TRGPGM := $(addprefix $(EXEDIR)/$(TRG).,$(TRGPGMEXT))
TRGCOF := $(EXEDIR)/$(TRG).cof

GENDEPFLAGS = -Wp,-MM,-MP,-MT,$@,-MF,$(@:.o=.d)
CFLAGS  += -mmcu=$(MCU) $(GENDEPFLAGS)
ASFLAGS += -mmcu=$(MCU) # $(GENDEPFLAGS)
LDFLAGS += -mmcu=$(MCU) -Wl,-Map=$(LSTDIR)/$(TRG).map,--cref

# search path for common sources and headers
vpath
vpath %.c $(SRCDIRS)
vpath %.cpp $(SRCDIRS)
vpath %.h $(SRCDIRS)
vpath %.S $(SRCDIRS)

#-----------------------------------------------------------------------
# targets of makefile
#
.PHONY : all debug printok depends

# default target - binaries for AVR programming
all:	begin $(TRGPGM) dump printok make_chti

begin:
	echo ======== Beginning of project  "$(TRG)"  processing ; $(CC) --version ;\
	mkdir -p $(OBJDIR) $(EXEDIR) $(LSTDIR)

printok:  $(TRGELF)
	echo ======== All OK,  project size: ; $(ELFSIZE) $<

make_chti:
	$(NM) -n -C -S $(EXEDIR)/$(TRG).elf > $(EXEDIR)/chti.mnu
#-----------------------------------------------------------------------
# Lets programm
#
prog0:
	$(PROG) -p $(MCU) -P /dev/ttyUSB0 -c avrisp2 -e -v -U flash:w:$(EXEDIR)/$(TRG).hex
prog1:
	$(PROG) -p $(MCU) -P /dev/ttyUSB1 -c avrisp2 -e -v -U flash:w:$(EXEDIR)/$(TRG).hex

ctags:
	$(CTAGS_EX) --extra=+q -R ../* /usr/local/avr/avr/include/
#-----------------------------------------------------------------------
# compilation rules
#
$(OBJDIR)/%.o : %.c
	echo ====  Compiling $< ; \
	$(CC) -c $(CFLAGS) $(addprefix -I,$(INCDIRS)) \
	-Wa,-ahlmsd=$(LSTDIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(OBJDIR)/%.o : %.cpp
	echo ====  Compiling $< ; \
	$(CC) -c $(CFLAGS) $(addprefix -I,$(INCDIRS)) \
	-Wa,-ahlmsd=$(LSTDIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(OBJDIR)/%.o : %.S
	echo ====  Compiling $< ; \
	$(AS) -E $(ASFLAGS) $(addprefix -I,$(INCDIRS)) $(GENDEPFLAGS) $< ; \
	$(AS) -c $(ASFLAGS) $(addprefix -I,$(INCDIRS)) \
	-Wa,-alm=$(LSTDIR)/$(notdir $(<:.S=.lst)) $< -o $@

%.s : %.c
	echo ====  Generate assembly source from $< ; \
	$(CC) -S $(CFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.c=.s)

%.s : %.cpp
	echo ====  Generate assembly source from $< ; \
	$(CC) -S $(CFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.cpp=.s)

%.E : %.c # preprocess only
	echo ====  Generate PREPROCESSED file from $< ; \
	$(CC) -E $(CFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.c=.E)

#-----------------------------------------------------------------------
# elf post-processing rules
#

# hex-files for programmer
%.hex: %.elf
	echo ====  extract $(notdir $@) ; \
	$(BIN) -O ihex -R .eeprom $< $@

%.eep: %.elf
	echo ====  extract $(notdir $@) ; \
	$(BIN) -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 $< $@

# files for simulator
%.obj: %.elf
	echo ====  extract $(notdir $@) ; \
	$(BIN) -O avrobj -R .eeprom $< $@

%.cof: %.elf
	echo ====  extract $(notdir $@) ; \
	$(OBJTOOL) loadelf $< mapfile $*.map writecof $@

#	$(OBJCOPY) --debugging \
#	--change-section-address .data-0x800000 \
#	--change-section-address .bss-0x800000 \
#	--change-section-address .noinit-0x800000 \
#	--change-section-address .eeprom-0x810000  \
#	-O coff-avr $< $@


# "dizassemble" elf file
dump: $(TRGELF)
	echo ====  disassemble $(notdir $<) ; \
	$(OBJDUMP) -d -S -C $< >$(LSTDIR)/$(TRG).dump

#-----------------------------------------------------------------------
# link: instructions to create elf output file from object files
#
.SECONDARY : $(TRG).elf
.PRECIOUS : $(OBJ)
$(TRGELF) : $(OBJ)
	echo ====  Link to $(notdir $@) ;\
	$(CC) $^ $(LIB) $(LDFLAGS) -o $@

#-----------------------------------------------------------------------
#  dependencies

# all obj files depend on makefile because of makefile contain
#  some compiler's switches (optimisation, debug options, etc..)
$(OBJ) : makefile

# dependencies inclusion
# if make target list not contain this targets - include dependencies
ifeq (,$(findstring clean,$(MAKECMDGOALS)))
 ifeq (,$(findstring cleanall,$(MAKECMDGOALS)))
  ifeq (,$(findstring directories,$(MAKECMDGOALS)))
-include $(shell mkdir $(OBJDIR) 2>/dev/null) $(wildcard $(OBJDIR)/*.d)
  endif
 endif
endif

#-----------------------------------------------------------------------
#  create temporary and ouptut directories
#
.PHONY : directories
directories:
	echo ====  Create working directories ;\
	mkdir -p $(OBJDIR) $(LSTDIR) $(EXEDIR)

.PHONY : dummy
dummy:

#-----------------------------------------------------------------------
# clean project directories from working & backup ('~' suffix) files
#
.PHONY : clean cleanall
clean:
	echo ====  Erasing working directories and indent/editor backup files; \
	rm -f $(TRGCOF) $(EXEDIR)/$(TRG).obj $(EXEDIR)/$(TRG).sym ; \
	rm -f $(TRGELF) ; 			\
	rm -f $(LSTDIR)/* ; 		\
	rm -f $(OBJDIR)/* ; 		\
	rm -f $(CSRC:.c=.s) ; 		\
	rm -f $(BAK)				\
	rm -f $(EXEDIR)/chti.mnu

cleanall: clean
	echo ====  Remove target binaries and working directories ; \
	rm -f $(TRGPGM) ; \
	test -e $(EXEDIR) && rmdir $(EXEDIR) ; \
	test -e $(LSTDIR) && rmdir $(LSTDIR) ; \
	test -e $(OBJDIR) && rmdir $(OBJDIR)


#####	end of avr.make

## end
