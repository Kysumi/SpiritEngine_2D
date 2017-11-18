#include "stdafx.h"
#include "Renderable.h"
#include "RenderManager.h"

namespace se
{
	namespace Rendering
	{

		Renderable::Renderable()
		{
            g_RenderManager.RegisterRenderable(this);
		}


		Renderable::~Renderable()
		{
		}
	}
}
