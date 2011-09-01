/*****************************************************************************
 * v4l2.h : Video4Linux2 input module for vlc
 *****************************************************************************
 * Copyright (C) 2002-2011 the VideoLAN team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <vlc_common.h>

#if defined(HAVE_LINUX_VIDEODEV2_H)
#   include <linux/videodev2.h>
#elif defined(HAVE_SYS_VIDEOIO_H)
#   include <sys/videoio.h>
#else
#   error "No Video4Linux2 headers found."
#endif

#ifdef HAVE_LIBV4L2
#   include <libv4l2.h>
#else
#   define v4l2_close close
#   define v4l2_dup dup
#   define v4l2_ioctl ioctl
#   define v4l2_read read
#   define v4l2_mmap mmap
#   define v4l2_munmap munmap
#endif

#define CFG_PREFIX "v4l2-"

int ControlList(vlc_object_t *, int fd, bool b_demux);

/* TODO: remove this, use callbacks */
typedef enum {
    IO_METHOD_READ=1,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
} io_method;

/* TODO: move this to .c */
struct demux_sys_t
{
    int  i_fd;

    /* Video */
    io_method io;

    unsigned i_selected_input;

    unsigned i_codec;
    struct v4l2_fmtdesc *p_codecs;

    struct buffer_t *p_buffers;
    unsigned int i_nbuffers;

    int i_width;
    int i_height;
    unsigned int i_aspect;
    int i_fourcc;
    uint32_t i_block_flags;

    es_out_id_t *p_es;

    /* Audio */
    uint32_t i_audio_input;

    /* Tuner */
    uint32_t i_tuner;
    enum v4l2_tuner_type i_tuner_type;
    int i_tuner_audio_mode;

#ifdef HAVE_LIBV4L2
    bool b_libv4l2;
#endif
};


