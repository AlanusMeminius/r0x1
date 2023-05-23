cmake_minimum_required(VERSION 3.24.0)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
set(VCPKG_APPLOCAL_DEPS ON)

project(R0x1 LANGUAGES CXX)


#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(R0x1 LANGUAGES CXX)

# json
find_package(nlohmann_json CONFIG REQUIRED)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
# spdlog
find_package(spdlog CONFIG REQUIRED)
find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")

# libaria2
include_directories(${PROJECT_SOURCE_DIR}/lib/aria2)
include_directories(src)
link_directories(${PROJECT_SOURCE_DIR}/lib/aria2)
# qt
set(QT_COMPONENTS
        Core
        Gui
        Network
        Widgets
        )

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${QT_COMPONENTS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# src
if (APPLE)
   set(PLATFORM
           src/platform/launchermac.h
           src/platform/launchermac.cpp
           src/platform/framelesswindow.mm
           src/platform/framelesswindow.h
           )
elseif (UNIX)
    set(PLATFORM
            src/platform/launcherlinux.cpp
            src/platform/launcherlinux.h
            )
elseif (WIN32)
    set(PLATFORM
            src/platform/launcherwin.cpp
            src/platform/launcherwin.h
            )
endif ()

set(QRC res/resources.qrc)
set(SRC src/core/launcher.cpp
        src/core/launcher.h
        src/core/app.cpp
        src/core/app.h
        src/core/task.cpp
        src/core/task.h
        src/platform/platform.h

     #   src/util/loger.cpp
    #    src/util/loger.h
        src/core/appevent.cpp
        src/core/appevent.h
        src/libaria2/ariainterface.cpp
        src/libaria2/ariainterface.h
        src/core/setting.cpp
        src/core/setting.h
        src/util/qvarianthelper.h)
set(UI

        src/ui/basewindow.cpp
        src/ui/basewindow.h
        src/ui/sidebar/sidebar.cpp
        src/ui/sidebar/sidebar.h
        src/ui/add/addpage.cpp
        src/ui/add/addpage.h
        src/ui/theme.cpp
        src/ui/theme.h
        src/ui/task/taskpage.cpp
        src/ui/task/taskpage.h
        src/ui/about/aboutpage.cpp
        src/ui/about/aboutpage.h
        src/ui/setting/settingpage.cpp
        src/ui/setting/settingpage.h
        src/ui/components/horizonnavigation.cpp
        src/ui/components/horizonnavigation.h
        src/ui/components/toast.cpp
        src/ui/components/toast.h
        src/ui/help/helppage.cpp src/ui/help/helppage.h)

set(Parser
        src/parser/parser.h
        src/parser/url.h
        src/parser/url.cpp
        src/parser/urlutil.h
        src/parser/urlutil.cpp
        src/parser/bili.cpp
        src/parser/bili.h
        )

add_executable(
        ${PROJECT_NAME}  ${SRC} ${Parser} ${QRC} ${UI} ${PLATFORM} src/main.cpp )
# List of Qt components required to build the app.

foreach (COMPONENTS ${QT_COMPONENTS})
    set(LIB ${LIB} Qt${QT_VERSION_MAJOR}::${COMPONENTS})
endforeach ()


if (APPLE)
    set(ARIA2 libaria2.dylib)
elseif (UNIX)
elseif (WIN32)
    set(ARIA2 )
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
        )
target_include_directories(${PROJECT_NAME} PRIVATE ${SIMPLEINI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE
        ${LIB}
        ${ARIA2}
        nlohmann_json::nlohmann_json
        curl
        spdlog::spdlog
        spdlog::spdlog_header_only
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${EXECUTABLE_OUTPUT_PATH}"
        BUNDLE DESTINATION "${EXECUTABLE_OUTPUT_PATH}"
        LIBRARY DESTINATION "${EXECUTABLE_OUTPUT_PATH}"
        )
