#include <erl_nif.h>

#include "header.h"


static ErlNifResourceType *frame_resource;

static ERL_NIF_TERM start(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

	struct frame_ctx *ctx = (struct frame_ctx*) enif_alloc_resource(frame_resource, sizeof(struct frame_ctx));
	ctx->frame = malloc(sizeof(struct frame));
	ctx->frame->data = malloc(DESCRIPTION_MAX_LENGTH);
	strcpy(ctx->frame->data, "framedata");

	strcpy(ctx->description, "frame");

	ERL_NIF_TERM bin = enif_make_resource_binary(env, ctx, ctx->description, strlen(ctx->description));

	return enif_make_tuple2(env, enif_make_atom(env, "ok"), bin);
}

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

static ErlNifFunc first_func[] = {
  {"start", 0, start},
  {"check", 1, check}
};

ERL_NIF_INIT(first, first_func, load, NULL, NULL, NULL);