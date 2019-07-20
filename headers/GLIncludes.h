#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#if defined(OSX)
#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include <OpenGL/glu.h>
// Apple's version of glut.h #undef's APIENTRY, redefine it
#define APIENTRY
#else
#include <GL/glu.h>
#endif
