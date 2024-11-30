# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
#
# Makefile for ChipWhisperer SimpleSerial-AES Program
#
#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
# make debug = Start either simulavr or avarice as specified for debugging, 
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# Target file name (without extension). 
#Following code 2 codeline uncomment, only if these parameters are not given
## This is the base name of the compiled .hex file.
ifeq ($(TARGET),)
  ${info using inputed TARGET '$(TARGET)'}
else
  TARGET=simpleserial-targe
  ${info using saved TARGET '$(TARGET)'}
endif

ifeq ($(SS_VER),)
  ${info using inputed SS_VER '$(SS_VER)'}
else
  SS_VER=SS_VER_2_1
  ${info using saved SS_VER '$(SS_VER)'}
endif

ifeq ($(PLATFORM),)
  ${info using inputed PLATFORM '$(PLATFORM)'}
else
  PLATFORM=CWLITEARM
  ${info using saved PLATFORM '$(PLATFORM)'}
endif


${info using saved CRYPTO_TARGET '$(CRYPTO_TARGET)'}
${info using saved FIRMWAREPATH '$(FIRMWAREPATH)'}
${info using saved FIRMWAREPATH '$(FIRMWAREPATH)'}

# List C source files here.
# Header files (.h) are automatically pulled in.
SRC += $(CRYPTO_TARGET)/main.c $(CRYPTO_TARGET)/network.c

# -----------------------------------------------------------------------------
#debugging:
#	gcc -o debug-target debug-source.c main.c

#Add simpleserial project to build
include $(FIRMWAREPATH)/simpleserial/Makefile.simpleserial

#FIRMWAREPATH = .
include ./Makefile.inc



# Specify additional dependencies for the target
$(TARGET): $(OBJ) network.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

${Debug GOT HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}


# Rule to build network.o from network.c
network.o: $(CRYPTO_TARGET)/network.c $(CRYPTO_TARGET)/network.h
	$(CC) $(CFLAGS) -c -o $@ $<