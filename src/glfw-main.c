/* [h] files */
#include <sys/time.h>    // Required for: timespec, nanosleep(), select() - POSIX
#include <poll.h>        // Required for: ppoll() - POSIX
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "external/glad.h"

/* project file includes */
/* [h] files */
#include "my_types.h"

/* [c] files */
#define _GLFW_X11 1
#include "my_glfw.c"

int main(int argc, char** argv) {

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
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    /* window loop */
    {
    }

    glfwTerminate();
    return 0;
}
