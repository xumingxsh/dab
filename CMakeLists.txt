PROJECT ("dab service")
set(CMAKE_CXX_FLAGS -std=c++11)

set(SERVICE_SRC_LIST 
	src/service/dab_service.cpp
	src/dab/app_attributies.cpp
	src/dab/hi_topic_handler.cpp
	)
file(GLOB  DAB_SRC_LIST src/dab/handler/*.cpp)
file(GLOB  DAB_API_SRC_LIST src/adapter_api/*.cpp	)
file(GLOB  CONTEXT_SRC_LIST  src/dab/context/*.cpp)
file(GLOB  MQTT_SRC_LIST  src/mqtt/*.cpp)
set(JSON_SRC_LIST  src/json/jsoncpp.cpp)
set(ALL_SRC_LIST 
	${SERVICE_SRC_LIST}
	${DAB_SRC_LIST}
	${DAB_API_SRC_LIST}
	${CONTEXT_SRC_LIST}
	${JSON_SRC_LIST}
	${MQTT_SRC_LIST}
	)

include_directories(include)

add_library(libdab SHARED ${ALL_SRC_LIST})