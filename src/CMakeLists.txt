add_executable(Empty
  "main.cpp"
)
target_compile_options(Empty PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Empty PROPERTY CXX_STANDARD 11)
endif()
