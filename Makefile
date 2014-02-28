QMAKE_TARGET  = TLCore
PROJECT_DIR	  := $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

include mk/cs-base.mk
