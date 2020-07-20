# Set static libraries depending on de dettected OS
ifeq ($(DETTECTED_OS),Linux)
	LINK_LIBS := -l:libflecs_static.a -l:libraylib-linux.a -l:libglfw3.a -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp
else ifeq ($(DETTECTED_OS),Darwin)
	LINK_LIBS := -O0 -framework IOKit -v -lraylib -framework OpenGL -framework cocoa 
	# find_library(LIB_GLUT GLUT)
    # find_library(OPEN_GL_LIBRARY OpenGL)
    # find_library(COCOA_LIBRARY Cocoa)
    # find_library(CORE_VIDEO_LIBRARY CoreVideo)
endif
