cmake_minimum_required(VERSION 3.19)
project(qt_project LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(qt_project
    WIN32 MACOSX_BUNDLE
    main.cpp
    admin_window.cpp
    admin_window.h
    admin_window.ui
    student_dialog.h student_dialog.cpp
)

target_link_libraries(qt_project
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS qt_project
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET qt_project
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
