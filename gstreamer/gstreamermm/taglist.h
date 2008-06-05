// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GSTREAMERMM_TAGLIST_H
#define _GSTREAMERMM_TAGLIST_H


#include <glibmm.h>

// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 2 -*-

/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gst/gsttaglist.h>
#include <gstreamermm/structure.h>
#include <gstreamermm/structurevalue.h>

namespace Gst
{

/** @addtogroup gstreamermmEnums Enums and Flags */

/**
 * @ingroup gstreamermmEnums
 */
enum TagMergeMode
{
  TAG_MERGE_UNDEFINED,
  TAG_MERGE_REPLACE_ALL,
  TAG_MERGE_REPLACE,
  TAG_MERGE_APPEND,
  TAG_MERGE_PREPEND,
  TAG_MERGE_KEEP,
  TAG_MERGE_KEEP_ALL,
  TAG_MERGE_COUNT
};

} // namespace Gst


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Gst::TagMergeMode> : public Glib::Value_Enum<Gst::TagMergeMode>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gst
{

/**
 * @ingroup gstreamermmEnums
 */
enum TagFlag
{
  TAG_FLAG_UNDEFINED,
  TAG_FLAG_META,
  TAG_FLAG_ENCODED,
  TAG_FLAG_DECODED,
  TAG_FLAG_COUNT
};

} // namespace Gst


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Gst::TagFlag> : public Glib::Value_Enum<Gst::TagFlag>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gst
{


/** Commonly used title (string).
 * The title as it should be displayed, e.g. 'The Doll House'.
 */
const Glib::ustring TAG_TITLE = GST_TAG_TITLE;

/** Commonly used title, as used for sorting (string).
 * The title as it should be sorted, e.g. 'Doll House, The'.
 *
 * Since 0.10.15.
 */
const Glib::ustring TAG_TITLE_SORTNAME = GST_TAG_TITLE_SORTNAME;

/** Person(s) responsible for the recording (string).
 * The artist name as it should be displayed, e.g. 'Jimi Hendrix' or 'The
 * Guitar Heroes'.
 */
const Glib::ustring TAG_ARTIST = GST_TAG_ARTIST;

/** Person(s) responsible for the recording, as used for sorting (string).
 * The artist name as it should be sorted, e.g. 'Hendrix, Jimi' or 'Guitar
 * Heroes, The'.
 *
 * Since 0.10.15.
 */
const Glib::ustring TAG_ARTIST_SORTNAME = GST_TAG_ARTIST_SORTNAME;

/** Album containing this data (string).
 * The album name as it should be displayed, e.g. 'The Jazz Guitar'.
 */
const Glib::ustring TAG_ALBUM = GST_TAG_ALBUM;

/** Album containing this data, as used for sorting (string).
 * The album name as it should be sorted, e.g. 'Jazz Guitar, The'.
 *
 * Since 0.10.15.
 */
const Glib::ustring TAG_ALBUM_SORTNAME = GST_TAG_ALBUM_SORTNAME;

/** Date the data was created (GDate structure).
 */
const Glib::ustring TAG_DATE = GST_TAG_DATE;

/** Genre this data belongs to (string).
 */
const Glib::ustring TAG_GENRE = GST_TAG_GENRE;

/** Free text commenting the data (string).
 */
const Glib::ustring TAG_COMMENT = GST_TAG_COMMENT;

/** Key/value text commenting the data (string).
 * Must be in the form of 'key=comment' or 'key[lc]=comment' where 'lc' is an
 * ISO-639 language code.
 *
 * This tag is used for unknown Vorbis comment tags, unknown APE tags and
 * certain ID3v2 comment fields.
 *
 * Since 0.10.10.
 */
const Glib::ustring TAG_EXTENDED_COMMENT = GST_TAG_EXTENDED_COMMENT;

/** Track number inside a collection (unsigned integer).
 */
const Glib::ustring TAG_TRACK_NUMBER = GST_TAG_TRACK_NUMBER;

/** Count of tracks inside collection this track belongs to (unsigned integer).
 */
const Glib::ustring TAG_TRACK_COUNT = GST_TAG_TRACK_COUNT;

/** Disc number inside a collection (unsigned integer).
 */
const Glib::ustring TAG_ALBUM_VOLUME_NUMBER = GST_TAG_ALBUM_VOLUME_NUMBER;

/** Count of discs inside collection this disc belongs to (unsigned integer).
 */
const Glib::ustring TAG_ALBUM_VOLUME_COUNT = GST_TAG_ALBUM_VOLUME_COUNT;

/** Original location of file as a URI (string).
 */
const Glib::ustring TAG_LOCATION = GST_TAG_LOCATION;

/** Short text describing the content of the data (string).
 */
const Glib::ustring TAG_DESCRIPTION = GST_TAG_DESCRIPTION;

/** Version of this data (string).
 */
const Glib::ustring TAG_VERSION = GST_TAG_VERSION;

/** International Standard Recording Code - see http://www.ifpi.org/isrc/
 * (string).
 */
const Glib::ustring TAG_ISRC = GST_TAG_ISRC;

/** Organization (string).
 */
const Glib::ustring TAG_ORGANIZATION = GST_TAG_ORGANIZATION;

/** Copyright notice of the data (string).
 */
const Glib::ustring TAG_COPYRIGHT = GST_TAG_COPYRIGHT;

/** URI to location where copyright details can be found (string).
 * Since 0.10.14.
 */
const Glib::ustring TAG_COPYRIGHT_URI = GST_TAG_COPYRIGHT_URI;

/** Person(s) who composed the recording (string).
 * Since 0.10.15.
 */
const Glib::ustring TAG_COMPOSER = GST_TAG_COMPOSER;

/** Contact information (string).
 */
const Glib::ustring TAG_CONTACT = GST_TAG_CONTACT;

/** License of data (string).
 */
const Glib::ustring TAG_LICENSE = GST_TAG_LICENSE;

/** URI to location where license details can be found (string).
 * Since 0.10.14.
 */
const Glib::ustring TAG_LICENSE_URI = GST_TAG_LICENSE_URI;

/** Person(s) performing (string).
 */
const Glib::ustring TAG_PERFORMER = GST_TAG_PERFORMER;

/** Length in GStreamer time units (nanoseconds) (unsigned 64-bit integer).
 */
const Glib::ustring TAG_DURATION = GST_TAG_DURATION;

/** Codec the data is stored in (string).
 */
const Glib::ustring TAG_CODEC = GST_TAG_CODEC;

/** Codec the video data is stored in (string).
 */
const Glib::ustring TAG_VIDEO_CODEC = GST_TAG_VIDEO_CODEC;

/** Codec the audio data is stored in (string).
 */
const Glib::ustring TAG_AUDIO_CODEC = GST_TAG_AUDIO_CODEC;

/** Exact or average bitrate in bits/s (unsigned integer).
 */
const Glib::ustring TAG_BITRATE = GST_TAG_BITRATE;

/** Nominal bitrate in bits/s (unsigned integer).
 */
const Glib::ustring TAG_NOMINAL_BITRATE = GST_TAG_NOMINAL_BITRATE;

/** Minimum bitrate in bits/s (unsigned integer).
 */
const Glib::ustring TAG_MINIMUM_BITRATE = GST_TAG_MINIMUM_BITRATE;

/** Maximum bitrate in bits/s (unsigned integer).
 */
const Glib::ustring TAG_MAXIMUM_BITRATE = GST_TAG_MAXIMUM_BITRATE;

/** Serial number of track (unsigned integer).
 */
const Glib::ustring TAG_SERIAL = GST_TAG_SERIAL;

/** Encoder used to encode this stream (string).
 */
const Glib::ustring TAG_ENCODER = GST_TAG_ENCODER;

/** Version of the encoder used to encode this stream (unsigned integer).
 */
const Glib::ustring TAG_ENCODER_VERSION = GST_TAG_ENCODER_VERSION;

/** Track gain in db (double).
 */
const Glib::ustring TAG_TRACK_GAIN = GST_TAG_TRACK_GAIN;

/** Peak of the track (double).
 */
const Glib::ustring TAG_TRACK_PEAK = GST_TAG_TRACK_PEAK;

/** Album gain in db (double).
 */
const Glib::ustring TAG_ALBUM_GAIN = GST_TAG_ALBUM_GAIN;

/** Peak of the album (double).
 */
const Glib::ustring TAG_ALBUM_PEAK = GST_TAG_ALBUM_PEAK;

/** Reference level of track and album gain values (double).
 * Since 0.10.12.
 */
const Glib::ustring TAG_REFERENCE_LEVEL = GST_TAG_REFERENCE_LEVEL;

/** Language code (ISO-639-1) (string) of the content.
 */
const Glib::ustring TAG_LANGUAGE_CODE = GST_TAG_LANGUAGE_CODE;

/** Image (buffer) (buffer caps should specify the content type and preferably
 * also set "image-type" field as GstTagImageType).
 * Since 0.10.6 
 */
const Glib::ustring TAG_IMAGE = GST_TAG_IMAGE;

/** Image that is meant for preview purposes, e.g. small icon-sized version
 * (buffer) (buffer caps should specify the content type).
 * Since 0.10.7.
 */
const Glib::ustring TAG_PREVIEW_IMAGE = GST_TAG_PREVIEW_IMAGE;

/** Number of beats per minute in audio (double).
 * Since 0.10.12.
 */
const Glib::ustring TAG_BEATS_PER_MINUTE = GST_TAG_BEATS_PER_MINUTE;

/** A List of tags and values used to describe media metadata.
 * Taglists form part of media streams and describe the content of a stream in
 * a non-technical way. Examples include the author of a song, the title of
 * that very same song or the album it is a part of. Tag reading is done
 * through a Gst::Bus. You can listen for Gst::MESSAGE_TAG messages and handle
 * them as you wish.
 *
 * Note, however, that the Gst::MESSAGE_TAG  message may be fired multiple
 * times in the pipeline. It is the application's responsibility to put all
 * those tags together and display them to the user in a nice, coherent way.
 * Usually, using merge() is a good enough way of doing this; make sure to
 * empty the cache when loading a new song, or after every few minutes when
 * listening to internet radio. Also, make sure you use Gst::TAG_MERGE_PREPEND
 * as merging mode, so that a new title (which came in later) has a preference
 * over the old one for display.
 */
class TagList : public Structure
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef TagList CppObjectType;
  typedef GstTagList BaseObjectType;

  static GType get_type() G_GNUC_CONST;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  TagList();

  explicit TagList(GstTagList* gobject, bool make_a_copy = true);

  TagList(const TagList& other);
  TagList& operator=(const TagList& other);

  ~TagList();

  void swap(TagList& other);

  ///Provides access to the underlying C instance.
  GstTagList*       gobj()       { return gobject_; }

  ///Provides access to the underlying C instance.
  const GstTagList* gobj() const { return gobject_; }

  ///Provides access to the underlying C instance. The caller is responsible for freeing it. Use when directly setting fields in structs.
  GstTagList* gobj_copy() const;

protected:
  GstTagList* gobject_;

private:


public:
  //TODO: Add operator bool() to handle when C functions return NULL TagList*?

  
  /** Checks if the given type is already registered.
   * @param tag Name of the tag.
   * @return <tt>true</tt> if the type is already registered.
   */
  static bool exists(const Glib::ustring& tag);
  
  /** Gets the Type used for this tag.
   * @param tag The tag.
   * @return The Type of this tag.
   */
  static GType get_type(const Glib::ustring& tag);
  
  /** Returns: the human-readable name of this tag
   * @param tag The tag.
   * @return The human-readable name of this tag.
   */
  static Glib::ustring get_nick(const Glib::ustring& tag);
  
  /** Returns: the human-readable description of this tag
   * @param tag The tag.
   * @return The human-readable description of this tag.
   */
  static Glib::ustring get_description(const Glib::ustring& tag);
  
  /** Gets the flag of @a tag.
   * @param tag The tag.
   * @return The flag of this tag.
   */
  static TagFlag get_flag(const Glib::ustring& tag);
  
  /** Checks if the given tag is fixed. A fixed tag can only contain one value.
   * Unfixed tags can contain lists of values.
   * @param tag Tag to check.
   * @return <tt>true</tt>, if the given tag is fixed.
   */
  static bool is_fixed(const Glib::ustring& tag);
  
  /** Checks if the given taglist is empty.
   * @return <tt>true</tt> if the taglist is empty, otherwise <tt>false</tt>.
   * 
   * Since: 0.10.11.
   */
  bool is_empty() const;
  
  /** Inserts the tags of the second list into the first list using the given mode.
   * @param from List to merge from.
   * @param mode The mode to use.
   */
  void insert(const TagList& other, TagMergeMode mode=TAG_MERGE_APPEND);
  
  /** Merges the two given lists into a new list. If one of the lists is <tt>0</tt>, a
   * copy of the other is returned. If both lists are <tt>0</tt>, <tt>0</tt> is returned.
   * @param list2 Second list to merge.
   * @param mode The mode to use.
   * @return The new list.
   */
  TagList merge(const TagList& other, TagMergeMode mode=TAG_MERGE_PREPEND);
  
  /** Checks how many value are stored in this tag list for the given tag.
   * @param tag The tag to query.
   * @return The number of tags stored.
   */
  guint get_tag_size(const Glib::ustring& tag) const;

  /** Sets a GValue for the given @a tag using the specified mode.
   *
   * @param tag The tag name.
   * @param mode The mode to use.
   * @param value The GValue to set.
   */
  void add(const Glib::ustring& tag, const Glib::ValueBase& value, TagMergeMode mode=TAG_MERGE_APPEND);

  /** Sets the value for the given tag to string @a data using the specified
   * mode.
   *
   * @param tag The tag name.
   * @param data A string to which the tag should be set to.
   * @param mode The merge mode to use.
   */
  void add(const Glib::ustring& tag, const char* data, TagMergeMode mode=TAG_MERGE_APPEND);

  /** Sets the value for the given tag using the specified mode.
   *
   * @param tag The tag name.
   * @param data A value which the tag should be set to (this can be any C++
   * class).
   * @param mode The merge mode to use.
   */
  template <class DataType>
  void add(const Glib::ustring& tag, const DataType& data, TagMergeMode mode=TAG_MERGE_APPEND);

  
  /** Removes the given tag from the taglist.
   * @param tag Tag to remove.
   */
  void remove_tag(const Glib::ustring& tag);

  /** For example,
   * void on_foreach(const Glib::ustring& tag);
   */
  typedef sigc::slot<void, const Glib::ustring&> SlotForeach;

  /** Calls the given slot for each tag inside the tag list. Note that if there
   * is no tag, the slot won't be called at all.
   *
   * @param slot Slot to be called for each tag.
   */
  void foreach(const SlotForeach& slot);

  /** Gets the value that is at the given index for the given tag.

   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @@param The Glib::ValueBase to store the value in.
   * @return true if tag was available and had right number of entries, false
   * otherwise.
   */
  bool get(const Glib::ustring& tag, guint index, Glib::ValueBase& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, char& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, char& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guchar& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, guchar& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, bool& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, bool& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, int& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, int& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, guint& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, long& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, long& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, gulong& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, gulong& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, float& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, float& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, double& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, double& value);

  /** Copies the contents for the given tag into the value, possibly merging
   * multiple values into one if multiple values are associated with the tag.
   *
   * Use the index version of this method if you want to retrieve the first
   * string associated with this tag unmodified.
   *
   * The resulting string in value will be in UTF-8 encoding.
   *
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, Glib::ustring& value);

  /** Gets the value that is at the given index for the given tag in the given
   * list.
   *
   * The resulting string in value will be in UTF-8 encoding.
   * 
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, Glib::ustring& value);

  /** Copies the contents for the given tag into the value, merging multiple
   * values into one if multiple values are associated with the tag.
   * @param tag The tag to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, Glib::Date& value);

  /** Gets the value that is at the given index for the given tag.
   * @param tag The tag to read out.
   * @param index Number of entry to read out.
   * @param value Location for the result.
   * @return true, if a value was copied, false if the tag didn't exist in the
   * given list.
   */
  bool get(const Glib::ustring& tag, guint index, Glib::Date& value);


};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/******************************* Gst::Caps *******************************/

