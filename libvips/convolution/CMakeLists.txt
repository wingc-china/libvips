add_library(libconvolution OBJECT
    canny.c
    sobel.c
    convolution.c
    correlation.c
    conv.c
    conva.c
    convf.c
    convi.c
    convasep.c
    convsep.c
    compass.c
    fastcor.c
    spcor.c
    sharpen.c
    gaussblur.c)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libconvolution PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)
