find_path(GLIB_BIN_DIR
    NAMES glib-mkenums glib-genmarshal
    PATHS ${_VCPKG_TOOLS_DIRS})

set(ENUM_TYPES_SRCS
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/resample.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/memory.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/create.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/foreign.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/conversion.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/arithmetic.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/util.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/image.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/colour.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/operation.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/convolution.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/morphology.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/draw.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/basic.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/object.h
    ${PROJECT_SOURCE_DIR}/libvips/include/vips/region.h
)

add_custom_command(
    OUTPUT enumtypes.c
    COMMAND perl ${GLIB_BIN_DIR}/glib-mkenums --template ${CMAKE_CURRENT_SOURCE_DIR}/enumtemplate ${ENUM_TYPES_SRCS} > enumtypes.c
    DEPENDS enumtemplate
)

add_custom_command(
    OUTPUT vipsmarshal.h
    COMMAND ${GLIB_BIN_DIR}/glib-genmarshal --prefix=vips --header ${CMAKE_CURRENT_SOURCE_DIR}/vipsmarshal.list > vipsmarshal.h
    DEPENDS vipsmarshal.list
)

add_custom_command(
    OUTPUT vipsmarshal.c
    COMMAND echo "#include \"vipsmarshal.h\"" > vipsmarshal.c && ${GLIB_BIN_DIR}/glib-genmarshal --prefix=vips --body ${CMAKE_CURRENT_SOURCE_DIR}/vipsmarshal.list >> vipsmarshal.c
    DEPENDS vipsmarshal.list vipsmarshal.h
)

add_library(libiofuncs OBJECT
    base64.c
    buf.c
    buffer.c
    cache.c
    dbuf.c
    ${CMAKE_CURRENT_BINARY_DIR}/enumtypes.c
    error.c
    gate.c
    generate.c
    header.c
    image.c
    init.c
    mapfile.c
    memory.c
    object.c
    operation.c
    rect.c
    region.c
    reorder.c
    semaphore.c
    sink.c
    sinkdisc.c
    sinkmemory.c
    sinkscreen.c
    system.c
    threadpool.c
    type.c
    util.c
    vector.c
    vips.c
    ${CMAKE_CURRENT_BINARY_DIR}/vipsmarshal.c
    window.c
)

find_package(EXPAT REQUIRED)
target_link_libraries(libiofuncs PRIVATE EXPAT::EXPAT)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libiofuncs PRIVATE
    unofficial::glib::gio
    unofficial::glib::glib
    unofficial::glib::gmodule
    unofficial::glib::gobject
)