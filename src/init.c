#include "master.h"

/**
* SetupMatrices. Sets the projection and modelview matrix to the program default.
* @param Width of viewport.
* @param Height of viewport.
*/
void SetupMatrices(GLsizei _w, GLsizei _h)
{
    /* Sanity */
    if(_h <= 0) _h = 1;
    if(_w <= 0) _w = 1;
    
    glViewport(0, 0, _w, _h); /* Set viewport to window dimensions. */
    
    /* Reset projection matrix stack. */
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(60.0f, 1.0f, 1.0f, 100.0f);

    /* Reset texture view matrix stack. */
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    /* Reset model view matrix stack. */
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    /* ... and keep it on for rendering. */  
}

/**
* SetupRenderingContext. Setup various OpenGL settings.
*/
void SetupRenderingContext()
{
    glClearColor(0.4f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW); /* Counter clockwise polys face out. */

    glAlphaFunc(GL_GREATER, 0.01); /* Skip pixels which alpha channel is lower than 0.01. */
    glEnable(GL_TEXTURE_2D);  /* Enable 2D texturing. */
    glEnable(GL_BLEND);  /* Enable blending. */
    glEnable(GL_ALPHA_TEST);  /* Enable alpha. */
    glEnable(GL_CULL_FACE);  /* Make sure face culling is enabled for speed. */
    glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);  /* Turn on alpha blending. */

    glPointSize(2); /* Size of points. */

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_NONE);

    glShadeModel(GL_SMOOTH); /* Smooth shading. */

    /* Enable Lighting. */
    glEnable(GL_LIGHTING);

    /* Set up light0. */
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat position[] = {  0.0, 40.0, -20.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    /* Create the newly set up lightsource. */
    glEnable(GL_LIGHT0);


    /* GLOBAL light settings. */
    GLfloat global_ambient[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    
    /* Material color tracking. */
    glEnable(GL_COLOR_MATERIAL);
    /* Make it so ambient and diffuse material properties will use glcolor
       Soo...  glColor3f(0.0f, 0.0f, 1.0f); would make blue reflective properties
       Exactly like calling:
       float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
       glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
       before the geometry */
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 
}

/**
* New Game. Set up board.
*/
void NewGame()
{
    /* Clear board */
    int i, j;
    for(i = GAMEBOARD_H-1; i >= 0; i--) 
        for(j = GAMEBOARD_W-1; j >= 0; j--)
            gameboard[i][j] = 0;
    
    /* Randomize next brick */
    brick_type_next = (rand() % MAX_BRICK_TYPES);
    brick_type_current = 0;         
    new_brick = true;  
    
    score = 0;
    level = 1;
    game_over = false;
}

/**
* Initialize. Setup SDL and other API's.
*/
void Initialize()
{
    /* Initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(width, height, 0, vid_flags);
    SDL_WM_SetCaption(APP_NAME, APP_NAME);

    /* Fake Setup for GLUT */
    char *myargv [1];
    int myargc = 1;
    myargv [0] = strdup ("");
    glutInit(&myargc, myargv);
    /* Setup OpenGL */
    SetupRenderingContext();
    SetupMatrices(width, height);
    
    /* Setup FMOD */
    SetupSound();
    
    /* Setup game timer */
    SetupTimers();
    /* Seed random number */
    srand(time(NULL));
}
