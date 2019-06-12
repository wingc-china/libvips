add_library(libmosaicing OBJECT
  global_balance.c
  im_avgdxdy.c
  im_chkpair.c
  im_clinear.c
  im_improve.c
  im_initialize.c
  im_lrcalcon.c
  im_lrmerge.c
  im_lrmosaic.c
  im_remosaic.c
  im_tbcalcon.c
  im_tbmerge.c
  im_tbmosaic.c
  match.c
  merge.c
  mosaic.c
  mosaic1.c
  mosaicing.c
)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libmosaicing PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)

