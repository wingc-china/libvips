add_library(libdraw OBJECT
  draw.c
  drawink.c
  draw_circle.c
  draw_flood.c
  draw_image.c
  draw_line.c
  draw_mask.c
  draw_rect.c
  draw_smudge.c
)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libdraw PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)
