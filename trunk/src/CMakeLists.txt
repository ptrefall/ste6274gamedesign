#---------------------------------------------------------------
set(SRC_ROOT ${GameDesignClient_SOURCE_DIR}/src)
set(QT_SRC_ROOT ${SRC_ROOT}/Qt)
set(QT_GV_SRC_ROOT ${QT_SRC_ROOT}/GraphicsView)
set(QT_CLIENT_SRC_ROOT ${QT_SRC_ROOT}/Client)
set(QT_UI_SRC_ROOT ${QT_SRC_ROOT}/UserInterface)
set(GAME_SRC_ROOT ${SRC_ROOT}/Game)
set(GAME_SYSTEMS_SRC_ROOT ${GAME_SRC_ROOT}/Systems)
set(GAME_COMPONENTS_SRC_ROOT ${GAME_SRC_ROOT}/Components)
#---------------------------------------------------------------
set(GV_HDRS
	${QT_GV_SRC_ROOT}/OpenGL3GraphicsScene.h
)
SOURCE_GROUP("Header Files\\Qt\\GraphicsView" FILES ${GV_HDRS})

set(GV_SRCS
	${QT_GV_SRC_ROOT}/OpenGL3GraphicsScene.cpp
)
SOURCE_GROUP("Source Files\\Qt\\GraphicsView" FILES ${GV_SRCS})
#---------------------------------------------------------------
set(CLIENT_HDRS
	${QT_CLIENT_SRC_ROOT}/Client.h
	${QT_CLIENT_SRC_ROOT}/NetworkSession.h
	${QT_CLIENT_SRC_ROOT}/GameProtocol.h
)
SOURCE_GROUP("Header Files\\Qt\\Client" FILES ${CLIENT_HDRS})

set(CLIENT_SRCS
	${QT_CLIENT_SRC_ROOT}/Client.cpp
	${QT_CLIENT_SRC_ROOT}/NetworkSession.cpp
)
SOURCE_GROUP("Source Files\\Qt\\Client" FILES ${CLIENT_SRCS})
#---------------------------------------------------------------
set(UI_UIC_HDRS
	${QT_UI_SRC_ROOT}/mainMenu.ui
)
set(UI_HDRS
	${QT_UI_SRC_ROOT}/MainMenu.h
	#${QT_UI_SRC_ROOT}/ui_mainMenu.h
)
set(UI_SRCS
	${QT_UI_SRC_ROOT}/MainMenu.cpp
)
SOURCE_GROUP("Header Files\\Qt\\UserInterface" FILES ${UI_HDRS})
SOURCE_GROUP("Source Files\\Qt\\UserInterface" FILES ${UI_UIC_HDRS} ${UI_SRCS})
#---------------------------------------------------------------
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
#---------------------------------------------------------------
set(GAME_SYSTEMS_HDRS
	${GAME_SYSTEMS_SRC_ROOT}/RenderSystem.h
)
SOURCE_GROUP("Header Files\\Game\\Systems" FILES ${GAME_SYSTEMS_HDRS})

set(GAME_SYSTEMS_SRCS
	${GAME_SYSTEMS_SRC_ROOT}/RenderSystem.cpp
)
SOURCE_GROUP("Source Files\\Game\\Systems" FILES ${GAME_SYSTEMS_SRCS})
#---------------------------------------------------------------
set(GAME_COMPONENTS_HDRS
	${GAME_COMPONENTS_SRC_ROOT}/Renderable.h
)
SOURCE_GROUP("Header Files\\Game\\Components" FILES ${GAME_COMPONENTS_HDRS})

set(GAME_COMPONENTS_SRCS
	${GAME_COMPONENTS_SRC_ROOT}/Renderable.cpp
)
SOURCE_GROUP("Source Files\\Game\\Components" FILES ${GAME_COMPONENTS_SRCS})
#---------------------------------------------------------------
set(HDRS
)

set(SRCS
    ${SRC_ROOT}/main.cpp
)
#---------------------------------------------------------------
find_package(OpenGL REQUIRED)
find_package(Glew REQUIRED)
find_package(Qt4 4.7.3 REQUIRED QtCore QtGui QtOpenGL QtNetwork)
CMP_QT_LIBRARIES_INSTALL_RULES("QtCore;QtGui;QtOpenGL;QtNetwork" ${GameDesignClient_BINARY_DIR}/src)
find_package(GLM REQUIRED)
set(WINDOW_EXT_LIBS ${OPENGL_gl_LIBRARY})
set(WINDOW_EXT_LIBS ${WINDOW_EXT_LIBS} winmm gdi32)
#---------------------------------------------------------------
include_directories(${OPENGL_INCLUDE_PATH})
include_directories(${GLEW_INCLUDE_PATH})
include(${QT_USE_FILE})
include_directories(${GLM_DIR})
include_directories(${GameDesignClient_BINARY_DIR}/src)
#---------------------------------------------------------------
QT4_WRAP_CPP(MOCS ${GV_HDRS} ${CLIENT_HDRS} ${UI_HDRS})
SOURCE_GROUP("Source Files\\Qt\\MOC" FILES ${MOCS})
#---------------------------------------------------------------
QT4_WRAP_UI(UICS ${UI_UIC_HDRS})
SOURCE_GROUP("Source Files\\Qt\\UIC" FILES ${UICS})
#---------------------------------------------------------------
add_executable(GameDesignClient 
	${MOCS} ${UICS}
	${GV_HDRS} ${GV_SRCS} 
	${CLIENT_HDRS} ${CLIENT_SRCS}
	${UI_HDRS} ${UI_UIC_HDRS} ${UI_SRCS}
	${GAME_HDRS} ${GAME_SRCS} 
	${GAME_SYSTEMS_HDRS} ${GAME_SYSTEMS_SRCS} 
	${GAME_COMPONENTS_HDRS} ${GAME_COMPONENTS_SRCS} 
	${HDRS} ${SRCS}
)
set_target_properties(GameDesignClient PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(GameDesignClient PROPERTIES LINKER_LANGUAGE CXX)
#---------------------------------------------------------------
target_link_libraries(GameDesignClient
  ${OPENGL_LIBRARIES}
  debug ${GLEW_LIBRARY_DEBUG_X86} optimized ${GLEW_LIBRARY_RELEASE_X86}
  ${QT_LIBRARIES}
  FactotumEDK
)
#---------------------------------------------------------------
#INSTALL(FILES ${UICS} DESTINATION "${QT_UI_SRC_ROOT}")