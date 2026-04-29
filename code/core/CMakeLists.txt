add_library(core STATIC
    Event.cpp
    Event.h
    DateRange.cpp
    DateRange.h
    EventManager.cpp
    EventManager.h
    IdGenerator.h
    TextQuery.h
    Validate.h
    IStorage.h
    JsonStorage.h
    JsonStorage.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core PUBLIC
        Qt::Core
)

target_compile_features(core PUBLIC cxx_std_20)
