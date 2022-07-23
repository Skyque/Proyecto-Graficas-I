////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "openglclass.h"
#include "cameraclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "Terreno.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "Modelos.h"
#include "Water.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(OpenGLClass*, HWND);
	void Shutdown();
	bool Frame();
	float angx, angy, angz, vel;

private:
	bool Render(float);

private:
	float desplazamiento = 0;
	float AlturaAgua = 3;
	bool Ida = true;
	bool Chocando = false;
	float ChoqueX = 0, ChoqueZ = 0, Radio;
	float PosicionesArbol[13][2] = { {25, 110}, {-146,21}, {9,155} ,{-12,153}, {-16,154}, {-103,101},
		{-102,124},{-106,45},{-119.5,-17},{-65.5,-18}, {-84,-99}, {-31,-90}, {-1.5,-48} }; //, {-68,-36},{-71,-27},{-1.5,-48}, {-146,21}, {38,104},{-5,99},{-58,126},{-170,52} ,{-41.6,156},{2.6,172},
	float PosicionesFlores[10][2] = { {7.6,23.6},{-59,-83},{75,40.6},{-20,-2},{-86.6,-38.5}, {-46,123},{-29,80},{-103,116},{-163,147},{-154.6,127} };
	float PosicionesFlores2[10][2] = { {52.5,43},{72.5,30},{39,-7},{-13,6},{8,121.5},{-9,168},{-106,75},{-124,98},{-172,65},{-142,58} };
	float PosicionesFlores3[8][3] = { {-52,49.5},{-31,52},{-5,93},{94.5,64},{91,98},{-20,-46},{18,-40},{-88,-69.5} };
	float PosicionesPozo[3][2] = { {-83,168},{81.5,121.5},{70,-107} };
	float PosicionesRocas[8][2] = { {-158,39},{-64,-29},{28,155},{-6.7,55.6}, {-194,-99},{101,-27},{-40,230},{-230,30} };
	float PosicionesBarril[3][2] = { {-83,157.6},{36.5,10.5},{-72.7,18} };
	OpenGLClass* m_OpenGL;
	CameraClass* m_Camera;	
	Terreno* terreno;
	Modelos* Agua;
	SkyDome* sky;
	Billboard* billArbol[13];
	Billboard* billMontaña1;
	Billboard* billMontaña2;
	Billboard* billMontaña3;
	Billboard* billMontaña4;
	Billboard* billMontaña5;
	Billboard* billMontaña6;
	Billboard* billMontaña7;
	Billboard* billMontaña8;
	Billboard* billFlores[10];
	Billboard* billFlores2[10];
	Billboard* billFlores3[8];
	Billboard* billPozo[3];
	Modelos* Casa1;
	Modelos* Casa2;
	Modelos* Casa3;
	Modelos* Casa4;
	Modelos* Casa5;
	Modelos* Casa6;
	Modelos* Rocas[8];
	Modelos* Barril[3];
	LightShaderClass* m_LightShader;
	LightShaderClass* m_AguaShader;
	LightShaderClass* m_LightShaderSky;
	LightShaderClass* m_BillArbolShader[16];
	LightShaderClass* m_BillMontaña1Shader;
	LightShaderClass* m_BillMontaña2Shader;
	LightShaderClass* m_BillMontaña3Shader;
	LightShaderClass* m_BillMontaña4Shader;
	LightShaderClass* m_BillMontaña5Shader;
	LightShaderClass* m_BillMontaña6Shader;
	LightShaderClass* m_BillMontaña7Shader;
	LightShaderClass* m_BillMontaña8Shader;
	LightShaderClass* m_BillFloresShader[10];
	LightShaderClass* m_BillFlores2Shader[10];
	LightShaderClass* m_BillFlores3Shader[8];
	LightShaderClass* m_BillPozoShader[3];
	LightShaderClass* m_ModeloShader;
	LightShaderClass* m_Casa2Shader;
	LightShaderClass* m_Casa3Shader;
	LightShaderClass* m_Casa4Shader;
	LightShaderClass* m_Casa5Shader;
	LightShaderClass* m_Casa6Shader;
	LightShaderClass* m_RocasShader[8];
	LightShaderClass* m_BarrilShader[3];
	LightClass* m_Light;
};

#endif