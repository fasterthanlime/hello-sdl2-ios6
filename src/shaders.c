#include <hello/shaders.h>

static char *VERTEX_SHADER_CODE = " \
  attribute vec4 Position;\n \
  attribute vec4 SourceColor;\n \
  \n \
  varying vec4 DestinationColor;\n \
  \n \
  void main(void) {\n \
      DestinationColor = SourceColor;\n \
      gl_Position = Position;\n \
  }\n \
";

static char *FRAGMENT_SHADER_CODE = " \
  varying lowp vec4 DestinationColor;\n \
  \n \
  void main(void) {\n \
      gl_FragColor = DestinationColor;\n \
  }\n \
";

static GLuint compileShader(GLenum shaderType, char *code) {
  GLuint handle = glCreateShader(shaderType);

  int length = strlen(code);
  glShaderSource(handle, 1, (const GLchar**) &code, &length);

  glCompileShader(handle);

  GLint compileSuccess;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &compileSuccess);
  if (compileSuccess == GL_FALSE) {
    GLchar messages[256];
    glGetShaderInfoLog(handle, sizeof(messages), NULL, &messages[0]);
    printf("Shader compilation error: %s\n", messages);
    exit(1);
  }

  return handle;
}

void loadShaders(GLuint *_positionSlot, GLuint *_colorSlot) {
  GLuint vertex   = compileShader(GL_VERTEX_SHADER, VERTEX_SHADER_CODE);
  GLuint fragment = compileShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_CODE);

  GLuint program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  glLinkProgram(program);

  GLint linkSuccess;
  glGetShaderiv(program, GL_COMPILE_STATUS, &linkSuccess);
  if (linkSuccess == GL_FALSE) {
    GLchar messages[256];
    glGetProgramInfoLog(program, sizeof(messages), NULL, &messages[0]);
    printf("Program linking error: %s\n", messages);
    exit(1);
  }

  glUseProgram(program);

  *_positionSlot = glGetAttribLocation(program, "Position");
  *_colorSlot = glGetAttribLocation(program, "SourceColor");
  glEnableVertexAttribArray(*_positionSlot);
  glEnableVertexAttribArray(*_colorSlot);

  return;
}

