PROJECT ("dab service")
set(CMAKE_CXX_FLAGS -std=c++14)

set(SERVICE_SRC_LIST 
	src/service/dab_service.cpp
	src/dab/app_attributies.cpp
	src/dab/hi_topic_handler.cpp
	)
file(GLOB  UTILS_SRC src/utils/*.cpp)
file(GLOB  DAB_SRC_LIST src/dab/handler/*.cpp src/dab/handler/utils/*.cpp)
file(GLOB  DAB_API_SRC_LIST src/adapter_api/*.cpp)
file(GLOB  CONTEXT_SRC_LIST  src/dab/context/*.cpp)
file(GLOB  MQTT_SRC_LIST  src/mqtt/*.cpp)
set(JSON_SRC_LIST  src/json/jsoncpp.cpp)
set(ALL_SRC_LIST 
	${UTILS_SRC}
	${SERVICE_SRC_LIST}
	${DAB_SRC_LIST}
	${DAB_API_SRC_LIST}
	${CONTEXT_SRC_LIST}
	${JSON_SRC_LIST}
	${MQTT_SRC_LIST}
	)

include_directories(include)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY src/out)
add_library(dab SHARED ${ALL_SRC_LIST})

file(GLOB NDLB_SRC test/ndlb/*.cpp)
set(TEST_SRC_LIST 	
	src/dab/app_attributies.cpp
	src/dab/hi_topic_handler.cpp
	${UTILS_SRC}
	${DAB_SRC_LIST}
	${DAB_API_SRC_LIST}
	${CONTEXT_SRC_LIST}
	${JSON_SRC_LIST}
	#${MQTT_SRC_LIST}
	${NDLB_SRC}
	)

add_executable(ndlb ${TEST_SRC_LIST})
target_link_libraries(ndlb PRIVATE gtest)