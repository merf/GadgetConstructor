#ifndef OpenGLUIKit_PackedTexture_h
#define OpenGLUIKit_PackedTexture_h

#include "cinder/vector.h"
#include "cinder/Rect.h"

enum ESpriteType
{
	ES_BAR_XXL,
	ES_BAR_XL,
	ES_BAR_L,
	ES_BAR_M,
	ES_BAR_S,
	ES_COG_L,
	ES_COG_M,
	ES_COG_S,
	ES_DRUM_STICK_HAND,
	ES_FOOT,
	ES_HAT_BOTTOM,
	ES_HAT_TOP,
	ES_KICK_DRUM,
	ES_KICK_DRUM_BEATER,
	ES_KICK_DRUM_PEDAL,
	ES_PULLEY,
	ES_RECORD,
	ES_SCRATCH_HAND,
	ES_SCREW,
	ES_SNARE_DRUM,
	ES_TURNTABLE,
	ES_TURNTABLE_ARM,
	ES_KNOT,
	ES_KNOT2,
	NUM_SPRITE_TYPES
};

struct CSpriteManager
{
	static const int		NUM_ATLASES = 3;
	
	static int				m_CurrAtlas;
	
	static void				Init(const std::string& file_name, int atlas_i);
	static std::string		m_Names[NUM_SPRITE_TYPES];
	static ci::Vec2f		m_Coords[NUM_ATLASES][NUM_SPRITE_TYPES][4];
	static ci::Rectf		m_Rects[NUM_ATLASES][NUM_SPRITE_TYPES];
	static bool				m_Horizontal[NUM_ATLASES][NUM_SPRITE_TYPES];
	static float			WidthToHeight[NUM_ATLASES][NUM_SPRITE_TYPES];
	static float			HeightToWidth[NUM_ATLASES][NUM_SPRITE_TYPES];
};

#endif
