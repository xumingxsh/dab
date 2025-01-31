#include "dab/dab_handler.h"
#include "utils/hi_log.h"
#include "dab/dab_api.h"

using namespace std;

void DABHandler::init() {
    FUN_LOG();
    UN_RE_ENTER();
	dab_api_init();
    DABHandler::startTelemetry();
}
void DABHandler::destroy() {
    FUN_LOG();
    UN_RE_ENTER();
    DABHandler::stopTelemetry();
	dab_api_destroy();
}