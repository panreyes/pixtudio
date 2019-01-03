LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := pxtrtm

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/pxtrtm/include/ \
	$(LOCAL_PATH)/../../../../../3rdparty/SDL2/include/ \
	$(LOCAL_PATH)/../../../../../3rdparty/SDL2_mixer/ \
	$(LOCAL_PATH)/../../../../../3rdparty/libpng-1.6.23/ \
	$(LOCAL_PATH)/../../../../../3rdparty/libglob-bsd/include/ \
	$(LOCAL_PATH)/../../../../../3rdparty/stb/ \
	$(LOCAL_PATH)/../../../../../3rdparty/theoraplay/ \
	$(LOCAL_PATH)/../../../../../3rdparty/libtheora-1.1.1/include/ \
	$(LOCAL_PATH)/../../../../../3rdparty/SDL2_mixer/external/libvorbis-1.3.3/include \
	$(LOCAL_PATH)/../../../../../3rdparty/tre/lib \
	$(LOCAL_PATH)/../../../../../3rdparty/openal-soft-1.17.0/include/ \
	$(LOCAL_PATH)/../../../../../3rdparty/freetype-2.7/include/ \
	$(LOCAL_PATH)/../../../../../3rdparty/libjpeg-turbo-2.0.0/ \
	$(MODULES_PATH)/libbgload/ \
	$(MODULES_PATH)/mod_say/ \
	$(MODULES_PATH)/mod_string/ \
	$(MODULES_PATH)/mod_math/ \
	$(MODULES_PATH)/mod_mem/ \
	$(MODULES_PATH)/mod_time/ \
	$(MODULES_PATH)/mod_file/ \
	$(MODULES_PATH)/mod_sound/ \
	$(MODULES_PATH)/libsdlhandler/ \
	$(MODULES_PATH)/libkey/ \
	$(MODULES_PATH)/mod_key/ \
	$(MODULES_PATH)/mod_proc/ \
	$(MODULES_PATH)/mod_sort/ \
	$(MODULES_PATH)/mod_timers/ \
	$(MODULES_PATH)/libgrbase/ \
	$(MODULES_PATH)/libblit/ \
	$(MODULES_PATH)/libvideo/ \
	$(MODULES_PATH)/librender/ \
	$(MODULES_PATH)/mod_video/ \
	$(MODULES_PATH)/libmouse/ \
	$(MODULES_PATH)/mod_mouse/ \
	$(MODULES_PATH)/mod_map/ \
	$(MODULES_PATH)/libfont/ \
	$(MODULES_PATH)/mod_dir/ \
	$(MODULES_PATH)/libtext/ \
	$(MODULES_PATH)/mod_text/ \
	$(MODULES_PATH)/mod_rand/ \
	$(MODULES_PATH)/mod_grproc/ \
	$(MODULES_PATH)/libscroll/ \
	$(MODULES_PATH)/mod_scroll/ \
	$(MODULES_PATH)/libdraw/ \
	$(MODULES_PATH)/mod_draw/ \
	$(MODULES_PATH)/mod_screen/ \
	$(MODULES_PATH)/mod_path/ \
	$(MODULES_PATH)/libwm/ \
	$(MODULES_PATH)/mod_wm/ \
	$(MODULES_PATH)/mod_sys/ \
	$(MODULES_PATH)/mod_regex/ \
	$(MODULES_PATH)/mod_multi/ \
	$(MODULES_PATH)/mod_gamecontroller/ \
	$(MODULES_PATH)/mod_joy/ \
	$(MODULES_PATH)/libjoy/ \
	$(MODULES_PATH)/mod_theora/ \
	$(MODULES_PATH)/mod_fsock/ \
	$(MODULES_PATH)/mod_effects/ \
	$(MODULES_PATH)/libsocket/ \
	$(MODULES_PATH)/mod_debug/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-D__PXTRTM__ \
	-D__MONOLITHIC__ \
	-DNO_MODCHIPMUNK \
	-DNO_MODICONV \
	-DNO_MODCURL \
	-DNO_MODSTEAM \
	-DWITH_SDLRWOPS \
	-ffast-math \
	-O3

