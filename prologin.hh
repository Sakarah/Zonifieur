///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_cxx.rb
//

#ifndef PROLOGIN_HH_
# define PROLOGIN_HH_

# include <vector>

# include <string>

///
// Taille du terrain (longueur et largeur).
//
# define TAILLE_TERRAIN            30

///
// Nombre de tours à jouer avant la fin de la partie.
//
# define NB_TOURS                  100

///
// Nombre de points de déplacement par tour (avant utilisation du turbo).
//
# define NB_POINTS_DEPLACEMENT     6

///
// Nombre de points d'action par tour.
//
# define NB_POINTS_ACTION          42

///
// Nombre de points d'action que coûte la capture d'un portail.
//
# define COUT_CAPTURE              3

///
// Nombre de points d'action que coûte la création d'un lien.
//
# define COUT_LIEN                 2

///
// Nombre de points d'action que coûte la neutralisation d'un portail de base.
//
# define COUT_NEUTRALISATION       10

///
// Nombre de points d'action supplémentaires que coûte la neutralisation pour chaque bouclier présent.
//
# define COUT_NEUTRALISATION_BOUCLIER 5

///
// Nombre de points d'action que coûte la mise en place d'un bouclier sur un portail sans bouclier.
//
# define COUT_BOUCLIER             3

///
// Nombre de points d'action que coûte l'utilisation d'un turbo.
//
# define COUT_TURBO                6

///
// Nombre maximum de boucliers sur un même portail.
//
# define MAX_BOUCLIERS             6

///
// Nombre de points que rapporte la capture d'un portail.
//
# define POINTS_CAPTURE            10

///
// Constante de proportionnalité reliant l'aire d'un champ au nombre de points qu'il rapporte par tour.
//
# define POINTS_CHAMP              2

///
// Erreurs possibles
//
enum erreur
{
  OK, /* <- L'action a été exécutée avec succès */
  PA_INSUFFISANTS, /* <- Vous ne possédez pas assez de points d'action pour cette action. */
  AUCUN_PORTAIL, /* <- La position spécifiée n'est pas un portail. */
  POSITION_INVALIDE, /* <- La position spécifiée est hors de la carte. */
  POSITION_ELOIGNEE, /* <- La destination est trop éloignée. */
  PORTAIL_AMI, /* <- Le portail vous appartient. */
  PORTAIL_NEUTRE, /* <- Le portail est neutre. */
  PORTAIL_ENNEMI, /* <- Le portail appartient à votre adversaire. */
  LIEN_INTERSECTION, /* <- Le lien croise un lien existant. */
  LIEN_CHAMP, /* <- Le lien se trouve dans un champ existant. */
  LIEN_DEGENERE, /* <- Les deux extrémités du lien coïncident. */
  LIMITE_BOUCLIERS, /* <- Ce portail est équipé du nombre maximal de boucliers. */
};


///
// Position sur la carte, donnée par deux coordonnées.
//
struct position
{
    position() = default;
    position(int _x, int _y){x=_x;y=_y;}
    int x;  /* <- Coordonnée en X */
    int y;  /* <- Coordonnée en Y */

    bool operator==(const position& o) const { return x==o.x && y==o.y; }
    bool operator!=(const position& o) const { return !((*this)==o); }
};


///
// Représente un lien existant.
//
struct lien
{
    lien() = default;
    lien(position e1, position e2, int p) { extr1=e1; extr2=e2; joueur_l=p; }
    position extr1;  /* <- Première extrémité du lien. */
    position extr2;  /* <- Seconde extrémité du lien. */
    int joueur_l;  /* <- Joueur possédant ce lien. */
};


///
// Représente un champ de contrôle existant.
//
struct champ
{
  position som1;  /* <- Premier sommet du champ. */
  position som2;  /* <- Deuxième sommet du champ. */
  position som3;  /* <- Troisième sommet du champ. */
  int joueur_c;  /* <- Joueur possédant ce champ. */
};


///
// Déplace votre agent sur la case passée en argument.
//
extern "C" erreur api_deplacer(position dest);
static inline erreur deplacer(position dest)
{
  return api_deplacer(dest);
}


///
// Utilise un turbo.
//
extern "C" erreur api_utiliser_turbo();
static inline erreur utiliser_turbo()
{
  return api_utiliser_turbo();
}


///
// Capture le portail où est positionné votre agent.
//
extern "C" erreur api_capturer();
static inline erreur capturer()
{
  return api_capturer();
}


///
// Crée un lien entre le portail où se trouve votre agent et le portail de destination donné en argument.
//
extern "C" erreur api_lier(position portail);
static inline erreur lier(position portail)
{
  return api_lier(portail);
}


