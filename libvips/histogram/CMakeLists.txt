add_library(libhistogram OBJECT
    histogram.c
    hist_cum.c
    hist_entropy.c
    hist_equal.c
    hist_ismonotonic.c
    hist_local.c
    hist_match.c
    hist_norm.c
    hist_plot.c
    hist_unary.c
    maplut.c
    percent.c
    stdif.c
)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libhistogram PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)

