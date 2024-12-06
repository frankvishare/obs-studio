#include <obs-module.h>

#include "vishare-output.h"
#include "vishare-service.h"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-vishare", "en-US")
MODULE_EXPORT const char *obs_module_description(void)
{
	return "OBS Vishare module";
}

bool obs_module_load()
{
	register_vishare_output();
	register_vishare_service();

	return true;
}
