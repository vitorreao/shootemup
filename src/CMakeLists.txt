find_package(libzip CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

create_zip(assets
  "sprites/ship.png"
)

add_executable(Shootemup
  "app.c"
  "app.h"
  "array.c"
  "array.h"
  "list.c"
  "list.h"
  "main.c"
  "opaque.h"
  "resource.c"
  "resource.h"
  "window.c"
  "window.h"
  ${assets}
)
target_compile_options(Shootemup PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
target_link_libraries(Shootemup PRIVATE libzip::zip)
target_link_libraries(Shootemup PRIVATE SDL3::SDL3)
target_link_libraries(Shootemup PRIVATE
  $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Shootemup PROPERTY C_STANDARD 99)
endif()
