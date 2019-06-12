add_library(libconversion OBJECT
    transpose3d.c
    composite.cpp
    smartcrop.c
    conversion.c
    tilecache.c
    gamma.c
    sequential.c
    flatten.c
    premultiply.c
    unpremultiply.c
    byteswap.c
    cache.c
    copy.c
    embed.c
    flip.c
    insert.c
    join.c
    arrayjoin.c
    extract.c
    replicate.c
    cast.c
    bandjoin.c
    bandrank.c
    recomb.c
    bandmean.c
    bandfold.c
    bandunfold.c
    bandbool.c
    bandary.c
    rot.c
    rot45.c
    autorot.c
    ifthenelse.c
    falsecolour.c
    msb.c
    grid.c
    scale.c
    wrap.c
    subsample.c
    zoom.c)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libconversion PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)
