#include <iostream>

#include "cinder/Xml.h"

//#include "../rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

#include "PackedTexture.h"

#include "cinder/app/AppBasic.h"

std::string CSpriteManager::m_Names[NUM_SPRITE_TYPES] =
{
	"bar_xxl",
	"bar_xl",
	"bar_l",
	"bar_m",
	"bar_s",
	"cog_l",
	"cog_m",
	"cog_s",
	"drum_stick_hand",
	"foot",
	"hat_bottom",
	"hat_top",
	"kick_drum",
	"kick_drum_beater",
	"kick_pedal",
	"pulley",
	"record",
	"scratch_hand",
	"screw",
	"snare_drum",
	"turntable",
	"turntable_arm",
	"knot",
	"knot2"
};

ci::Vec2f CSpriteManager::m_Coords[NUM_ATLASES][NUM_SPRITE_TYPES][4];
ci::Rectf CSpriteManager::m_Rects[NUM_ATLASES][NUM_SPRITE_TYPES];
bool CSpriteManager::m_Horizontal[NUM_ATLASES][NUM_SPRITE_TYPES];
float CSpriteManager::WidthToHeight[NUM_ATLASES][NUM_SPRITE_TYPES];
float CSpriteManager::HeightToWidth[NUM_ATLASES][NUM_SPRITE_TYPES];

int CSpriteManager::m_CurrAtlas = 0;

void CSpriteManager::Init(const std::string& file_name, int atlas_i)
{
	std::string asset_path = ci::app::getAssetPath("/").generic_string();

	std::string filename;
	
	ci::XmlTree xml(ci::loadFile(asset_path + file_name));
	
	ci::XmlTree atlas_xml = xml.getChild("TextureAtlas");
	
	float tex_w = atlas_xml.getAttribute("width").getValue<float>();
	float tex_h = atlas_xml.getAttribute("height").getValue<float>();
	

	ci::app::console() << "width = " << tex_w;
	ci::app::console() << "height = " << tex_h;

	for(auto it = atlas_xml.begin(); it != atlas_xml.end(); ++it)
	{
		std::string name = it->getAttribute("n").getValue<std::string>();
		
		int x = it->getAttribute("x").getValue<int>();
		int y = it->getAttribute("y").getValue<int>();
		int w = it->getAttribute("w").getValue<int>();
		int h = it->getAttribute("h").getValue<int>();

		float l = x / tex_w;
		float r = (x+w) / tex_w;
		float t = y / tex_h;
		float b = (y+h) / tex_h;
		
		bool found = false;
		
		//find the slot for this guy...
		for(int i=0; i<NUM_SPRITE_TYPES; ++i)
		{
			if(name == m_Names[i])
			{
				m_Coords[atlas_i][i][0] = ci::Vec2f(l, t);
				m_Coords[atlas_i][i][1] = ci::Vec2f(l, b);
				m_Coords[atlas_i][i][2] = ci::Vec2f(r, t);
				m_Coords[atlas_i][i][3] = ci::Vec2f(r, b);
				
				m_Rects[atlas_i][i] = ci::Rectf(l,t,r,b);
				
				WidthToHeight[atlas_i][i] = h/(float)w;
				HeightToWidth[atlas_i][i] = w/(float)h;
				
				m_Horizontal[atlas_i][i] = w > h;
				
				found = true;
				
				break;
			}
		}
		
		if(!found)
		{
			ci::app::console() << "Missing sprite entry - " << name << std::endl;
		}
	}
}
