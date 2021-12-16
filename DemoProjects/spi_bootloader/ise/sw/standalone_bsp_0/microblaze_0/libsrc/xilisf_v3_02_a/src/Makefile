####################################/-*-Makefile-*- 
#
# Copyright (c) 2008 Xilinx, Inc.  All rights reserved.
#
# Xilinx, Inc.
#
# XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
# COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
# ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
# STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
# IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
# FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  
# XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
# THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
# ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
# FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
# AND FITNESS FOR A PARTICULAR PURPOSE.
# 
######################################################

COMPILER=
ARCHIVER=
CP=cp
COMPILER_FLAGS=
EXTRA_COMPILER_FLAGS=

RELEASEDIR=../../../lib
INCLUDEDIR=../../../include
INCLUDES=-I${INCLUDEDIR} 
ISF_DIR = .

LIB_SRCS = $(ISF_DIR)/xilisf.c \
          $(ISF_DIR)/xilisf_read.c \
          $(ISF_DIR)/xilisf_erase.c \
          $(ISF_DIR)/xilisf_write.c \
          $(ISF_DIR)/xilisf_spr.c 
          
# create ISF_SRCS based on configured options

ISF_SRCS = $(LIB_SRCS)

ISF_OBJS = $(ISF_SRCS:%.c=%.o)
          

EXPORT_INCLUDE_FILES = $(ISF_DIR)/include/xilisf.h \
			$(ISF_DIR)/include/xilisf_atmel.h \
			$(ISF_DIR)/include/xilisf_intelstm.h 

			
libs: libxilisf.a
	cp libxilisf.a $(RELEASEDIR)
	make clean

include: 
	@for i in $(EXPORT_INCLUDE_FILES); do \
	echo ${CP} -r $$i ${INCLUDEDIR}; \
	${CP} -r $$i ${INCLUDEDIR}; \
	done

clean:
	rm -rf obj/*.o	
	rmdir obj
	rm libxilisf.a


libxilisf.a: obj_dir print_msg_isf_base $(ISF_OBJS) 
	@echo "Creating archive $@"
	$(ARCHIVER) rc $@ obj/*.o

obj_dir:
	mkdir -p obj

print_msg_isf_base:
	@echo "Compiling XilIsf Library"

.c.o:
	$(COMPILER) $(COMPILER_FLAGS) $(EXTRA_COMPILER_FLAGS) $(INCLUDES) -c $< -o obj/$(@F)
