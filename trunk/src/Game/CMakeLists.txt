
cmake_minimum_required(VERSION 2.8)

set(GAME_SRC_ROOT ${SRC_ROOT}/Game)

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
