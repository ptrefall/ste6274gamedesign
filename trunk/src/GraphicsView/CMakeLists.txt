
cmake_minimum_required(VERSION 2.8)

set(GV_SRC_ROOT ${SRC_ROOT}/GraphicsView)

set(GV_HDRS
	${GV_SRC_ROOT}/OpenGL3GraphicsScene.h
)
SOURCE_GROUP("Header Files\\GraphicsView" FILES ${GV_HDRS})

set(GV_SRCS
	${GV_SRC_ROOT}/OpenGL3GraphicsScene.cpp
)
SOURCE_GROUP("Source Files\\GraphicsView" FILES ${GV_SRCS})
