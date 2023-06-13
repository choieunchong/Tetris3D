//#include "LightClass.h"
//
//
//LightClass::LightClass()
//{
//}
//
//
//LightClass::LightClass(const LightClass& other)
//{
//}
//
//
//LightClass::~LightClass()
//{
//}
//
//void LightClass::SetType(D3DLIGHTTYPE type)
//{
//	m_light.Type = type;
//}
//
//void LightClass::SetDiffuseColor(const D3DXCOLOR& color)
//{
//	m_light.Diffuse = color;
//}
//
//void LightClass::SetDirection(const D3DXVECTOR3& direction)
//{
//	D3DXVec3Normalize(&m_light.Direction, &direction);
//}
//
//void LightClass::Enable(bool enable)
//{
//	m_enabled = enable;
//}
//
//void LightClass::Apply(IDirect3DDevice9* device, DWORD index) const
//{
//	device->SetLight(index, &m_light);
//	device->LightEnable(index, m_enabled);
//}
