add_library(libcreate OBJECT
  black.c
  buildlut.c
  create.c
  eye.c
  fractsurf.c
  gaussmat.c
  gaussnoise.c
  grey.c
  identity.c
  invertlut.c
  logmat.c
  mask.c
  mask_butterworth.c
  mask_butterworth_band.c
  mask_butterworth_ring.c
  mask_fractal.c
  mask_gaussian.c
  mask_gaussian_band.c
  mask_gaussian_ring.c
  mask_ideal.c
  mask_ideal_band.c
  mask_ideal_ring.c
  perlin.c
  point.c
  sines.c
  text.c
  tonelut.c
  worley.c
  xyz.c
  zone.c
)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libcreate PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)

