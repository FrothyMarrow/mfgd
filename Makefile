CC=clang
CXX=clang++
RM=rm -f
CPPFLAGS=-D_DEBUG -g #-O2
LDFLAGS=-Llib/
LDLIBS=-lglfw -framework OpenGL -framework ApplicationServices
INCLUDES=-I. -Icommon -Imath -Iinclude

SRCS_CPP= \
    common/platform_osx.cpp \
    common/mtrand.cpp \
    datamanager/data.cpp \
    datamanager/dataserializer.cpp \
	game/character.cpp \
	game/game.cpp \
	game/handle.cpp \
	game/main.cpp \
	math/collision.cpp \
	math/color.cpp \
	math/euler.cpp \
	math/frustum.cpp \
	math/matrix.cpp \
	math/quaternion.cpp \
	math/vector.cpp \
	math/graph.cpp \
	renderer/application.cpp \
	renderer/image_read.cpp \
	renderer/renderer.cpp \
	renderer/renderingcontext.cpp \
	renderer/shaders.cpp \
	renderer/stanfordbunny.cpp \

SRCS_C= \
	renderer/gl.c \

SRCS= $(SRCS_CPP) $(SRCS_C)

OBJS_CPP=$(subst .cpp,.o,$(SRCS_CPP))
OBJS_C=$(subst .c,.o,$(SRCS_C))

OBJS=$(OBJS_CPP) $(OBJS_C)

all: mfgd

mfgd: $(OBJS)
	$(CXX) $(LDFLAGS) -o mfgd $(OBJS) $(LDLIBS) 

%.o:%.c
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

%.o:%.cpp
	$(CXX) $(CPPFLAGS) -std=c++0x $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) libglfw.3.dylib mfgd