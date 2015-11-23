set ( SOURCES
    "src/sound_player.cpp"
    "src/interface.cpp"
)

set (HEADERS
    "include/sound_player.h"
    "include/sound_player/sound_player_utils.h"
)

include_directories("include")
add_library (sound_player MODULE ${SOURCES} ${HEADERS})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(sound_player PRIVATE ${SFML_LIBRARIES})
endif()
target_link_libraries(sound_player PRIVATE lmscore)
