#include <hello/hello.h>
#include <hello/shaders.h>
#include <stdbool.h>

static const int screen_width = 320;
static const int screen_height = 480;

static SDL_Window *win;
static SDL_GLContext ctx;

void sdl_error_die() {
  printf("Error: %s\n", SDL_GetError());
  exit(1);
}

typedef struct {
  float Position[3];
  float Color[4];
} Vertex;

void createGeometry(GLuint *vertexBuffer, GLuint *indexBuffer, int *numIndices) {
  const Vertex Vertices[] = {
    {{1, -1, 0}, {1, 0, 0, 1}},
    {{1, 1, 0}, {0, 1, 0, 1}},
    {{-1, 1, 0}, {0, 0, 1, 1}},
    {{-1, -1, 0}, {0, 0, 0, 1}}
  };

  glGenBuffers(1, vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  const GLubyte Indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  glGenBuffers(1, indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

  *numIndices = sizeof(Indices)/sizeof(Indices[0]);
}

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    sdl_error_die();
  }

  // Hide the status bar
  win = SDL_CreateWindow(NULL, 0, 0, screen_width, screen_height,
      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
  if (!win) {
    sdl_error_die();
  }

  // Use OpenGL ES 2.0
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  ctx = SDL_GL_CreateContext(win);

  // V-Sync
  SDL_GL_SetSwapInterval(1);

  // Create geometry
  GLuint vertexBuffer, indexBuffer;
  int numIndices;
  createGeometry(&vertexBuffer, &indexBuffer, &numIndices);

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
    }

    glClearColor(0.1, 0.2, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /*
     
    // Set up the viewport
    glViewport(0, 0, screen_width, screen_height);

    // Tell OpenGL about the structure of our data
    glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), 0);
    glVertexAttribPointer(_colorSlot, 4, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (GLvoid*) (sizeof(float) * 3));

    // Draw it!
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_BYTE, 0);

    */

    SDL_GL_SwapWindow(win);
  }

  SDL_GL_DeleteContext(ctx);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}

