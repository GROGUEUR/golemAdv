#define S_LEN 100
#define B_LIM 4

typedef enum{
	rien,
	b_pv,
	b_pm,
	b_pcs,
	b_itl,
	b_vit,
	b_esq,
	b_crt
} boost_t;

typedef enum{
	rien,
	basique,
	vegetal,
	aeree,
	feu,
	glace,
	poison
} partie_armure_t;

typedef struct{
	partie_armure_t casque;
	partie_armure_t plastron;
	partie_armure_t bottes;
} armure_t;

typedef struct{
	char nom[S_LEN];
	char desc[S_LEN];
	/* insérer type du sprite */
	int dgt;
	boost_t boosts[B_LIM];
} arme_t;

typedef struct{
	char nom[S_LEN];
	char desc[S_LEN];
	/* insérer type du sprite */
	int rdc;
	boost_t boosts[B_LIM];
} bouclier_t;

typedef struct{
	/* Barre de vie */
	int pv, pv_max;
	/* Barre de magie */
	int pm, pm_max;
	/* Attaque et défense (physique et magique) */
	int atq, def, atq_mg, def_mg;
	/* Précision et intelligence (précision magique) */
	int pcs, itl;
	/* Vitesse, esquive et niveau */
	int vit, esq, niv;
	/* Chances de coup critique */
	float crt;
} profil_t;

typedef struct{
	profil_t profil;
	armure_t armure;
	arme_t arme;
	bouclier_t bouclier;
} perso_t;

/* -------------------------------- */

typedef enum{
	rien,
	brulure,
	gel,
	paralysie,
	poison,
	sommeil
} alter_t;

typedef enum{
	rien,
	chgm_atq,
	chgm_def,
	chgm_atq_mg,
	chgm_def_mg,
	chgm_pcs,
	chgm_itl,
	chgm_vit,
	chgm_esq,
	chgm_crt
} effet_t;

typedef struct{
	/* Nom de l'action */
	char * nom[S_LEN];
	/* Multiplicateur de dégâts (en pourcentage) (si ce n'est pas une attaque on met à 0) */
	float dgt;
	/* Effet (voir effet_t) */
	effet_t effet;
	/* Altération d'état (voir alter_t) */
	alter_t alter;
	/* Coût de l'attaque (enlève des pm une fois utilisée) */
	int cout;
} attaque_t;

/* -------------------------------- */

typedef struct objet_s{
	char nom[S_LEN];
	char desc[S_LEN];
	int nb;
	objet_s * suiv_l;
	objet_s * suiv_c;
	void (*consommer) (objet_s *);
	void (*equiper) (objet_s *);
	void (*jeter) (objet_s *);
} objet_t;

objet_t * inventaire;

