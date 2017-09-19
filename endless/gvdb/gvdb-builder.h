/*
 * Copyright © 2010 Codethink Limited
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the licence, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: Allison Lortie <desrt@desrt.ca>
 */

#ifndef __gvdb_builder_h__
#define __gvdb_builder_h__

#include <gio/gio.h>

typedef struct _GvdbItem GvdbItem;

G_GNUC_INTERNAL
GHashTable *            gvdb_hash_table_new                             (GHashTable    *parent,
                                                                         const gchar   *key);

G_GNUC_INTERNAL
GvdbItem *              gvdb_hash_table_insert                          (GHashTable    *table,
                                                                         const gchar   *key);
G_GNUC_INTERNAL
void                    gvdb_hash_table_insert_string                   (GHashTable    *table,
                                                                         const gchar   *key,
                                                                         const gchar   *value);

G_GNUC_INTERNAL
void                    gvdb_item_set_value                             (GvdbItem      *item,
                                                                         GVariant      *value);
G_GNUC_INTERNAL
void                    gvdb_item_set_hash_table                        (GvdbItem      *item,
                                                                         GHashTable    *table);
G_GNUC_INTERNAL
void                    gvdb_item_set_parent                            (GvdbItem      *item,
                                                                         GvdbItem      *parent);

G_GNUC_INTERNAL
gboolean                gvdb_table_write_contents                       (GHashTable     *table,
                                                                         const gchar    *filename,
                                                                         gboolean        byteswap,
                                                                         GError        **error);
G_GNUC_INTERNAL
GBytes *                gvdb_table_write_bytes                          (GHashTable     *table,
                                                                         gboolean        byteswap);

#endif /* __gvdb_builder_h__ */
