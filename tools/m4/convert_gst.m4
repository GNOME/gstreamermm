dnl Copyright 2008 The gstreamermm Development Team

dnl Enums
_CONV_ENUM(Gst,AssocFlags)
_CONV_ENUM(Gst,AudioCdSrcMode)
_CONV_ENUM(Gst,AutoplugSelectResult)
_CONV_ENUM(Gst,AudioBaseSinkSlaveMethod)
_CONV_ENUM(Gst,AudioBaseSinkDiscontReason)
_CONV_ENUM(Gst,AudioBaseSrcSlaveMethod)
_CONV_ENUM(Gst,AudioFlags)
_CONV_ENUM(Gst,AudioLayout)
_CONV_ENUM(Gst,BufferCopyFlags)
_CONV_ENUM(Gst,BufferFlags)
_CONV_ENUM(Gst,AudioFormat)
_CONV_ENUM(Gst,AudioFormatFlags)
_CONV_ENUM(Gst,AudioRingBufferFormatType)
_CONV_ENUM(Gst,BaseSrcFlags)
_CONV_ENUM(Gst,CapsFlags)
_CONV_ENUM(Gst,CapsIntersectMode)
_CONV_ENUM(Gst,ClockEntryType)
_CONV_ENUM(Gst,ClockReturn)
_CONV_ENUM(Gst,ClockTime)
_CONV_ENUM(Gst,ColorBalanceType)
_CONV_ENUM(Gst,DiscovererResult)
_CONV_ENUM(Gst,EventType)
_CONV_ENUM(Gst,EventTypeFlags)
_CONV_ENUM(Gst,FlowReturn)
_CONV_ENUM(Gst,Format)
_CONV_ENUM(Gst,IndexCertainty)
_CONV_ENUM(Gst,IndexEntryType)
_CONV_ENUM(Gst,IndexFlags)
_CONV_ENUM(Gst,IndexLookupMethod)
_CONV_ENUM(Gst,IndexResolverMethod)
_CONV_ENUM(Gst,LockFlags)
_CONV_ENUM(Gst,MapFlags)
_CONV_ENUM(Gst,MemoryFlags)
_CONV_ENUM(Gst,MessageType)
_CONV_ENUM(Gst,MixerFlags)
_CONV_ENUM(Gst,MixerType)
_CONV_ENUM(Gst,MultiHandleSinkClientStatus)
_CONV_ENUM(Gst,MultiHandleSinkSyncMethod)
_CONV_ENUM(Gst,NavigationCommand)
_CONV_ENUM(Gst,NavigationEventType)
_CONV_ENUM(Gst,NavigationMessageType)
_CONV_ENUM(Gst,NavigationQueryType)
_CONV_ENUM(Gst,PadDirection)
_CONV_ENUM(Gst,PadLinkCheck)
_CONV_ENUM(Gst,PadLinkReturn)
_CONV_ENUM(Gst,PadMode)
_CONV_ENUM(Gst,PadPresence)
_CONV_ENUM(Gst,PadProbeType)
_CONV_ENUM(Gst,PlayFlags)
_CONV_ENUM(Gst,PluginDependencyFlags)
_CONV_ENUM(Gst,PluginFlags)
_CONV_ENUM(Gst,ProgressType)
_CONV_ENUM(Gst,QOSType)
_CONV_ENUM(Gst,QueryType)
_CONV_ENUM(Gst,QueryTypeFlags)
_CONV_ENUM(Gst,Rank)
_CONV_ENUM(Gst,SchedulingFlags)
_CONV_ENUM(Gst,SeekFlags)
_CONV_ENUM(Gst,SeekType)
_CONV_ENUM(Gst,State)
_CONV_ENUM(Gst,StateChange)
_CONV_ENUM(Gst,StateChangeReturn)
_CONV_ENUM(Gst,StreamFlags)
_CONV_ENUM(Gst,StreamStatusType)
_CONV_ENUM(Gst,StreamVolumeFormat)
_CONV_ENUM(Gst,StructureChangeType)
_CONV_ENUM(Gst,TagMergeMode)
_CONV_ENUM(Gst,TaskState)
_CONV_ENUM(Gst,TocEntryType)
_CONV_ENUM(Gst,TocLoopType)
_CONV_ENUM(Gst,TocScope)
_CONV_ENUM(Gst,TunerChannelFlags)
_CONV_ENUM(Gst,URIType)
_CONV_ENUM(Gst,VideoBufferFlags)
_CONV_ENUM(Gst,VideoChromaSite)
_CONV_ENUM(Gst,VideoFlags)
_CONV_ENUM(Gst,VideoFormat)
_CONV_ENUM(Gst,VideoFormatFlags)
_CONV_ENUM(Gst,VideoFrameFlags)
_CONV_ENUM(Gst,VideoFrameMapFlags)
_CONV_ENUM(Gst,VideoInterlaceMode)
_CONV_ENUM(Gst,VideoMultiviewFlags)
_CONV_ENUM(Gst,VideoMultiviewFramePacking)
_CONV_ENUM(Gst,VideoMultiviewMode)
_CONV_ENUM(Gst,VideoPackFlags)
_CONV_ENUM(GstSDP,Result)

