include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-sdk-base/script/max-pretarget.cmake)

#############################################################
# MAX EXTERNAL
#############################################################
include_directories( 
	"${MAX_SDK_INCLUDES}"
	"${MAX_SDK_MSP_INCLUDES}"
	"${MAX_SDK_JIT_INCLUDES}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
)

set(PROJECT_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/ADSR.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/BeeThree.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Envelope.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Filter.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/FM.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/FMVoices.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Generator.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/HevyMetl.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Instrmnt.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/PercFlut.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Phonemes.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Rhodey.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Stk.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/TubeBell.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/TwoZero.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/WaveLoop.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Wurley.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/WvIn.cpp"
	"prc_fm~.cpp"
)

add_library( 
	${PROJECT_NAME} 
	MODULE
	${PROJECT_SRC}
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-sdk-base/script/max-posttarget.cmake)