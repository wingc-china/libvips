add_library(libcolour OBJECT
    CMYK2XYZ.c
    colour.c
    colourspace.c
    dE00.c
    dE76.c
    dECMC.c
    float2rad.c
    HSV2sRGB.c
    icc_transform.c
    Lab2LabQ.c
    Lab2LabS.c
    Lab2LCh.c
    Lab2XYZ.c
    LabQ2Lab.c
    LabQ2LabS.c
    LabQ2sRGB.c
    LabS2Lab.c
    LabS2LabQ.c
    LCh2Lab.c
    LCh2UCS.c
    profiles.c  #TODO: Should be automatically generated from the profiles/*.icm
    profile_load.c
    rad2float.c
    scRGB2BW.c
    scRGB2sRGB.c
    scRGB2XYZ.c
    sRGB2HSV.c
    sRGB2scRGB.c
    UCS2LCh.c
    XYZ2CMYK.c
    XYZ2Lab.c
    XYZ2scRGB.c
    XYZ2Yxy.c
    Yxy2XYZ.c
)

# TODO
#add_custom_command(
#    OUTPUT profiles.c
#    COMMAND sh 
#    DEPENDS profiles/*
#)


find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libcolour PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)

