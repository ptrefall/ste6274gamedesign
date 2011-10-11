
FIND_PATH(SPARK_DIR include/SPK.h
      D:/Development/3rdParty/SPARK/SPARK-1.5.5/sdk/
    )

FIND_PATH(SPARK_INCLUDE_PATH SPK.h
      D:/Development/3rdParty/SPARK/SPARK-1.5.5/sdk/include
    )
	
FIND_PATH(SPARK_LIB_PATH SPARK.lib
      D:/Development/3rdParty/SPARK/SPARK-1.5.5/sdk/lib/vc2008/static
    )
	
FIND_LIBRARY(SPARK_LIBRARY_RELEASE
  NAMES SPARK.lib
  PATHS D:/Development/3rdParty/SPARK/SPARK-1.5.5/sdk/lib/vc2008/static
    )
	
FIND_LIBRARY(SPARK_LIBRARY_DEBUG
  NAMES SPARK_debug.lib
  PATHS D:/Development/3rdParty/SPARK/SPARK-1.5.5/sdk/lib/vc2008/static
    )

FIND_LIBRARY(SPARK_GL_LIBRARY_RELEASE
  NAMES SPARK_GL.lib
  PATHS D:/Development/3rdParty/SPARK/SPARK-1.5.5/sdk/lib/vc2008/static
    )
	
FIND_LIBRARY(SPARK_GL_LIBRARY_DEBUG
  NAMES SPARK_GL_debug.lib
  PATHS D:/Development/3rdParty/SPARK/SPARK-1.5.5/sdk/lib/vc2008/static
    )
