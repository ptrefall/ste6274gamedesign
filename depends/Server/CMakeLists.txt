project(GameDesignServer)

#---------------------------------------------------------------
set(HDRS
	../Protocol/gameprotocol.h
)

set(PKG_HDRS
	#./buildclienterrorpkgtask.h
	#./buildconnectanswerpkgtask.h
	#./builddsqpkgtask.h
	#./buildjoinanswerpkgtask.h
	#./buildmapqueryanswerpkgtask.h
	#./buildpkgtask.h
	./datapacket.h
)

set(CLIENT_HDRS
	./clientconnection.h
	./clienterrorpw.h
	./clientparsetask.h
	#./clientverificationtask.h
	./connectanswerpw.h
	./connection.h
	./connectrhtask.h
	./dsquerypw.h
	./joinanswerpw.h
)

set(PLAYER_HDRS
	./playerinstance.h
	./playerjoininfo.h
	./playerparsetask.h
)

set(SERVER_HDRS
	./server.h
	./serverinfo.h
	./serverworker.h
	./tcpparsetask.h
	./tcpserver.h
	./tcpsocket.h
	./negotiationpf.h
	./packetfactory.h
	./packetworker.h
	./requesthandlertask.h
	./requestinfo.h
	./sendpctworker.h
	#./sendpkgtask.h
)

set(GAME_HDRS
	./gameinfo.h
	./gameinstance.h
	./gamepf.h
	#./gamepfw.h
	./gamestatepw.h
	./gameupdatepw.h
	./teaminfo.h
	#./mapinfo.h
)

set(MAP_HDRS
	./mapinstance.h
	./mapobject.h
	./mapqueryanswerpw.h
)

SOURCE_GROUP("Header Files\\Package" FILES ${PKG_HDRS})
SOURCE_GROUP("Header Files\\Client" FILES ${CLIENT_HDRS})
SOURCE_GROUP("Header Files\\Player" FILES ${PLAYER_HDRS})
SOURCE_GROUP("Header Files\\Server" FILES ${SERVER_HDRS})
SOURCE_GROUP("Header Files\\Game" FILES ${GAME_HDRS})
SOURCE_GROUP("Header Files\\Map" FILES ${MAP_HDRS})

set(MOC_HDRS
	./debugutils.h
	./mainwindow.h
	${PKG_HDRS}
	${CLIENT_HDRS}
	${PLAYER_HDRS}
	${SERVER_HDRS}
	${GAME_HDRS}
	${MAP_HDRS}
)

##---------------------------------------------------------------------

set(PKG_SRCS
	#./buildclienterrorpkgtask.cpp
	#./buildconnectanswerpkgtask.cpp
	#./builddsqpkgtask.cpp
	#./buildjoinanswerpkgtask.cpp
	#./buildmapqueryanswerpkgtask.cpp
	#./buildpkgtask.cpp
	./datapacket.cpp
)

set(CLIENT_SRCS
	./clientconnection.cpp
	./clienterrorpw.cpp
	./clientparsetask.cpp
	#./clientverificationtask.cpp
	./connectanswerpw.cpp
	./connection.cpp
	./connectrhtask.cpp
	./dsquerypw.cpp
	./joinanswerpw.cpp
)

set(PLAYER_SRCS
	./playerinstance.cpp
	./playerjoininfo.cpp
	./playerparsetask.cpp
)

set(SERVER_SRCS
	./server.cpp
	./serverinfo.cpp
	./serverworker.cpp
	./tcpparsetask.cpp
	./tcpserver.cpp
	./tcpsocket.cpp
	./negotiationpf.cpp
	./packetfactory.cpp
	./packetworker.cpp
	./requesthandlertask.cpp
	./requestinfo.cpp
	./sendpctworker.cpp
	#./sendpkgtask.cpp
)

set(GAME_SRCS
	./gameinfo.cpp
	./gameinstance.cpp
	./gamepf.cpp
	#./gamepfw.cpp
	./gamestatepw.cpp
	./gameupdatepw.cpp
	./teaminfo.cpp
	#./mapinfo.cpp
)

set(MAP_SRCS
	./mapinstance.cpp
	./mapobject.cpp
	./mapqueryanswerpw.cpp
)

SOURCE_GROUP("Source Files\\Package" FILES ${PKG_SRCS})
SOURCE_GROUP("Source Files\\Client" FILES ${CLIENT_SRCS})
SOURCE_GROUP("Source Files\\Player" FILES ${PLAYER_SRCS})
SOURCE_GROUP("Source Files\\Server" FILES ${SERVER_SRCS})
SOURCE_GROUP("Source Files\\Game" FILES ${GAME_SRCS})
SOURCE_GROUP("Source Files\\Map" FILES ${MAP_SRCS})

set(SRCS
	./main.cpp
	./debugutils.cpp
	./mainwindow.cpp
	${PKG_SRCS}
	${CLIENT_SRCS}
	${PLAYER_SRCS}
	${SERVER_SRCS}
	${GAME_SRCS}
	${MAP_SRCS}
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