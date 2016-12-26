#ifndef HEADER_H
#define HEADER_H

#define DESCRIPTION_MAX_LENGTH 128

#include <string.h>

struct frame {
	char *data;
};

struct frame_ctx {
	struct frame *frame;

	char description[DESCRIPTION_MAX_LENGTH];
};

static void frame_ctx_destruct(ErlNifEnv* env, void *obj) {
	struct frame_ctx *ctx = (struct frame_ctx*)obj;
	free(ctx->frame);
	free(ctx);
	enif_release_resource(obj);
} 

#endif