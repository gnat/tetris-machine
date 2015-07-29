#include "master.h"

/**
* EnableOrtho2D. Pushes older projection and modelview matrices onto the stack, creates new projection matrix as ortho mode. (For 2D)
*/
void EnableOrtho2D() 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    
	glOrtho(0, width, height, 0, -10, 10);

    glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 2, 0, 2, 0, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	/* .. you want to resume in modelview mode, so do it last. */

	/* Make sure the rest of the program knows by setting a state. */
    rendering_ortho = true;
}

/**
* DisableOrtho2D. Pops ortho mode from the matrix stack, returning the projection and modelview matrixes to their former selves.
*/
void DisableOrtho2D() 
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	/* .. you want to resume in modelview mode, so do it last. */
	
	/* Make sure the rest of the program knows by setting a state. */
    rendering_ortho = false;
}

/**
* CleanObject. Clean up OpenGL state for next drawing.
*/
void CleanObject() 
{
    glLoadIdentity();
    glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f ); /* Reset color. */	
    glBindTexture ( GL_TEXTURE_2D, NULL ); /* Reset texture. */
    glTranslatef( 0.0f, 0.0f, 0.0f);
    
    /* Apply camera rotations if ortho mode is off. */
    if(!rendering_ortho)
    {
        gluLookAt(
    		0.0f, -14.5f, -14.0f,
    		0.0f, -10.4f, 3.0f,
    		0.0f, 1.0f, 0.0f);
    }
}

/**
* Draw2DTextureEx. Expanded 2D drawing.
* @param X Coordinate.
* @param Y Coordinate.
* @param Z Coordinate.
* @param Alpha value.
* @param Pointer to TEXTURE to draw.
*/
void Draw2DTextureEx(float _x, float _y, float _z, float _alpha,  TEXTURE* _tex) 
{
    /* Only use when currently rendering in ortho projection matrix. */
    if(rendering_ortho)
    {
        /* Temporarily disable lighting. */
        glDisable(GL_LIGHTING);
        
        CleanObject();
        glTranslatef(_x, _y, _z);
        glScalef(_tex->width, _tex->height, 1.0f); /* Blow up quad to texture size. */
        glBindTexture(GL_TEXTURE_2D, _tex->id);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); /* Do proper blending with alpha channel. */
        glColor4f ( 1.0f, 1.0f, 1.0f, _alpha );
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            /* Top left. */
            glTexCoord2f(0, 0);
            glVertex2f(0, 0);
            
            /* Bottom left. */
            glTexCoord2f(0, 1);
            glVertex2f(0, 1);
    
            /* Bottom right.*/
            glTexCoord2f(1, 1);
            glVertex2f(1, 1);
            
            /* Top right. */
            glTexCoord2f(1, 0);
            glVertex2f(1, 0);
        glEnd();  
        glDisable(GL_TEXTURE_2D);
        
        glEnable(GL_LIGHTING);
    }
}

/**
* Draw2DTexture. 2D drawing.
* @param X Coordinate.
* @param Y Coordinate.
* @param Pointer to TEXTURE to draw.
*/
void Draw2DTexture(float _x, float _y, TEXTURE* _tex) 
{
    Draw2DTextureEx(_x, _y, -10.0f, 1.0f, _tex);
}

