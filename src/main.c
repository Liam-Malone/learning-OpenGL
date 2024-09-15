/* stdlib includes */
#include <sys/time.h>    // Required for: timespec, nanosleep(), select() - POSIX
#include <poll.h>        // Required for: ppoll() - POSIX
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 3rd party library includes */
#include "external/glad.h"
#include "external/glad.c"

/* project file includes */
/* [h] files */
#include "base/base_types.h"

/* [c] files */
#define _GLFW_X11 1
#include "my_glfw.c"
#include "base/base_types.c"

#ifdef _debug
/* debug mode defines */
#define PROGRAM_EXIT_KEY GLFW_KEY_Q

#else
/* release mode defines */
#define PROGRAM_EXIT_KEY GLFW_KEY_NULL

#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void input_handle(GLFWwindow* window);
void clear_background(Color color, int clear_bits);

int main(int argc, char** argv) {

    int exit_code = 0;
    /* print out program args */
    if (argc > 0) {
        for (int i=0; i<argc; i++) {
            printf("  > Arg [%d]: %s\n", i, argv[i]);
        }
    }

    int res = glfwInit();
    if (res != true) {
        printf(" :: glfw init failed: %d ::\n", res);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); /* Setting version to 3.4 fails as 'invalid version' */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (!window) {
        printf(" :: glfw window init failed ::\n");
        exit_code = 1;
        goto cleanup_exit;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("  :: GLAD init failed ::\n");
        exit_code = 1;
        goto cleanup_exit;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    static f32 vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    u32 VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    u32 VAO;
    glGenVertexArrays(1, &VAO);
    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);

    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*) 0);
    glEnableVertexAttribArray(0);

    Shader my_shader = Shader_load("src/shaders/glsl/vert.glsl" ,"src/shaders/glsl/frag.glsl");

    static Color bg = { 0.1, 0.3, 0.3, 1.0 };
    /* window loop */
    while (!glfwWindowShouldClose(window))
    {
        /* Handle Inputs */
        {
            input_handle(window);
        }

        /* Update Program State */
        {
        }

        /* Draw */
        {
            /* Clear background before drawing the rest */
            clear_background(bg, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /* next step: drawing a triangle */
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*) 0);
            glEnableVertexAttribArray(0);

            /* Drawing with VAO */
            Shader_use(my_shader);
            glBindVertexArray(VAO);

            // 3. now draw the object
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

cleanup_exit:
    glfwTerminate();
    return exit_code;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void input_handle(GLFWwindow* window) {
    if (glfwGetKey(window, PROGRAM_EXIT_KEY) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void clear_background(Color color, int clear_bits) {
        glClear(clear_bits);
        glClearColor(color.r, color.g, color.b, color.a);
}
