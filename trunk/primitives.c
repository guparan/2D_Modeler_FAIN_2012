#include "primitives.h"
#include "evenement.h"

static int TAILLE_PIXEL=10;
static int reshape_deja_lance=0;

static couleur image[MAXX][MAXY];
static int Width,Height;

static struct{	unsigned char r,g,b;} couleurs[]=
{
  {  0,  0,  0},/* NOIR    */
  {255,255,255},/* BLANC   */
  {255,  0,  0},/* ROUGE   */
  {  0,255,  0},/* VERT    */
  {  0,  0,255},/* BLEU    */
  {255,255,  0},/* JAUNE   */
  {255,  0,255},/* MAGENTA */
  {  0,255,255},/* CYAN    */
  {128,128,128},/* GRIS    */
};


//-----------------------------------------------------------------
// procedure lancee quand on retaille la fenetre

static void reshape(int width, int height)
{
  reshape_deja_lance=1;
  Width=width;
  Height=height;
  printf("reshape(%d,%d)\n",width,height);
  glViewport(0, 0, width, height);
  glLoadIdentity();
  gluOrtho2D(-0.5,((double)width)/TAILLE_PIXEL-0.5,
			 -0.5,((double)height)/TAILLE_PIXEL-0.5);
}


//-----------------------------------------------------------------
// procedure permettant de changer la taille des pixels pour mieux
// voir comment fonctionnent les algorithmes de geometrie discrete.

void change_taille_pixel(int t)
{
	TAILLE_PIXEL=t;
	if(reshape_deja_lance)
	{
		glPointSize(TAILLE_PIXEL);
		reshape(Width,Height);
		glutPostRedisplay();
		// Indicate that things will have to be redisplayed
	}
}


//-----------------------------------------------------------------
// procedure lancee pour afficher l'image. En l'occurrence, elle
// affiche le contenu du tableau image[][].

static couleur current_color=-1;

static void display(void)
{
	printf("display\n");
	glClear(GL_COLOR_BUFFER_BIT);

	int x,y,w,h;
	if(Width<MAXX) w=Width; else w=MAXX;
	if(Height<MAXY) h=Height; else h=MAXY;

	glBegin(GL_POINTS);
	for(x=0;x<w;x++)
		for(y=0;y<h;y++)
		{
			couleur c=image[x][y];
			if(c)
			{
				if(c!=current_color)
				{
					glColor3ub(couleurs[c].r,couleurs[c].g,couleurs[c].b);
					current_color=c;
				}
				glVertex2i(x,y);
			}
		}
	glEnd();
	glFinish();
	glFlush();
	glutReportErrors();
}


//-----------------------------------------------------------------
// Change la couleur du point de coordonnées (x,y)

void change_point(int x, int y, couleur c)
{
	if(x<0 || y<0 || x>=MAXX || y>=MAXY) return;

	image[x][y]=c;

	if(c!=current_color)
	{
		glColor3ub(couleurs[c].r,couleurs[c].g,couleurs[c].b);
		current_color=c;
	}
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}


//-----------------------------------------------------------------
// C'est la pipette : retourne la couleur du point de coord (x,y).

couleur val_point(int x, int y)
{
  if(x<0 || y<0 || x>=MAXX || y>=MAXY) return NOIR;
  return image[x][y];
}


//-----------------------------------------------------------------
// L'action à réaliser lorsqu'on clique :
// Pour le bouton gauche : si la couleur préexistant est le noir,
// alors on la change en blanc, sinon, on la remet à noir.
// Pour le bouton du milieu et le bouton droit, on execute
// action_bouton_milieu et action_bouton_droit (à definir).

static void souris(int b,int s,int x,int y)
{
	int x2=x/TAILLE_PIXEL;
	int y2=(Height-1-y)/TAILLE_PIXEL;
	switch(b)
	{
	case GLUT_LEFT_BUTTON:
	{
		if(s==GLUT_DOWN)
			change_point(x2,y2,!val_point(x2,y2));
		break;
	}
    case GLUT_MIDDLE_BUTTON:
	{
		evenement_boutonMilieu(x2,y2,s==GLUT_UP);
		break;
	}
	case GLUT_RIGHT_BUTTON:	evenement_boutonDroit(x2,y2,s==GLUT_UP);    break;
  }
  /*glutPostRedisplay();*/
	glutReportErrors();
}



//-----------------------------------------------------------------
// Les initialisations de glut

int main_Modeleurlib(int nargs, char **args)
{
	glutInit(&nargs,args);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow(args[0]);

    /* Gestion des evenements */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(souris);
	glutKeyboardFunc(evenement_clavier);

	glPointSize(TAILLE_PIXEL);
	glutMainLoop();
	return 0;
}

//-----------------------------------------------------------------
// Retourne la largeur de l'écran (en nombre de gros pixels)

int largeur_ecran(void)
{
	int w=(Width-1)/TAILLE_PIXEL+1;

	if(w<=MAXX)	return w;
	else		return MAXX;
}

//-----------------------------------------------------------------
// Retourne la largeur de l'écran (en nombre de gros pixels)

int hauteur_ecran(void)
{
	int h=(Height-1)/TAILLE_PIXEL+1;
	if(h<=MAXY)	return h;
	else 		return MAXY;
}

//-----------------------------------------------------------------
// Fonction qui change la couleur de tous les pixels à NOIR.

void efface_tout(void)
{
	int x;
	for(x=0;x<MAXX;x++)
		memset(&image[x][0],0,MAXY*sizeof(couleur));

	glClear(GL_COLOR_BUFFER_BIT); /* au cas ou on fait des calculs apres */
	glutPostRedisplay();
}
