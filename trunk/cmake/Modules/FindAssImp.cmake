
FIND_PATH(ASSIMP_DIR include/assimp.hpp
      D:/Development/3rdParty/AssImp/trunk
	  C:/Paal/Development/3rdParties/assimp--2.0.863-sdk
    )

FIND_PATH(ASSIMP_INCLUDE_PATH assimp.hpp
      D:/Development/3rdParty/AssImp/trunk/include
	  C:/Paal/Development/3rdParties/assimp--2.0.863-sdk/include
    )
	
FIND_PATH(ASSIMP_LIB_PATH Debug/assimp.lib
      D:/Development/3rdParty/AssImp/trunk/build2010/code/
	  C:/Paal/Development/3rdParties/assimp--2.0.863-sdk/lib
    )
	
FIND_LIBRARY(ASSIMP_LIBRARY_DEBUG_X86
  NAMES assimp.lib
  PATHS D:/Development/3rdParty/AssImp/trunk/build2010/code/Debug
		C:/Paal/Development/3rdParties/assimp--2.0.863-sdk/lib/assimp_debug-dll_win32
    )
	
FIND_LIBRARY(ASSIMP_LIBRARY_RELEASE_X86
  NAMES assimp.lib
  PATHS D:/Development/3rdParty/AssImp/trunk/build2010/code/MinSizeRel
		C:/Paal/Development/3rdParties/assimp--2.0.863-sdk/lib/assimp_release-dll_win32
    )
	
FIND_PATH(ASSIMP_BIN_DEBUG_X86 assimp.dll
      D:/Development/3rdParty/AssImp/trunk/build2010/code/Debug
	  C:/Paal/Development/3rdParties/assimp--2.0.863-sdk/bin/assimp_debug-dll_win32
    )
	
FIND_PATH(ASSIMP_BIN_RELEASE_X86 assimp.dll
      D:/Development/3rdParty/AssImp/trunk/build2010/code/MinSizeRel
	  C:/Paal/Development/3rdParties/assimp--2.0.863-sdk/bin/assimp_release-dll_win32
    )
