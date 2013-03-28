//
//  GadgetCreatorApp.h
//  basicApp
//
//  Created by Neil Wallace on 26/03/2013.
//
//

#ifndef basicApp_GadgetCreatorApp_h
#define basicApp_GadgetCreatorApp_h

#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Vbo.h"

//**************************************************************************************************
class BasicApp : public cinder::app::AppBasic
{
public:
	void				setup();
	void				draw();
	
	void				keyDown(cinder::app::KeyEvent e);
	
	ci::gl::Texture		m_Texture;
	ci::gl::VboMesh		m_VBO;
};



#endif
