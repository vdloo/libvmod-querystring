/*
 * libvmod-querystring - querystring manipulation module for Varnish
 *
 * Copyright (C) 2012-2016, Dridi Boukelmoune <dridi.boukelmoune@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define QS_LOG_CALL(ctx, fmt, ...) \
	VSLb(ctx->vsl, SLT_VCL_call, "%s(" fmt ")", __func__, __VA_ARGS__);

#define QS_LOG_RETURN(ctx, val) VSLb(ctx->vsl, SLT_VCL_return, "\"%s\"", val);

typedef const struct vrt_ctx re_ctx;

/* ------------------------------------------------------------------- */

#ifndef QS_ENABLE_LOGGING

#undef QS_LOG_CALL
#undef QS_LOG_RETURN

#define QS_LOG_CALL
#define QS_LOG_RETURN

#endif

/* ------------------------------------------------------------------- */

struct query_param {
	const char	*value;
	size_t		len;
};

VSTAILQ_HEAD(qs_list, qs_name);

struct qs_name {
	VSTAILQ_ENTRY(qs_name)	list;
	char			*name;
};

struct qs_filter;

typedef int qs_match(VRT_CTX, const char *, size_t, const struct qs_filter *);

struct qs_filter {
	union {
		struct qs_list	names;
		void		*regex;
	};
	qs_match		*match;
	int			keep;
};
