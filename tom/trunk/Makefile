#This is automatically generated by the configure.py script
#Keep your dirty hands off
#Run ./configure.py to generate a fresh one.
MCC18=mcc18
PIC=18F8722
LIBNAME=FRC_library.lib
ARGS=-D_FRC_BOARD -w3 pa=3
LINKER=mplink
MP2HEX=mp2hex
IFILOAD=picloader
SERIAL_DEV=/dev/ttyS0
READLOG=./read.log
LIB_PATH=/opt/mcc18/lib
CODE_PATH=Z:\home\prog\code\robo2007\trunk\\
INCLUDE_PATH=/opt/mcc18/h
INCLUDE_PATHW=Z:\\opt\\mcc18\\h




ALL_TARGETS=ifi_utilities.o pwm.o controller.o serial_ports.o interrupts.o trajectory.o traj_turn.o user_routines.o adc.o ifi_startup.o joymap.o velocity.o gyro.o user_routines_fast.o main.o traj_straight_nogyro.o traj_null.o 
INCLUDE_FILES=ifi_utilities.h pwm.h controller.h trajectory.h user_routines.h serial_ports.h ifi_aliases.h traj_null.h ifi_default.h interrupts.h delays.h adc.h common_def.h velocity.h traj_straight_nogyro.h gyro.h traj_turn.h joymap.h user_routines_tom.h user_routines_yvette.h 
############ Targets: 
default: FrcCode.hex

#Remove all the individual file backup (The files ending with ~)
#NOTE that this does NOT remove your tbz2 backups!
clean-backup-files:
	@echo -e "Removing all the ~ backup files your annoying editor makes..."
	@find . -name "*~" |xargs rm -f

#Removes all compiled files from the directory
clean: clean-backup-files clean-deps nohex
	@echo -e "Cleaning compiler intermediate files..."
	@rm -rf *.o *.err

#Remove deps folder
clean-deps:
	@echo -e "Cleaning dependency folder..."
	@rm -rf .deps
	@mkdir .deps
	@touch .deps/dummy

#Remove hexfiles
nohex:
	@echo -e "Cleaning linker output and hex files..."
	@rm -rf *.hex *.cod *.cof

#These all start the IFI Loader.
safeload: prettycode clean check load
load: FrcCode.hex
	$(IFILOAD) FrcCode.hex $(SERIAL_DEV)

read:
	@echo -e "Monitoring $(SERIAL_DEV) for data"
	@echo -e "Output will also be logged to $(READLOG)"
	@echo -e "---------"
	@picreader $(SERIAL_DEV) | tee $(READLOG) || /bin/true
	
	
prettycode:
	@echo -e "Using indent to autoformat your .c and .h files..."
	@indent *.c *.h
all: clean FrcCode.hex
%.o: %.c
	@echo -e "Compiling $@..."
	@echo -e "1.   Checking Dependencies for $@"
	@cpp -nostdinc -isystem $(INCLUDE_PATH) -D__$(PIC) -M -MP $< -MF .deps/$*.deps
	@echo -e "2.   Launching Compiler..."
	@echo -n "A thought to keep you occupied:  "
	@fortune -s || echo "GET FORTUNE"
	@$(MCC18) -p=$(PIC) -fo $@ $< /i\""$(INCLUDE_PATHW)"\" $(ARGS) 
	@echo -e "Done with $@."




FrcCode.hex :  $(ALL_TARGETS) $(INCLUDE_FILES)
	@echo -e "Linking..."
	$(LINKER) /l\""$(LIB_PATH)"\" \""`echo $(PIC) | tr F f `.lkr"\" $(ALL_TARGETS) \""$(CODE_PATH)$(LIBNAME)"\" /m\""FrcCode.map"\" /o\""FrcCode.cof"\"
	$(MP2HEX) FrcCode.cof
	@echo -e "Linked FrcCode.hex"



.deps/*: 
	@echo -e "Creating Dependency Makefiles..."
	@mkdir -p .deps
	@touch .deps/dummy
	@echo -e "Done!"

include .deps/*
