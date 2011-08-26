project(GameDesignServer)

#---------------------------------------------------------------
set(HDRS
	../Protocol/gameprotocol.h
)
set(MOC_HDRS
	./server.h
	./mainwindow.h
	./gamedata.h
	./clientdata.h
	./clientconnection.h
)

set(SRCS
	./main.cpp
	./server.cpp
	./mainwindow.cpp
	./gamedata.cpp
	./clientdata.cpp
	./clientconnection.cpp
)

include(${GameDesignClient_SOURCE_DIR}/cmake/Config.cmake)
set(CMAKE_MODULE_PATH ${GameDesignClient_SOURCE_DIR}/cmake/Modules)

#---------------------------------------------------------------
find_package(Qt4 4.7.3 REQUIRED QtCore QtGui QtOpenGL QtNetwork)
CMP_QT_LIBRARIES_INSTALL_RULES("QtCore;QtGui;QtOpenGL;QtNetwork" ${GameDesignClient_BINARY_DIR}/depends/server)
#---------------------------------------------------------------
include(${QT_USE_FILE})
include_directories(${Server_BINARY_DIR}/src)
include_directories(${GameDesignClient_SOURCE_DIR}/depends/Protocol)
#---------------------------------------------------------------
QT4_WRAP_CPP(MOCS ${MOC_HDRS})
SOURCE_GROUP("Source Files\\MOC" FILES ${MOCS})
#---------------------------------------------------------------
add_executable(GameDesignServer
	${MOCS} ${MOC_HDRS} 
	${HDRS} ${SRCS}
)
set_target_properties(GameDesignServer PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(GameDesignServer PROPERTIES LINKER_LANGUAGE CXX)
#---------------------------------------------------------------
target_link_libraries(GameDesignServer
  ${QT_LIBRARIES}
)
#---------------------------------------------------------------
#INSTALL(FILES ${UICS} DESTINATION "${QT_UI_SRC_ROOT}")