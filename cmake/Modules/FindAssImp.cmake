
FIND_PATH(ASSIMP_DIR include/assimp.hpp
      D:/Development/3rdParty/AssImp/trunk
    )

FIND_PATH(ASSIMP_INCLUDE_PATH assimp.hpp
      D:/Development/3rdParty/AssImp/trunk/include
    )
	
FIND_LIBRARY(ASSIMP_LIBRARY_DEBUG_X86
  NAMES glew32sd
  PATHS D:\Development\3rdParty\AssImp\trunk\build2010\code\Debug
    )
	
FIND_LIBRARY(ASSIMP_LIBRARY_RELEASE_X86
  NAMES glew32s
  PATHS D:\Development\3rdParty\AssImp\trunk\build2010\code\MinSizeRel
    )
