include(ProjectDefaults)

check_include_file(sys/resource.h HAVE_SYS_RESOURCE_H)
if(HAVE_SYS_RESOURCE_H)
    add_definitions(-DHAVE_SYS_RESOURCE_H=1)
endif()

check_include_file(unistd.h HAVE_UNISTD_H)
if(HAVE_UNISTD_H)
    add_definitions(-DHAVE_UNISTD_H=1)
endif()

if(WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN
        -D_CRT_SECURE_NO_WARNINGS
        -D_CRT_NONSTDC_NO_WARNINGS)
endif()

include_directories(
    .
    ../../include
    ../../src/core
    ../common
    ${BOSON_INT_DIST_DIR}/include)

list(APPEND SOURCES
    main.cc
    ../common/utils.cc
)

list(APPEND DEPENDS
    cpp-httplib
    boson0)

if(ENABLE_SHARED)
    set(BOSON_LIB boson-shared)
else()
    set(BOSON_LIB boson-static)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(SYSTEM_LIBS pthread dl)
endif()

set(LIBS
    sqlite3)

if(WIN32)
    add_definitions(
        -DWIN32_LEAN_AND_MEAN
        -D_CRT_SECURE_NO_WARNINGS
        -D_CRT_NONSTDC_NO_WARNINGS)

    set(LIBS
        ${LIBS}
        libsodium.lib
        Ws2_32
        crypt32
        iphlpapi
        Shlwapi)
else()
    set(LIBS
        ${LIBS}
        sodium)
endif()

add_executable(sybiltests ${SOURCES})
target_link_libraries(sybiltests LINK_PUBLIC ${BOSON_LIB} ${LIBS} ${SYSTEM_LIBS})
add_dependencies(sybiltests ${DEPENDS})

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    install(TARGETS sybiltests
        RUNTIME DESTINATION "bin"
        ARCHIVE DESTINATION "lib"
        LIBRARY DESTINATION "lib")
endif()
