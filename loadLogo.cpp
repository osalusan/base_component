#include "loadLogo.h"

void LoadLogo::Update()
{
	Polygon2D::Update();
	m_TransForm->m_Rotation.z++;
}
