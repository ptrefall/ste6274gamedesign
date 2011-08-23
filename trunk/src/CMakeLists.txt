
set(SRC_ROOT ${GameDesignClient_SOURCE_DIR}/src)
set(GV_SRC_ROOT ${SRC_ROOT}/GraphicsView)

set(GV_HDRS
	${GV_SRC_ROOT}/OpenGL3GraphicsScene.h
)
SOURCE_GROUP("Header Files\\GraphicsView" FILES ${GV_HDRS})

set(GV_SRCS
	${GV_SRC_ROOT}/OpenGL3GraphicsScene.cpp
)
SOURCE_GROUP("Source Files\\GraphicsView" FILES ${GV_SRCS})

set(SRCS
    ${SRC_ROOT}/main.cpp
)

find_package(Qt4 4.7.3 REQUIRED QtCore QtGui QtOpenGL)
CMP_QT_LIBRARIES_INSTALL_RULES("QtCore;QtGui;QtOpenGL" ${GameDesignClient_BINARY_DIR}/src)
find_package(OpenGL REQUIRED)
find_package(Glew REQUIRED)
find_package(GLM REQUIRED)
set(WINDOW_EXT_LIBS ${OPENGL_gl_LIBRARY})
set(WINDOW_EXT_LIBS ${WINDOW_EXT_LIBS} winmm gdi32)

include(${QT_USE_FILE})
include_directories(${OPENGL_INCLUDE_PATH})
include_directories(${GLEW_INCLUDE_PATH})
include_directories(${GLM_DIR})

QT4_WRAP_CPP(GV_MOCS ${GV_HDRS})
SOURCE_GROUP("Source Files\\GraphicsView" FILES ${GV_MOCS})

add_executable(GameDesignClient ${GV_HDRS} ${GV_SRCS} ${GV_MOCS} ${SRCS})
set_target_properties(GameDesignClient PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(GameDesignClient PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(GameDesignClient
  ${QT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  debug ${GLEW_LIBRARY_DEBUG} optimized ${GLEW_LIBRARY_RELEASE}
)
