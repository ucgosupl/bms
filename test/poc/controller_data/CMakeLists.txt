set(CMAKE_C_COMPILER gcc)
set(CMAKE_AR ar)
set(CMAKE_RANLIB ranlib)

set(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_BUILD_TYPE  "Debug")

set(SRC_PATH ../../../src)

set(INCLUDE_DIRS
	${SRC_PATH}
)

set(TEST_INCLUDE_DIRS
	..
	.
)

set(SRCS
	${SRC_PATH}/gateway/controller_data/controller_data.c
	${SRC_PATH}/gateway/updater/updater.c
	${SRC_PATH}/gateway/server/server.c
)

set(POC_NAME controller_data)

set(TEST_SRCS
	modbus_mock.c
	datetime_mock.c
	server_protocol_mock.c

	main.c
)

set(GLOBAL_DEFINES

)

add_executable(poc_${POC_NAME} ${SRCS} ${TEST_SRCS})
add_test(${POC_NAME} poc_${POC_NAME})

target_include_directories(poc_${POC_NAME} PRIVATE ${INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})
target_compile_definitions(poc_${POC_NAME} PRIVATE ${GLOBAL_DEFINES})
