CC=clang
CXX=clang++
RM=rm -f
CPPFLAGS=-D_DEBUG -g#-O2
LDLIBS=-lglfw -framework OpenGL -framework ApplicationServices
INCLUDES=-Iinclude -Iengine -Iengine/common -Iengine/math -Iengine/include

SRCS_CPP= \
    engine/common/platform_osx.cpp \
    engine/common/mtrand.cpp \
    engine/datamanager/data.cpp \
    engine/datamanager/dataserializer.cpp \
	engine/math/collision.cpp \
	engine/math/color.cpp \
	engine/math/euler.cpp \
	engine/math/frustum.cpp \
	engine/math/matrix.cpp \
	engine/math/quaternion.cpp \
	engine/math/vector.cpp \
	engine/math/graph.cpp \
	engine/renderer/application.cpp \
	engine/renderer/image_read.cpp \
	engine/renderer/renderer.cpp \
	engine/renderer/renderingcontext.cpp \
	engine/renderer/shaders.cpp \
	engine/renderer/stanfordbunny.cpp \
	game/character.cpp \
	game/game.cpp \
	game/handle.cpp \
	game/main.cpp \

SRCS_C= \
	engine/renderer/gl.c \

SRCS= $(SRCS_CPP) $(SRCS_C)

OBJS_CPP=$(subst .cpp,.o,$(SRCS_CPP))
OBJS_C=$(subst .c,.o,$(SRCS_C))

OBJS=$(OBJS_CPP) $(OBJS_C)

all: mfgd

mfgd: $(OBJS)
	$(CXX) -o mfgd $(OBJS) $(LDLIBS) 

%.o:%.c
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

%.o:%.cpp
	$(CXX) $(CPPFLAGS) -std=c++0x $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) mfgd