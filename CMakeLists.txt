cmake_minimum_required(VERSION 3.5)

# Project Name
project(CG_G31)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB SOURCES_SHARED "src/shared/*.cpp")
file(GLOB SOURCES_ENGINE "src/engine/*.cpp" "src/engine/transform/*.cpp" "src/engine/lights/*.cpp" "src/engine/frustum/*.cpp" "src/engine/imgui/*.cpp")
file(GLOB SOURCES_GENERATOR "src/generator/*.cpp")

set(CMAKE_BUILD_TYPE Debug)
set(SOURCES_ENGINE ${SOURCES_SHARED} ${SOURCES_ENGINE})
set(SOURCES_GENERATOR ${SOURCES_SHARED} ${SOURCES_GENERATOR})

add_executable(engine ${SOURCES_ENGINE})
add_executable(generator ${SOURCES_GENERATOR})

set_target_properties(engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

set_target_properties(generator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS} include)
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif()

if(WIN32)
    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

    if(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(ERROR ": GLUT not found")
    endif()

    if(NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
        message(ERROR ": GLEW not found")
    endif()

    if(NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/DevIL.lib")
        message(ERROR ": DevIL not found")
    endif()

    include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew ${TOOLKITS_FOLDER}/devil)
    target_link_libraries(engine ${OPENGL_LIBRARIES}
                                      ${TOOLKITS_FOLDER}/glut/glut32.lib
                                      ${TOOLKITS_FOLDER}/glew/glew32.lib 
                                      ${TOOLKITS_FOLDER}/devil/DevIL.lib)

    target_link_libraries(generator ${OPENGL_LIBRARIES}
                                          ${TOOLKITS_FOLDER}/glut/glut32.lib
                                          ${TOOLKITS_FOLDER}/glew/glew32.lib 
                                          ${TOOLKITS_FOLDER}/devil/DevIL.lib)

    if(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${TOOLKITS_FOLDER}/devil/DevIL.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif()

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else() # Linux and Mac

    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated")

    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    find_package(DevIL REQUIRED)
    include_directories(${IL_INCLUDE_DIR})
    link_directories(${IL_LIBRARY_DIRS})

    if(NOT APPLE)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
        target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
        target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
    else()
        target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${IL_LIBRARIES})
        target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${IL_LIBRARIES})
    endif()

    target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${IL_LIBRARIES})
    target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${IL_LIBRARIES})
    if(NOT GLUT_FOUND)
      message(ERROR ": GLUT not found!")
    endif()

endif()

# Target for compiling with debug flags
add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Building with debug flags"
)
