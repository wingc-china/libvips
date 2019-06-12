add_library(libfreqfilt OBJECT
    freqfilt.c
    fwfft.c
    invfft.c
    freqmult.c
    spectrum.c
    phasecor.c
)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libfreqfilt PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)

