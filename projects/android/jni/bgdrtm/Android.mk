LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := bgdrtm

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL_mixer/ \
	$(LOCAL_PATH)/../../../../3rdparty/libpng/ \
	$(LOCAL_PATH)/../../../../3rdparty/libglob-bsd/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/curl-7.23.1/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/Chipmunk-6.1.3/include/chipmunk/ \
	$(MODULES_PATH)/libbgload/ \
	$(MODULES_PATH)/mod_say/ \
	$(MODULES_PATH)/mod_string/ \
	$(MODULES_PATH)/mod_math/ \
	$(MODULES_PATH)/mod_mem/ \
	$(MODULES_PATH)/mod_time/ \
	$(MODULES_PATH)/mod_file/ \
	$(MODULES_PATH)/mod_sound/ \
	$(MODULES_PATH)/libsdlhandler/ \
	$(MODULES_PATH)/mod_joy/ \
	$(MODULES_PATH)/libjoy/ \
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
	$(MODULES_PATH)/mod_effects/ \
	$(MODULES_PATH)/mod_blendop/ \
	$(MODULES_PATH)/mod_m7/ \
	$(MODULES_PATH)/libwm/ \
	$(MODULES_PATH)/mod_wm/ \
	$(MODULES_PATH)/mod_sys/ \
	$(MODULES_PATH)/mod_flic/ \
	$(MODULES_PATH)/mod_regex/ \
	$(MODULES_PATH)/mod_multi/ \
	$(MODULES_PATH)/mod_curl/ \
	$(MODULES_PATH)/mod_sensor/ \
	$(MODULES_PATH)/mod_chipmunk/ \
	$(MODULES_PATH)/mod_iap/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-D__BGDRTM__ \
	-D__MONOLITHIC__ \
	-DNO_MODMATHI \
	-DNO_MODIMAGE \
	-DNO_MODICONV \
	-DNO_MODFMODEX \
	-DNO_FSOCK \
	-DCP_USE_DOUBLES=0 \
	-DTARGET_LINUX \
	-DTARGET_ANDROID \
	-DWITH_SDLRWOPS \
	-DWITH_GPL_CODE \
	-ffast-math \
	-O3