///
// Neutralise le portail où se trouve votre agent.
//
extern "C" erreur api_neutraliser();
static inline erreur neutraliser()
{
  return api_neutraliser();
}


///
// Ajoute un bouclier au portail sur lequel se trouve votre agent.
//
extern "C" erreur api_ajouter_bouclier();
static inline erreur ajouter_bouclier()
{
  return api_ajouter_bouclier();
}


///
// Renvoie la liste de tous les liens présents.
//
extern "C" std::vector<lien> api_liste_liens();
static inline std::vector<lien> liste_liens()
{
  return api_liste_liens();
}


///
// Renvoie la liste de tous les champs de contrôle.
//
extern "C" std::vector<champ> api_liste_champs();
static inline std::vector<champ> liste_champs()
{
  return api_liste_champs();
}


///
// Renvoie la liste de tous les portails de la carte.
//
extern "C" std::vector<position> api_liste_portails();
static inline std::vector<position> liste_portails()
{
  return api_liste_portails();
}


///
// Renvoie la liste de tous les liens existants qui croisent un segment, entravant la création d'un lien.
//
extern "C" std::vector<lien> api_liens_bloquants(position ext1, position ext2);
static inline std::vector<lien> liens_bloquants(position ext1, position ext2)
{
  return api_liens_bloquants(ext1, ext2);
}


///
// Prend les positions de deux portails, et renvoie un booléen indiquant s'ils sont reliés. Le résultat est `false` lorsque l'une des deux positions ne repère pas un portail.
//
extern "C" bool api_lien_existe(position ext1, position ext2);
static inline bool lien_existe(position ext1, position ext2)
{
  return api_lien_existe(ext1, ext2);
}


///
// Renvoie un booléen indiquant si les 3 positions repèrent bien 3 portails tous reliés entre eux.
//
extern "C" bool api_champ_existe(position som1, position som2, position som3);
static inline bool champ_existe(position som1, position som2, position som3)
{
  return api_champ_existe(som1, som2, som3);
}


///
// Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
//
extern "C" bool api_case_dans_champ(position pos);
static inline bool case_dans_champ(position pos)
{
  return api_case_dans_champ(pos);
}


///
// Renvoie la liste des champs à l'intérieur desquels ``pos`` se trouve. Si la case est un portail, le résultat de ``case_champs`` sera disjoint de celui de ``champs_incidents_portail``.
//
extern "C" std::vector<champ> api_case_champs(position pos);
static inline std::vector<champ> case_champs(position pos)
{
  return api_case_champs(pos);
}


///
// Renvoie le numéro du joueur correspondant au portail donné, -1 si le portail est neutre, -2 si la case n'est pas un portail. Vous pouvez utiliser cette fonction pour vérifier qu'une case donnée est bien un portail.
//
extern "C" int api_portail_joueur(position portail);
static inline int portail_joueur(position portail)
{
  return api_portail_joueur(portail);
}


///
// Renvoie le nombre de boucliers présents sur un portail (-2 si la case n'est pas un portail).
//
extern "C" int api_portail_boucliers(position portail);
static inline int portail_boucliers(position portail)
{
  return api_portail_boucliers(portail);
}


///
// Renvoie la liste de tous les liens dont le portail donné est une extrémité.
//
extern "C" std::vector<lien> api_liens_incidents_portail(position portail);
static inline std::vector<lien> liens_incidents_portail(position portail)
{
  return api_liens_incidents_portail(portail);
}


///
// Renvoie la liste de tous les champs dont le portail donné est un sommet.
//
extern "C" std::vector<champ> api_champs_incidents_portail(position portail);
static inline std::vector<champ> champs_incidents_portail(position portail)
{
  return api_champs_incidents_portail(portail);
}


///
// Renvoie la liste de tous les champs dont le lien donné est un côté. Si le segment n'est pas un lien présent, renvoie la liste de tous les champs que la création du lien ferait apparaître.
//
extern "C" std::vector<champ> api_champs_incidents_segment(position ext1, position ext2);
static inline std::vector<champ> champs_incidents_segment(position ext1, position ext2)
{
  return api_champs_incidents_segment(ext1, ext2);
}


///
// Renvoie la liste des portails capturés par votre adversaire au dernier tour.
//
extern "C" std::vector<position> api_hist_portails_captures();
static inline std::vector<position> hist_portails_captures()
{
  return api_hist_portails_captures();
}


///
// Renvoie la liste des portails neutralisés par votre adversaire au dernier tour.
//
extern "C" std::vector<position> api_hist_portails_neutralises();
static inline std::vector<position> hist_portails_neutralises()
{
  return api_hist_portails_neutralises();
}


