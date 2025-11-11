#ifndef TETRIS_H
#define TETRIS_H

#include "ft_minirt.h"

#define T_W  10
#define T_H  20
#define POOL (T_W * T_H) /* maksimum sphere pool */


typedef struct s_tetris
{
    int      inited;
    float    cell;
    t_vec3     org;
    float    z;
    int      board[T_W * T_H];  /* -1 kosong, >=0 terisi */
    int      used;
    t_sphere *sph[POOL];
    t_obj    *pool[POOL];

    /* anim state */
    double   acc;
    double   drop_iv;    /* interval jatuh */
    int      phase;      /* 0=drop, 1=reset_pause */
    double   phase_t;
    int      target_y0;  /* 16..19 */
    int      cur_x;      /* kolom O-piece (per 2 kolom) */
    int      cur_y;      /* posisi y atas piece */
    double   last;       /* timestamp frame sebelumnya (hindari static) */
} t_tetris;

/* API */
void tetris_simple_start(t_app *a);
void tetris_simple_update(t_app *a, double now);

#endif