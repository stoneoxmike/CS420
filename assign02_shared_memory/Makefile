#
# Makefile for a CS420 lab or programming assignment.
# Do not modify this file!!!
#

SUBMIT_URL = https://cs.ycp.edu/marmoset/bluej/SubmitProjectViaBlueJSubmitter
COURSE_NAME = CS 420
SEMESTER = Fall $(shell date +%Y)
PROJECT_NUMBER = assign02

CC =gcc
CFLAGS =-Wall -std=gnu99



all: childProc mainProc


childProc: ipcEx.h childProc.c
	$(CC) $(CFLAGS) childProc.c -o childProc

mainProc: ipcEx.h mainProc.c
	$(CC) $(CFLAGS) mainProc.c -o mainProc


runTest: mainProc childProc
	./mainProc 5


clean:
	rm -f *.o *.exe *~ childProc mainProc solution.zip submit.properties


###############################################
# The following is for submission to Marmoset
###############################################

submit : clean submit.properties solution.zip
	perl submitToMarmoset.pl solution.zip submit.properties

solution.zip : collected-files.txt
	@echo "Creating a solution zip file"
	@zip -9 $@ `cat collected-files.txt`
	@rm -f collected-files.txt

# Create the submit.properties file that describes how
# the project should be uploaded to the Marmoset server.
submit.properties : nonexistent
	@echo "Creating submit.properties file"
	@rm -f $@
	@echo "submitURL = $(SUBMIT_URL)" >> $@
	@echo "courseName = $(COURSE_NAME)" >> $@
	@echo "semester = $(SEMESTER)" >> $@
	@echo "projectNumber = $(PROJECT_NUMBER)" >> $@

# Collect the names of all files that don't appear
# to be generated files.
collected-files.txt :
	@echo "Collecting the names of files to be submitted"
	@rm -f $@
	@find . -not \( \
				-name '*\.o' \
				-or -name '*\.exe' \
				-or -name '*.pl' \
				-or -name '*~' \
				-or -name 'collected-files.txt' \
				-or -name 'submit.properties' \
				-or -type d -path './.idea' -prune \
				-or -type d -path './.vs' -prune \
				-or -type d -path './cmake-build-debug' -prune \
				-or -type d \
			\) -print \
		| perl -ne 's,\./,,; print' \
		> $@

# This is just a dummy target to force other targets
# to always be out of date.
nonexistent :


