SUBDIRS(pxlib-0.6.3)

add_executable (paradox2xml main.cpp)

include_directories (pxlib-0.6.3)
include_directories (pxlib-0.6.3/include)


target_link_libraries (paradox2xml pxlib)


install(TARGETS paradox2xml DESTINATION bin)
