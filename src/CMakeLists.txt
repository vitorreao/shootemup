find_package(SDL3 CONFIG REQUIRED)

add_executable(Shootemup
  "main.c"
)
target_compile_options(Shootemup PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
target_link_libraries(Shootemup PRIVATE SDL3::SDL3)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Shootemup PROPERTY C_STANDARD 99)
endif()
