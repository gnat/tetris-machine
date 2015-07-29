#ifndef _DRAWING_H_
#define _DRAWING_H_

extern void EnableOrtho2D();
extern void DisableOrtho2D();
extern void Draw2DTexture(float _x, float _y, TEXTURE* _tex);
extern void Draw2DTextureEx(float _x, float _y, float _z, float _alpha,  TEXTURE* _tex);
extern void Draw2DNumberFromRight(float _x, float _y, TEXTURE* _tex, int _char_width, int _char_height, int _number);
extern void Draw2DNumberFromRightEx(float _x, float _y, float _z, float _alpha, TEXTURE* _tex, int _char_width, int _char_height, int _number);
extern void DrawBlockStationary(float _x, float _y, float _r, float _g, float _b);
extern void DrawBlockMoving(float _x, float _y, float _r, float _g, float _b);
extern void DrawBlockBackground(float _x, float _y, float _r, float _g, float _b);
extern void Drawing();

#endif
