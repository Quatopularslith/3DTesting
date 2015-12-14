cmake_minimum_required(VERSION 3.3)
project(Cpp3D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SOURCE_FILES src/core/Main.cpp src/core/Main.h src/graphics/Render.cpp src/graphics/Render.h src/graphics/shaders/Shaders.cpp src/graphics/shaders/Shaders.h src/input/Controls.cpp src/input/Controls.h)

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

add_executable(Cpp3D ${SOURCE_FILES})

add_custom_command(TARGET Cpp3D PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        src/resources $<TARGET_FILE_DIR:Cpp3D>)

add_subdirectory(lib/glfw)

include_directories(
        lib/glfw/include/GLFW
        lib/glew/include
        lib/glm/glm
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
    )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set(GLEW_SOURCE lib/glew/src/glew.c)
set(GLEW_HEADERS)
add_library(GLEW_1130 STATIC ${GLEW_SOURCE} ${GLEW_INCLUDE})
target_link_libraries(Cpp3D glfw ${GLFW_LIBRARIES} GLEW_1130 opengl32 ${OPENGL_LIBRARY} ${EXTRA_LIBS})