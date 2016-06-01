#include <string.h>
#include <stdio.h>

#include <json-c/json.h>

#include <respondd.h>

#include "ffffm.h"

static struct json_object *respondd_provider_statistics(void) {

	struct ffffm_airtime *a = NULL;
	struct json_object *ret = json_object_new_object();
	if (!ret)
		goto end;
        a = ffffm_get_airtime();
        if (!a)
                return NULL;

        struct json_object *v;

	if (a->a24 >= 0) {
		v = json_object_new_double(a->a24);
		if (!v)
			goto end;
		json_object_object_add(ret, "airtime2", v);
	}
	if (a->a50 >= 0) {
		v = json_object_new_double(a->a50);
		if (!v)
			goto end;
		json_object_object_add(ret, "airtime5", v);
	}

end:
        free(a);
        return ret;
}

static struct json_object *respondd_provider_nodeinfo(void) {
	struct ffffm_wifi_info *i = NULL;
	struct json_object *ret = NULL;
        
        ret = json_object_new_object();
	if (!ret)
		goto end;

        i = ffffm_get_wifi_info();
	if (!i)
		goto end;

        struct json_object *v;

	if (i->c24) {
		v = json_object_new_int64(i->c24);
		if (!v)
			goto end;
		json_object_object_add(ret, "chan2", v);
	}
	if (i->c50) {
		v = json_object_new_int64(i->c50);
		if (!v)
			goto end;
		json_object_object_add(ret, "chan5", v);
	}
	if (i->t24) {
		v = json_object_new_int64(i->t24);
		if (!v)
			goto end;
		json_object_object_add(ret, "txpower2", v);
	}
	if (i->t50) {
		v = json_object_new_int64(i->t50);
		if (!v)
			goto end;
		json_object_object_add(ret, "txpower5", v);
	}
end:
        free(i);
	return ret;
	
}

const struct respondd_provider_info respondd_providers[] = {
	{"statistics", respondd_provider_statistics},
	{"nodeinfo", respondd_provider_nodeinfo},
	{0},
};
