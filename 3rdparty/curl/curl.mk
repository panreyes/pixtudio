
LIB=libcurl.a

SRCROOT=../..
ANDROID_SOURCE=$(HOME)/android/source/cupcake

RM=rm -f
RM_DIR=rm -rf
MD=mkdir
RANLIB=ranlib
CP=cp
AR=ar cqs

INCLUDES=-I$(ANDROID_SOURCE)/external/icu4c/common/ -I$(ANDROID_SOURCE)/external/skia/include/core/ \
	-I$(ANDROID_SOURCE)/bionic/libc/include -I$(ANDROID_SOURCE)/bionic/libstdc++/include \
	-I$(ANDROID_SOURCE)/bionic/libc/arch-arm/include -I$(ANDROID_SOURCE)/bionic/libc/kernel/common \
	-I$(ANDROID_SOURCE)/bionic/libc/kernel/arch-arm -I$(ANDROID_SOURCE)/bionic/libm/include \
	-I$(ANDROID_SOURCE)/system/core/include -I$(ANDROID_SOURCE)/hardware/libhardware/include \
	-I$(ANDROID_SOURCE)/frameworks/base/include \
	-I$(HOME)/projects/freebrowser/GMo/jni

DEFINES=-D__ANDROID__ -DANDROID -I. \
	-I$(SRCROOT)/third/curl/include

CXX=$(ANDROID_SOURCE)/prebuilt/linux-x86/toolchain/arm-eabi-4.2.1/bin/arm-eabi-g++
CXXFLAGS= -pipe -fpermissive -fno-short-enums -fno-exceptions -Wno-multichar -msoft-float -fstack-protector -fpic -ffunction-sections -fdata-sections -march=armv5te -mtune=xscale -D__ARM_ARCH_5__ -D__ARM_ARCH_5T__ -D__ARM_ARCH_5TE__ -mthumb-interwork -fmessage-length=0 -W -Wall -Wno-unused -Wstrict-aliasing=2 -finline-functions -fgcse-after-reload -frerun-cse-after-loop -frename-registers -fvisibility-inlines-hidden -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -fno-rtti -MD -funwind-tables -include $(ANDROID_SOURCE)/system/core/include/arch/linux-arm/AndroidConfig.h -include $(ANDROID_SOURCE)/bionic/libc/include/string.h -mthumb -D__MARM_THUMB__ -DTHUMB  $(INCLUDES) $(DEFINES)
CC=$(ANDROID_SOURCE)/prebuilt/linux-x86/toolchain/arm-eabi-4.2.1/bin/arm-eabi-gcc
CCFLAGS = -pipe -O2 -fno-short-enums $(INCLUDES) $(DEFINES) -include $(SRCROOT)/third/curl/lib/curl_config.h
LD=$(ANDROID_SOURCE)/prebuilt/linux-x86/toolchain/arm-eabi-4.2.1/bin/arm-eabi-g++
LDFLAGS=-nostdlib -Bdynamic -Wl,-T,$(ANDROID_SOURCE)/build/core/armelf.x -Wl,-dynamic-linker,/system/bin/linker -Wl,--gc-sections -Wl,-z,nocopyreloc -Wl,-rpath-link=$(ANDROID_SOURCE)/out/target/product/generic/obj/lib -lc -lstdc++ -lm -Wl,--no-undefined $(ANDROID_SOURCE)/out/target/product/generic/obj/lib/crtbegin_dynamic.o $(ANDROID_SOURCE)/out/target/product/generic/obj/lib/crtend_android.o

SRCS=base64.c connect.c content_encoding.c cookie.c curl_addrinfo.c curl_fnmatch.c \
	 curl_gethostname.c curl_memrchr.c curl_rand.c curl_rtmp.c curl_sspi.c \
	 curl_threads.c dict.c easy.c escape.c file.c fileinfo.c formdata.c \
	 ftp.c ftplistparser.c getenv.c getinfo.c gtls.c hash.c hmac.c hostares.c \
	 hostasyn.c hostip.c hostip4.c hostip6.c hostsyn.c hostthre.c http.c \
	 http_chunks.c http_digest.c http_negotiate.c http_ntlm.c if2ip.c \
	 imap.c inet_ntop.c inet_pton.c krb4.c krb5.c llist.c md4.c md5.c \
	 memdebug.c mprintf.c multi.c netrc.c nonblock.c nss.c nwlib.c \
	 nwos.c openldap.c parsedate.c pingpong.c polarssl.c pop3.c progress.c \
	 qssl.c rawstr.c rtsp.c security.c select.c sendf.c share.c slist.c \
	 smtp.c socks.c socks_gssapi.c socks_sspi.c speedcheck.c splay.c \
	 ssh.c sslgen.c ssluse.c strdup.c strequal.c strerror.c strtok.c \
	 strtoofft.c telnet.c tftp.c timeval.c transfer.c url.c version.c \
	 warnless.c wildcard.c
SRCS_CPP=

SRC_DIR=$(SRCROOT)/third/curl/lib
OBJ_DIR=android-obj
STATIC_LIBS=
DYNAMIC_LIBS= -llog -ldl -lm -lpthread

OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
OBJCPP = $(addprefix $(OBJ_DIR)/,$(SRCS_CPP:.cpp=.o))


all : $(LIB)

$(LIB) : $(OBJ) $(OBJCPP)
	@$(AR) $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(MD) -p $(dir $@)
	@$(CC) $(CCFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(MD) -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

clean :
	@$(RM) $(LIB)
	cd $(OBJ_DIR)
	@$(RM) $(OBJ) $(OBJCPP)
	cd ..
