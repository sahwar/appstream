/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2012-2016 Matthias Klumpp <matthias@tenstral.net>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the license, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined (__APPSTREAM_H) && !defined (AS_COMPILATION)
#error "Only <appstream.h> can be included directly."
#endif

#ifndef __AS_METADATA_H
#define __AS_METADATA_H

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>

#include "as-component.h"

G_BEGIN_DECLS

#define AS_TYPE_METADATA (as_metadata_get_type ())
G_DECLARE_DERIVABLE_TYPE (AsMetadata, as_metadata, AS, METADATA, GObject)

struct _AsMetadataClass
{
	GObjectClass		parent_class;
	/*< private >*/
	void (*_as_reserved1)	(void);
	void (*_as_reserved2)	(void);
	void (*_as_reserved3)	(void);
	void (*_as_reserved4)	(void);
	void (*_as_reserved5)	(void);
	void (*_as_reserved6)	(void);
};

/**
 * AsParserMode:
 * @AS_PARSER_MODE_METAINFO:	Parse AppStream upstream metadata (metainfo files)
 * @AS_PARSER_MODE_COLLECTION:	Parse AppStream metadata collections (shipped by software distributors)
 *
 * There are a few differences between AppStream's metainfo files (shipped by upstream projects)
 * and the collection metadata (shipped by distributors).
 * The parser mode indicates which style we should process.
 * Usually you do not want to set this explicitly.
 **/
typedef enum {
	AS_PARSER_MODE_METAINFO,
	AS_PARSER_MODE_COLLECTION,
	/*< private >*/
	AS_PARSER_MODE_LAST
} AsParserMode;

/**
 * AsDataFormat:
 * @AS_DATA_FORMAT_UNKNOWN:	Unknown metadata format.
 * @AS_DATA_FORMAT_XML:		AppStream XML metadata.
 * @AS_DATA_FORMAT_YAML:	AppStream YAML (DEP-11) metadata.
 *
 * Format of the AppStream metadata.
 **/
typedef enum {
	AS_DATA_FORMAT_UNKNOWN,
	AS_DATA_FORMAT_XML,
	AS_DATA_FORMAT_YAML,
	/*< private >*/
	AS_DATA_FORMAT_LAST
} AsDataFormat;

const gchar		*as_data_format_to_string (AsDataFormat format);
AsUrgencyKind		 as_data_format_from_string (const gchar *format_str);

/**
 * AsMetadataError:
 * @AS_METADATA_ERROR_FAILED:			Generic failure.
 * @AS_METADATA_ERROR_PARSE:			Unable to parse the metadata file.
 * @AS_METADATA_ERROR_FORMAT_UNEXPECTED:	Expected collection metadata but got metainfo metadata, or vice versa.
 * @AS_METADATA_ERROR_NO_COMPONENT:		We expected a component in the pool, but couldn't find one.
 *
 * A metadata processing error.
 **/
typedef enum {
	AS_METADATA_ERROR_FAILED,
	AS_METADATA_ERROR_PARSE,
	AS_METADATA_ERROR_FORMAT_UNEXPECTED,
	AS_METADATA_ERROR_NO_COMPONENT,
	/*< private >*/
	AS_METADATA_ERROR_LAST
} AsMetadataError;

#define	AS_METADATA_ERROR	as_metadata_error_quark ()

AsMetadata		*as_metadata_new (void);
GQuark			as_metadata_error_quark (void);

void			as_metadata_parse_file (AsMetadata *metad,
						GFile *file,
						AsDataFormat format,
						GError **error);

void			as_metadata_parse (AsMetadata *metad,
						const gchar *data,
						AsDataFormat format,
						GError **error);

AsComponent		*as_metadata_get_component (AsMetadata *metad);
GPtrArray		*as_metadata_get_components (AsMetadata *metad);

void			as_metadata_clear_components (AsMetadata *metad);
void			as_metadata_add_component (AsMetadata *metad,
							AsComponent *cpt);

gchar			*as_metadata_component_to_metainfo (AsMetadata *metad,
								AsDataFormat format,
								GError **error);
void			as_metadata_save_metainfo (AsMetadata *metad,
							const gchar *fname,
							AsDataFormat format,
							GError **error);

gchar			*as_metadata_components_to_collection (AsMetadata *metad,
								AsDataFormat format,
								GError **error);
void			as_metadata_save_collection (AsMetadata *metad,
							const gchar *fname,
							AsDataFormat format,
							GError **error);

void			as_metadata_set_locale (AsMetadata *metad,
							const gchar *locale);
const gchar		*as_metadata_get_locale (AsMetadata *metad);

const gchar		*as_metadata_get_origin (AsMetadata *metad);
void			as_metadata_set_origin (AsMetadata *metad,
							const gchar *origin);

gboolean		as_metadata_get_update_existing (AsMetadata *metad);
void			as_metadata_set_update_existing (AsMetadata *metad,
								gboolean update);

gboolean		as_metadata_get_write_header (AsMetadata *metad);
void			as_metadata_set_write_header (AsMetadata *metad,
								gboolean wheader);

void			as_metadata_set_parser_mode (AsMetadata *metad,
							AsParserMode mode);
AsParserMode		as_metadata_get_parser_mode (AsMetadata *metad);

const gchar		*as_metadata_get_architecture (AsMetadata *metad);
void			as_metadata_set_architecture (AsMetadata *metad,
							const gchar *arch);

G_END_DECLS

#endif /* __AS_METADATA_H */
