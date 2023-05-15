#
# Makefile for a CS420 lab or programming assignment.
# Do not modify this file!!!
#

SUBMIT_URL = https://cs.ycp.edu/marmoset/bluej/SubmitProjectViaBlueJSubmitter
COURSE_NAME = CS 420
SEMESTER = Fall $(shell date +%Y)
PROJECT_NUMBER = assign03

CC = clang
CFLAGS=-std=c11 -Wall
LIBS=-pthread



all: main rmsem

rmsem: rmsem.c
	$(CC) $(CFLAGS) rmsem.c -o rmsem $(LIBS)

utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c

verify.o: verify.h verify.c
	$(CC) $(CFLAGS) -c verify.c

main: utils.o verify.o fileWriter main.c
	$(CC) $(CFLAGS) main.c -o main utils.o verify.o $(LIBS)
    
fileWriter: utils.o verify.o fileWriter.c
	$(CC) $(CFLAGS) fileWriter.c -o fileWriter utils.o $(LIBS)

fileWriter_standalone: utils.o verify.o fileWriter.c
	$(CC) $(CFLAGS) -DFILEWRITER_STANDALONE_MODE fileWriter.c -o fileWriter_standalone utils.o verify.o $(LIBS)


mainTest: all
	@echo ""
	@echo "=================================================================="
	@echo "Starting pre-run cleanup"
	@echo "=================================================================="
	./rmsem
	@echo "=================================================================="
	@echo "Done with pre-run cleanup"
	@echo "=================================================================="
	@echo ""
	@echo "Running main program ... "
	./main -p 25 -t 25 -f testOutput.txt

fileWriterTest: fileWriter_standalone rmsem
	@echo ""
	@echo "=================================================================="
	@echo "Starting pre-run cleanup and setup"
	@echo "=================================================================="
	./rmsem
	@echo ""
	@echo "Setting up output file for fileWriter standalone run..."
	./fileWriterTestSetup.sh testOutput.txt
	@echo "=================================================================="
	@echo "Done with pre-run cleanup and setup"
	@echo "=================================================================="
	@echo ""
	@echo "Running fileWriter in standalone mode ... "
	./fileWriter_standalone 50 testOutput.txt


clean:
	rm -f *.o *~ solution.zip submit.properties
	rm -rf *.dSYM
	rm -f main fileWriter fileWriter_standalone rmsem testOutput.txt


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


