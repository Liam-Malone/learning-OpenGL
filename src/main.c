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
#include "my_types.h"

/* [c] files */
#define _GLFW_X11 1
#include "my_glfw.c"

#ifdef _debug
/* debug mode defines */
#define PROGRAM_EXIT_KEY GLFW_KEY_Q

#else
/* release mode defines */
#define PROGRAM_EXIT_KEY GLFW_KEY_NULL

#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void input_handle(GLFWwindow* window) {
    if (glfwGetKey(window, PROGRAM_EXIT_KEY) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

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

    /* window loop */
    while (!glfwWindowShouldClose(window))
    {
        input_handle(window);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

cleanup_exit:
    glfwTerminate();
    return exit_code;
}
