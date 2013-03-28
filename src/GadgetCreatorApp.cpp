#include "GadgetCreatorApp.h"

#include "PackedTexture.h"

#include "cinder/ImageIO.h"

using namespace ci;
using namespace ci::app;

using namespace std;

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void BasicApp::setup()
{
	m_Texture = loadImage(loadAsset("Atlas1.png"));
	setWindowSize(1024, 768);
	
	CSpriteManager::Init("Atlas1.xml", 0);
}

//--------------------------------------------------------------------------------------------------
void BasicApp::keyDown(KeyEvent e)
{
	switch(e.getCode())
	{
		case KeyEvent::KEY_ESCAPE:
			quit();
			break;
	}
}

//--------------------------------------------------------------------------------------------------
void DrawSprite(ci::Rectf rect, ESpriteType sprite_type)
{
	Rectf tex_rect = CSpriteManager::m_Rects[0][sprite_type];

	glEnableClientState( GL_VERTEX_ARRAY );
	GLfloat verts[8];
	glVertexPointer( 2, GL_FLOAT, 0, verts );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	GLfloat texCoords[8];
	glTexCoordPointer( 2, GL_FLOAT, 0, texCoords );
	
	verts[0*2+0] = rect.getX2(); texCoords[0*2+0] = tex_rect.getX2();
	verts[0*2+1] = rect.getY1(); texCoords[0*2+1] = tex_rect.getY1();
	verts[1*2+0] = rect.getX1(); texCoords[1*2+0] = tex_rect.getX1();
	verts[1*2+1] = rect.getY1(); texCoords[1*2+1] = tex_rect.getY1();
	verts[2*2+0] = rect.getX2(); texCoords[2*2+0] = tex_rect.getX2();
	verts[2*2+1] = rect.getY2(); texCoords[2*2+1] = tex_rect.getY2();
	verts[3*2+0] = rect.getX1(); texCoords[3*2+0] = tex_rect.getX1();
	verts[3*2+1] = rect.getY2(); texCoords[3*2+1] = tex_rect.getY2();
	
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
	
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );

}

//--------------------------------------------------------------------------------------------------
void BasicApp::draw()
{
	gl::setMatricesWindow(getWindowSize());
	gl::clear(ColorA::white());
	
	gl::enableAlphaBlending();
	
	gl::enable(GL_TEXTURE_2D);
	
	float w = getWindowWidth();
	float h = getWindowHeight();
	
	int i_w = (int)w;
	int i_h = (int)h;
	
	int sprite_w = 128;
	int sprite_h = 128;
	
	gl::color(ColorA(1,1,1,1));
	
	int sprite_type = 0;
	
	for(int y=0; y<i_h; y+=sprite_h)
	{
		for(int x=0; x<i_w; x+=sprite_w)
		{
			int scaled_w	= sprite_w;
			int scaled_h	= sprite_h;
			
			if(CSpriteManager::m_Horizontal[0][sprite_type])
			{
				scaled_h /= CSpriteManager::HeightToWidth[0][sprite_type];
			}
			else
			{
				scaled_w /= CSpriteManager::WidthToHeight[0][sprite_type];
			}

			Rectf rect(x, y, x+scaled_w, y+scaled_h);
			DrawSprite(rect, (ESpriteType)sprite_type++);
		}
	}
	
}

// This line tells Flint to actually create the application
CINDER_APP_BASIC( BasicApp, RendererGl )