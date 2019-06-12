add_library(libarithmetic OBJECT 
    find_trim.c
    sum.c
    hough.c
    hough_line.c
    hough_circle.c
    abs.c
    complex.c
    deviate.c
    divide.c
    measure.c
    getpoint.c
    multiply.c
    remainder.c
    sign.c
    statistic.c
    stats.c
    avg.c
    min.c
    max.c
    hist_find.c
    hist_find_ndim.c
    hist_find_indexed.c
    project.c
    profile.c
    subtract.c
    math.c
    arithmetic.c
    binary.c
    unary.c
    nary.c
    unaryconst.c
    relational.c
    boolean.c
    add.c
    linear.c
    invert.c
    math2.c
    round.c)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libarithmetic PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)
