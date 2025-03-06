cmake_minimum_required(VERSION 3.16)

project(io-sim VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SerialPort LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialPort LinguistTools)

set(TS_FILES io-sim_de_AT.ts)

set(PROJECT_SOURCES
        main.cpp



        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(io-sim
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ledwidget.h ledwidget.cpp
        seesawcanvas.h seesawcanvas.cpp
        seesawgraphcanvas.h seesawgraphcanvas.cpp
        segmentcolon.h segmentcolon.cpp
        segmentdigit.h segmentdigit.cpp
        maincontroller.h maincontroller.cpp
        mainview.h mainview.cpp
        alarmclockmodel.h alarmclockmodel.cpp
        alarmclockview.h alarmclockview.cpp
        alarmclockviewcontroller.h alarmclockviewcontroller.cpp
        iomodel.h iomodel.cpp
        ioview.h ioview.cpp
        ioviewcontroller.h ioviewcontroller.cpp
        textview.h textview.cpp
        textviewcontroller.h textviewcontroller.cpp
        seesawmodel.h seesawmodel.cpp
        seesawview.h seesawview.cpp
        seesawcontroller.h seesawcontroller.cpp
        serialservice.h serialservice.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET io-sim APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(io-sim SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(io-sim
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(io-sim PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SerialPort)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.io-sim)
endif()
set_target_properties(io-sim PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS io-sim
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(io-sim)
endif()
