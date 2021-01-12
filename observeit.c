/*
   +----------------------------------------------------------------------+
   | Copyright (c) 2021 Derick Rethans                                    |
   +----------------------------------------------------------------------+
   | This source file is subject to the 2-Clause BSD license which is     |
   | available through the LICENSE file, or online at                     |
   | http://opensource.org/licenses/bsd-license.php                       |
   +----------------------------------------------------------------------+
   | Authors:  Derick Rethans <derick@derickrethans.nl>                   |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_variables.h"
#include "zend_exceptions.h"
#include "ext/json/php_json.h"
#include "zend_observer.h"

static zend_always_inline zend_string* tracing_get_class_name(zend_execute_data *data)
{
	zend_function *curr_func;

	if (!data) {
		return NULL;
	}

	curr_func = data->func;

	if (!curr_func) {
		return NULL;
	}

	if (curr_func->common.scope != NULL) {
		zend_string_addref(curr_func->common.scope->name);

		return curr_func->common.scope->name;
	}

	return NULL;
}

static zend_always_inline zend_string* tracing_get_function_name(zend_execute_data *data)
{
	zend_function *curr_func;

	if (!data) {
		return NULL;
	}

	curr_func = data->func;

	if (!curr_func) {
		return NULL;
	}

	if (!curr_func->common.function_name) {
		// This branch includes execution of eval and include/require(_once) calls
		return NULL;
	}

	zend_string_addref(curr_func->common.function_name);

	return curr_func->common.function_name;
}


static int has_callback(zend_execute_data *execute_data)
{
	zend_string *class_name = NULL;
	zend_string *function_name = tracing_get_function_name(execute_data);
	class_name = tracing_get_class_name(execute_data);

	fprintf(stderr, "%s::%s\n",
		class_name ? ZSTR_VAL(class_name) : "",
		function_name ? ZSTR_VAL(function_name) : ""
	);

	if (class_name != NULL) {
		zend_string_release(class_name);
	}
	if (function_name != NULL) {
		zend_string_release(function_name);
	}

	return 1;
}

static void tracer_observer_begin(zend_execute_data *execute_data)
{
//    fprintf(stderr, "→ Observed: %s\n", "foo");
}

static void tracer_observer_end(zend_execute_data *execute_data, zval *return_value)
{
//    fprintf(stderr, "← Observed: %s\n", "foo");
}

static zend_observer_fcall_handlers tracer_observer(zend_execute_data *execute_data)
{
	if (! has_callback(execute_data)) {
		return (zend_observer_fcall_handlers){NULL, NULL};
	}

	return (zend_observer_fcall_handlers){tracer_observer_begin, tracer_observer_end};
}

PHP_MINIT_FUNCTION(observeit)
{
	zend_observer_fcall_register(tracer_observer);

	return SUCCESS;
}

/* {{{ observeit_module_entry
 */
zend_module_entry observeit_module_entry = {
	STANDARD_MODULE_HEADER,
	"observeit",
	NULL,
	PHP_MINIT(observeit),
	NULL, //MSHUTDOWN
	NULL, //RINIT
	NULL, //RSHUTDOWN
	NULL, //MINFO
	"0.0.2",
	NO_MODULE_GLOBALS,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_OBSERVEIT
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(observeit)
#endif
