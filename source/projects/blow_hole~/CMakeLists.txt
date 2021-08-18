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
    # We may not need all of these, but keeping it for consistency with pre-cmake builds
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/ADSR.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/BiQuad.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/BlowHole.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Delay.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/DelayL.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Envelope.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Filter.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Function.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Generator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Instrmnt.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/JetTable.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Noise.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/OneZero.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/PoleZero.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/ReedTable.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/Stk.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/WaveLoop.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/src/WvIn.cpp"
    "blow_hole~.cpp"
)

add_library( 
	${PROJECT_NAME} 
	MODULE
	${PROJECT_SRC}
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-sdk-base/script/max-posttarget.cmake)