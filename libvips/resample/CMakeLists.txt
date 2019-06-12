add_library(libresample OBJECT 
    thumbnail.c
    mapim.c
    affine.c
    quadratic.c
    resample.c
    similarity.c
    resize.c
    shrink.c
    shrinkh.c
    shrinkv.c
    reduce.c
    reduceh.cpp
    reducev.cpp
    interpolate.c
    transform.c
    bicubic.cpp
    lbb.cpp
    nohalo.cpp
    vsqbs.cpp)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libresample PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)

