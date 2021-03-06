cmake_minimum_required(VERSION 3.17)

project(Redshift)

set(CMAKE_CXX_STANDARD 20)
set(THIRD_PARTY_ROOT ${PROJECT_SOURCE_DIR}/vendor)
set(STEAMWORKS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/steamworks/public)

if(WIN32)
    if(${ARCHITECTURE} STREQUAL "x86")
        set(STEAMWORKS_LIBRARY_LIB ${PROJECT_SOURCE_DIR}/vendor/steamworks/redistributable_bin/steam_api.lib)
        set(STEAMWORKS_LIBRARY_DLL ${PROJECT_SOURCE_DIR}/vendor/steamworks/redistributable_bin/steam_api.dll)
        set(STEAMWORKS_ENCRYPTION_LIBRARY ${PROJECT_SOURCE_DIR}/vendor/steamworks/public/steam/lib/win32/sdkencryptedappticket)
        message("-- Steamworks SDK: Windows x86")
    else()
        set(STEAMWORKS_LIBRARY_LIB ${PROJECT_SOURCE_DIR}/vendor/steamworks/redistributable_bin/win64/steam_api64.lib)
        set(STEAMWORKS_LIBRARY_DLL ${PROJECT_SOURCE_DIR}/vendor/steamworks/redistributable_bin/win64/steam_api64.dll)
        set(STEAMWORKS_ENCRYPTION_LIBRARY ${PROJECT_SOURCE_DIR}/vendor/steamworks/public/steam/lib/win64/sdkencryptedappticket64)
        message("-- Steamworks SDK: Windows x64")
    endif()
endif()

add_subdirectory(core)
add_subdirectory(editor)
add_subdirectory(game)
add_subdirectory(server)