LOCAL_SRC_FILES := \
	../../../../../3rdparty/libglob-bsd/src/glob.c \
	../../../../../core/common/debug.c \
	../../../../../core/common/files.c \
	../../../../../core/common/xctype.c \
	../../../../../core/pxtrtm/src/copy.c \
	../../../../../core/pxtrtm/src/dcbr.c \
	../../../../../core/pxtrtm/src/dirs.c \
	../../../../../core/pxtrtm/src/fmath.c \
	../../../../../core/pxtrtm/src/instance.c \
	../../../../../core/pxtrtm/src/interpreter.c \
	../../../../../core/pxtrtm/src/misc.c \
	../../../../../core/pxtrtm/src/strings.c \
	../../../../../core/pxtrtm/src/sysprocs.c \
	../../../../../core/pxtrtm/src/varspace_file.c \
	../../../../../modules/libbgload/bgload.c \
	../../../../../modules/libblit/g_blit.c \
	../../../../../modules/libblit/g_pixel.c \
	../../../../../modules/libdraw/libdraw.c \
	../../../../../modules/libfont/libfont.c \
	../../../../../modules/libgrbase/g_bitmap.c \
	../../../../../modules/libgrbase/g_blendop.c \
	../../../../../modules/libgrbase/g_clear.c \
	../../../../../modules/libgrbase/g_conversion.c \
	../../../../../modules/libgrbase/g_grlib.c \
	../../../../../modules/libgrbase/g_pal.c \
	../../../../../modules/libgrbase/libgrbase.c \
	../../../../../modules/libjoy/libjoy.c \
	../../../../../modules/libkey/libkey.c \
	../../../../../modules/libmouse/libmouse.c \
	../../../../../modules/librender/g_fade.c \
	../../../../../modules/librender/g_frame.c \
	../../../../../modules/librender/g_instance.c \
	../../../../../modules/librender/g_object.c \
	../../../../../modules/librender/g_rects.c \
	../../../../../modules/librender/g_screen.c \
	../../../../../modules/librender/librender.c \
	../../../../../modules/libscroll/libscroll.c \
	../../../../../modules/libsdlhandler/libsdlhandler.c \
	../../../../../modules/libsocket/libsocket.c \
	../../../../../modules/libtext/libtext.c \
	../../../../../modules/libvideo/g_regions.c \
	../../../../../modules/libvideo/g_video.c \
	../../../../../modules/libwm/libwm.c \
	../../../../../modules/mod_debug/mod_debug.c \
	../../../../../modules/mod_dir/mod_dir.c \
	../../../../../modules/mod_draw/mod_draw.c \
	../../../../../modules/mod_effects/mod_effects.c \
	../../../../../modules/mod_file/mod_file.c \
	../../../../../modules/mod_fsock/mod_fsock.c \
	../../../../../modules/mod_gamecontroller/mod_gamecontroller.c \
	../../../../../modules/mod_grproc/mod_grproc.c \
	../../../../../modules/mod_joy/mod_joy.c \
	../../../../../modules/mod_key/mod_key.c \
	../../../../../modules/mod_map/file_fnt.c \
	../../../../../modules/mod_map/file_fpg.c \
	../../../../../modules/mod_map/file_map.c \
	../../../../../modules/mod_map/file_pal.c \
	../../../../../modules/mod_map/file_pcx.c \
	../../../../../modules/mod_map/file_png.c \
	../../../../../modules/mod_map/file_jpg.c \
	../../../../../modules/mod_map/mod_map.c \
	../../../../../modules/mod_math/mod_math.c \
	../../../../../modules/mod_mem/mod_mem.c \
	../../../../../modules/mod_multi/mod_multi.c \
	../../../../../modules/mod_path/mod_path.c \
	../../../../../modules/mod_proc/mod_proc.c \
	../../../../../modules/mod_rand/mod_rand.c \
	../../../../../modules/mod_regex/mod_regex.c \
	../../../../../modules/mod_say/mod_say.c \
	../../../../../modules/mod_screen/mod_screen.c \
	../../../../../modules/mod_scroll/mod_scroll.c \
	../../../../../modules/mod_sort/mod_sort.c \
	../../../../../modules/mod_sound/mod_sound.c \
	../../../../../modules/mod_string/mod_string.c \
	../../../../../modules/mod_sys/mod_sys.c \
	../../../../../modules/mod_text/mod_text.c \
	../../../../../modules/mod_theora/mod_theora.c \
	../../../../../3rdparty/theoraplay/theoraplay.c \
	../../../../../modules/mod_time/mod_time.c \
	../../../../../modules/mod_timers/mod_timers.c \
	../../../../../modules/mod_video/mod_video.c \
	../../../../../modules/mod_wm/mod_wm.c \
	../../../../../modules/mod_wm/locale/android.c

LOCAL_LDLIBS := -llog -ldl -lz
LOCAL_SHARED_LIBRARIES += SDL2 SDL2_mixer png theora libopenal
LOCAL_STATIC_LIBRARIES += tre freetype libjpeg-turbo

include $(BUILD_SHARED_LIBRARY)
