#
# Makefile for a CS420 lab or programming assignment.
# Do not modify this file!!!
#

SUBMIT_URL = https://cs.ycp.edu/marmoset/bluej/SubmitProjectViaBlueJSubmitter
COURSE_NAME = CS 420
SEMESTER = Fall $(shell date +%Y)
PROJECT_NUMBER = assign01

CC = gcc
CFLAGS = -Wall -std=c11

all: filecopy


filecopy: clean filecopy.c
	$(CC) $(CFLAGS) filecopy.c -o filecopy

runTest: all
	@rm -rf test1_input_copy.txt filecopy_copy filecopy_copy_2
	@echo "=================================================================="
	@echo "TEST #1"
	@echo "Running filecopy on test1_input.txt"
	@echo "================================="
	./filecopy test1_input.txt test1_output.txt
	@echo ""
	@echo "================================="
	@echo "Checking to see if files differ"
	@echo "..."
	@diff -qs test1_input.txt test1_output.txt || exit 0
	@echo "=================================================================="
	@echo ""
	@echo ""
	@echo "=================================================================="
	@echo "TEST #2"
	@echo "Running filecopy on test2_input.txt"
	@echo " -- overwriting a long file with a shorter file"
	@echo "================================="
	cp test1_input.txt test2_output.txt
	./filecopy test2_input.txt test2_output.txt
	@echo ""
	@echo "================================="
	@echo "Checking to see if files differ"
	@echo "..."
	@diff -qs test2_input.txt test2_output.txt || exit 0
	@echo "=================================================================="
	@echo ""
	@echo ""
	@echo "=================================================================="
	@echo "TEST #3"
	@echo "Running filecopy on filecopy"
	@echo "================================="
	./filecopy filecopy filecopy_copy
	@echo ""
	@echo "================================="
	@echo "Checking to see if files differ"
	@echo "..."
	@diff -aqs filecopy filecopy_copy || exit 0
	@echo "=================================================================="
	@echo ""
	@echo ""
	@echo "=================================================================="
	@echo "TEST #4"
	@echo "Running filecopy_copy on filecopy"
	@echo "================================="
	./filecopy_copy filecopy filecopy_copy_2
	@echo ""
	@echo "================================="
	@echo "Checking to see if files differ"
	@echo "..."
	@diff -aqs filecopy filecopy_copy_2 || exit 0
	@echo "=================================================================="
	@echo ""

clean:
	rm -f *.o *.exe *~ filecopy filecopy_copy filecopy_copy_2 test1_output.txt test2_output.txt solution.zip submit.properties



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


