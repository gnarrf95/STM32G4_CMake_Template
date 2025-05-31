cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_TOOLCHAIN_FILE gcc-arm-none-eabi)

project(STM32G4_CMake_Template)
enable_language(C ASM)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32G431KBTX_FLASH.ld)
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

set(SOURCES
	App/startup_stm32g431kbtx.s
	App/main.c
	App/syscalls.c
	App/sysmem.c
)

set(INCLUDES
)

set(LIBRARIES
)

set(DEFINES
)



add_executable(${EXECUTABLE} ${SOURCES})
target_compile_options(${EXECUTABLE} PRIVATE
	-mthumb
	-mcpu=cortex-m4
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard	

	-Wall
	-Wpedantic
	-Wno-unused-parameter
	-ffunction-sections
	-fdata-sections
)
target_link_options(${EXECUTABLE} PRIVATE
	-T${LINKER_SCRIPT}

	-mthumb
	-mcpu=cortex-m4
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard

	--specs=nosys.specs
	-lc
	-lm
	-Wl,--start-group
	-Wl,--end-group
	-Wl,--print-memory-usage
	-Wl,-Map=${CMAKE_PROJECT_NAME}.map
)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
	COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
)
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
)

