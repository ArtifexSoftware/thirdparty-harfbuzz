/*
 * Copyright © 2018  Ebrahim Byagowi
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

#ifndef HB_OT_COLOR_COLR_TABLE_HH
#define HB_OT_COLOR_COLR_TABLE_HH

#include "hb-open-type.hh"

/*
 * COLR -- Color
 * https://docs.microsoft.com/en-us/typography/opentype/spec/colr
 */
#define HB_OT_TAG_COLR HB_TAG('C','O','L','R')


namespace OT {


struct LayerRecord
{
  inline bool sanitize (hb_sanitize_context_t *c) const
  {
    TRACE_SANITIZE (this);
    return_trace (c->check_struct (this));
  }

  public:
  GlyphID	glyphId;	/* Glyph ID of layer glyph */
  HBUINT16	colorIdx;	/* Index value to use with a
				 * selected color palette.
				 * An index value of 0xFFFF
				 * is a special case indicating
				 * that the text foreground
				 * color (defined by a
				 * higher-level client) should
				 * be used and shall not be
				 * treated as actual index
				 * into CPAL ColorRecord array. */
  public:
  DEFINE_SIZE_STATIC (4);
};

struct BaseGlyphRecord
{
  inline bool sanitize (hb_sanitize_context_t *c) const
  {
    TRACE_SANITIZE (this);
    return_trace (likely (c->check_struct (this)));
  }

  inline int cmp (hb_codepoint_t g) const {
    return g < glyphId ? -1 : g > glyphId ? 1 : 0;
  }

  public:
  GlyphID	glyphId;	/* Glyph ID of reference glyph */
  HBUINT16	firstLayerIdx;	/* Index (from beginning of
				 * the Layer Records) to the
				 * layer record. There will be
				 * numLayers consecutive entries
				 * for this base glyph. */
  HBUINT16	numLayers;	/* Number of color layers
				 * associated with this glyph */
  public:
  DEFINE_SIZE_STATIC (6);
};

static int compare_bgr (const void *pa, const void *pb)
{
  const hb_codepoint_t *a = (const hb_codepoint_t *) pa;
  const BaseGlyphRecord *b = (const BaseGlyphRecord *) pb;
  return b->cmp (*a);
}

struct COLR
{
  static const hb_tag_t tableTag = HB_OT_TAG_COLR;

  inline bool sanitize (hb_sanitize_context_t *c) const
  {
    TRACE_SANITIZE (this);
    return_trace (likely (c->check_struct (this) &&
			  (this+baseGlyphsZ).sanitize (c, numBaseGlyphs) &&
			  (this+layersZ).sanitize (c, numLayers)));
  }

  inline bool get_base_glyph_record (hb_codepoint_t glyph_id,
				     unsigned int *first_layer /* OUT */,
				     unsigned int *num_layers /* OUT */) const
  {
    const BaseGlyphRecord* record;
    record = (BaseGlyphRecord *) bsearch (&glyph_id, &(this+baseGlyphsZ), numBaseGlyphs,
					  sizeof (BaseGlyphRecord), compare_bgr);
    if (unlikely (!record))
      return false;

    if (first_layer) *first_layer = record->firstLayerIdx;
    if (num_layers) *num_layers = record->numLayers;
    return true;
  }

  inline bool get_layer_record (unsigned int record,
				hb_codepoint_t *glyph_id /* OUT */,
				unsigned int *color_index /* OUT */) const
  {
    if (unlikely (record >= numLayers))
    {
      *glyph_id = 0;
      *color_index = 0xFFFF;
      return false;
    }
    const LayerRecord &layer = (this+layersZ)[record];
    if (glyph_id) *glyph_id = layer.glyphId;
    if (color_index) *color_index = layer.colorIdx;
    return true;
  }

  protected:
  HBUINT16	version;	/* Table version number */
  HBUINT16	numBaseGlyphs;	/* Number of Base Glyph Records */
  LOffsetTo<UnsizedArrayOf<BaseGlyphRecord>, false>
		baseGlyphsZ;	/* Offset to Base Glyph records. */
  LOffsetTo<UnsizedArrayOf<LayerRecord>, false>
		layersZ;	/* Offset to Layer Records */
  HBUINT16	numLayers;	/* Number of Layer Records */
  public:
  DEFINE_SIZE_STATIC (14);
};

} /* namespace OT */


#endif /* HB_OT_COLOR_COLR_TABLE_HH */
