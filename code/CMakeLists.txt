cmake_minimum_required(VERSION 3.5)
project(Timely LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)


add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(app)
message(STATUS "resources.qrc exists? ${CMAKE_SOURCE_DIR}/resources.qrc = $<IF:$<BOOL:$<PATH_EXISTS:${CMAKE_SOURCE_DIR}/resources.qrc>>,YES,NO>")

target_sources(Timely PRIVATE ${CMAKE_SOURCE_DIR}/resources.qrc)

include(GNUInstallDirs)

# ---- Unit tests ----
include(CTest)

if(BUILD_TESTING)
  add_subdirectory(test/unit_tests)
endif()



install(TARGETS Timely
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Timely
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})



target_include_directories(Timely PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/core
        ${CMAKE_CURRENT_SOURCE_DIR}/storage
)
