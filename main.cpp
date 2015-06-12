#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
 
// Define some of the global variables we're using for this sample
GLuint program;
GLuint vao;
 
// This is the callback we'll be registering with GLFW for errors.
// It'll just print out the error to the STDERR stream.
void error_callback(int error, const char* description) {
  fputs(description, stderr);
}
 
// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}
 
int main() {
  // Initialize GLFW, and if it fails to initialize for any reason, print it out to STDERR.
  if (!glfwInit()) {
    fprintf(stderr, "Failed initialize GLFW.");
    exit(EXIT_FAILURE);
  }
 
  // Set the error callback, as mentioned above.
  glfwSetErrorCallback(error_callback);
 
  // Set up OpenGL options.
  // Use OpenGL verion 4.3,
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Indicate we only want the newest core profile, rather than using backwards compatible and deprecated features.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Make the window resize-able.
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
 
  // Create a window to put our stuff in.
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
 
  // If the window fails to be created, print out the error, clean up GLFW and exit the program.
  if(!window) {
    fprintf(stderr, "Failed to create GLFW window.");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
 
  // Use the window as the current context (everything that's drawn will be place in this window).
  glfwMakeContextCurrent(window);
 
  // Set the keyboard callback so that when we press ESC, it knows what to do.
  glfwSetKeyCallback(window, key_callback);
 
  printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
 
  // Makes sure all extensions will be exposed in GLEW and initialize GLEW.
  glewExperimental = GL_TRUE;
  glewInit();
 
  // Generate vertex arrays for our program. More explanation on this will come in the future.
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLfloat vertices[] = {
      -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
       0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
       0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
       0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

       0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
       0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
       0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
       0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
       0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
       0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
       0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,


      -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
       1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
       1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
       1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      -1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
  };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
  };
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  // Shaders is the next part of our program. Notice that we use version 410 core. This has to match our version of OpenGL we are using, which is the core profile in version 4.1, thus 410 core.
 
  // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
  // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
  static const char * vs_source[] =
  {
      "#version 410 core                                                 \n"
      "                                                                  \n"
      "in vec3 position;                                                 \n"
      "in vec3 color;                                                    \n"
      "in vec2 texturePos;                                               \n"
      "out vec3 Color;                                                   \n"
      "out vec2 TexturePos;                                              \n"
      "                                                                  \n"
      "uniform mat4 model;                                               \n"
      "uniform mat4 view;                                                \n"
      "uniform mat4 proj;                                                \n"
      "void main(void)                                                   \n"
      "{                                                                 \n"
      "    Color = color;                                                \n"
      "    TexturePos = texturePos;                                      \n"
      "    gl_Position = proj * view * model * vec4(position, 1.0); \n"
      "}                                                                 \n"
  };
 
  // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
  static const char * fs_source[] =
  {
      "#version 410 core                                                 \n"
      "                                                                  \n"
      "uniform sampler2D tex1;                                           \n"
      "uniform sampler2D tex2;                                           \n"
      "uniform vec3 overrideColor;                                           \n"
      "in vec3 Color;                                                    \n"
      "in vec2 TexturePos;                                               \n"
      "out vec4 color;                                                   \n"
      "                                                                  \n"
      "void main(void)                                                   \n"
      "{                                                                 \n"
      "    vec4 col1 = texture(tex1, TexturePos);                        \n"
      "    vec4 col2 = texture(tex2, TexturePos);                        \n"
      "    color = vec4(overrideColor, 1.0) * vec4(Color, 1.0) * mix(col1, col2, 0.5);                                 \n"
      "}                                                                 \n"
  };
 
  // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
  program = glCreateProgram();
 
  GLint status;

  // We create a shader with our fragment shader source code and compile it.
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, fs_source, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
  assert(status == GL_TRUE);
 
  // We create a shader with our vertex shader source code and compile it.
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, vs_source, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
  // char buffer[512];
  // glGetShaderInfoLog(vs, 512, NULL, buffer);
  // printf("%s\n", buffer);
  assert(status == GL_TRUE);
 
  // We'll attach our two compiled shaders to the OpenGL program.
  glAttachShader(program, vs);
  glAttachShader(program, fs);


  glBindFragDataLocation(program, 0, "color");

  glLinkProgram(program);
 

 
  // Making the link between vertex data and attributes
  GLint posAttrib = glGetAttribLocation(program, "position");
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
  glEnableVertexAttribArray(posAttrib);

  GLint colAttrib = glGetAttribLocation(program, "color");
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(colAttrib);

  GLint texAttrib = glGetAttribLocation(program, "texturePos");
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
  glEnableVertexAttribArray(texAttrib);

  // We'll specify that we want to use this program that we've attached the shaders to.
  glUseProgram(program);
  // MUST use program before setting uniforms!@@

  // Import texture
  GLuint tex[2];
  glGenTextures(2, tex);

  int width, height;
  unsigned char* image;
  GLint location;

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex[0]);
  image = SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);
  location = glGetUniformLocation(program, "tex1");
  glUniform1i(location, 0);

  // These parameters MUST be set for each texture, or you will end up with a black screen
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, tex[1]);
  image = SOIL_load_image("img.jpg", &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);
  location = glGetUniformLocation(program, "tex2");
  glUniform1i(location, 1);


  // These parameters MUST be set for each texture, or you will end up with a black screen
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  glm::mat4 view = glm::lookAt(
      glm::vec3(2.2f, 2.2f, 2.2f),
      glm::vec3(0.0f, 0.0f, -0.5f),
      glm::vec3(0.0f, 0.0f, 1.0f)
  );
  GLint uniView = glGetUniformLocation(program, "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10.0f);
  GLint uniProj = glGetUniformLocation(program, "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

  glEnable(GL_DEPTH_TEST);

  auto t_start = std::chrono::high_resolution_clock::now();

  // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
  while(!glfwWindowShouldClose(window))
  {
    // Set up our white background color
    static const GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // Clear the entire buffer with our white color (sets the background to be white).
    glClearBufferfv(GL_COLOR, 0, white);

    glClear(GL_DEPTH_BUFFER_BIT);

    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float> >(t_now - t_start).count();

    GLint uniReflecColor = glGetUniformLocation(program, "overrideColor");
    glUniform3f(uniReflecColor, 1.0f, 1.0f, 1.0f);


    glm::mat4 trans;
    trans = glm::rotate(
        trans,
        time * glm::radians(180.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    GLint uniTrans = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    // Draw our triangles
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Draw the floor
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF); // Write to stencil buffer
    glDepthMask(GL_FALSE); // Don't write to depth buffer
    glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)

    glDrawArrays(GL_TRIANGLES, 36, 6);

    glDepthMask(GL_TRUE);

    //Draw reflection
    trans = glm::scale(
        glm::translate(trans, glm::vec3(0, 0, -1)),
        glm::vec3(1, 1, -1)
    );
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    glUniform3f(uniReflecColor, 0.3f, 0.3f, 0.3f);

    glStencilFunc(GL_EQUAL, 1, 0xFF); 
    glStencilMask(0x00);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisable(GL_STENCIL_TEST);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // Swap the buffers so that what we drew will appear on the screen.
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
 
  glDisable(GL_DEPTH_TEST);

  // Program clean up when the window gets closed.
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
}
