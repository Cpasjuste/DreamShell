cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

include(toolchain.cmake)

#############
# ds loader
#############
project(loader)
enable_language(ASM)

#############
# code
#############
file(GLOB SOURCES
        src/*.c
        ../../src/drivers/rtc.c
        ../../src/drivers/spi.c
        ../../src/drivers/sd.c
        ../../src/fs/fs.c
        ../../src/fs/fat/dc.c
        ../../src/fs/fat/ff.c
        ../../src/fs/fat/utils.c
        ../../src/fs/fat/option/ccsbcs.c
        ../../src/fs/fat/option/syscall.c
        ../../src/utils/memcpy.S
        ../../src/utils/memset.S
        )

set(INCLUDES
        include
        ../../include
        ../../include/fatfs
        )
set(CFLAGS -DTARGET_NAME=DreamShell_boot_loader_v2.5 -DVERSION="2.5")
set(LDFLAGS kosext2fs z ${KOS_LIBS})

#############
# executable
#############
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})
target_link_libraries(${PROJECT_NAME} ${LDFLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)

include(targets.cmake)