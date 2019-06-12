add_library(libmorphology OBJECT
    nearest.c
    morphology.c
    countlines.c
    rank.c
    hitmiss.c
    morph.c
    labelregions.c
)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libmorphology PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)