///
// Renvoie la liste des liens créés par votre adversaire au dernier tour.
//
extern "C" std::vector<lien> api_hist_liens_crees();
static inline std::vector<lien> hist_liens_crees()
{
  return api_hist_liens_crees();
}


///
// Renvoie la liste des champs créés par votre adversaire au dernier tour.
//
extern "C" std::vector<champ> api_hist_champs_crees();
static inline std::vector<champ> hist_champs_crees()
{
  return api_hist_champs_crees();
}


///
// Renvoie la liste des positions où votre adversaire a ajouté des boucliers au dernier tour.
//
extern "C" std::vector<position> api_hist_boucliers_ajoutes();
static inline std::vector<position> hist_boucliers_ajoutes()
{
  return api_hist_boucliers_ajoutes();
}


///
// Renvoie la distance de Manhattan entre deux positions.
//
extern "C" int api_distance(position pos1, position pos2);
static inline int distance(position pos1, position pos2)
{
  return api_distance(pos1, pos2);
}


///
// Renvoie le nombre de points que rapporte(rait) chaque tour un champ existant ou hypothétique.
//
extern "C" int api_score_triangle(position som1, position som2, position som3);
static inline int score_triangle(position som1, position som2, position som3)
{
  return api_score_triangle(som1, som2, som3);
}


///
// Indique si deux segments se croisent. Cette fonction correspond exactement à la condition d'interférence entre liens, c'est-à-dire qu'elle renvoie ``false`` si l'intersection est une extrémité des deux segments.
//
extern "C" bool api_intersection_segments(position a1, position a2, position b1, position b2);
static inline bool intersection_segments(position a1, position a2, position b1, position b2)
{
  return api_intersection_segments(a1, a2, b1, b2);
}


///
// Indique si un point se trouve à l'intérieur d'un triangle. Le critère coïncide avec celui de ``case_champs``.
//
extern "C" bool api_point_dans_triangle(position p, position som1, position som2, position som3);
static inline bool point_dans_triangle(position p, position som1, position som2, position som3)
{
  return api_point_dans_triangle(p, som1, som2, som3);
}


///
// Renvoie votre numéro de joueur.
//
extern "C" int api_moi();
static inline int moi()
{
  return api_moi();
}


///
// Renvoie le numéro de votre adversaire.
//
extern "C" int api_adversaire();
static inline int adversaire()
{
  return api_adversaire();
}


///
// Indique la position de l'agent du joueur désigné par le numéro ``id_joueur``.
//
extern "C" position api_position_agent(int id_joueur);
static inline position position_agent(int id_joueur)
{
  return api_position_agent(id_joueur);
}


///
// Indique votre nombre de points d'actions restants pour ce tour-ci.
//
extern "C" int api_points_action();
static inline int points_action()
{
  return api_points_action();
}


///
// Indique votre nombre de points de déplacement restants pour ce tour-ci.
//
extern "C" int api_points_deplacement();
static inline int points_deplacement()
{
  return api_points_deplacement();
}


///
// Renvoie le score du joueur désigné par le numéro ``id_joueur``.
//
extern "C" int api_score(int id_joueur);
static inline int score(int id_joueur)
{
  return api_score(id_joueur);
}


///
// Renvoie le numéro du tour actuel.
//
extern "C" int api_tour_actuel();
static inline int tour_actuel()
{
  return api_tour_actuel();
}


///
// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
//
extern "C" bool api_annuler();
static inline bool annuler()
{
  return api_annuler();
}


///
// Affiche le contenu d'une valeur de type erreur
//
extern "C" void api_afficher_erreur(erreur v);
static inline void afficher_erreur(erreur v)
{
  api_afficher_erreur(v);
}


///
// Affiche le contenu d'une valeur de type position
//
extern "C" void api_afficher_position(position v);
static inline void afficher_position(position v)
{
  api_afficher_position(v);
}


///
// Affiche le contenu d'une valeur de type lien
//
extern "C" void api_afficher_lien(lien v);
static inline void afficher_lien(lien v)
{
  api_afficher_lien(v);
}


///
// Affiche le contenu d'une valeur de type champ
//
extern "C" void api_afficher_champ(champ v);
static inline void afficher_champ(champ v)
{
  api_afficher_champ(v);
}



extern "C" {

///
// Fonction appelée au début de la partie.
//
void partie_init();

///
// Fonction appelée à chaque tour.
//
void jouer_tour();

///
// Fonction appelée à la fin de la partie.
//
void partie_fin();

}
#endif
