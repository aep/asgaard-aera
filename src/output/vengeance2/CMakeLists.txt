cmake_minimum_required(VERSION 2.6)

include_directories (xml2mysql /usr/include/mysql src)

add_executable (xml2mysql src/main.cpp src/analyser.cpp src/db.cpp)
target_link_libraries (xml2mysql mysqlclient expat)

