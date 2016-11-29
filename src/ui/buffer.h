/*
 * buffer.h
 *
 * Copyright (C) 2012 - 2016 James Booth <boothj5@gmail.com>
 *
 * This file is part of Profanity.
 *
 * Profanity is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Profanity is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Profanity.  If not, see <https://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link the code of portions of this program with the OpenSSL library under
 * certain conditions as described in each individual source file, and
 * distribute linked combinations including the two.
 *
 * You must obey the GNU General Public License in all respects for all of the
 * code used other than OpenSSL. If you modify file(s) with this exception, you
 * may extend this exception to your version of the file(s), but you are not
 * obligated to do so. If you do not wish to do so, delete this exception
 * statement from your version. If you delete this exception statement from all
 * source files in the program, then also delete it here.
 *
 */

#ifndef UI_BUFFER_H
#define UI_BUFFER_H

#include <glib.h>

#include "config.h"
#include "config/theme.h"

typedef struct prof_buff_receipt_t {
    char *id;
    gboolean received;
} ProfBuffReceipt;

typedef struct prof_buff_date_t {
    GDateTime *timestamp;
    gboolean colour_date;
} ProfBuffDate;

typedef enum {
    FROM_THEM,
    FROM_ME
} prof_buff_from_type_t;

typedef struct prof_buff_from_t {
    prof_buff_from_type_t type;
    char *from;
} ProfBuffFrom;

typedef struct prof_buff_entry_t {
    theme_item_t theme_item;
    ProfBuffDate* date;
    char show_char;
    ProfBuffFrom *from;
    char *message;
    int pad_indent;
    gboolean newline;
    ProfBuffReceipt *receipt;
} ProfBuffEntry;

typedef struct prof_buff_t *ProfBuff;

ProfBuff buffer_create();
void buffer_free(ProfBuff buffer);

ProfBuffDate* buffer_date_new_now(void);
ProfBuffDate* buffer_date_new(GDateTime *timestamp, gboolean colour);

void buffer_append(
    ProfBuff buffer,
    theme_item_t theme_item,
    ProfBuffDate *date,
    const char show_char,
    ProfBuffFrom *from,
    const char *const message,
    int pad_indent,
    gboolean newline,
    ProfBuffReceipt *receipt);

int buffer_size(ProfBuff buffer);
ProfBuffEntry* buffer_get_entry(ProfBuff buffer, int entry);
ProfBuffEntry* buffer_get_entry_by_id(ProfBuff buffer, const char *const id);
gboolean buffer_mark_received(ProfBuff buffer, const char *const id);

#endif
