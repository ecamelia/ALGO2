#include <stdio.h>
#include <string.h>
#include "fractal.h"
#include "point.h"
#include "sg.h"
#include <math.h>


#define QUIT  'q'

#define TITLE_ORDER " / order = "

//  ndigits : renvoie le nombre de chiffres de n dans son écriture en base base,
//    en supposant n >= 0 et base >= 2.
static size_t ndigits(int n, int base) {
  if (n < base) {
    return 1;
  }
  return 1 + ndigits(n / base, base);
}

//  set_title : efface la fenêtre, affiche le titre title avec affichage de
//    l'ordre n, en supposant n >= 0.
static void make_title(const char *title, int n) {
  sg_clear();
  char s[strlen(title) + strlen(TITLE_ORDER) + ndigits(n, 10) + 1];
  sprintf(s, "%s%s%d", title, TITLE_ORDER, n);
  sg_set_title(s);
}

//  graduate_color : fixe la couleur de premier plan entre le vert et le marron
//    proportionnellement à k, en supposant 0 <= k <= n et n >= 1.
static void graduate_color(int k, int n) {
  sg_set_fgcolor(
      COLOR((int) (RGBMAX * (double) k / n), RGBMAX / 2, RGBMAX / 4));
}

#define MARGIN(size) (size) / 10

//--- Carrés emboités ----------------------------------------------------------

#define RF4_SHIFT 9.0

//  r_fitted_4 : produit l'emboité d'ordre n du quadrilatère de sommets pa, pb,
//    pc et pd avec rotation droite de proportion 1 / (RF4_SHIFT + 1).
static void r_fitted_4(int n, point pa, point pb, point pc, point pd) {
  if (n < 0) {
    return;
  }
  draw_line(pa, pb);
  draw_line(pb, pc);
  draw_line(pc, pd);
  draw_line(pd, pa);
  if (n == 0) {
    return;
  }
  r_fitted_4(n - 1,
      barycenter(pa, RF4_SHIFT, pb, 1.0),
      barycenter(pb, RF4_SHIFT, pc, 1.0),
      barycenter(pc, RF4_SHIFT, pd, 1.0),
      barycenter(pd, RF4_SHIFT, pa, 1.0));
}

int fitted_squares(const char *title, unsigned int size, int n) {
  unsigned int d = MARGIN(size);
  for (int k = 0; k <= n; ++k) {
    make_title(title, k);
    graduate_color(k, n);
    r_fitted_4(k,
        (point) { d, d },
        (point) { size - d, d },
        (point) { size - d, size - d },
        (point) { d, size - d });
    if (sg_get_key() == QUIT) {
      return -1;
    }
  }
  return 0;
}

//  r_koch : Dessine récursivement une courbe de Koch d'ordre `n` entre les
//  points `a` et `b`. À chaque récursion, elle divise la ligne en 4 segments,
//  avec un sommet formant // la caractéristique "bosse" de la courbe de Koch
static void r_koch(int n, point pa, point pb) {
    if (n == 0) {
        draw_line(pa, pb);
    } else {
        point p_ab1 = barycenter(pa, RF4_SHIFT - 1, pb, 1.0);
        point p_ab2 = barycenter(pa, 1.0, pb, RF4_SHIFT - 1);

        point culmier = {
            (p_ab1.x + p_ab2.x) / 2 - (p_ab2.y - p_ab1.y) * sqrt(3) / 6,
            (p_ab1.y + p_ab2.y) / 2 + (p_ab2.x - p_ab1.x) * sqrt(3) / 6
        };

        r_koch(n - 1, pa, p_ab1);
        r_koch(n - 1, p_ab1, culmier);
        r_koch(n - 1, culmier, p_ab2);
        r_koch(n - 1, p_ab2, pb);
    }
}

int koch_curve(const char *title, unsigned int size, int n) {
    point pa = { 0, size / 2 };
    point pb = { size, size / 2 };
    for (int k = 0; k <= n; ++k) {
        make_title(title, k);
        graduate_color(k, n);
        r_koch(k, pa, pb);
        if (sg_get_key() == QUIT) {
            return -1;
        }
    }
    return 0;
}

//  r_sierpinski : produit l'emboité d'ordre n du quadrilatère de sommets pa,
//  pb et pc , qui a chaque appel recursive divise en 2 le sengment et
//  designe un autre triangle
static void r_sierpinski(int n, point pa, point pb, point pc) {
    if (n == 0) {
        draw_line(pa, pb);
        draw_line(pb, pc);
        draw_line(pc, pa);
    } else {
        point p_ab = barycenter(pa, 1.0, pb, 1.0);
        point p_ac = barycenter(pa, 1.0, pc, 1.0);
        point p_bc = barycenter(pb, 1.0, pc, 1.0);
        r_sierpinski(n - 1, pa, p_ab, p_ac);
        r_sierpinski(n - 1, p_ab, pb, p_bc);
        r_sierpinski(n - 1, p_ac, p_bc, pc);
    }
}

int sierpinski_triangle(const char *title, unsigned int size, int n) {
    point pa = { size / 2.0, 0 };
    point pb = { 0, size * (sqrt(3) / 2) };
    point pc = { size, size * (sqrt(3) / 2) };

    for (int k = 0; k <= n; ++k) {
        make_title(title, k);
        graduate_color(k, n);
        r_sierpinski(k, pa, pb, pc);
        if (sg_get_key() == QUIT) {
            return -1;
        }
    }
    return 0;
}


// r_pythagoras_tree : Dessine récursivement un arbre de Pythagore d'ordre `n`.
// Le point `base` est la base de la branche, `length` est la longueur de la branche, 
// et `angle` est l'angle de la branche par rapport à l'axe vertical.
static void r_pythagoras_tree(int n, point base, double length, double angle) {
    if (n == 0) {
        return;  
    }

    point top = {
        base.x + length * cos(angle),  
        base.y - length * sin(angle)   
    };

    
    draw_line(base, top);

    
    double next_length = length * 0.7;

    
    double left_angle = angle + M_PI / 4;   
    double right_angle = angle - M_PI / 4;  

    
    r_pythagoras_tree(n - 1, top, next_length, left_angle);
    r_pythagoras_tree(n - 1, top, next_length, right_angle);
}


int pythagoras_tree(const char *title, unsigned int size, int n) {

    point base = { size / 2.0, size };  
    double length = size / 3.0;  
    double angle = M_PI / 2;  

    for (int k = 0; k <= n; ++k) {
    make_title(title, n);  
    graduate_color(k, n);  
    r_pythagoras_tree(k, base, length, angle);  
        if (sg_get_key() == QUIT) {
            return -1;
        }
    }
    return 0;
}



