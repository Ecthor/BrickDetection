# This file is used when other components needs to use something provided by this DCL. 
# Provide any include paths and lib directories. Use /home/lkorpal/discode_ws/DCL/BrickDetection/dist
# to point to 'dist' directory of current DCL, it'll be substituted during installation. 

# directory containing header files
SET(BrickDetection_INCLUDE_DIR /home/lkorpal/discode_ws/DCL/BrickDetection/dist/include)
INCLUDE_DIRECTORIES(${BrickDetection_INCLUDE_DIR})

# directory containing libraries
SET(BrickDetection_LIB_DIR /home/lkorpal/discode_ws/DCL/BrickDetection/dist/lib)
LINK_DIRECTORIES(${BrickDetection_LIB_DIR})

# list of libraries to link against when using features of BrickDetection
# add all additional libraries built by this dcl (NOT components)
# SET(BrickDetection_LIBS lib_1 lib_2)
# SET(ADDITIONAL_LIB_DIRS /home/lkorpal/discode_ws/DCL/BrickDetection/dist/lib ${ADDITIONAL_LIB_DIRS})