dnl Glibmm Enums
_CONV_GLIB_ENUM(ThreadPriority)


dnl ############### gstreamermm Class Conversions ######################

dnl AllocationParams
_CONVERSION(`const Gst::AllocationParams&', `GstAllocationParams*', `const_cast<GstAllocationParams*>($3.gobj())')
_CONVERSION(`GstAllocationParams*', `const Gst::AllocationParams&', `Gst::AllocationParams($3, true)')

dnl Allocator
_CONVERSION(`const Glib::RefPtr<Gst::Allocator>&',`GstAllocator*', `const_cast<GstAllocator*>(Glib::unwrap($3))')
_CONVERSION(`Glib::RefPtr<Gst::Allocator>&&',`GstAllocator*',`($3) ? $3.release()->gobj() : nullptr');
_CONVERSION(`GstAllocator*', `Glib::RefPtr<Gst::Allocator>', `Glib::wrap($3)')
_CONVERSION(`GstAllocator*', `Glib::RefPtr<const Gst::Allocator>', `Glib::wrap($3)')

dnl AudioFormatInfo
_CONVERSION(`const GstAudioFormatInfo*', `const Gst::AudioFormatInfo', `Gst::AudioFormatInfo($3)')

dnl AudioInfo
_CONVERSION(`const Gst::AudioInfo&', `const GstAudioInfo*', `$3.gobj()')
_CONVERSION(`const GstAudioInfo*', `const Gst::AudioInfo&', `Gst::AudioInfo(const_cast<GstAudioInfo*>($3))')

