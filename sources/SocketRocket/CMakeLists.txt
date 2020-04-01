


set(SOCKET_ROCKET_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/SRWebSocket.m
    ${CMAKE_CURRENT_LIST_DIR}/NSRunLoop+SRWebSocket.m
    ${CMAKE_CURRENT_LIST_DIR}/SRSecurityPolicy.m
    ${CMAKE_CURRENT_LIST_DIR}/SocketRocket.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/SRConstants.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Proxy/SRProxyConnect.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Proxy/SRProxyConnect.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/RunLoop/SRRunLoopThread.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/RunLoop/SRRunLoopThread.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Security/SRPinningSecurityPolicy.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Security/SRPinningSecurityPolicy.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/NSRunLoop+SRWebSocketPrivate.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Delegate/SRDelegateController.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Delegate/SRDelegateController.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/NSURLRequest+SRWebSocketPrivate.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRHash.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRLog.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRMutex.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRHTTPConnectMessage.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRSIMDHelpers.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRRandom.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRURLUtilities.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRError.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRLog.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRHash.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRMutex.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRHTTPConnectMessage.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRError.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRRandom.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRURLUtilities.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities/SRSIMDHelpers.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/IOConsumer/SRIOConsumerPool.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/IOConsumer/SRIOConsumer.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/IOConsumer/SRIOConsumer.h
    ${CMAKE_CURRENT_LIST_DIR}/Internal/IOConsumer/SRIOConsumerPool.m
    ${CMAKE_CURRENT_LIST_DIR}/Internal/SRConstants.m
    ${CMAKE_CURRENT_LIST_DIR}/NSURLRequest+SRWebSocket.h
    ${CMAKE_CURRENT_LIST_DIR}/SRWebSocket.h
    ${CMAKE_CURRENT_LIST_DIR}/NSRunLoop+SRWebSocket.h
    ${CMAKE_CURRENT_LIST_DIR}/SRSecurityPolicy.h
    ${CMAKE_CURRENT_LIST_DIR}/NSURLRequest+SRWebSocket.m
)

add_library(SocketRocket ${SOCKET_ROCKET_SOURCES})
if(IOS)
    set_property(TARGET SocketRocket PROPERTY XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET ${TARGET_IOS_VERSION})
    set_property(TARGET SocketRocket PROPERTY XCODE_ATTRIBUTE_ENABLE_BITCODE "NO")
    set_property(TARGET SocketRocket PROPERTY XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "YES")
endif()
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} PREFIX "Source Files" FILES ${SOCKET_ROCKET_SOURCES})

target_include_directories(SocketRocket 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Internal
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Internal/RunLoop
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Internal/Security
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Internal/Delegate
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Internal/IOConsumer
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Internal/Proxy
)

target_compile_options(SocketRocket PRIVATE
    -fobjc-arc
)
