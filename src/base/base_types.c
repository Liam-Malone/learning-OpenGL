/* Begin Shader Functions */
global Shader Shader_load(const char* restrict vs_filepath, const char* restrict fs_filepath) {
    printf(" :: Shader Loading ::\n   > Attempting to load:\n    vs: %s\n    fs: %s\n\n",
            vs_filepath,
            fs_filepath);
    /* Return var, 0 init */
    Shader shader = {};

    /* File Usage Vars */
    u64 fsize;
    FILE* fp = nullptr;
    char* vsbuf = nullptr;
    char* fsbuf = nullptr;

    /* Shader Compilation Vars */
    u32 vert_shader = 0;
    u32 frag_shader = 0;
    i32 success;
    char err_log[512];

    /* Vertex Shader Load */
    fsize = 0;
    fp = fopen(vs_filepath, "rb");
    if (!fp) {
        shader = (Shader) {};
        fprintf(stderr, 
                "  Failed to open file: %s\n",
                vs_filepath);
        goto exit;
    } else {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        vsbuf = malloc(sizeof(char) * (fsize + 1));
        fread(vsbuf, fsize, 1, fp);
        vsbuf[fsize] = 0;

        /* Actually use the buffer to create vert shader */
        {
            fprintf(stderr, "  > Vert Shader Code:\n%s\n\n", vsbuf);

            vert_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vert_shader, 1, &vsbuf, NULL);
            glCompileShader(vert_shader);

            memset(err_log, 0, 512);
            glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vert_shader, 512, NULL, err_log);
                fprintf(stderr, 
                        " :: ERR: Vertex Shader Compilation Failed ::\n  > %s\n\n", 
                        err_log);

                goto exit;
            }
        }

        fclose(fp);
        fp = 0;
    }

    /* Fragment Shader Load */
    fsize = 0;
    fp = fopen(fs_filepath, "rb");
    if (!fp) {
        shader = (Shader) {};
        fprintf(stderr, 
                "  Failed to open file: %s\n",
                fs_filepath);
        goto exit;
    } else {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        fsbuf = malloc(sizeof(char) * (fsize + 1));
        fread(fsbuf, fsize, 1, fp);
        fsbuf[fsize] = 0;

        /* Actually use the buffer to create frag shader */
        {
            fprintf(stderr, "  > Frag Shader Code:\n%s\n\n", fsbuf);

            frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(frag_shader, 1, &fsbuf, NULL);
            glCompileShader(frag_shader);

            memset(err_log, 0, 512);
            glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(frag_shader, 512, NULL, err_log);
                fprintf(stderr,
                        " :: ERR: Fragment Shader Compilation Failed ::\n  > %s\n\n", 
                        err_log);

                goto exit;
            }
        }

        fclose(fp);
        fp = 0;
    }

    /* Construct full shader program */
    {
        shader.id = glCreateProgram();
        glAttachShader(shader.id, vert_shader);
        glAttachShader(shader.id, frag_shader);
        glLinkProgram(shader.id);

        /* Err check and log */
        glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader.id, 512, NULL, err_log);
            fprintf(stderr,
                    " :: ERR: Shader Program Linking Failed ::\n  > %s\n\n",
                    err_log);

            glDeleteProgram(shader.id);
            goto exit;
        }

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);

        vert_shader = frag_shader = 0;

        printf("  :: Shader Load Successful!! ::\n");
    }
    
exit: 
    if (fp) 
        fclose(fp);

    if (vsbuf) 
        free(vsbuf);

    if (fsbuf) 
        free(fsbuf);

    if (vert_shader) 
        glDeleteShader(vert_shader);

    if (frag_shader) 
        glDeleteShader(frag_shader);


    return shader;
}

global void Shader_use(Shader shader) {
    glUseProgram(shader.id);
}

/* End Shader Functions */
