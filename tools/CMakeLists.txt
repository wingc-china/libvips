include_directories("${PROJECT_SOURCE_DIR}/libvips/include")

add_executable(vips vips.c)

target_link_libraries(vips PRIVATE ${PROJECT_NAME})

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(vips PRIVATE unofficial::glib::gio
  unofficial::glib::glib
  unofficial::glib::gmodule
  unofficial::glib::gobject)