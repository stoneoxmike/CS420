cmake_minimum_required(VERSION 3.16)
project(assign03_semaphores)

set(CMAKE_CXX_COMPILER "clang")
set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(MAIN_SOURCE_FILES
        utils.h
        utils.c
        verify.h
        verify.c
        sem_name.h
        main.c)

set(FILE_WRITER_SOURCE_FILES
        utils.h
        utils.c
        verify.h
        verify.c
        sem_name.h
        fileWriter.c)

set(RMSEM_SOURCE_FILES
        sem_name.h
        rmsem.c)


find_package(Threads)

add_executable(main       ${MAIN_SOURCE_FILES})
add_executable(fileWriter ${FILE_WRITER_SOURCE_FILES})
add_executable(rmsem      ${RMSEM_SOURCE_FILES})

target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(fileWriter ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(rmsem ${CMAKE_THREAD_LIBS_INIT})


#############################################################################################################
# The following lines are included to enable compiling, setup, and running of fileWriter in standalone mode
#############################################################################################################
add_executable(fileWriter_standalone ${FILE_WRITER_SOURCE_FILES})
target_compile_definitions(fileWriter_standalone PUBLIC FILEWRITER_STANDALONE_MODE=1)
target_link_libraries(fileWriter_standalone ${CMAKE_THREAD_LIBS_INIT})

# specify command to run after building and prior to executing fileWriter_standalone
set(FILEWRITER_OUTPUT_FILE "testOutput.txt")

add_custom_command(
        OUTPUT ${FILEWRITER_OUTPUT_FILE}
        COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fileWriterTestSetup.sh ${FILEWRITER_OUTPUT_FILE}
        COMMENT "${CMakeCurrentProgramArguments}"
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        
add_custom_target(
        fileWriterTestSetup ALL
        DEPENDS ${FILEWRITER_OUTPUT_FILE})
#############################################################################################################
#############################################################################################################
