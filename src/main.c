/* stdlib includes */
#include <sys/time.h>    // Required for: timespec, nanosleep(), select() - POSIX
#include <poll.h>        // Required for: ppoll() - POSIX
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

int poly_draw_mode = GL_FILL;

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
    /* glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); */

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

    static Color bg = { 0.1, 0.3, 0.3, 1.0 };
    Shader my_shader = Shader_load("src/shaders/glsl/vert.glsl" ,"src/shaders/glsl/frag.glsl");

    /* Initial Triangle */
    static f32 triangle_vertices[] = {
        -0.5f, -0.5f, 0.0f,     /* Bottom Left */
         0.5f, -0.5f, 0.0f,     /* Bottom Right */
         0.0f,  0.5f, 0.0f     /* Top */
    };

    /* Rectangle */
    static f32 vertices[] = {
         0.5f,  0.5f, 0.0f, /* Top Right    */
         0.5f, -0.5f, 0.0f, /* Bottom Right */
        -0.5f, -0.5f, 0.0f, /* Bottom Left  */
        -0.5f,  0.5f, 0.0f  /* Top Left     */
    };

    /* Indices for rectangle */
    static u32 idx_buf[] = {
        0, 1, 3,  /* Tri 1 */
        1, 2, 3   /* Tri 2 */
    };

    u32 VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* Bind Vertex Array Object */
    glBindVertexArray(VAO);

    /* Copy Vertices into a Vertex Buffer for OpenGL */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Copy Indices into Element Buffer for OpenGL */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx_buf), idx_buf, GL_STATIC_DRAW);

    /* Set Vertex Attribute Pointers */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 * sizeof(f32)), (void*) 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    f32 time = 0;
    Color rect_col = { .r = 0, .g = 0, .b = 0, .a = 1.0 };
    i32 vertexColorLocation = Shader_get_uniform_location(my_shader, "progCol");
    /* window loop */
    while (!glfwWindowShouldClose(window))
    {
        /* Handle Inputs */
        {
            input_handle(window);
        }

        /* Update Program State */
        {
            time = glfwGetTime();
            rect_col.r = (cos(time) / 2.0f) + 0.5f;
            rect_col.g = (sin(time) / 2.0f) + 0.5f;
            rect_col.b = (cos(time) / 2.0f) + 0.5f;
        }

        /* Draw */
        {
            /* Clear background before drawing the rest */
            clear_background(bg, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /* Begin Shader Mode */
            Shader_use(my_shader);
            glUniform4f(vertexColorLocation, rect_col.r, rect_col.g, rect_col.b, 1.0f);

            glBindVertexArray(VAO);
            glPolygonMode(GL_FRONT_AND_BACK, poly_draw_mode);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

cleanup_exit:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    Shader_unload(my_shader);

    glfwTerminate();
    return exit_code;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void input_handle(GLFWwindow* window) {
    if (glfwGetKey(window, PROGRAM_EXIT_KEY) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        if (poly_draw_mode == GL_LINE) 
            poly_draw_mode = GL_FILL;
        else 
            poly_draw_mode = GL_LINE;
    }
}

void clear_background(Color color, int clear_bits) {
        glClear(clear_bits);
        glClearColor(color.r, color.g, color.b, color.a);
}
