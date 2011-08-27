
FIND_PATH(ASSIMP_DIR include/assimp.hpp
      D:/Development/3rdParty/AssImp/trunk
    )

FIND_PATH(ASSIMP_INCLUDE_PATH assimp.hpp
      D:/Development/3rdParty/AssImp/trunk/include
    )
	
FIND_PATH(ASSIMP_LIB_PATH Debug/assimp.lib
      D:/Development/3rdParty/AssImp/trunk/build2010/code/
    )
	
FIND_LIBRARY(ASSIMP_LIBRARY_DEBUG_X86
  NAMES assimp.lib
  PATHS D:/Development/3rdParty/AssImp/trunk/build2010/code/Debug
    )
	
FIND_LIBRARY(ASSIMP_LIBRARY_RELEASE_X86
  NAMES assimp.lib
  PATHS D:/Development/3rdParty/AssImp/trunk/build2010/code/MinSizeRel
    )
