/*
 * Copyright (C) 2021 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *   Alyssa Rosenzweig <alyssa.rosenzweig@collabora.com>
 *   Boris Brezillon <boris.brezillon@collabora.com>
 */

#ifndef __PAN_DESC_H
#define __PAN_DESC_H

#include "genxml/gen_macros.h"

#include "pan_texture.h"

struct pan_compute_dim {
   uint32_t x, y, z;
};

struct pan_fb_color_attachment {
   const struct pan_image_view *view;
   bool *crc_valid;
   bool clear;
   bool preload;
   bool discard;
   uint32_t clear_value[4];
};

struct pan_fb_zs_attachment {
   struct {
      const struct pan_image_view *zs, *s;
   } view;

   struct {
      bool z, s;
   } clear;

   struct {
      bool z, s;
   } discard;

   struct {
      bool z, s;
   } preload;

   struct {
      float depth;
      uint8_t stencil;
   } clear_value;
};

struct pan_tiler_context {
   union {
      struct {
         uint64_t desc;
         /* A tiler descriptor can only handle a limited amount of layers.
          * If the number of layers is bigger than this, several tiler
          * descriptors will be issued, each with a different layer_offset.
          */
         uint8_t layer_offset;
      } valhall;
      struct {
         uint64_t desc;
      } bifrost;
      struct {
         /* Sum of vertex counts (for non-indexed draws), index counts, or ~0 if
          * any indirect draws are used. Helps tune hierarchy masks.
          */
         uint32_t vertex_count;
         bool disable;
         bool no_hierarchical_tiling;
         uint64_t polygon_list;
         struct {
            uint64_t start;
            unsigned size;
         } heap;
      } midgard;
   };
};

struct pan_tls_info {
   struct {
      uint64_t ptr;
      unsigned size;
   } tls;

   struct {
      unsigned instances;
      uint64_t ptr;
      unsigned size;
   } wls;
};

struct pan_fb_bifrost_info {
   struct {
      struct panfrost_ptr dcds;
      unsigned modes[3];
   } pre_post;
};

struct pan_fb_info {
   unsigned width, height;
   struct {
      /* Max values are inclusive */
      unsigned minx, miny, maxx, maxy;
   } extent;
   unsigned nr_samples;
   unsigned force_samples; /* samples used for rasterization */
   unsigned rt_count;
   struct pan_fb_color_attachment rts[8];
   struct pan_fb_zs_attachment zs;

   struct {
      unsigned stride;
      uint64_t base;
   } tile_map;

   union {
      struct pan_fb_bifrost_info bifrost;
   };

   /* Optimal tile buffer size. */
   unsigned tile_buf_budget;
   unsigned z_tile_buf_budget;
   unsigned tile_size;
   unsigned cbuf_allocation;

   /* Sample position array. */
   uint64_t sample_positions;

   /* Only used on Valhall */
   bool sprite_coord_origin;
   bool first_provoking_vertex;
};

static inline unsigned
pan_wls_instances(const struct pan_compute_dim *dim)
{
   return util_next_power_of_two(dim->x) * util_next_power_of_two(dim->y) *
          util_next_power_of_two(dim->z);
}

static inline unsigned
pan_wls_adjust_size(unsigned wls_size)
{
   return util_next_power_of_two(MAX2(wls_size, 128));
}

#ifdef PAN_ARCH

static inline enum mali_sample_pattern
pan_sample_pattern(unsigned samples)
{
   switch (samples) {
   case 1:
      return MALI_SAMPLE_PATTERN_SINGLE_SAMPLED;
#if PAN_ARCH >= 12
   case 2:
      return MALI_SAMPLE_PATTERN_ROTATED_2X_GRID;
#endif
   case 4:
      return MALI_SAMPLE_PATTERN_ROTATED_4X_GRID;
   case 8:
      return MALI_SAMPLE_PATTERN_D3D_8X_GRID;
   case 16:
      return MALI_SAMPLE_PATTERN_D3D_16X_GRID;
   default:
      unreachable("Unsupported sample count");
   }
}

void GENX(pan_select_tile_size)(struct pan_fb_info *fb);

void GENX(pan_emit_tls)(const struct pan_tls_info *info,
                        struct mali_local_storage_packed *out);

int GENX(pan_select_crc_rt)(const struct pan_fb_info *fb, unsigned tile_size);

unsigned GENX(pan_emit_fbd)(const struct pan_fb_info *fb, unsigned layer_idx,
                            const struct pan_tls_info *tls,
                            const struct pan_tiler_context *tiler_ctx,
                            void *out);

#if PAN_ARCH >= 6
unsigned GENX(pan_select_tiler_hierarchy_mask)(uint32_t width, uint32_t height,
                                               uint32_t max_levels,
                                               uint32_t tile_size,
                                               uint32_t mem_budget);
#endif

#if PAN_ARCH <= 9
void GENX(pan_emit_fragment_job_payload)(const struct pan_fb_info *fb,
                                         uint64_t fbd, void *out);
#endif

#endif /* ifdef PAN_ARCH */

#endif
