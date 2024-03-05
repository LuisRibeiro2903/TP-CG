cmake_minimum_required(VERSION 3.0)
project(ProjetoG31 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add executable for engine
add_executable(engine src/engine/engine_main.cpp)

# Add executable for generator
add_executable(generator src/generator/generator_main.cpp)


find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if(WIN32)
    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

    if(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(FATAL_ERROR "GLUT not found")
    endif()

    if(NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
        message(FATAL_ERROR "GLEW not found")
    endif()

    include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew)

    # Link libraries to engine executable
    target_link_libraries(engine ${OPENGL_LIBRARIES} 
                                 ${TOOLKITS_FOLDER}/glut/glut32.lib 
                                 ${TOOLKITS_FOLDER}/glew/glew32.lib)

    # Link libraries to generator executable
    target_link_libraries(generator ${OPENGL_LIBRARIES} 
                                     ${TOOLKITS_FOLDER}/glut/glut32.lib 
                                     ${TOOLKITS_FOLDER}/glew/glew32.lib)

    # Copy DLL files if they exist
    if(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif()

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT engine)

else() # Linux and Mac

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")

    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    if(NOT APPLE)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
        target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
        target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
    else()
        target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
        target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
    endif()

    if(NOT GLUT_FOUND)
        message(FATAL_ERROR "GLUT not found!")
    endif()

endif()

