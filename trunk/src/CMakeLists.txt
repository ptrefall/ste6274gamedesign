
set(SRC_ROOT ${GameDesignClient_SOURCE_DIR}/src)
set(GV_SRC_ROOT ${SRC_ROOT}/GraphicsView)
set(GAME_SRC_ROOT ${SRC_ROOT}/Game)
set(GAME_SYSTEMS_SRC_ROOT ${GAME_SRC_ROOT}/Systems)
set(GAME_COMPONENTS_SRC_ROOT ${GAME_SRC_ROOT}/Components)

set(GV_HDRS
	${GV_SRC_ROOT}/OpenGL3GraphicsScene.h
)
SOURCE_GROUP("Header Files\\GraphicsView" FILES ${GV_HDRS})

set(GV_SRCS
	${GV_SRC_ROOT}/OpenGL3GraphicsScene.cpp
)
SOURCE_GROUP("Source Files\\GraphicsView" FILES ${GV_SRCS})

set(GAME_HDRS
	${GAME_SRC_ROOT}/Game.h
	${GAME_SRC_ROOT}/EntityManager.h
)
SOURCE_GROUP("Header Files\\Game" FILES ${GAME_HDRS})

set(GAME_SRCS
	${GAME_SRC_ROOT}/Game.cpp
	${GAME_SRC_ROOT}/EntityManager.cpp
)
SOURCE_GROUP("Source Files\\Game" FILES ${GAME_SRCS})

set(GAME_SYSTEMS_HDRS
	${GAME_SYSTEMS_SRC_ROOT}/RenderSystem.h
)
SOURCE_GROUP("Header Files\\Game\\Systems" FILES ${GAME_SYSTEMS_HDRS})

set(GAME_SYSTEMS_SRCS
	${GAME_SYSTEMS_SRC_ROOT}/RenderSystem.cpp
)
SOURCE_GROUP("Source Files\\Game\\Systems" FILES ${GAME_SYSTEMS_SRCS})

set(GAME_COMPONENTS_HDRS
	${GAME_COMPONENTS_SRC_ROOT}/Renderable.h
)
SOURCE_GROUP("Header Files\\Game\\Components" FILES ${GAME_COMPONENTS_HDRS})

set(GAME_COMPONENTS_SRCS
	${GAME_COMPONENTS_SRC_ROOT}/Renderable.cpp
)
SOURCE_GROUP("Source Files\\Game\\Components" FILES ${GAME_COMPONENTS_SRCS})

set(HDRS
)

set(SRCS
    ${SRC_ROOT}/main.cpp
)

find_package(OpenGL REQUIRED)
find_package(Glew REQUIRED)
find_package(Qt4 4.7.3 REQUIRED QtCore QtGui QtOpenGL)
CMP_QT_LIBRARIES_INSTALL_RULES("QtCore;QtGui;QtOpenGL" ${GameDesignClient_BINARY_DIR}/src)
find_package(GLM REQUIRED)
set(WINDOW_EXT_LIBS ${OPENGL_gl_LIBRARY})
set(WINDOW_EXT_LIBS ${WINDOW_EXT_LIBS} winmm gdi32)

include_directories(${OPENGL_INCLUDE_PATH})
include_directories(${GLEW_INCLUDE_PATH})
include(${QT_USE_FILE})
include_directories(${GLM_DIR})

QT4_WRAP_CPP(GV_MOCS ${GV_HDRS})
SOURCE_GROUP("Source Files\\GraphicsView" FILES ${GV_MOCS})

add_executable(GameDesignClient ${GV_HDRS} ${GV_SRCS} ${GV_MOCS} ${GAME_HDRS} ${GAME_SRCS} ${GAME_SYSTEMS_HDRS} ${GAME_SYSTEMS_SRCS} ${GAME_COMPONENTS_HDRS} ${GAME_COMPONENTS_SRCS} ${HDRS} ${SRCS})
set_target_properties(GameDesignClient PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(GameDesignClient PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(GameDesignClient
  ${OPENGL_LIBRARIES}
  debug ${GLEW_LIBRARY_DEBUG_X86} optimized ${GLEW_LIBRARY_RELEASE_X86}
  ${QT_LIBRARIES}
  FactotumEDK
)
