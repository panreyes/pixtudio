#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	bgdrtm
BUILD     :=	build
SOURCES		:=	src
INCLUDES	:=	include ../include ../../modules/mod_say/ ../../modules/mod_string/ \
                ../../modules/mod_math/ ../../modules/mod_time/ ../../modules/mod_file/ \
                ../../modules/mod_sound/ ../../modules/libsdlhandler/ ../../modules/mod_joy/ \
                ../../modules/libjoy/ ../../modules/mod_proc/ ../../modules/mod_sort/ \
                ../../modules/mod_timers/ ../../modules/mod_regex/ ../../modules/libgrbase/ \
                ../../modules/libblit/ ../../modules/libvideo/ ../../modules/librender/ \
                ../../modules/mod_video/ ../../modules/libmouse/ ../../modules/mod_mouse/ \
                ../../modules/mod_map/ ../../modules/libfont/ ../../modules/mod_dir/ \
                ../../modules/libtext/ ../../modules/mod_text/ ../../modules/mod_rand/ \
                ../../modules/mod_grproc/ ../../modules/libscroll/ ../../modules/mod_scroll/ \
                ../../modules/libkey/ ../../modules/mod_key/ ../../modules/libdraw/ \
                ../../modules/mod_draw/ ../../modules/mod_screen/ ../../modules/mod_path/ \
                ../../modules/mod_effects/ ../../modules/mod_blendop/ ../../modules/mod_m7/ \
                ../../modules/libwm/ ../../modules/mod_wm/ ../../modules/mod_sys/ \
                ../../modules/mod_mem/ ../../modules/mod_flic/ \
                ../../modules/mod_debug/ ../../modules/mod_iconv/ ../../modules/mod_wpad/ \
                ../../modules/mod_image/ ../../modules/mod_sqlite3/ ../../modules/mod_chipmunk/ \
                ../../modules/libbgload/

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

CFLAGS		=	-O3 -Wall -D__BGDRTM__ -D__MONOLITHIC__ -DWITH_GPL_CODE -DNO_MODMATHI -DNO_MODIMAGE -DNO_MODCHIPMUNK -DNO_MODMULTI -DNO_MODFMODEX -DNO_MODCURL -DTARGET_WII -DVERSION='"1.0.0"' -DSTDC_HEADERS $(MACHDEP) $(INCLUDE) -finline-functions -fno-strict-aliasing
CXXFLAGS	=	-save-temps -Xassembler -aln=$@.lst $(CFLAGS)
LDFLAGS		=	-O3 $(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS := -lwiiuse -lbte -logc -lm
#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(CURDIR) $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGETDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	dcbr.c sysprocs.c strings.c dirs.c copy.c misc.c instance.c \
              interpreter.c varspace_file.c \
              ../../../3rdparty/libc_additions/realpath.c \
              ../../common/debug.c \
              ../../common/files.c \
              ../../common/xctype.c \
              ../../../modules/libbgload/bgload.c \
              ../../../modules/mod_say/mod_say.c \
              ../../../modules/mod_string/mod_string.c \
              ../../../modules/mod_math/mod_math.c \
              ../../../modules/mod_time/mod_time.c \
              ../../../modules/mod_file/mod_file.c \
              ../../../modules/mod_sound/mod_sound.c \
              ../../../modules/libsdlhandler/libsdlhandler.c \
              ../../../modules/libjoy/libjoy.c \
              ../../../modules/mod_joy/mod_joy.c \
              ../../../modules/mod_proc/mod_proc.c \
              ../../../modules/mod_sort/mod_sort.c \
              ../../../modules/mod_timers/mod_timers.c \
              ../../../modules/mod_regex/mod_regex.c \
              ../../../modules/mod_regex/regex.c \
              ../../../modules/libgrbase/g_bitmap.c \
              ../../../modules/libgrbase/g_clear.c \
              ../../../modules/libgrbase/g_grlib.c \
              ../../../modules/libgrbase/g_pal.c \
              ../../../modules/libgrbase/g_blendop.c \
              ../../../modules/libgrbase/g_conversion.c \
              ../../../modules/libgrbase/libgrbase.c \
              ../../../modules/libblit/g_blit.c \
              ../../../modules/libblit/g_pixel.c \
              ../../../modules/libblit/libblit.c \
              ../../../modules/libvideo/g_regions.c \
              ../../../modules/libvideo/g_video.c \
              ../../../modules/librender/g_fade.c \
              ../../../modules/librender/g_frame.c \
              ../../../modules/librender/g_instance.c \
              ../../../modules/librender/g_object.c \
              ../../../modules/librender/g_rects.c \
              ../../../modules/librender/g_screen.c \
              ../../../modules/librender/librender.c \
              ../../../modules/librender/scaler_hq2x.c \
              ../../../modules/librender/scaler_normal.c \
              ../../../modules/librender/scaler_scale2x.c \
              ../../../modules/librender/scaler_scanline.c \
              ../../../modules/mod_video/mod_video.c \
              ../../../modules/libmouse/libmouse.c \
              ../../../modules/mod_map/file_fnt.c \
              ../../../modules/mod_map/file_fpg.c \
              ../../../modules/mod_map/file_map.c \
              ../../../modules/mod_map/file_pal.c \
              ../../../modules/mod_map/file_pcx.c \
              ../../../modules/mod_map/file_png.c \
              ../../../modules/mod_map/mod_map.c \
              ../../../modules/libfont/libfont.c \
              ../../../modules/mod_dir/mod_dir.c \
              ../../../modules/libtext/libtext.c \
              ../../../modules/mod_text/mod_text.c \
              ../../../modules/mod_rand/mod_rand.c \
              ../../../modules/mod_grproc/mod_grproc.c \
              ../../../modules/libscroll/libscroll.c \
              ../../../modules/mod_scroll/mod_scroll.c \
              ../../../modules/libkey/libkey.c \
              ../../../modules/mod_key/mod_key.c \
              ../../../modules/libdraw/libdraw.c \
              ../../../modules/mod_draw/mod_draw.c \
              ../../../modules/mod_screen/mod_screen.c \
              ../../../modules/mod_path/mod_path.c \
              ../../../modules/mod_effects/mod_effects.c \
              ../../../modules/mod_blendop/mod_blendop.c \
              ../../../modules/mod_m7/mod_m7.c \
              ../../../modules/libwm/libwm.c \
              ../../../modules/mod_wm/mod_wm.c \
              ../../../modules/mod_sys/mod_sys.c \
              ../../../modules/mod_mem/mod_mem.c \
              ../../../modules/mod_flic/mod_flic.c \
              ../../../modules/mod_iconv/iconv.c \
              ../../../modules/mod_wpad/mod_wpad.c

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
export LD	:=	$(CC)

export OFILES	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) \
					$(sFILES:.s=.o) $(SFILES:.S=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD) \
					-I$(LIBOGC_INC) -I$(PORTLIBS)/include/SDL \
					-I$(PORTLIBS)/include/chipmunk/ \
					-I$(CURDIR)/../../3rdparty/libc_additions/

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
					-L$(LIBOGC_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	make -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).a

#---------------------------------------------------------------------------------

else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).a: $(OFILES)
	@echo Gonna link $(OUTPUT).a
	@powerpc-eabi-ar crs $@ $(OFILES)
	@echo done linking

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
