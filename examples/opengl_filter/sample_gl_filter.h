#ifndef SAMPLE_GL_FILTER_H_
#define SAMPLE_GL_FILTER_H_

#define GST_USE_UNSTABLE_API
#include <gstreamermm.h>
#include <gstreamermm/glfilter.h>
#include <gstreamermm/private/glfilter_p.h>

class SampleGLFilter: public Gst::GLFilter
{
  void callback (gint /* width */, gint /* height */, guint texture)
  {
    GstGLFuncs *gl = GST_GL_BASE_FILTER (gobj())->context->gl_vtable;
    const GLfloat texcoords[] = { 0.0f, 0.0f,	1.0f, 0.0f,	1.0f, 1.0f,	0.0f, 1.0f };
    const GLfloat quadVertices[] = {-1.0f, -1.0f, 1.0f, -1.0f, 1.0f,1.0f, -1.0f, 1.0f};

    gl->MatrixMode (GL_PROJECTION);
    gl->LoadIdentity ();
    gl->Enable (GL_TEXTURE_2D);
    gl->BindTexture (GL_TEXTURE_2D, texture);
    gl->EnableClientState(GL_VERTEX_ARRAY);
    gl->EnableClientState (GL_TEXTURE_COORD_ARRAY);

    gl->TexCoordPointer (2, GL_FLOAT, 0, &texcoords);
    gl->VertexPointer(2, GL_FLOAT, 0, quadVertices);
    gl->DrawArrays(GL_QUADS, 0, 4);
    gl->DisableClientState(GL_TEXTURE_COORD_ARRAY);
    gl->DisableClientState(GL_VERTEX_ARRAY);
  }

public:
  static void base_init(Gst::ElementClass<SampleGLFilter> *klass)
  {
      klass->set_metadata("sample gl filter",
              "gstreamermm/examples",
               "sample gl filter", "Marcin Kolny <marcin.kolny@flytronic.pl>");
  }

  explicit SampleGLFilter(GstGLFilter *gobj)
      : Glib::ObjectBase(typeid (SampleGLFilter)),
        Gst::GLFilter(gobj)
  {
    // To use filter_texture vfunc, we have to set filter vfunc to null
      GST_GL_FILTER_GET_CLASS(gobj)->filter = NULL;
  }

  virtual ~SampleGLFilter() {}

  static bool register_element(Glib::RefPtr<Gst::Plugin> plugin)
  {
    return Gst::ElementFactory::register_element(plugin, "sampleglfilter", 10, Gst::register_mm_type<SampleGLFilter>("sampleglfilter"));
  }

  virtual bool filter_texture_vfunc(guint in_tex, guint out_tex)
  {
    render_to_target(false, in_tex, out_tex, sigc::mem_fun(*this, &SampleGLFilter::callback));
    return true;
  }

};

#endif /* SAMPLE_GL_FILTER_H_ */