dnl AudioRingBuffer
_CONVERSION(`GstAudioRingBuffer*',`Glib::RefPtr<Gst::AudioRingBuffer>',`Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::AudioRingBuffer>',`GstAudioRingBuffer*',`Glib::unwrap($3)')

dnl AudioRingBufferSpec
_CONVERSION(`Gst::AudioRingBufferSpec&', `GstAudioRingBufferSpec*', `$3.gobj()')

dnl Buffer
_CONVERSION(`GstBuffer*',`Glib::RefPtr<Gst::Buffer>',`Glib::wrap($3)')
_CONVERSION(`GstBuffer*',`const Glib::RefPtr<Gst::Buffer>&',`Glib::wrap($3, true)')
_CONVERSION(`const Glib::RefPtr<Gst::Buffer>&',`GstBuffer*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::Buffer>&',`GstBuffer*', `const_cast<GstBuffer*>(Glib::unwrap($3))')
_CONVERSION(`const Glib::RefPtr<Gst::Buffer>&',`const GstBuffer*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Buffer>',`GstBuffer*', `Glib::unwrap($3)')
_CONVERSION(`GstBuffer*', `const Glib::RefPtr<Gst::Buffer>&', `Glib::wrap($3, true)')
_CONVERSION(`Glib::RefPtr<Gst::Buffer>&&',`GstBuffer*',`($3) ? $3.release()->gobj() : nullptr')


dnl BufferList
_CONVERSION(`Glib::RefPtr<Gst::BufferList>',`GstBufferList*', `Glib::unwrap($3)')
_CONVERSION(`GstBufferList*', `Glib::RefPtr<Gst::BufferList>', `Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::BufferList>&', `GstBufferList*', `Glib::unwrap($3)')

dnl Bus
_CONVERSION(`const Glib::RefPtr<Gst::Bus>&',`GstBus*', `Glib::unwrap($3)')
_CONVERSION(`GstBus*',`Glib::RefPtr<Gst::Bus>',`Glib::wrap($3)')
_CONVERSION(`GstBus*',`Glib::RefPtr<const Gst::Bus>',`Glib::wrap($3)')

dnl Caps
_CONVERSION(`GstCaps*',`Glib::RefPtr<Gst::Caps>',`Glib::wrap($3)')
_CONVERSION(`GstCaps*',`Glib::RefPtr<const Gst::Caps>',`Glib::wrap($3)')
_CONVERSION(`GstCaps*',`const Glib::RefPtr<Gst::Caps>&',`Glib::wrap($3, true)')
_CONVERSION(`GstCaps*',`const Glib::RefPtr<const Gst::Caps>&',`Glib::wrap($3, true)')
_CONVERSION(`const GstCaps*',`const Glib::RefPtr<const Gst::Caps>&',`Glib::wrap(const_cast<GstCaps*>($3))')
_CONVERSION(`Glib::RefPtr<Gst::Caps>',`GstCaps*',`Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Caps>&',`GstCaps*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::Caps>&',`GstCaps*', `const_cast<$2>(Glib::unwrap($3))')
_CONVERSION(`const Glib::RefPtr<Gst::Caps>&',`const GstCaps*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::Caps>&',`const GstCaps*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Caps>&&',`GstCaps*',`($3) ? $3.release()->gobj() : nullptr')

dnl CapsFeatures
_CONVERSION(`const Gst::CapsFeatures&',`const GstCapsFeatures*',`$3.gobj()')
_CONVERSION(`GstCapsFeatures*',`Gst::CapsFeatures',`CapsFeatures($3, false)')

dnl Clock
_CONVERSION(`GstClock*',`Glib::RefPtr<Gst::Clock>',`Glib::wrap($3)')
_CONVERSION(`GstClock*',`Glib::RefPtr<const Gst::Clock>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Clock>&',`GstClock*', `Glib::unwrap($3)')
_CONVERSION(`const Clock&',`GstClock*',`((GstClock*)(&$3))')
_CONVERSION(`Glib::RefPtr<Gst::Clock>',`GstClock*', `Glib::unwrap($3)')

dnl ClockID
_CONVERSION(`GstClockID',`Glib::RefPtr<Gst::ClockID>',`Glib::wrap((GstClockEntry*)($3))')
_CONVERSION(`const Glib::RefPtr<Gst::ClockID>&',`GstClockEntry*',`Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::ClockID>&',`GstClockID',`Glib::unwrap($3)')

dnl ColorBalanceChannel
_CONVERSION(`const Glib::RefPtr<Gst::ColorBalanceChannel>&',`GstColorBalanceChannel*',`Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::ColorBalanceChannel>&',`GstColorBalanceChannel*',`const_cast<GstColorBalanceChannel*>(Glib::unwrap($3))')

dnl Context
_CONVERSION(`GstContext*',`Glib::RefPtr<Gst::Context>',`Glib::wrap($3)')
_CONVERSION(`GstContext*',`const Glib::RefPtr<Gst::Context>&',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Context>&',`GstContext*',`$3->gobj()')

dnl DiscovererInfo
_CONVERSION(`GstDiscovererInfo*',`Glib::RefPtr<Gst::DiscovererInfo>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::DiscovererInfo>&',`GstDiscovererInfo*',`Glib::unwrap($3)')

dnl DiscovererStreamInfo
_CONVERSION(`GstDiscovererStreamInfo*', `Glib::RefPtr<Gst::DiscovererStreamInfo>', `Glib::wrap($3)')

dnl Element
_CONVERSION(`Glib::RefPtr<Gst::Element>',`GstElement*', `Glib::unwrap($3)')
_CONVERSION(`GstElement*',`Glib::RefPtr<Gst::Element>',`Glib::wrap($3)')
_CONVERSION(`GstElement*',`Glib::RefPtr<const Gst::Element>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Element>&',`GstElement*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::Element>&',`GstElement*', `const_cast<GstElement*>(Glib::unwrap($3))')
_CONVERSION(`State&',`GstState*',`(GstState*)(&$3)')

dnl ElementFactory
_CONVERSION(`GstElementFactory*',`Glib::RefPtr<Gst::ElementFactory>',`Glib::wrap($3)')
_CONVERSION(`GstElementFactory*',`Glib::RefPtr<const Gst::ElementFactory>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::ElementFactory>&',`GstElementFactory*', `Glib::unwrap($3)')

dnl EncodingProfile
_CONVERSION(`const Glib::RefPtr<Gst::EncodingProfile>&', `GstEncodingProfile*', `Glib::unwrap($3)')

dnl Event
_CONVERSION(`const Glib::RefPtr<Gst::Event>&',`GstEvent*', `Glib::unwrap($3)')
_CONVERSION(`GstEvent*',`const Glib::RefPtr<Gst::Event>&', `Glib::wrap($3)')
_CONVERSION(`GstEvent*',`Glib::RefPtr<Gst::Event>', `Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Event>&&',`GstEvent*',`($3) ? $3.release()->gobj() : nullptr')

dnl Socket
_CONVERSION(`const Glib::RefPtr<Gio::Socket>&',`GSocket*', `Glib::unwrap($3)')

dnl Index
_CONVERSION(`GstIndex*',`Glib::RefPtr<Gst::Index>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Index>&',`GstIndex*',`Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Index>',`GstIndex*',`Glib::unwrap($3)')

dnl IndexFactory
_CONVERSION(`GstIndexFactory*',`Glib::RefPtr<Gst::IndexFactory>',`Glib::wrap($3)')

dnl Iterator
_CONVERSION(`GstIterator*',`Gst::Iterator<Gst::Element>',`Gst::Iterator<Gst::Element>($3)')
_CONVERSION(`GstIterator*',`Gst::Iterator<const Gst::Element>',`Gst::Iterator<const Gst::Element>($3)')
_CONVERSION(`GstIterator*',`Gst::Iterator<Gst::Pad>',`Gst::Iterator<Gst::Pad>($3)')
_CONVERSION(`GstIterator*',`Gst::Iterator<const Gst::Pad>',`Gst::Iterator<const Gst::Pad>($3)')
_CONVERSION(`GstIterator*',`Gst::IteratorBasic<const Gst::QueryTypeDefinition>',`Gst::IteratorBasic<const Gst::QueryTypeDefinition>($3)')

dnl MapInfo
_CONVERSION(`const Gst::MapInfo&', `GstMapInfo*', `const_cast<GstMapInfo*>($3.gobj())')
_CONVERSION(`Gst::MapInfo&', `GstMapInfo*', `($3.gobj())')

dnl Memory
_CONVERSION(`GstMemory*',`Glib::RefPtr<Gst::Memory>&',`Glib::wrap($3)')
_CONVERSION(`GstMemory*',`Glib::RefPtr<Gst::Memory>',`Glib::wrap($3)')
_CONVERSION(`GstMemory*',`Glib::RefPtr<const Gst::Memory>',`Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Memory>&',`GstMemory*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Memory>&',`GstMemory*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Memory>',`GstMemory*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Memory>&&',`GstMemory*',`($3) ? $3.release()->gobj() : nullptr')

dnl Message
_CONVERSION(`GstMessage*',`Glib::RefPtr<Gst::Message>',`Glib::wrap($3)')
_CONVERSION(`GstMessage*',`Glib::RefPtr<const Gst::Message>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Message>&',`GstMessage*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Message>&&',`GstMessage*',`($3) ? $3.release()->gobj() : nullptr')

dnl MiniObject
_CONVERSION(`GstMiniObject*',`Glib::RefPtr<Gst::MiniObject>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::MiniObject>&',`GstMiniObject*',`Glib::unwrap($3)')

dnl Mixer
_CONVERSION(`const Glib::RefPtr<Gst::MixerOptions>&',`GstMixerOptions*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::MixerOptions>&',`GstMixerOptions*', `const_cast<$2>(Glib::unwrap($3))')
_CONVERSION(`const Glib::RefPtr<Gst::MixerTrack>&',`GstMixerTrack*', `Glib::unwrap($3)')

dnl Gst::Object
_CONVERSION(`GstObject*',`Glib::RefPtr<Gst::Object>',`Glib::wrap($3)')
_CONVERSION(`GstObject*',`Glib::RefPtr<const Gst::Object>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Object>&',`GstObject*',`Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Object>',`GstObject*',`Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::Object>&',`GstObject*',`const_cast<GstObject*>(Glib::unwrap($3))')
_CONVERSION(`const Glib::RefPtr<Gst::Object>&', `GstObject*', `Glib::unwrap($3)')

dnl Pad
_CONVERSION(`GstPad*',`Glib::RefPtr<Gst::Pad>',`Glib::wrap($3)')
_CONVERSION(`GstPad*',`Glib::RefPtr<const Gst::Pad>',`Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Pad>',`GstPad*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Pad>&',`GstPad*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::Pad>&',`GstPad*',`const_cast<GstPad*>(Glib::unwrap($3))')

dnl PadTemplate
_CONVERSION(`GstPadTemplate*',`Glib::RefPtr<Gst::PadTemplate>', `Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::PadTemplate>',`GstPadTemplate*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::PadTemplate>&',`GstPadTemplate*',`Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::PadTemplate>&',`GstPadTemplate*',`const_cast<GstPadTemplate*>(Glib::unwrap($3))')

dnl StaticPadTemplate
_CONVERSION(`Gst::StaticPadTemplate&',`GstStaticPadTemplate*',($3).gobj())
_CONVERSION(`const Gst::StaticPadTemplate&',`const GstStaticPadTemplate*',($3).gobj())

dnl Plugin
_CONVERSION(`const Glib::RefPtr<Gst::Plugin>&',`GstPlugin*',`Glib::unwrap($3)')
_CONVERSION(`GstPlugin*',`Glib::RefPtr<Gst::Plugin>',`Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Plugin>&&',`GstPlugin*',`($3) ? $3.release()->gobj() : nullptr')

dnl PluginFeature
_CONVERSION(`GstPluginFeature*',`Glib::RefPtr<Gst::PluginFeature>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::PluginFeature>&',`GstPluginFeature*',`Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::PluginFeature>&&',`GstPluginFeature*',`($3) ? $3.release()->gobj() : nullptr')

dnl Query
_CONVERSION(`const Glib::RefPtr<Gst::Query>&',`GstQuery*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Query>',`GstQuery*', `Glib::unwrap($3)')
_CONVERSION(`GstQuery*', `Glib::RefPtr<Gst::Query>',`Glib::wrap($3)')

dnl Registry
_CONVERSION(`GstRegistry*',`Glib::RefPtr<Gst::Registry>', `Glib::wrap($3)')

dnl Sample
_CONVERSION(`GstSample*',`Glib::RefPtr<Gst::Sample>',`Glib::wrap($3)')
_CONVERSION(`GstSample*',`Glib::RefPtr<const Gst::Sample>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Sample>&',`GstSample*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Sample>', `GstSample*', `Glib::unwrap($3)')

dnl Segment
_CONVERSION(`GstSegment*',`Gst::Segment',`Glib::wrap($3)')
_CONVERSION(`const Gst::Segment&',`const GstSegment*', `$3.gobj()')

dnl Structure
_CONVERSION(`Gst::Structure&',`GstStructure*',`$3.gobj()')
_CONVERSION(`const Gst::Structure&',`GstStructure*',`const_cast<GstStructure*>($3.gobj())')
_CONVERSION(`GstStructure*', `Gst::Structure', `Glib::wrap($3)')
_CONVERSION(`const Gst::Structure&',`const GstStructure*',`$3.gobj()')
_CONVERSION(`const GstStructure*',`Gst::Structure', `Glib::wrap(const_cast<GstStructure*>($3), false)')
_CONVERSION(`const GstStructure*',`const Gst::Structure&', `Glib::wrap(const_cast<GstStructure*>($3), false)')
_CONVERSION(`Gst::Structure&&',`GstStructure*',`($3) ? $3.release() : nullptr')


dnl TagList
_CONVERSION(`const Gst::TagList&',`const GstTagList*',`$3.gobj()')
_CONVERSION(`const Gst::TagList&',`GstTagList*',`const_cast<GstTagList*>($3.gobj())')
_CONVERSION(`Gst::TagList&',`GstTagList*',`$3.gobj()')
_CONVERSION(`Gst::TagList',`GstTagList*',`$3.gobj()')

dnl TaskPool
_CONVERSION(`const Glib::RefPtr<Gst::TaskPool>&',`GstTaskPool*', `Glib::unwrap($3)')
_CONVERSION(`GstTaskPool*',`Glib::RefPtr<Gst::TaskPool>',`Glib::wrap($3)')
_CONVERSION(`GstTaskPool*',`Glib::RefPtr<const Gst::TaskPool>',`Glib::wrap($3)')

dnl Toc
_CONVERSION(`const GstToc*',`Glib::RefPtr<const Gst::Toc>',`Glib::wrap(const_cast<GstToc*>($3))')
_CONVERSION(`GstToc*',`Glib::RefPtr<Gst::Toc>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Toc>&', `GstToc*',`Glib::unwrap($3)')

dnl TocEntry
_CONVERSION(`GstTocEntry*',`Glib::RefPtr<Gst::TocEntry>',`Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::TocEntry>', `GstTocEntry*',`Glib::unwrap($3)')

dnl TocLoopType
_CONVERSION(`Gst::TocLoopType&',`GstTocLoopType*',`reinterpret_cast<GstTocLoopType*>(&($3))')

dnl TypeFind
_CONVERSION(`Gst::TypeFind&',`GstTypeFind*',`$3.gobj()')

dnl VideoInfo
_CONVERSION(`Gst::VideoInfo', `GstVideoInfo*', `$3.gobj()')
_CONVERSION(`const Gst::VideoInfo&', `const GstVideoInfo*', `$3.gobj()')
_CONVERSION(`const Gst::VideoInfo&', `GstVideoInfo*', `const_cast<GstVideoInfo*>($3.gobj())')
_CONVERSION(`const Gst::VideoInfo&', `GstVideoInfo', `*($3.gobj())')
_CONVERSION(`Gst::VideoInfo', `GstVideoInfo', `*($3.gobj())')
_CONVERSION(`GstVideoInfo', `Gst::VideoInfo', `Gst::VideoInfo(Gst::VideoInfo(const_cast<GstVideoInfo*>(&$3), false))')

dnl VideoFormatInfo
_CONVERSION(`const GstVideoFormatInfo*', `const VideoFormatInfo', `VideoFormatInfo($3)')

dnl VideoFrame
_CONVERSION(`const Gst::VideoFrame&', `GstVideoFrame*', `$3.gobj()')
_CONVERSION(`const Gst::VideoFrame&', `const GstVideoFrame*', `$3.gobj()')
_CONVERSION(`const Gst::VideoFrame&', `GstVideoFrame*', `const_cast<GstVideoFrame*>($3.gobj())')


dnl ############## gstreamermm Interface Conversions ######################

dnl TunerChannel
_CONVERSION(`GstTunerChannel*',`Glib::RefPtr<Gst::TunerChannel>', `Glib::wrap($3)')
_CONVERSION(`GstTunerChannel*',`Glib::RefPtr<const Gst::TunerChannel>', `Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::TunerChannel>&',`GstTunerChannel*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::TunerChannel>&',`GstTunerChannel*', `const_cast<GstTunerChannel*>(Glib::unwrap($3))')
_CONVERSION(`Glib::RefPtr<Gst::TunerChannel>', `GstTunerChannel*', `Glib::unwrap($3)')

dnl TunerNorm
_CONVERSION(`GstTunerNorm*',`Glib::RefPtr<Gst::TunerNorm>', `Glib::wrap($3)')
_CONVERSION(`GstTunerNorm*',`Glib::RefPtr<const Gst::TunerNorm>', `Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::TunerNorm>&',`GstTunerNorm*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Gst::TunerNorm>&',`GstTunerNorm*', `const_cast<GstTunerNorm*>(Glib::unwrap($3))')
_CONVERSION(`Glib::RefPtr<Gst::TunerNorm>', `GstTunerNorm*', `Glib::unwrap($3)')

dnl URIHandler
_CONVERSION(`const Glib::RefPtr<Gst::URIHandler>&',`GstURIHandler*',`Glib::unwrap($3)')

dnl ##################General Conversions############################

dnl Basic General Conversions
_CONVERSION(`guint64&',`guint64*',`&$3')
_CONVERSION(`guint*',`guint&',`*$3')
_CONVERSION(`const guint&',`guint',`$3')
_CONVERSION(`gsize*',`gsize&',`*$3')
_CONVERSION(`const guint32&',`guint32',`$3')
_CONVERSION(`guint8*&',`guint8**',`&$3')
_CONVERSION(`gdouble&',`gdouble*',`&$3')
_CONVERSION(`guint8*',`const guint8*',`$3')

dnl Basic Gstreamermm Conversions
_CONVERSION(`Gst::ClockTime&',`GstClockTime*',`(GstClockTime*)(&$3)')
_CONVERSION(`Gst::ClockTimeDiff',`GstClockTimeDiff',`GstClockTimeDiff($3)')
_CONVERSION(`GstClockTimeDiff',`Gst::ClockTimeDiff',`Gst::ClockTimeDiff($3)')
_CONVERSION(`Gst::ClockTimeDiff&',`GstClockTimeDiff*',`(GstClockTimeDiff*)(&$3)')
_CONVERSION(`GstClockTimeDiff*',`Gst::ClockTimeDiff&',`(Gst::ClockTimeDiff&)(*$3)')
_CONVERSION(`GstMixerMessageType',`Gst::MixerMessageType',`(Gst::MixerMessageType)($3)')
_CONVERSION(`const GstQueryType*',`const Gst::QueryType*',`(Gst::QueryType*)($3)')
_CONVERSION(`GstState*',`State&',`*reinterpret_cast<Gst::State*>($3)')
_CONVERSION(`GstTagFlag',`Gst::TagFlag',`(Gst::TagFlag)($3)')
_CONVERSION(`guint64',`Gst::ClockTime',`(Gst::ClockTime)($3)')
_CONVERSION(`const Gst::URIType',`const GstURIType',`(GstURIType)($3)')
_CONVERSION(`const Gst::AudioChannelPosition&',`const GstAudioChannelPosition*',`(const GstAudioChannelPosition*)(&$3)')
dnl C++ Conversions
_CONVERSION(`const va_list&',`va_list',`const_cast<va_list&>($3)')

dnl Glibmm Conversions
_CONVERSION(`const Glib::Error&', `const GError*', `$3.gobj()')
_CONVERSION(`const Glib::Error&', `GError*', `const_cast<GError*>($3.gobj())')
_CONVERSION(`GQuark',`Glib::QueryQuark',`Glib::QueryQuark($3)')
_CONVERSION(`const Glib::QueryQuark&',`GQuark',`$3')
_CONVERSION(`Glib::Threads::RecMutex&',`GRecMutex*',`$3.gobj()')
_CONVERSION(`const Glib::StringArrayHandle&',`const gchar**',`const_cast<const char**>($3.data())')
_CONVERSION(`const Glib::ValueArray&',`GValueArray*',`const_cast<GValueArray*>($3.gobj())')

dnl String Conversions

_CONVERSION(`const std::string&',`const guchar*',`($2)($3.c_str())')
_CONVERSION(`gchar*',`const Glib::ustring&',__GCHARP_TO_USTRING)
_CONVERSION(`gchararray',`const Glib::ustring&',__GCHARP_TO_USTRING)
_CONVERSION(`const gchar*',`const Glib::ustring&',__GCHARP_TO_USTRING)
_CONVERSION(`Glib::ustring&',`const guchar*', ($2)($3.c_str()))
_CONVERSION(`const Glib::ustring&',`gchararray', $3.c_str())

dnl libxml++ Conversions
_CONVERSION(`xmlpp::Node*',`xmlNodePtr',`$3->cobj()')
_CONVERSION(`xmlpp::Node*',`GstXmlNodePtr',`$3->cobj()')
_CONVERSION(`xmlpp::Document*',`xmlDocPtr',`$3->cobj()')
