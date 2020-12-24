# INCOMING (HATES SPACES IN THE END OF STR)
LAB_NAME=LAB4
FILENAMES=$(LAB_NAME)# <== Файл лабы

DOSBOX_EXECUTOR=dosbox

MAKEFILE_PATH=$(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_FOLDER='D:\Asm\'# <== папка лабы  | $(patsubst %/,%,$(dir $(MAKEFILE_PATH)))
WORK_FOLDER=D:\Asm\bin# folder with tasm/tlink/td.exe $(CURRENT_FOLDER)/bin
DIST_FOLDER=dist
DATA_FOLDER=data
DEBUG_FOLDER=debug\$(LAB_NAME)# <== папка, область лабы

INPUT_FILE=$(DATA_FOLDER)/INPUT.TXT
OUTPUT_FILE=$(DATA_FOLDER)/OUTPUT.TXT
STARTUP_FILE=$(DATA_FOLDER)/STARTUP.TXT

COMPILE_LOG_FILE=$(DEBUG_FOLDER)/COMPILE.TXT
LINK_LOG_FILE=$(DEBUG_FOLDER)/LINK.TXT

DISK_COMPILATOR_NAME=C
DISK_EXECUTABLE_NAME=D
CMD_INTERFACE=-c

# PARSING FILES
ASSEMBLY = $(foreach filename,$(FILENAMES),$(filename).ASM)
OBJECTS = $(foreach filename,$(FILENAMES),$(filename).OBJ)
EXECUTABLE = $(foreach filename,$(FILENAMES),$(filename).EXE)
MAP = $(foreach filename,$(FILENAMES),$(filename).MAP)

# CMD INTERFACE
CMD = $(CMD_INTERFACE) $(1)

MOVE_CMD = $(call CMD,"copy $(1) $(2)") \
$(call CMD, "del $(1)")

all: build execute# init build or build execute or deb or execute

init:
	mkdir -p debug\$(LAB_NAME)
	
build:
	$(DOSBOX_EXECUTOR) \
	$(call CMD,"mount $(DISK_COMPILATOR_NAME) $(WORK_FOLDER)") \
	$(call CMD,"mount $(DISK_EXECUTABLE_NAME) $(CURRENT_FOLDER)") \
	$(call CMD,"$(DISK_EXECUTABLE_NAME):") \
	$(call CMD,"$(DISK_COMPILATOR_NAME):\TASM.EXE $(ASSEMBLY) < $(STARTUP_FILE) > $(COMPILE_LOG_FILE)") \
	$(call CMD,"$(DISK_COMPILATOR_NAME):\TLINK.EXE $(OBJECTS) < $(STARTUP_FILE) > $(LINK_LOG_FILE)") \
	$(call MOVE_CMD,$(OBJECTS),$(DEBUG_FOLDER)) \
	$(call MOVE_CMD,$(EXECUTABLE),$(DEBUG_FOLDER)) \
	$(call MOVE_CMD,$(MAP),$(DEBUG_FOLDER)) \
	$(call CMD,"exit")

execute:
	$(DOSBOX_EXECUTOR) \
	$(call CMD,"mount $(DISK_EXECUTABLE_NAME) $(DEBUG_FOLDER)") \
	$(call CMD,"$(DISK_EXECUTABLE_NAME):") \
	#$(call CMD,"cls") \
	$(call CMD,"$(EXECUTABLE)")
	
deb: build
	$(DOSBOX_EXECUTOR) \
	$(call CMD,"mount $(DISK_COMPILATOR_NAME) $(WORK_FOLDER)") \
	$(call CMD,"mount $(DISK_EXECUTABLE_NAME) $(CURRENT_FOLDER)") \
	$(call CMD,"$(DISK_EXECUTABLE_NAME):") \
	$(call CMD,"cd \$(DEBUG_FOLDER)") \
	$(call CMD,"$(DISK_COMPILATOR_NAME):\TD.EXE $(EXECUTABLE)")
	