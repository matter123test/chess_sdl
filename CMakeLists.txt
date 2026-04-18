cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("chess_sdl")

find_package(SDL3 CONFIG REQUIRED)
 find_package(SDL3_image CONFIG REQUIRED)

find_package(imgui CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (${PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS src/*.hpp)

target_sources(${PROJECT_NAME} PRIVATE
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(${PROJECT_NAME}
       PRIVATE

       SDL3::SDL3
       $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>

       imgui::imgui
)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
