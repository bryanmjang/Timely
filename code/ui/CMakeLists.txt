qt_add_library(ui STATIC
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    eventdialog.h eventdialog.cpp
    eventdialog.ui
    reminderservice.h reminderservice.cpp
    searchwindow.h searchwindow.cpp searchwindow.ui
)

target_link_libraries(ui
    PRIVATE
        Qt::Core
        Qt::Widgets
        core
)
