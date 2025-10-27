#include "ft_minirt.h"
#include "tetris.h"
#include <string.h>

/* --- util --- */
static int  idx(int x, int y) { return y * T_W + x; }

static t_rgb rgb_u8(int r, int g, int b)
{
    t_rgb c;
    if (r < 0) r = 0; 
	if (r > 255) r = 255;
    if (g < 0) g = 0; 
	if (g > 255) g = 255;
    if (b < 0) b = 0; 
	if (b > 255) b = 255;
    c.r = (unsigned char)r; c.g = (unsigned char)g; c.b = (unsigned char)b;
    return c;
}

static void board_clear(int *b)
{
    int i = 0;
    while (i < T_W * T_H) { b[i] = -1; i++; }
}

/* Pastikan pool sphere dibuat SEKALI untuk app yang Tetris-enabled */
static void ensure_pool(t_app *a, t_ts *st)
{
    int i;

    if (!a || !st || st->inited) return;

    st->cell = 0.6f;
    st->z    = -8.0f;
    st->org  = v3(-(float)T_W * st->cell * 0.5f,
                   (float)T_H * st->cell * 0.5f,
                   st->z);

    board_clear(st->board);

    i = 0;
    while (i < POOL) {
        t_sphere *sp = (t_sphere *)emalloc(sizeof(t_sphere));
        t_obj    *o  = (t_obj *)emalloc(sizeof(t_obj));
        sp->c = v3(0,0,0); sp->r = 0.0f;
        sp->m.color = rgb_u8(230,230,230);
        sp->m.checker = 0; sp->m.specular = 0.25f; sp->m.sp_exp = 48; sp->m.bump = 0;
        o->type = OBJ_SPHERE; o->ptr = sp; o->next = NULL;

        /* Masuk ke scene HANYA untuk scene Tetris karena ensure_pool dipanggil
           dari tetris_simple_start() yang dipanggil saat tetris_enabled = 1 */
        scene_add_obj(&a->sc, o);

        st->sph[i]  = sp;
        st->pool[i] = o;
        i++;
    }

    st->drop_iv = 0.25;
    st->acc     = 0.0;
    st->phase   = 0;
    st->phase_t = 0.0;
    st->target_y0 = 16;
    st->cur_x   = 0;
    st->cur_y   = 0;
    st->last    = 0.0;

    st->inited  = 1;
}

static void draw_cell(t_ts *st, int x, int y, t_rgb c)
{
    int   id;
    float r;
    t_vec3  p;

    if (!st) return;
    id = st->used;
    if (id >= POOL) return;

    p.x = st->org.x + (float)x * st->cell;
    p.y = st->org.y - (float)y * st->cell;
    p.z = st->z;

    r = st->cell * 0.48f;

    st->sph[id]->c = p;
    st->sph[id]->r = r;
    st->sph[id]->m.color = c;

    st->used = id + 1;
}

static void hide_unused(t_ts *st)
{
    int i;
    if (!st) return;
    i = st->used;
    while (i < POOL) {
        st->sph[i]->r = 0.0f;
        i++;
    }
}

/* Cek apakah O-piece 2x2 bisa ditempatkan */
static int can_place_O(int *b, int px, int py)
{
    if (px < 0 || px + 1 >= T_W || py < 0 || py + 1 >= T_H) return 0;
    if (b[idx(px,py)]     >= 0) return 0;
    if (b[idx(px+1,py)]   >= 0) return 0;
    if (b[idx(px,py+1)]   >= 0) return 0;
    if (b[idx(px+1,py+1)] >= 0) return 0;
    return 1;
}

static void lock_O(int *b, int px, int py)
{
    b[idx(px,py)]     = 1; b[idx(px+1,py)]   = 1;
    b[idx(px,py+1)]   = 1; b[idx(px+1,py+1)] = 1;
}

static void render_board_and_piece(t_ts *st)
{
    int y, x;

    if (!st) return;
    st->used = 0;

    y = 0;
    while (y < T_H) {
        x = 0;
        while (x < T_W) {
            if (st->board[idx(x,y)] >= 0)
                draw_cell(st, x, y, rgb_u8(200,200,200));
            x++;
        }
        y++;
    }

    draw_cell(st, st->cur_x,     st->cur_y,     rgb_u8(255,210,80));
    draw_cell(st, st->cur_x + 1, st->cur_y,     rgb_u8(255,210,80));
    draw_cell(st, st->cur_x,     st->cur_y + 1, rgb_u8(255,210,80));
    draw_cell(st, st->cur_x + 1, st->cur_y + 1, rgb_u8(255,210,80));

    hide_unused(st);
}

static void scripted_drop(t_ts *st, double dt)
{
    int y0;

    if (!st) return;
    st->acc += dt;
    if (st->acc < st->drop_iv) return;
    st->acc -= st->drop_iv;

    y0 = st->target_y0;

    if (st->cur_y + 1 < y0 && can_place_O(st->board, st->cur_x, st->cur_y + 1)) {
        st->cur_y = st->cur_y + 1;
    } else {
        lock_O(st->board, st->cur_x, st->cur_y);
        st->cur_x += 2;
        st->cur_y  = 0;

        if (st->cur_x >= T_W) {
            st->cur_x = 0;
            st->target_y0 += 1;
        }
        if (st->target_y0 >= 20) {
            st->phase = 1;
            st->phase_t = 0.0;
        }
    }
}

static void step_reset(t_ts *st, double dt)
{
    if (!st) return;
    st->phase_t += dt;
    if (st->phase_t >= 0.8) {
        board_clear(st->board);
        st->target_y0 = 16;
        st->cur_x = 0;
        st->cur_y = 0;
        st->phase = 0;
    }
}

/* ==== API ==== */
void tetris_simple_start(t_app *a)
{
    if (!a) return;
    if (!a->tetris)
        a->tetris = (t_ts *)emalloc(sizeof(t_ts));

    memset(a->tetris, 0, sizeof(t_ts));  // pengganti ft_bzero
    ensure_pool(a, a->tetris);
    board_clear(a->tetris->board);
    a->tetris->target_y0 = 16;
    a->tetris->cur_x = 0;
    a->tetris->cur_y = 0;
    a->tetris->last  = 0.0;
}

void tetris_simple_update(t_app *a, double now)
{
    t_ts   *st;
    double  dt;

    if (!a || !a->tetris_enabled) return;
    st = a->tetris;
    if (!st || !st->inited) return;

    if (st->last == 0.0)
        st->last = now;

    dt = now - st->last;
    if (dt < 0.0) dt = 0.0;
    if (dt > 0.1) dt = 0.1;

    if (st->phase == 0) scripted_drop(st, dt);
    else                 step_reset(st, dt);

    render_board_and_piece(st);
    st->last = now;
    a->needs_redraw = 1;
}