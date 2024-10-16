cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("PirateGame")

# Recursively collect all .cpp files in the source directory and its subdirectories
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/PirateGame/Source/*.cpp")

# Add them to the executable
add_executable(PirateGame ${SOURCES})

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PirateGame PROPERTY CXX_STANDARD 26)
endif()

target_include_directories(PirateGame PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/PirateGame/include/")

# Get the absolute path to the Resources folder
set(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/PirateGame/Resources/")

# Define the RESOURCES_PATH macro for the project
target_compile_definitions(PirateGame PUBLIC RESOURCES_PATH="${RESOURCES_PATH}")

############################################################################
# SFML
############################################################################

# Specify where CMake can find the SFML config files
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/PirateGame/ThirdParty/SFML-2.6.0/lib/cmake/SFML")

# Find the SFML package
find_package(SFML 2.6 COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(PirateGame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Specify where the SFML DLLs are located
set(SFML_DLL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/PirateGame/ThirdParty/SFML-2.6.0/bin")

# Copy SFML DLLs to the output directory after build
add_custom_command(TARGET PirateGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SFML_DLL_DIR}"
    $<TARGET_FILE_DIR:PirateGame>)

# Set profiling flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
