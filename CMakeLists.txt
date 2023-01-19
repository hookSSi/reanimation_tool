if(NOT DEFINED ENV{CMAKE_EXPORT_COMPILE_COMMANDS})
    message("ENV(CMAKE_EXPORT_COMPILE_COMMANDS) NOT DEFINED")
    set($ENV{CMAKE_EXPORT_COMPILE_COMMANDS} TRUE)
endif()

cmake_minimum_required( VERSION 3.2 )

project(Reanimation-Tool
    VERSION 0.0.1
    DESCRIPTION "reanimation tool"
    HOMEPAGE_URL "gihub/hookssi"
    LANGUAGES CXX
)

option(CLANG_TIDY   "Enable clang-tidy checks during compilation" OFF)

include(cmake/clang-tidy.cmake)

find_package( OpenGL REQUIRED )

include_directories( "glfw/include" )

include_directories("imgui")
include_directories("imgui/backends")
include_directories("RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem")
include_directories("RuntimeCompiledCPlusPlus/Aurora/RuntimeCompiler")
include_directories("imgui-node-editor")
include_directories("reanimation-ui")
include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( BUILD_EXAMPLES OFF CACHE BOOL  "RCCpp libsonly" )

add_subdirectory( glfw )
add_subdirectory( RuntimeCompiledCPlusPlus/Aurora )
add_subdirectory( imgui-node-editor )

if( UNIX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

if( APPLE )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++" )
endif()

if( WIN32 )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
endif()

set( REANIMATION-TOOL-SRC
    # imgui
     imgui/imgui.h
     imgui/imgui.cpp
     imgui/imgui_internal.h
     imgui/imgui_demo.cpp
     imgui/imgui_draw.cpp
     imgui/imgui_tables.cpp
     imgui/imgui_widgets.cpp
     imgui/imconfig.h
     imgui/backends/imgui_impl_glfw.h
     imgui/backends/imgui_impl_glfw.cpp
     imgui/backends/imgui_impl_opengl2.h
     imgui/backends/imgui_impl_opengl2.cpp

    # my app
     reanimation-ui/reanimation_ui.h
     reanimation-ui/reanimation_ui.cpp

    # template
     main.cpp
     StdioLogSystem.h
     StdioLogSystem.cpp
     RCCppMainLoop.h
     RCCppMainLoop.cpp
     SystemTable.h
)

add_executable( Reanimation-Tool ${REANIMATION-TOOL-SRC} )
target_link_libraries( Reanimation-Tool ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} RuntimeCompiler RuntimeObjectSystem ImGuiNodeEditor )

if( MSVC )
    if( ${CMAKE_VERSION} VERSION_LESS "3.6.0" )
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'Reanimation-Tool' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Reanimation-Tool )
    endif()
endif()
