/*
 * Copyright © 2022 Red Hat, Inc.
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */

#if !defined(HB_H_IN) && !defined(HB_NO_SINGLE_HEADER_ERROR)
#error "Include <hb.h> instead."
#endif

#ifndef HB_CONFIG_H
#define HB_CONFIG_H

#include "hb-common.h"

HB_BEGIN_DECLS


/**
 * HB_FREETYPE:
 *
 * Defined if Harfbuzz has been built with Freetype support.
 */
#undef HB_FREETYPE

/**
 * HB_GDI:
 *
 * Defined if Harfbuzz has been built with GDI support.
 */
#undef HB_GDI

/**
 * HB_GRAPHITE:
 *
 * Defined if Harfbuzz has been built with Graphite support.
 */
#undef HB_GRAPHITE

/**
 * HB_GLIB:
 *
 * Defined if Harfbuzz has been built with GLib support.
 */
#undef HB_GLIB

/**
 * HB_UNISCRIBE:
 *
 * Defined if Harfbuzz has been built with Uniscribe support.
 */
#undef HB_UNISCRIBE

/**
 * HB_DIRECTWRITE:
 *
 * Defined if Harfbuzz has been built with DirectWrite support.
 */
#undef HB_DIRECTWRITE

/**
 * HB_CORETEXT:
 *
 * Defined if Harfbuzz has been built with CoreText support.
 */
#undef HB_CORETEXT

/**
 * HB_ICU:
 *
 * Defined if Harfbuzz has been built with ICU support.
 */
#undef HB_ICU


HB_END_DECLS

#endif /* HB_CONFIG_H */
