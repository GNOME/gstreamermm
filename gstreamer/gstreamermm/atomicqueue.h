/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2014 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _GSTREAMERMM_ATOMICQUEUE_H
#define _GSTREAMERMM_ATOMICQUEUE_H

#include <glibmm/refptr.h>
#include <gstreamermm/handle_error.h>
#include <gst/gstatomicqueue.h>

namespace Gst
{

/**
 * The Gst::AtomicQueue object implements a queue that can be used from multiple
 * threads without performing any blocking operations.
 */
template <typename T>
class AtomicQueue
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AtomicQueue CppObjectType;
  typedef GstAtomicQueue BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


  /** Increment the reference count for this object.
   * You should never need to do this manually - use the object via a RefPtr instead.
   */
  void reference()   const
  {
    // See the comment at the top of this file, if you want to know why the cast works.
    gst_atomic_queue_ref(reinterpret_cast<GstAtomicQueue*>(const_cast<AtomicQueue<T>*>(this)));
  }

  /** Decrement the reference count for this object.
   * You should never need to do this manually - use the object via a RefPtr instead.
   */
  void unreference() const
  {
    // See the comment at the top of this file, if you want to know why the cast works.
    gst_atomic_queue_unref(reinterpret_cast<GstAtomicQueue*>(const_cast<AtomicQueue<T>*>(this)));
  }

  ///Provides access to the underlying C instance.
  const GstAtomicQueue* gobj() const
  {
    // See the comment at the top of this file, if you want to know why the cast works.
    return reinterpret_cast<const GstAtomicQueue*>(this);
  }

  ///Provides access to the underlying C instance.
  GstAtomicQueue*       gobj()
  {
    // See the comment at the top of this file, if you want to know why the cast works.
    return reinterpret_cast<GstAtomicQueue*>(this);
  }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GstAtomicQueue* gobj_copy() const
  {
    // See the comment at the top of this file, if you want to know why the cast works.
    GstAtomicQueue *const gobject = reinterpret_cast<GstAtomicQueue*>(const_cast<AtomicQueue<T>*>(this));
    gst_atomic_queue_ref(gobject);
    return gobject;
  }

  static Glib::RefPtr<Gst::AtomicQueue<T> > create(guint initial_size)
  {
    // See the comment at the top of this file, if you want to know why the cast works.
    return Glib::RefPtr<AtomicQueue<T> >(reinterpret_cast<AtomicQueue<T>*>(gst_atomic_queue_new(initial_size)));
  }

protected:
  // Do not derive this.  Gst::AtomicQueue can neither be constructed nor deleted.
  AtomicQueue();
  void operator delete(void*, std::size_t);

private:
  // noncopyable
  AtomicQueue(const AtomicQueue&);
  AtomicQueue& operator=(const AtomicQueue&);


public:
  
  /** Get the amount of items in the queue.
   * @return The number of elements in the queue.
   */
  guint length()
  {
    return gst_atomic_queue_length(gobj());
  }

  /** Get the amount of items in the queue.
   * @return The number of elements in the queue.
   */
  guint length() const
  {
	  return const_cast<AtomicQueue*>(this)->length();
  }

  /** Append @a data to the tail of the queue.
   * @param data The data.
   */
  void push(const T& data)
  {
    T* tmp = new T(data);
    gst_atomic_queue_push(gobj(), tmp);
  }
  
  /** Peek the head element of the queue without removing it from the queue.
   * @return The head element of queue.
   *
   * @throws std::runtime_error if the queue is empty.
   */
  T peek()
  {
    gpointer val = gst_atomic_queue_peek(gobj());
    if (val == nullptr)
      gstreamermm_handle_error("Queue is empty");
    T v = *(T*)val;
    return v;
  }
  
  /** Get the head element of the queue.
   * @return The head element of queue.
   *
   * @throws std::runtime_error if the queue is empty.
   */
  T pop()
  {
    gpointer val = gst_atomic_queue_pop(gobj());
    if (val == nullptr)
      gstreamermm_handle_error("Queue is empty");
    T v = *(T*)val;
    delete (T*)val;
    return v;
  }

};

} // namespace Gst


namespace Glib
{

  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gst::AtomicQueue
   */
  template <typename T>
  Glib::RefPtr<Gst::AtomicQueue<T> > wrap(GstAtomicQueue* object, bool take_copy = false)
  {
    if(take_copy && object)
      gst_atomic_queue_ref(object);
    // See the comment at the top of this file, if you want to know why the cast works.
    return Glib::RefPtr<Gst::AtomicQueue<T> >(reinterpret_cast<Gst::AtomicQueue<T>*>(object));
  }

} // namespace Glib


#endif /* _GSTREAMERMM_ATOMICQUEUE_H */

