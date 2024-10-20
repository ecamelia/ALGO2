//  Module implantant diverses figures fractales dans l'environnement de bureau
//    X11. Chacune de figures est supposée s'inscrire dans une fenêtre
//    préalablement ouverte par exemple à l'aide de la procédure sg_open du
//    module sg.

#ifndef FRACTAL__H
#define FRACTAL__H

//  fitted_squares : produit la figure fractale d'ordre n des carrés emboités à
//    l'intérieur d'un carré dont la longueur des côtés exprimée en pixels est
//    size. La chaine de caractères pointée par title est affichée dans le titre
//    de la fenêtre. Si une demande d'abandon est détectée, renvoie une valeur
//    non nulle ; renvoie zéro sinon.
extern int fitted_squares(const char *title, unsigned int size, int n);


// sierpinski_triangle : produit la figure fractale d'ordre n du triangle de Sierpiński
// à l'intérieur d'un triangle équilatéral dont la longueur des côtés exprimée en pixels est size.
// La chaine de caractères pointée par title est affichée dans le titre de la fenêtre.
// Si une demande d'abandon est détectée, renvoie une valeur non nulle ; renvoie zéro sinon.
extern int sierpinski_triangle(const char *title, unsigned int size, int n);

// koch_curve : produit la courbe fractale d'ordre n de la courbe de Koch
// à l'intérieur d'un carré dont la longueur des côtés exprimée en pixels est size.
// La chaîne de caractères pointée par title est affichée dans le titre de la fenêtre.
// Si une demande d'abandon est détectée, renvoie une valeur non nulle ;
// renvoie zéro sinon.
extern int koch_curve(const char *title, unsigned int size, int n);

extern int pythagoras_tree(const char *title, unsigned int size, int n);

#endif