template <class DataType>
void TagList::add(const Glib::ustring& tag, const DataType& data, TagMergeMode mode)
{
  typedef typename Gst::StructureValue<DataType> type_cppdata;
  typedef typename type_cppdata::ValueType ValueType;

  ValueType value;
  value.init(ValueType::value_type());
  value.set(data);
  this->add(tag, (Glib::ValueBase) value, mode);
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */


} //namespace Gst


namespace Gst
{

/** @relates Gst::TagList
 * @param lhs The left-hand side
 * @param rhs The right-hand side
 */
inline void swap(TagList& lhs, TagList& rhs)
  { lhs.swap(rhs); }

} // namespace Gst

namespace Glib
{

/** A Glib::wrap() method for this object. The dummy boolean parameter is added to disambiguate Gst::TagList::wrap() from Gst::Structure::wrap() (GstTagList is in fact a GstStructure so wrap method becomes ambiguous).
 * 
 * @param object The C instance.
 * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
 * @param dummy An unused parameter to disambiguate Gst::TagList::wrap() from Gst::Structure::wrap().
 * @result A C++ instance that wraps this C instance.
 *
 * @relates Gst::TagList
 */
Gst::TagList wrap(GstTagList* object, bool take_copy = false, bool dummy = false);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <>
class Value<Gst::TagList> : public Glib::Value_Boxed<Gst::TagList>
{};
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace Glib


#endif /* _GSTREAMERMM_TAGLIST_H */