LOCAL_SRC_FILES := \
	../../../../core/bgdrtm/src/copy.c \
	../../../../core/bgdrtm/src/dcbr.c \
	../../../../core/bgdrtm/src/dirs.c \
	../../../../core/bgdrtm/src/instance.c \
	../../../../core/bgdrtm/src/interpreter.c \
	../../../../core/bgdrtm/src/misc.c \
	../../../../core/bgdrtm/src/strings.c \
	../../../../core/bgdrtm/src/sysprocs.c \
	../../../../core/bgdrtm/src/varspace_file.c \
	../../../../core/bgdrtm/src/fmath.c \
	../../../../core/common/debug.c \
	../../../../core/common/files.c \
	../../../../core/common/xctype.c \
	../../../../3rdparty/libglob-bsd/src/glob.c \
	../../../../modules/libbgload/bgload.c \
	../../../../modules/mod_say/mod_say.c \
	../../../../modules/mod_string/mod_string.c \
	../../../../modules/mod_math/mod_math.c \
    ../../../../modules/mod_mem/mod_mem.c \
	../../../../modules/mod_time/mod_time.c \
	../../../../modules/mod_file/mod_file.c \
	../../../../modules/mod_sound/mod_sound.c \
	../../../../modules/libsdlhandler/libsdlhandler.c \
	../../../../modules/libjoy/libjoy.c \
	../../../../modules/mod_joy/mod_joy.c \
	../../../../modules/libkey/libkey.c \
	../../../../modules/mod_key/mod_key.c \
	../../../../modules/mod_proc/mod_proc.c \
	../../../../modules/mod_sort/mod_sort.c \
	../../../../modules/mod_timers/mod_timers.c \
	../../../../modules/libgrbase/g_bitmap.c \
	../../../../modules/libgrbase/g_clear.c \
	../../../../modules/libgrbase/g_grlib.c \
	../../../../modules/libgrbase/g_pal.c \
	../../../../modules/libgrbase/g_blendop.c \
	../../../../modules/libgrbase/g_conversion.c \
	../../../../modules/libgrbase/libgrbase.c \
	../../../../modules/libblit/g_blit.c \
	../../../../modules/libblit/g_pixel.c \
	../../../../modules/libblit/libblit.c \
	../../../../modules/libvideo/g_regions.c \
	../../../../modules/libvideo/g_video.c \
	../../../../modules/librender/g_fade.c \
	../../../../modules/librender/g_frame.c \
	../../../../modules/librender/g_instance.c \
	../../../../modules/librender/g_object.c \
	../../../../modules/librender/g_rects.c \
	../../../../modules/librender/g_screen.c \
	../../../../modules/librender/librender.c \
	../../../../modules/mod_video/mod_video.c \
	../../../../modules/libmouse/libmouse.c \
	../../../../modules/mod_map/file_fnt.c \
	../../../../modules/mod_map/file_fpg.c \
	../../../../modules/mod_map/file_map.c \
	../../../../modules/mod_map/file_pal.c \
	../../../../modules/mod_map/file_pcx.c \
	../../../../modules/mod_map/file_png.c \
	../../../../modules/mod_map/mod_map.c \
	../../../../modules/libfont/libfont.c \
	../../../../modules/mod_dir/mod_dir.c \
	../../../../modules/libtext/libtext.c \
	../../../../modules/mod_text/mod_text.c \
	../../../../modules/mod_rand/mod_rand.c \
	../../../../modules/mod_grproc/mod_grproc.c \
	../../../../modules/libscroll/libscroll.c \
	../../../../modules/mod_scroll/mod_scroll.c \
	../../../../modules/libdraw/libdraw.c \
	../../../../modules/mod_draw/mod_draw.c \
	../../../../modules/mod_screen/mod_screen.c \
	../../../../modules/mod_path/mod_path.c \
	../../../../modules/mod_effects/mod_effects.c \
	../../../../modules/mod_blendop/mod_blendop.c \
	../../../../modules/mod_m7/mod_m7.c \
	../../../../modules/libwm/libwm.c \
	../../../../modules/mod_wm/mod_wm.c \
	../../../../modules/mod_sys/mod_sys.c \
	../../../../modules/mod_flic/mod_flic.c \
	../../../../modules/mod_regex/mod_regex.c \
	../../../../modules/mod_regex/regex.c \
	../../../../modules/mod_multi/mod_multi.c \
	../../../../modules/mod_curl/mod_curl.c \
	../../../../modules/mod_sensor/mod_sensor.c \
	../../../../modules/mod_chipmunk/Arreglos.c \
	../../../../modules/mod_chipmunk/Constraints.c \
	../../../../modules/mod_chipmunk/Cuerpo.c \
	../../../../modules/mod_chipmunk/Espacio.c \
	../../../../modules/mod_chipmunk/Handlers.c \
	../../../../modules/mod_chipmunk/HeapSort.c \
	../../../../modules/mod_chipmunk/LL.c \
	../../../../modules/mod_chipmunk/Miscelanea.c \
	../../../../modules/mod_chipmunk/agua.c \
	../../../../modules/mod_chipmunk/arbitros.c \
	../../../../modules/mod_chipmunk/automGenTerr.c \
	../../../../modules/mod_chipmunk/convexHull.c \
	../../../../modules/mod_chipmunk/main.c \
	../../../../modules/mod_iap/mod_iap_fake.c

LOCAL_LDLIBS := -llog -ldl -lz
LOCAL_SHARED_LIBRARIES += SDL2 SDL2_mixer png
LOCAL_STATIC_LIBRARIES += curl chipmunk

include $(BUILD_SHARED_LIBRARY)
