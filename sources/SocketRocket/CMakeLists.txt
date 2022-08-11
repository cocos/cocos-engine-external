


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

set(SOCKET_ROCKET_SOURCES_M ${SOCKET_ROCKET_SOURCES})
list(FILTER SOCKET_ROCKET_SOURCES_M INCLUDE REGEX ".*m$")
set_source_files_properties(${SOCKET_ROCKET_SOURCES_M} PROPERTIES COMPILE_FLAGS
    -fobjc-arc
    )


list(APPEND CC_EXTERNAL_PRIVATE_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/Internal
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Utilities
    ${CMAKE_CURRENT_LIST_DIR}/Internal/RunLoop
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Security
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Delegate
    ${CMAKE_CURRENT_LIST_DIR}/Internal/IOConsumer
    ${CMAKE_CURRENT_LIST_DIR}/Internal/Proxy
)

list(APPEND CC_EXTERNAL_SOURCES ${SOCKET_ROCKET_SOURCES})
list(APPEND CC_EXTERNAL_INCLUDES ${CMAKE_CURRENT_LIST_DIR})
