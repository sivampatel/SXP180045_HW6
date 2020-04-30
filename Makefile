#!/usr/bin/make -f                                                                                                                                                                                         
#                                                                                                                                                                                                          
# Filename:             Makefile                                                                                                                                                                           
# Date:                 4/30/2020                                                                                                                                                                          
# Author:               Sivam Patel                                                                                                                                                                        
# Email:                sxp180045@utdallas.edu                                                                                                                                                             
# Version:              1.0                                                                                                                                                                                
# Copyright:            202, All Rights Reserved                                                                                                                                                           
#                                                                                                                                                                                                          
# Description:                                                                                                                                                                                             
#                                                                                                                                                                                                          
#       Make file to build assignment6. It will take all the files and                                                                                                                                     
#       individually compile them. Also includes the needed libraries from 
#       /scratch/perkins.
# 

CXX = g++
CXXFLAGS =
CPPFLAGS = -Wall -g -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

# Executable Name
EXECFILE = CDKMatrix

# Auto include all .cc files
SOURCES := $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

PROJECTNAME = HW6

# Rely on implicit rules for compilation

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#* $(EXECFILE)


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H.%M.%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
