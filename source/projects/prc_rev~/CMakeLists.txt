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
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Chorus.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Delay.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/DelayL.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Effect.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Filter.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/PRCRev.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Stk.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/WaveLoop.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/WvIn.cpp"
    "prc_rev~.cpp"
)
add_library( 
	${PROJECT_NAME} 
	MODULE
	${PROJECT_SRC}
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-sdk-base/script/max-posttarget.cmake)