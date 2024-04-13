#include <platform.h>

#ifdef __cplusplus
extern "C" {
#endif

void fontmgrInit();
void fontmgrTexSetup();
void FontDrawStart();
void FontDrawStart_alpha(u8 alpha);
void FontDrawEdge();
void FontDrawEdgeOff();
void FontDrawRainbowColor();
void FontDrawRainbowColorOff();
void FontDrawNoise();
void FontDrawNoiseOff();
void FontDrawColorIDX(u32 idx);
void FontDrawColor(u8 color[4]);
void FontDrawColor_();
u32 FontGetDrawColor();
void FontDrawScale(float scale);
void FontDrawScaleVec(float scale[3]);
void FontDrawCode(float x, float y, u16 code);
void FontDrawCodeMtx(float matrix[3][4], u16 code);
void FontDrawString(float x, float y, const char *text);
void FontDrawStringPitch(float x, float y, float pitch, const char *text);
void FontDrawStringVecPitch(float position[3], float pitch, const char *text);
void FontDrawStringMtx(float matrix[3][4], const char *text);
void FontDrawStringCenterMtx(float matrix[3][4], const char *text);
void FontDrawStringShake(float x, float y, const char *text);
void FontDrawMessage(int x, int y, const char *message);
void FontDrawMessageMtx(float matrix[3][4], const char *message);
u16 FontGetMessageWidthLine(const char *message, u16 *outLines);
u16 FontGetMessageWidth(const char *message);

u16 hankakuSearch(u8 code);
u16 kanjiSearch(u16 code);
u8 kanjiGetWidth(u16 code);
u32 HSV2RGB(u8 hsv[3]);

void JUTFontSetup(u32 index);
u16 JUTFont_CodeToGlyph(u16 code);
void JUTFont_DrawStart(u8 color[4]);
u8 _JUTFont_DrawPos(u16 glyph, s16 x, s16 y);

#ifdef __cplusplus
}
#endif
