qt_add_executable(Timely
    main.cpp

    # main window ui
    ${CMAKE_SOURCE_DIR}/ui/mainwindow.ui
    ${CMAKE_SOURCE_DIR}/ui/mainwindow.cpp
    ${CMAKE_SOURCE_DIR}/ui/mainwindow.h

    # event dialog ui
    ${CMAKE_SOURCE_DIR}/ui/eventdialog.ui
    ${CMAKE_SOURCE_DIR}/ui/eventdialog.cpp
    ${CMAKE_SOURCE_DIR}/ui/eventdialog.h

    ${CMAKE_SOURCE_DIR}/ui/reminderservice.cpp
    ${CMAKE_SOURCE_DIR}/ui/reminderservice.h

    ${CMAKE_SOURCE_DIR}/ui/searchwindow.h
    ${CMAKE_SOURCE_DIR}/ui/searchwindow.cpp
    ${CMAKE_SOURCE_DIR}/ui/searchwindow.ui

)


target_include_directories(Timely PRIVATE
    ${CMAKE_SOURCE_DIR}/ui
    ${CMAKE_SOURCE_DIR}/core
)


target_link_libraries(Timely PRIVATE Qt::Core Qt::Widgets core)
