/* stdlib includes */
#include <sys/time.h>    // Required for: timespec, nanosleep(), select() - POSIX
#include <poll.h>        // Required for: ppoll() - POSIX
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 3rd party library includes */
#include "external/glad.h"
#include "external/glad.c"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC /* Ensure Static for Single Translation Unit */
#include "external/stb_image.h" /* STB library for Image Loading */

/* project file includes */
/* [c] files */
#define _GLFW_X11 1
#include "my_glfw.c" /* Single Translation Unit Build */
#include "base/base.c"

#ifdef _debug
/* debug mode defines */
#define PROGRAM_EXIT_KEY GLFW_KEY_Q

#else
/* release mode defines */
#define PROGRAM_EXIT_KEY GLFW_KEY_UNKNOWN

#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void input_handle(GLFWwindow* window);
void clear_background(Color color, int clear_bits);

int poly_draw_mode = GL_FILL;

int main(void) {
    int exit_code = 0;

    int res = glfwInit();
    if (res != GLFW_TRUE) {
        printf(" :: glfw init failed: %d ::\n", res);
        exit_code = 1;
        goto glfw_cleanup_exit;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); /* Setting version to 3.4 fails as 'invalid version' */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __apple__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (!window) {
        printf(" :: glfw window init failed ::\n");
        exit_code = 1;
        goto glfw_cleanup_exit;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("  :: GLAD init failed ::\n");
        exit_code = 1;
        goto glfw_cleanup_exit;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Initial Triangle */
    // static f32 vertices[] = {
    //      /* X,  Y,    Z */    /* R, G,    B */
    //      0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    /* Bottom Right */
    //     -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    /* Bottom Left */
    //      0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f     /* Top */
    // };

    /* Rectangle */
    // static f32 rectangle_vertices[] = {
    //      0.5f,  0.5f, 0.0f, /* Top Right    */
    //      0.5f, -0.5f, 0.0f, /* Bottom Right */
    //     -0.5f, -0.5f, 0.0f, /* Bottom Left  */
    //     -0.5f,  0.5f, 0.0f  /* Top Left     */
    // };

    /* Indices for rectangle */
    static u32 idx_buf[] = {
        0, 1, 3,  /* Tri 1 */
        1, 2, 3   /* Tri 2 */
    };
    static f32 tex_vertices[] = {
        /* positions */      /* colors  */        /* texture coords */
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, /* Top Right    */
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right */
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left  */
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left     */
    };

    u32 VBO = 0; 
    u32 VAO = 0; 
    u32 EBO = 0;

    /* Preparing buffers */
    { 
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        /* Bind Vertex Array Object */
        glBindVertexArray(VAO);

        /* Copy Vertices into a Vertex Buffer for OpenGL */
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tex_vertices), tex_vertices, GL_STATIC_DRAW);

        /* Copy Indices into Element Buffer for OpenGL */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx_buf), idx_buf, GL_STATIC_DRAW);

        /* Set Vertex Attribute Pointers */
        /* Position Attribute */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(f32)), (void*) 0);
        glEnableVertexAttribArray(0);

        /* Color Attribute */
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(f32)), (void*) (3 * sizeof(f32)));
        glEnableVertexAttribArray(1);

        /* Textures */
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(6 * sizeof(f32)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    static Color bg = { 0.1, 0.3, 0.3, 1.0 };
    Shader my_shader = Shader_load("src/shaders/glsl/vert.glsl" ,"src/shaders/glsl/frag.glsl");


    // const char* asset1_path = "assets/PNG/Double/pattern_18.png";
    // const char* asset2_path = "assets/PNG/Double/pattern_49.png";

    const char* assets[2] = {
            "assets/PNG/Double/pattern_18.png",
            "assets/PNG/Double/pattern_49.png"
    };

    slice(const char*) _assets = slice_range(assets, 0, 2);

    i32 width, height, channel_count;
    u8* img_data = 0;
    u32 texture;

    /* Prepare Image 1 */
    img_data = stbi_load(slice_get(_assets, 0), &width, &height, &channel_count, 0);
    if (img_data) {
        /* Create Texture */
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, texture);

        /* set the texture wrapping/filtering options (on currently bound texture) */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /* Assign image to texture */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        /* Image memory is no longer needed */
        stbi_image_free(img_data); img_data = nullptr;
        width = height = channel_count = 0;
    } else { fprintf(stderr, "  :: Failed to load image: %s ::\n", slice_get(_assets, 0)); goto cleanup_exit; }

    /* Prepare Image 2 */
    u32 texture_2;
    img_data = stbi_load(slice_get(_assets, 1), &width, &height, &channel_count, 0);
    if (img_data) {
        /* Create Texture */
        glGenTextures(1, &texture_2);
        glActiveTexture(GL_TEXTURE1);

        glBindTexture(GL_TEXTURE_2D, texture_2);

        /* set the texture wrapping/filtering options (on currently bound texture) */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /* Assign image to texture */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        /* Image memory is no longer needed */
        stbi_image_free(img_data); img_data = nullptr;
        width = height = channel_count = 0;
    } else { fprintf(stderr, "  :: Failed to load image: %s ::\n", slice_get(_assets, 1)); goto cleanup_exit; }

    f32 time = 0;
    Color rect_col = { .r = 0, .g = 0, .b = 0, .a = 1.0 };
    /* i32 vertexColorLocation = Shader_get_uniform_location(my_shader, "progCol"); */
    i32 tex_locs[2] = { 
        Shader_get_uniform_location(my_shader, "tex1"),
        Shader_get_uniform_location(my_shader, "tex2"),
    };

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

            // glBindTexture(GL_TEXTURE_2D, texture);

            /* Begin Shader Mode */
            Shader_use(my_shader);
            /* glUniform4f(vertexColorLocation, rect_col.r, rect_col.g, rect_col.b, 1.0f); */
            // Shader_set_value(my_shader, vertexColorLocation, (void*) &rect_col, shader_uniform_vec4f32);
            int ints[] = { 0, 1 };
            Shader_set_value(my_shader, tex_locs[0], (void*) &ints[0], shader_uniform_i32);
            Shader_set_value(my_shader, tex_locs[1], (void*) &ints[1], shader_uniform_i32);

            glBindTexture(GL_TEXTURE_2D, texture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture_2);

            glBindVertexArray(VAO);
            // glPolygonMode(GL_FRONT_AND_BACK, poly_draw_mode);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            // glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

cleanup_exit:

    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);

    Shader_unload(my_shader);

    if (img_data) stbi_image_free(img_data);

glfw_cleanup_exit:

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
