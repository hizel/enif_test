#include <erl_nif.h>

#include "header.h"


static ErlNifResourceType *frame_resource;


static ERL_NIF_TERM check(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	struct frame_ctx *ctx;
	if (!enif_get_resource(env, argv[0], frame_resource, (void **)&ctx)) {
		return enif_make_badarg(env);
	}

	return enif_make_tuple2(env, enif_make_atom(env, "ok"), enif_make_atom(env, ctx->frame->data));
}

static int load(ErlNifEnv *env, void **priv, ERL_NIF_TERM load_info) {
	if(!frame_resource)
		frame_resource = enif_open_resource_type(env, NULL, "frame", frame_ctx_destruct, ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER, NULL);
	return 0;
}

static ErlNifFunc second_func[] = {  
  {"check", 1, check}
};

ERL_NIF_INIT(second, second_func, load, NULL, NULL, NULL);