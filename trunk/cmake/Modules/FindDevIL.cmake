
FIND_PATH(DEVIL_DIR include/IL/il.h
      D:/Development/3rdParty/DevIL/x86/
    )

FIND_PATH(DEVIL_INCLUDE_PATH IL/il.h
      D:/Development/3rdParty/DevIL/x86/include
    )
	
FIND_PATH(DEVIL_LIB_PATH DevIL.lib
      D:/Development/3rdParty/DevIL/x86
    )
	
FIND_LIBRARY(DEVIL_LIBRARY
  NAMES DevIL.lib
  PATHS D:/Development/3rdParty/DevIL/x86
    )

FIND_LIBRARY(DEVIL_ILU_LIBRARY
  NAMES ILU.lib
  PATHS D:/Development/3rdParty/DevIL/x86
    )
	
FIND_LIBRARY(DEVIL_ILUT_LIBRARY
  NAMES ILUT.lib
  PATHS D:/Development/3rdParty/DevIL/x86
    )
