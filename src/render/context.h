#ifndef CONTEXT_H
#define CONTEXT_H

struct Settings {
    const char* title;
    unsigned int width;
    unsigned int height;
    int fullscreen;
    int show_cursor;
};

struct Context {
    struct Settings* settings;
    struct Renderer* renderer;
    unsigned int width;
    unsigned int height;
    double time;
    double tpf;
    void (*create)(struct Context* ctx);
    void (*destroy)(struct Context* ctx);
    void (*set_title)(struct Context* ctx, const char* title);
    /* system callbacks */
    void (*cursor_callback)(struct Context*, double, double, double, double, int, int, int);
    void (*wheel_callback)(struct Context*, double, double);
    void (*key_callback)(struct Context*, int, int, int, int);
    void (*resize_callback)(struct Context*, int, int);
    void (*close_callback)(struct Context*);
    /* Set this context as the current openGL context */
    void (*make_current)(struct Context*);
    /* update this context, event polling, timer */
    void (*update)(struct Context*);
    /* return the time betweem the last swap */
    double (*swap_buffer)(struct Context*);
    void* user_data;

    void* priv_data;
    double last_time;
    double last_x;
    double last_y;
};

#endif
