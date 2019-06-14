include_directories("${PROJECT_SOURCE_DIR}/libvips/include")

find_package(unofficial-glib CONFIG REQUIRED)

add_executable(vips vips.c)
add_executable(vipsedit vipsedit.c)
add_executable(vipsthumbnail vipsthumbnail.c)
add_executable(vipsheader vipsheader.c)

target_link_libraries(vips PRIVATE ${PROJECT_NAME})
target_link_libraries(vips PRIVATE unofficial::glib::gio
  unofficial::glib::glib
  unofficial::glib::gmodule
  unofficial::glib::gobject)

target_link_libraries(vipsedit PRIVATE ${PROJECT_NAME})
target_link_libraries(vipsedit PRIVATE unofficial::glib::gio
  unofficial::glib::glib
  unofficial::glib::gmodule
  unofficial::glib::gobject)

target_link_libraries(vipsthumbnail PRIVATE ${PROJECT_NAME})
target_link_libraries(vipsthumbnail PRIVATE unofficial::glib::gio
  unofficial::glib::glib
  unofficial::glib::gmodule
  unofficial::glib::gobject)

target_link_libraries(vipsheader PRIVATE ${PROJECT_NAME})
target_link_libraries(vipsheader PRIVATE unofficial::glib::gio
  unofficial::glib::glib
  unofficial::glib::gmodule
  unofficial::glib::gobject)