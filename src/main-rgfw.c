/* 3rd-party library includes */
/* defines */
#define RGFWDEF
#define RGFW_ALLOC_DROPFILES
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
/* [h] files */
#include "external/RGFW.h"

/* project file includes */
/* [h] files */
#include "my_types.h"
#include "base/base_arena.h"

/* [c] files */
#include "base/base_arena.c"

unsigned char running = 1;


/* callbacks are another way you can handle events in RGFW */
// void refreshCallback(RGFW_window* win) {
//     drawLoop(win);
// }

int main(int argc, char** argv) {

    /* print out program args */
    if (argc > 0) {
        for (int i=0; i<argc; i++) {
            printf("  > Arg [%d]: %s\n", i, argv[i]);
        }
    }

    RGFW_window* win = RGFW_createWindow("LearningGL", RGFW_RECT(500, 500, 500, 500), RGFW_ALLOW_DND | RGFW_CENTER);
    RGFW_window_makeCurrent(win);
    
    // RGFW_setWindowRefreshCallback(refreshCallback);
    // RGFW_createThread((RGFW_threadFunc_ptr)loop2, NULL); /* the function must be run after the window of this thread is made for some reason (using X11) */

    unsigned char i;

    #ifndef RGFW_VULKAN
    glEnable(GL_BLEND);
    glClearColor(0, 0, 0, 0);
    #endif

    // RGFW_window_setMouseStandard(win, RGFW_MOUSE_RESIZE_NESW);
    
    Color bg = { 
        .r = 0.2f,
        .g = 0.3f,
        .b = 0.3f,
        .a = 1.0f
    };

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    bool increase_r = true;
    u32 fps = 0;

    while (running && !RGFW_isPressed(win, RGFW_q)) {   

        /* Check for events, but don't stop rendering */
        RGFW_window_eventWait(win, RGFW_NO_WAIT);

        /* Input Handling */
        {
            while (RGFW_window_checkEvent(win) != NULL) {
                if (win->event.type == RGFW_windowMoved) {
                    /* printf("window moved\n"); */
                }
                else if (win->event.type == RGFW_windowResized) {
                    /* printf("window resized\n"); */
                    if ( (bg.r >= 1.0f) || (bg.r <= 0.0f) ) 
                        increase_r = !increase_r;

                    if (increase_r)
                        bg.r += 0.01f;
                    else
                        bg.r -= 0.01f;
                }

                if (win->event.type == RGFW_quit) {
                    running = 0;  
                    break;
                }
                if (RGFW_isPressed(win, RGFW_Up)) {
                    char* str = RGFW_readClipboard(NULL);
                    printf("Pasted : %s\n", str);
                    free(str);
                }
                else if (RGFW_isPressed(win, RGFW_Down))
                    RGFW_writeClipboard("DOWN", 4);
                else if (RGFW_isPressed(win, RGFW_Space))
                    printf("fps : %i\n", fps);
                else if (RGFW_isPressed(win, RGFW_w))
                     RGFW_window_setMouseDefault(win);

                if (win->event.type == RGFW_dnd) {
                    for (i = 0; i < win->event.droppedFilesCount; i++)
                        printf("dropped : %s\n", win->event.droppedFiles[i]);
                }

                else if (win->event.type == RGFW_jsButtonPressed)
                    printf("pressed %i\n", win->event.button);

                else if (win->event.type == RGFW_jsAxisMove && !win->event.button)
                    printf("{%i, %i}\n", win->event.axis[0].x, win->event.axis[0].y);
            }
        }

        /* Draw Loop */
        {
            RGFW_window_makeCurrent(win);

            #ifndef RGFW_VULKAN
            glClearColor(bg.r, bg.g, bg.b, bg.a);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            
            glBegin(GL_TRIANGLES);

            /* Darker, broader triangle in the middle */
                glColor4f(0.5, 0,   0,   1.0);   glVertex3f(-0.6, -0.75,  0.0);   // bottom left
                glColor4f(0,   0.5, 0,   1.0);   glVertex3f(0.6,  -0.75,  0.0);   // bottom right
                glColor4f(0,   0,   0.5, 1.0);   glVertex3f(0,     0.75,  0.0);   // top

            /* Brighter, slimmer triangle to the left */
                glColor4f(0,   0,   0.9, 1.0);   glVertex3f(0,     0.75,  0.0);  // top left
                glColor4f(0.9, 0,   0,   1.0);   glVertex3f(-0.6, -0.75,  0.0);  // top right
                glColor4f(0,   0.9, 0,   1.0);   glVertex3f(-0.6,  0.75,  0.0);  // bottom

            /* Brighter, slimmer triangle to the right */
                glColor4f(0.9, 0,   0,   1.0);   glVertex3f(0.6,   0.75,  0.0);  // top left
                glColor4f(0,   0,   0.9, 1.0);   glVertex3f(0,     0.75,  0.0);  // top right
                glColor4f(0,   0.9, 0,   1.0);   glVertex3f(0.6,   -0.75,  0.0);  // bottom

            glEnd();
            #endif
            
            RGFW_window_swapBuffers(win);
        }

        fps = RGFW_window_checkFPS(win, 60);
    }

    RGFW_window_close(win);
    return 0;
}