/**
* Draw2DNumberFromRightEx. 2D drawing of basic text.
* @param X Coordinate.
* @param Y Coordinate.
* @param Z Coordinate.
* @param Alpha value.
* @param Pointer to TEXTURE to draw.
* @param Width of character.
* @param Height of character.
* @param Character to draw.
*/
void Draw2DNumberFromRightEx(float _x, float _y, float _z, float _alpha, TEXTURE* _tex, int _char_width, int _char_height, int _number) 
{
    char buffer[BUFFER_MAX];
    sprintf(buffer, "%d", _number);
    
    /* Only use when currently rendering in ortho projection matrix. */
    if(rendering_ortho)
    {
        /* Temporarily disable lighting. */
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);

        int current_char_x;
        int right_offset = _char_width * strlen(buffer); /* Find the right offset for Drawing from the right */
        
        /* Draw your numbers. */
        int i;
        for(i = 0; i < strlen(buffer); i+=1)
        {  
            switch(buffer[i])
            {
                case '0':
                    current_char_x = 9 * _char_width;
                break;
                case '1':
                    current_char_x = 0 * _char_width;
                break;
                case '2':
                    current_char_x = 1 * _char_width;
                break;
                case '3':
                    current_char_x = 2 * _char_width;
                break;
                case '4':
                    current_char_x = 3 * _char_width;
                break;
                case '5':
                    current_char_x = 4 * _char_width;
                break;
                case '6':
                    current_char_x = 5 * _char_width;
                break;
                case '7':
                    current_char_x = 6 * _char_width;
                break;
                case '8':
                    current_char_x = 7 * _char_width;
                break;
                case '9':
                    current_char_x = 8 * _char_width;
                break;
            }

            CleanObject();
            glTranslatef(_x+(i*_char_width)-right_offset, _y, _z);
            glScalef(_char_width, _char_height, 1.0f); /* Blow up quad to texture size. */
            glBindTexture(GL_TEXTURE_2D, _tex->id);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
            glColor4f ( 1.0f, 1.0f, 1.0f, _alpha );
            
            glBegin(GL_QUADS);
                /* Top left. */
                glTexCoord2f((float)current_char_x/_tex->width, 0);
                glVertex2f(0, 0);
                
                /* Bottom left. */
                glTexCoord2f((float)current_char_x/_tex->width, 1);
                glVertex2f(0, 1);
                
                /* Bottom right. */
                glTexCoord2f((float)(current_char_x+_char_width)/_tex->width, 1);
                glVertex2f(1, 1);
                
                /* Top right. */
                glTexCoord2f((float)(current_char_x+_char_width)/_tex->width, 0);
                glVertex2f(1, 0);
            glEnd();  
        }

        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
    }
}

/**
* Draw2DNumberFromRight. 2D drawing of basic text.
* @param X Coordinate.
* @param Y Coordinate.
* @param Pointer to TEXTURE to draw.
* @param Width of character.
* @param Height of character.
* @param Character to draw.
*/
void Draw2DNumberFromRight(float _x, float _y, TEXTURE* _tex, int _char_width, int _char_height, int _number) 
{
    Draw2DNumberFromRightEx(_x, _y, -10.0f, 1.0f, _tex, _char_width, _char_height, _number);
}

/**
* DrawBlockStationary. Draw tetris block which is stationary.
* @param X Coordinate.
* @param Y Coordinate.
* @param Red value.
* @param Green value.
* @param Blue value.
*/
void DrawBlockStationary(float _x, float _y, float _r, float _g, float _b)
{
    /* Draw outline. */
    CleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 0.8);
    glColor4f ( 0.0f, 0.0f, 0.0f, 1.0f );
    glutSolidCube(1.0);

    /* Fill in the creamy center. */
    CleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 1.4);
    glColor4f( _r, _g, _b, 1.0f );
    glutSolidCube(.90);                                         
}

/**
* DrawBlockMoving. Draw tetris block which is currently moving.
* @param X Coordinate.
* @param Y Coordinate.
* @param Red value.
* @param Green value.
* @param Blue value.
*/
void DrawBlockMoving(float _x, float _y, float _r, float _g, float _b)
{ 
    /* Draw outline. */
    CleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 0.8);
    glColor4f ( 0.15f, 0.15f, 0.15f, 1.0f );
    glutSolidCube(1.0);

    /* Fill in the creamy center. */
    CleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 1.0);
    glColor4f( _r, _g, _b, 1.0f );
    glutSolidCube(.90);                                
}

/**
* DrawBlockBackground. Draw background geometry.
* @param X Coordinate.
* @param Y Coordinate.
* @param Red value.
* @param Green value.
* @param Blue value.
*/
void DrawBlockBackground(float _x, float _y, float _r, float _g, float _b)
{ 
    CleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 1);
    glColor4f ( _r, _g, _b, 1.0f );
    glutSolidCube(0.95);                               
}

/**
* Call the current Screen's Drawing function.
*/
void Drawing()
{
    switch(screen_current)
    {
        case SCREEN_GAMEPLAY:
            ScreenGameplayDrawing();
        break;
    }

    glFlush(); /* Make sure OpenGL has finished for this frame. */
    SDL_GL_SwapBuffers(); /* Put it on the screen. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* Clear screen. */
}
