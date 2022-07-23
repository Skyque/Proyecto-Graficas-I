////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#define PI 3.1416

GraphicsClass::GraphicsClass()
{
	m_OpenGL = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_LightShaderSky = 0;
	for (int i = 0; i <= 15; i++) {
		m_BillArbolShader[i] = 0;
	}
	m_Light = 0;
	angx = angy = angz = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(OpenGLClass* OpenGL, HWND hwnd)
{
	bool result;


	// Store a pointer to the OpenGL class object.
	m_OpenGL = OpenGL;

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(-15.0f, 15.0f, 0.0f);

	terreno = new Terreno(hwnd, m_OpenGL, L"Imagenes//Altura6.png", L"Imagenes//Tierra_color.jpg", L"Imagenes//Tierra_normal.png", L"Imagenes//Zacate2_color.jpg", L"Imagenes//Zacate2_normal.png",
		L"Imagenes//Camino_color.jpg", L"Imagenes//Camino_normal.png", L"Imagenes//Blend_map3.png", (float)620, (float)620, 0, 1, 2, 3, 4, 5, 6);

	Agua = new Modelos(hwnd, m_OpenGL, "Modelos//Agua//Agua.obj", L"Imagenes//Agua2.jpg", L"Imagenes//Agua2_Normal.png", L"Imagenes//Agua2_Altura.png", 20, 177, 7, 0, 40, 41, 42);
	// Create the light shader object.

	m_LightShader = new LightShaderClass((char*)"light.vs", (char*)"light.ps");
	if(!m_LightShader)
	{
		return false;
	}

	m_AguaShader = new LightShaderClass((char*)"Agua.vs", (char*)"Agua.ps");
	if (!m_AguaShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_OpenGL, hwnd);
	if(!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	// Initialize the light shader object.
	result = m_AguaShader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-5.0f, 0.5f, -1.0f);

	sky = new SkyDome(hwnd, m_OpenGL, 32, 32, 420, L"Imagenes//Cielo.jpg", L"Imagenes//Tarde.jpg", L"Imagenes//Noche.jpg", 8, 43, 44);
	// Create the light shader object.
	m_LightShaderSky = new LightShaderClass((char*)"Sky.vs", (char*)"Sky.ps");
	if (!m_LightShaderSky)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShaderSky->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	for (int i = 0; i <= 12; i++) {
		billArbol[i] = new Billboard(hwnd, m_OpenGL, L"Imagenes//Arbol.png", L"Imagenes//ArbolNormal.png", 10 + rand() % 12, 9 + rand() % 11, PosicionesArbol[i][0], PosicionesArbol[i][1], 9, 13);
		// Create the light shader object.
		m_BillArbolShader[i] = new LightShaderClass((char*)"Bill.vs", (char*)"Bill.ps");
		if (!m_BillArbolShader[i])
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillArbolShader[i]->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	for (int i = 0; i <= 9; i++) {
		billFlores[i] = new Billboard(hwnd, m_OpenGL, L"Imagenes//Flores1.jpg", L"Imagenes//Flores1_Normal.png", 3 + rand() % 5, 3 + rand() % 4, PosicionesFlores[i][0], PosicionesFlores[i][1], 26, 27);
		// Create the light shader object.
		m_BillFloresShader[i] = new LightShaderClass((char*)"Flores.vs", (char*)"Flores.ps");
		if (!m_BillFloresShader[i])
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillFloresShader[i]->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	for (int i = 0; i <= 9; i++) {
		billFlores2[i] = new Billboard(hwnd, m_OpenGL, L"Imagenes//Flores2.png", L"Imagenes//Flores2_Normal.png", 3 + rand() % 7, 2 + rand() % 6, PosicionesFlores2[i][0], PosicionesFlores2[i][1], 28, 29);
		// Create the light shader object.
		m_BillFlores2Shader[i] = new LightShaderClass((char*)"Flores2.vs", (char*)"Flores2.ps");
		if (!m_BillFlores2Shader[i])
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillFlores2Shader[i]->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	for (int i = 0; i <= 7; i++) {
		billFlores3[i] = new Billboard(hwnd, m_OpenGL, L"Imagenes//Flores3.png", L"Imagenes//Flores3_Normal.png", 5 + rand() % 7, 13, PosicionesFlores3[i][0], PosicionesFlores3[i][1], 30, 31);
		// Create the light shader object.
		m_BillFlores3Shader[i] = new LightShaderClass((char*)"Flores3.vs", (char*)"Flores3.ps");
		if (!m_BillFlores3Shader[i])
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillFlores3Shader[i]->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	for (int i = 0; i <= 2; i++) {
		billPozo[i] = new Billboard(hwnd, m_OpenGL, L"Imagenes//Pozo.png", L"Imagenes//Pozo_Normal.png", 5 + rand() % 6, 5 + rand() % 7, PosicionesPozo[i][0], PosicionesPozo[i][1], 32, 33);
		// Create the light shader object.
		m_BillPozoShader[i] = new LightShaderClass((char*)"Pozo.vs", (char*)"Pozo.ps");
		if (!m_BillPozoShader[i])
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillPozoShader[i]->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	billMontaña1 = new Billboard(hwnd, m_OpenGL, L"Imagenes//Montañas3.jpg", L"Imagenes//Montañas3_Normal.png", 1500, 350, 0, 500, 20, 21);
	// Create the light shader object.
	m_BillMontaña1Shader = new LightShaderClass((char*)"Montañas1.vs", (char*)"Montañas1.ps");

	billMontaña2 = new Billboard(hwnd, m_OpenGL, L"Imagenes//Montañas3.jpg", L"Imagenes//Montañas3_Normal.png", 1500, 200, -500, 0, 22, 23);
	// Create the light shader object.
	m_BillMontaña2Shader = new LightShaderClass((char*)"Montañas2.vs", (char*)"Montañas2.ps");

	billMontaña3 = new Billboard(hwnd, m_OpenGL, L"Imagenes//Montañas5.jpg", L"Imagenes//Montañas5_Normal.png", 1500, 150, 500, 0, 24, 25);
	// Create the light shader object.
	m_BillMontaña3Shader = new LightShaderClass((char*)"Montañas3.vs", (char*)"Montañas3.ps");

	billMontaña4 = new Billboard(hwnd, m_OpenGL, L"Imagenes//Montañas3.jpg", L"Imagenes//Montañas3_Normal.png", 1300, 250, 0, -500, 20, 21);
	// Create the light shader object.
	m_BillMontaña4Shader = new LightShaderClass((char*)"Montañas1.vs", (char*)"Montañas1.ps");

	billMontaña5 = new Billboard(hwnd, m_OpenGL, L"Imagenes//Montañas5.jpg", L"Imagenes//Montañas5_Normal.png", 350, 200, 380, 380, 24, 25);
	// Create the light shader object.
	m_BillMontaña5Shader = new LightShaderClass((char*)"Montañas3.vs", (char*)"Montañas3.ps");

	billMontaña6 = new Billboard(hwnd, m_OpenGL, L"Imagenes//Montañas5.jpg", L"Imagenes//Montañas5_Normal.png", 430, 180, -380, 380, 24, 25);
	// Create the light shader object.
	m_BillMontaña6Shader = new LightShaderClass((char*)"Montañas3.vs", (char*)"Montañas3.ps");

	billMontaña7 = new Billboard(hwnd, m_OpenGL, L"Imagenes//Montañas5.jpg", L"Imagenes//Montañas5_Normal.png", 340, 210, -380, -380, 20, 21);
	// Create the light shader object.
	m_BillMontaña7Shader = new LightShaderClass((char*)"Montañas3.vs", (char*)"Montañas3.ps");

	billMontaña8 = new Billboard(hwnd, m_OpenGL, L"Imagenes//Montañas5.jpg", L"Imagenes//Montañas5_Normal.png", 300, 255, 380, -380, 20, 21);
	// Create the light shader object.
	m_BillMontaña8Shader = new LightShaderClass((char*)"Montañas3.vs", (char*)"Montañas3.ps");

	if (!m_BillMontaña1Shader)
	{
		return false;
	}

	if (!m_BillMontaña2Shader)
	{
		return false;
	}

	if (!m_BillMontaña3Shader)
	{
		return false;
	}

	if (!m_BillMontaña4Shader)
	{
		return false;
	}

	if (!m_BillMontaña5Shader)
	{
		return false;
	}

	if (!m_BillMontaña6Shader)
	{
		return false;
	}

	if (!m_BillMontaña7Shader)
	{
		return false;
	}

	if (!m_BillMontaña8Shader)
	{
		return false;
	}


	// Initialize the light shader object.
	result = m_BillMontaña1Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_BillMontaña2Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_BillMontaña3Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_BillMontaña4Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_BillMontaña5Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_BillMontaña6Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_BillMontaña7Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_BillMontaña8Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}


	Casa1 = new Modelos(hwnd, m_OpenGL, "Modelos//Casa1//Casa1.obj", L"Modelos//Casa1//House_01.png", L"Modelos//Casa1//Casa1_Normal.png", L"Modelos//Casa1//Casa1_Especular.png", 1.2, -88, 7, 16,
		10, 11, 12);

	Casa2 = new Modelos(hwnd, m_OpenGL, "Modelos//Casa2//Casa2.obj", L"Modelos//Casa2//House_02.png", L"Modelos//Casa2//Casa2_Normal.png", L"Modelos//Casa2//Casa2_Especular.png", 1.3, 15, 2, 18,
		14, 15, 16);

	Casa3 = new Modelos(hwnd, m_OpenGL, "Modelos//Casa3//Casa3.obj", L"Modelos//Casa3//House_03.png", L"Modelos//Casa3//Casa3_Normal.png", L"Modelos//Casa3//Casa3_Especular.png", 1.0, -30, 124, 18,
		17, 18, 19);

	Casa4 = new Modelos(hwnd, m_OpenGL, "Modelos//Casa3//Casa3.obj", L"Modelos//Casa3//House_03.png", L"Modelos//Casa3//Casa3_Normal.png", L"Modelos//Casa3//Casa3_Especular.png", .85, -60, -70, 18,
		17, 18, 19);

	Casa5 = new Modelos(hwnd, m_OpenGL, "Modelos//Casa1//Casa1.obj", L"Modelos//Casa1//House_01.png", L"Modelos//Casa1//Casa1_Normal.png", L"Modelos//Casa1//Casa1_Especular.png", .85, 89, 37, 16,
		10, 11, 12);

	Casa6 = new Modelos(hwnd, m_OpenGL, "Modelos//Casa2//Casa2.obj", L"Modelos//Casa2//House_02.png", L"Modelos//Casa2//Casa2_Normal.png", L"Modelos//Casa2//Casa2_Especular.png", .9, -130, 117, 18,
		14, 15, 16);

	Rocas[0] = new Modelos(hwnd, m_OpenGL, "Modelos//Rocas//Roca1.obj", L"Modelos//Rocas//Rock_01.png", L"Modelos//Rocas//Roca_Normal.png", L"Modelos//Rocas//Roca_Especular.png", 1 + rand() % 2, PosicionesRocas[0][0], PosicionesRocas[0][1], 4,
		34, 35, 36);

	Rocas[1] = new Modelos(hwnd, m_OpenGL, "Modelos//Rocas//Roca2.obj", L"Modelos//Rocas//Rock_01.png", L"Modelos//Rocas//Roca_Normal.png", L"Modelos//Rocas//Roca_Especular.png", 1 + rand() % 2, PosicionesRocas[1][0], PosicionesRocas[1][1], 4,
		34, 35, 36);

	Rocas[2] = new Modelos(hwnd, m_OpenGL, "Modelos//Rocas//Roca3.obj", L"Modelos//Rocas//Rock_01.png", L"Modelos//Rocas//Roca_Normal.png", L"Modelos//Rocas//Roca_Especular.png", 1 + rand() % 2, PosicionesRocas[2][0], PosicionesRocas[2][1], 4,
		34, 35, 36);

	Rocas[3] = new Modelos(hwnd, m_OpenGL, "Modelos//Rocas//Roca4.obj", L"Modelos//Rocas//Rock_01.png", L"Modelos//Rocas//Roca_Normal.png", L"Modelos//Rocas//Roca_Especular.png", 1 + rand() % 2, PosicionesRocas[3][0], PosicionesRocas[3][1], 7,
		34, 35, 36);

	Rocas[4] = new Modelos(hwnd, m_OpenGL, "Modelos//Rocas//Roca1.obj", L"Modelos//Rocas//Rock_01.png", L"Modelos//Rocas//Roca_Normal.png", L"Modelos//Rocas//Roca_Especular.png", 1 + rand() % 2, PosicionesRocas[4][0], PosicionesRocas[4][10], 4,
		34, 35, 36);

	Rocas[5] = new Modelos(hwnd, m_OpenGL, "Modelos//Rocas//Roca2.obj", L"Modelos//Rocas//Rock_01.png", L"Modelos//Rocas//Roca_Normal.png", L"Modelos//Rocas//Roca_Especular.png", 1 + rand() % 2, PosicionesRocas[5][0], PosicionesRocas[5][1], 4,
		34, 35, 36);

	Rocas[6] = new Modelos(hwnd, m_OpenGL, "Modelos//Rocas//Roca3.obj", L"Modelos//Rocas//Rock_01.png", L"Modelos//Rocas//Roca_Normal.png", L"Modelos//Rocas//Roca_Especular.png", 1 + rand() % 2, PosicionesRocas[6][0], PosicionesRocas[6][1], 4,
		34, 35, 36);

	Rocas[7] = new Modelos(hwnd, m_OpenGL, "Modelos//Rocas//Roca4.obj", L"Modelos//Rocas//Rock_01.png", L"Modelos//Rocas//Roca_Normal.png", L"Modelos//Rocas//Roca_Especular.png", 1 + rand() % 2, PosicionesRocas[7][0], PosicionesRocas[7][1], 7,
		34, 35, 36);

	for (int i = 0; i <= 7; i++) 
	{
		m_RocasShader[i] = new LightShaderClass((char*)"Rocas.vs", (char*)"Rocas.ps");
		if (!m_RocasShader)
		{
			return false;
		}

		result = m_RocasShader[i]->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	for (int i = 0; i <= 2; i++) {
		Barril[i]=new Modelos(hwnd, m_OpenGL, "Modelos//Barril//Barril.obj", L"Modelos//Barril//Barril.jpg", L"Modelos//Barril//Barril_Normal.png", L"Modelos//Barril//Barril_Especular.png", 1.0, PosicionesBarril[i][0], PosicionesBarril[i][1], 1,
			37, 38, 39);
		m_BarrilShader[i] = new LightShaderClass((char*)"Barril.vs", (char*)"Barril.ps");
		if (!m_BarrilShader)
		{
			return false;
		}

		result = m_BarrilShader[i]->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	m_ModeloShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	if (!m_ModeloShader)
	{
		return false;
	}

	m_Casa2Shader = new LightShaderClass((char*)"Casa2.vs", (char*)"Casa2.ps");
	if (!m_Casa2Shader)
	{
		return false;
	}

	m_Casa3Shader = new LightShaderClass((char*)"Casa3.vs", (char*)"Casa3.ps");
	if (!m_Casa3Shader)
	{
		return false;
	}

	m_Casa4Shader = new LightShaderClass((char*)"Casa3.vs", (char*)"Casa3.ps");
	if (!m_Casa4Shader)
	{
		return false;
	}

	m_Casa5Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	if (!m_Casa5Shader)
	{
		return false;
	}

	m_Casa6Shader = new LightShaderClass((char*)"Casa2.vs", (char*)"Casa2.ps");
	if (!m_Casa6Shader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_ModeloShader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_Casa2Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_Casa3Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_Casa4Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_Casa5Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	result = m_Casa6Shader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown(m_OpenGL);
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the light shader object.
	if (m_LightShaderSky)
	{
		m_LightShaderSky->Shutdown(m_OpenGL);
		delete m_LightShaderSky;
		m_LightShaderSky = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the terreno object.
	if (terreno)
	{
		delete terreno;
		m_Camera = 0;
	}

	// Release the pointer to the OpenGL class object.
	m_OpenGL = 0;

	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += 0.0174532925f * 2.0f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	float worldMatrix[16];
	float SkyMatrix[16];
	float viewMatrix[16];
	float projectionMatrix[16];
	float lightDirection[3];
	float diffuseLightColor[4];
	float TraslacionBill[16];
	float RotacionBill[16];
	float worldMatrixBill[16];
	float TraslacionModelos[16];
	float RotacionModelos[16];

	float TraslaciónAgua[16];
	float RotaciónAgua[16];


	// Clear the buffers to begin the scene.
	m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->SetRotation(angx, angy, angz);
	m_Camera->SetYPos(terreno->Superficie(m_Camera->GetXPos(), m_Camera->GetZPos()) + 3);
	m_Camera->Render(vel, Chocando, ChoqueX, ChoqueZ, Radio);
	Chocando = false;

	// Get the world, view, and projection matrices from the opengl and camera objects.
	m_OpenGL->GetWorldMatrix(worldMatrix);
	m_OpenGL->GetWorldMatrix(worldMatrixBill);
	m_Camera->GetViewMatrix(viewMatrix);
	m_OpenGL->GetProjectionMatrix(projectionMatrix);

	//////////////////////////////////////////////////////////
	//actualizar aqui el vector de luz y el color de la misma
	//////////////////////////////////////////////////////////

	// Get the light properties.
	m_Light->GetDirection(lightDirection);
	m_Light->GetDiffuseColor(diffuseLightColor);

	glDisable(GL_DEPTH_TEST);
	m_OpenGL->GetWorldMatrix(SkyMatrix);
	static float Angulo = 0;
	static int Factor = 0;
	static int AportacionAmbiental = 1;
	static int Fase = 1;
	Angulo += 0.00025;
	static int Hora = 0;
	Hora++;

	if (Fase == 1) {
		if (Hora > 1650) {
			static float Cambio = 0;
			Cambio += 0.005;
			if (Factor < 5000) {
				Factor = (sin(Cambio) + 1) * 5000;
			}
			if (AportacionAmbiental > 7000) {
				AportacionAmbiental -= 20;
			}
		}
		else {
			AportacionAmbiental = 10000;
		}
		if (Hora > 2000) {
			Factor = 0;
			Fase = 2;
		}
	}
	else if (Fase == 2) {
		if (Hora > 3650) {
			static float Cambio = 0;
			Cambio += 0.005;
			if (Factor < 5000) {
				Factor = (sin(Cambio) + 1) * 5000;
			}
			if (AportacionAmbiental > 2000) {
				AportacionAmbiental -= 25;
			}
		}
		else {
			AportacionAmbiental = 7000;
		}
		if (Hora > 4000) {
			Factor = 0;
			Fase = 3;
		}
	}
	else if (Fase == 3) {
		if (Hora > 5650) {
			static float Cambio = 0;
			Cambio += 0.005;
			if (Factor < 5000) {
				Factor = (sin(Cambio) + 1) * 5000;
			}
			if (AportacionAmbiental < 10000) {
				AportacionAmbiental += 35;
			}
		}
		else {
			AportacionAmbiental = 2000;
		}
		if (Hora > 6000) {
			Factor = 0;
			Fase = 1;
			Hora = 0;
		}
	}

	m_OpenGL->MatrixRotationY(SkyMatrix, Angulo);
	m_LightShaderSky->SetShader(m_OpenGL);
	m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", SkyMatrix);
	m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_LightShaderSky->Pon1Entero(m_OpenGL, (char*)"Manana", 8);
	m_LightShaderSky->Pon1Entero(m_OpenGL, (char*)"Tarde", 43);
	m_LightShaderSky->Pon1Entero(m_OpenGL, (char*)"Noche", 44);
	m_LightShaderSky->Pon1Entero(m_OpenGL, (char*)"Factor", Factor);
	m_LightShaderSky->Pon1Entero(m_OpenGL, (char*)"Fase", Fase);
	m_LightShaderSky->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_LightShaderSky->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_LightShaderSky->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	sky->Render(m_OpenGL);
	glEnable(GL_DEPTH_TEST);
	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//m_OpenGL->MatrixRotationY(worldMatrix, rotation);

	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	m_LightShader->SetShader(m_OpenGL);	
	m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrix);
	m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"TextCol1", 0);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"TextNorm1", 1);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"TextCol2", 2);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"TextNorm2", 3);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"TextCol3", 4);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"TextNorm3", 5);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"Blend", 6);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_LightShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_LightShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	terreno->Render(m_OpenGL);

	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	if (desplazamiento < Agua->getAlto() / 2 && Ida) {
		desplazamiento += .25;
		AlturaAgua += .002;
	}
	else {
		Ida = false;
		desplazamiento -= .25;
		AlturaAgua -= .002;
		if (desplazamiento <= 0) {
			Ida = true;
		}
	}
	m_AguaShader->SetShader(m_OpenGL);
	float modmatrix[16];
	m_OpenGL->GetWorldMatrix(modmatrix);
	m_OpenGL->MatrixTranslation(TraslacionModelos, Agua->x, terreno->Superficie(Agua->x, Agua->z) + AlturaAgua, Agua->z);
	m_OpenGL->MatrixRotationY(RotacionModelos, 0);
	m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
	m_AguaShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
	m_AguaShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_AguaShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_AguaShader->Pon1Entero(m_OpenGL, (char*)"AguaText", 40);
	m_AguaShader->Pon1Entero(m_OpenGL, (char*)"AguaNorm", 41);
	m_AguaShader->Pon1Entero(m_OpenGL, (char*)"AguaSpec", 42);
	m_AguaShader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_AguaShader->Pon1Entero(m_OpenGL, (char*)"Desplazamiento", desplazamiento);
	float campos[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	m_AguaShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	m_AguaShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_AguaShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	Agua->Render(m_OpenGL);

	for (int i = 0; i <= 12; i++) {
		//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
		//
		m_OpenGL->MatrixTranslation(TraslacionBill, billArbol[i]->x, terreno->Superficie(billArbol[i]->x, billArbol[i]->z), billArbol[i]->z);
		m_BillArbolShader[i]->SetShader(m_OpenGL);
		m_OpenGL->MatrixRotationY(RotacionBill, -90);
		float VectorVista[3];
		VectorVista[0] = m_Camera->GetXPos() - billArbol[i]->x;
		VectorVista[1] = 0;
		VectorVista[2] = m_Camera->GetZPos() - billArbol[i]->z;
		float Magnitud = sqrt(VectorVista[0] * VectorVista[0] + VectorVista[2] * VectorVista[2]);
		VectorVista[0] = VectorVista[0] / Magnitud;
		VectorVista[2] = VectorVista[2] / Magnitud;
		float Angulo = VectorVista[0] * 0 + VectorVista[2] * 1; //Producto punto = cos
		Angulo = acos(Angulo);
		if (billArbol[i]->x > m_Camera->GetXPos()) {
			m_OpenGL->MatrixRotationY(RotacionBill, -Angulo);
		}
		else {
			m_OpenGL->MatrixRotationY(RotacionBill, Angulo);
		}
		m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
		m_BillArbolShader[i]->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillArbolShader[i]->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillArbolShader[i]->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillArbolShader[i]->Pon1Entero(m_OpenGL, (char*)"BillArbolCol", 9);
		m_BillArbolShader[i]->Pon1Entero(m_OpenGL, (char*)"BillArbolNorm", 13);
		m_BillArbolShader[i]->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
		m_BillArbolShader[i]->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillArbolShader[i]->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billArbol[i]->Render(m_OpenGL);
	}

	for (int i = 0; i <= 9; i++) {
		//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
		//
		m_OpenGL->MatrixTranslation(TraslacionBill, billFlores[i]->x, terreno->Superficie(billFlores[i]->x, billFlores[i]->z) - 1, billFlores[i]->z);
		m_BillFloresShader[i]->SetShader(m_OpenGL);
		m_OpenGL->MatrixRotationY(RotacionBill, -90);
		float VectorVista[3];
		VectorVista[0] = m_Camera->GetXPos() - billFlores[i]->x;
		VectorVista[1] = 0;
		VectorVista[2] = m_Camera->GetZPos() - billFlores[i]->z;
		float Magnitud = sqrt(VectorVista[0] * VectorVista[0] + VectorVista[2] * VectorVista[2]);
		VectorVista[0] = VectorVista[0] / Magnitud;
		VectorVista[2] = VectorVista[2] / Magnitud;
		float Angulo = VectorVista[0] * 0 + VectorVista[2] * 1; //Producto punto = cos
		Angulo = acos(Angulo);
		if (billFlores[i]->x > m_Camera->GetXPos()) {
			m_OpenGL->MatrixRotationY(RotacionBill, -Angulo);
		}
		else {
			m_OpenGL->MatrixRotationY(RotacionBill, Angulo);
		}
		m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
		m_BillFloresShader[i]->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillFloresShader[i]->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillFloresShader[i]->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillFloresShader[i]->Pon1Entero(m_OpenGL, (char*)"BillFloresCol", 26);
		m_BillFloresShader[i]->Pon1Entero(m_OpenGL, (char*)"BillFloresNorm", 27);
		m_BillFloresShader[i]->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
		m_BillFloresShader[i]->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillFloresShader[i]->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billFlores[i]->Render(m_OpenGL);
	}

	for (int i = 0; i <= 9; i++) {
		//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
		//
		m_OpenGL->MatrixTranslation(TraslacionBill, billFlores2[i]->x, terreno->Superficie(billFlores2[i]->x, billFlores2[i]->z) - 1.65, billFlores2[i]->z);
		m_BillFlores2Shader[i]->SetShader(m_OpenGL);
		m_OpenGL->MatrixRotationY(RotacionBill, -90);
		float VectorVista[3];
		VectorVista[0] = m_Camera->GetXPos() - billFlores2[i]->x;
		VectorVista[1] = 0;
		VectorVista[2] = m_Camera->GetZPos() - billFlores2[i]->z;
		float Magnitud = sqrt(VectorVista[0] * VectorVista[0] + VectorVista[2] * VectorVista[2]);
		VectorVista[0] = VectorVista[0] / Magnitud;
		VectorVista[2] = VectorVista[2] / Magnitud;
		float Angulo = VectorVista[0] * 0 + VectorVista[2] * 1; //Producto punto = cos
		Angulo = acos(Angulo);
		if (billFlores2[i]->x > m_Camera->GetXPos()) {
			m_OpenGL->MatrixRotationY(RotacionBill, -Angulo);
		}
		else {
			m_OpenGL->MatrixRotationY(RotacionBill, Angulo);
		}
		m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
		m_BillFlores2Shader[i]->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillFlores2Shader[i]->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillFlores2Shader[i]->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillFlores2Shader[i]->Pon1Entero(m_OpenGL, (char*)"BillFlores2Col", 28);
		m_BillFlores2Shader[i]->Pon1Entero(m_OpenGL, (char*)"BillFlores2Norm", 29);
		m_BillFlores2Shader[i]->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
		m_BillFlores2Shader[i]->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillFlores2Shader[i]->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billFlores2[i]->Render(m_OpenGL);
	}

	for (int i = 0; i <= 7; i++) {
		//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
		//
		m_OpenGL->MatrixTranslation(TraslacionBill, billFlores3[i]->x, terreno->Superficie(billFlores3[i]->x, billFlores3[i]->z) - 5.5, billFlores3[i]->z);
		m_BillFlores3Shader[i]->SetShader(m_OpenGL);
		m_OpenGL->MatrixRotationY(RotacionBill, -90);
		float VectorVista[3];
		VectorVista[0] = m_Camera->GetXPos() - billFlores3[i]->x;
		VectorVista[1] = 0;
		VectorVista[2] = m_Camera->GetZPos() - billFlores3[i]->z;
		float Magnitud = sqrt(VectorVista[0] * VectorVista[0] + VectorVista[2] * VectorVista[2]);
		VectorVista[0] = VectorVista[0] / Magnitud;
		VectorVista[2] = VectorVista[2] / Magnitud;
		float Angulo = VectorVista[0] * 0 + VectorVista[2] * 1; //Producto punto = cos
		Angulo = acos(Angulo);
		if (billFlores3[i]->x > m_Camera->GetXPos()) {
			m_OpenGL->MatrixRotationY(RotacionBill, -Angulo);
		}
		else {
			m_OpenGL->MatrixRotationY(RotacionBill, Angulo);
		}
		m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
		m_BillFlores3Shader[i]->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillFlores3Shader[i]->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillFlores3Shader[i]->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillFlores3Shader[i]->Pon1Entero(m_OpenGL, (char*)"BillFlores3Col", 30);
		m_BillFlores3Shader[i]->Pon1Entero(m_OpenGL, (char*)"BillFlores3Norm", 31);
		m_BillFlores3Shader[i]->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
		m_BillFlores3Shader[i]->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillFlores3Shader[i]->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billFlores3[i]->Render(m_OpenGL);
	}

	for (int i = 0; i <= 2; i++) {
		//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
		//
		m_OpenGL->MatrixTranslation(TraslacionBill, billPozo[i]->x, terreno->Superficie(billPozo[i]->x, billPozo[i]->z) - .3, billPozo[i]->z);
		m_BillPozoShader[i]->SetShader(m_OpenGL);
		m_OpenGL->MatrixRotationY(RotacionBill, -90);
		float VectorVista[3];
		VectorVista[0] = m_Camera->GetXPos() - billPozo[i]->x;
		VectorVista[1] = 0;
		VectorVista[2] = m_Camera->GetZPos() - billPozo[i]->z;
		float Magnitud = sqrt(VectorVista[0] * VectorVista[0] + VectorVista[2] * VectorVista[2]);
		VectorVista[0] = VectorVista[0] / Magnitud;
		VectorVista[2] = VectorVista[2] / Magnitud;
		float Angulo = VectorVista[0] * 0 + VectorVista[2] * 1; //Producto punto = cos
		Angulo = acos(Angulo);
		if (billPozo[i]->x > m_Camera->GetXPos()) {
			m_OpenGL->MatrixRotationY(RotacionBill, -Angulo);
		}
		else {
			m_OpenGL->MatrixRotationY(RotacionBill, Angulo);
		}
		m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
		m_BillPozoShader[i]->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillPozoShader[i]->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillPozoShader[i]->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillPozoShader[i]->Pon1Entero(m_OpenGL, (char*)"BillPozoCol", 32);
		m_BillPozoShader[i]->Pon1Entero(m_OpenGL, (char*)"BillPozoNorm", 33);
		m_BillPozoShader[i]->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
		m_BillPozoShader[i]->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillPozoShader[i]->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billPozo[i]->Render(m_OpenGL);
	}

	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	//
	m_OpenGL->MatrixTranslation(TraslacionBill, billMontaña1->x, -60, billMontaña1->z);
	m_BillMontaña1Shader->SetShader(m_OpenGL);
	m_OpenGL->MatrixRotationY(RotacionBill, 3.1416);
	m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
	m_BillMontaña1Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_BillMontaña1Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_BillMontaña1Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_BillMontaña1Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana1Col", 20);
	m_BillMontaña1Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana1Norm", 21);
	m_BillMontaña1Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_BillMontaña1Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_BillMontaña1Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	billMontaña1->Render(m_OpenGL);


	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	//
	m_OpenGL->MatrixTranslation(TraslacionBill, billMontaña2->x, -13, billMontaña2->z);
	m_BillMontaña2Shader->SetShader(m_OpenGL);
	m_OpenGL->MatrixRotationY(RotacionBill, 1.57);
	m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
	m_BillMontaña2Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_BillMontaña2Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_BillMontaña2Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_BillMontaña2Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana2Col", 22);
	m_BillMontaña2Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana2Norm", 23);
	m_BillMontaña2Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_BillMontaña2Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_BillMontaña2Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	billMontaña2->Render(m_OpenGL);


	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	//
	m_OpenGL->MatrixTranslation(TraslacionBill, billMontaña3->x, -15, billMontaña3->z);
	m_BillMontaña3Shader->SetShader(m_OpenGL);
	m_OpenGL->MatrixRotationY(RotacionBill, -1.57);
	m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
	m_BillMontaña3Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_BillMontaña3Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_BillMontaña3Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_BillMontaña3Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Col", 24);
	m_BillMontaña3Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Norm", 25);
	m_BillMontaña3Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_BillMontaña3Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_BillMontaña3Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	billMontaña3->Render(m_OpenGL);

	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	//
	m_OpenGL->MatrixTranslation(TraslacionBill, billMontaña4->x, -15, billMontaña4->z);
	m_BillMontaña4Shader->SetShader(m_OpenGL);
	m_OpenGL->MatrixRotationY(RotacionBill, 0);
	m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
	m_BillMontaña4Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_BillMontaña4Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_BillMontaña4Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_BillMontaña4Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana1Col", 20);
	m_BillMontaña4Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana1Norm", 21);
	m_BillMontaña4Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_BillMontaña4Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_BillMontaña4Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	billMontaña4->Render(m_OpenGL);


	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	//
	m_OpenGL->MatrixTranslation(TraslacionBill, billMontaña5->x, -15, billMontaña5->z);
	m_BillMontaña5Shader->SetShader(m_OpenGL);
	m_OpenGL->MatrixRotationY(RotacionBill, -135 * PI / 180);
	m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
	m_BillMontaña5Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_BillMontaña5Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_BillMontaña5Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_BillMontaña5Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Col", 24);
	m_BillMontaña5Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Norm", 25);
	m_BillMontaña5Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_BillMontaña5Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_BillMontaña5Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	billMontaña5->Render(m_OpenGL);



	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	//
	m_OpenGL->MatrixTranslation(TraslacionBill, billMontaña6->x, -15, billMontaña6->z);
	m_BillMontaña6Shader->SetShader(m_OpenGL);
	m_OpenGL->MatrixRotationY(RotacionBill, 135 * PI / 180);
	m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
	m_BillMontaña6Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_BillMontaña6Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_BillMontaña6Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_BillMontaña6Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Col", 24);
	m_BillMontaña6Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Norm", 25);
	m_BillMontaña6Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_BillMontaña6Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_BillMontaña6Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	billMontaña6->Render(m_OpenGL);


	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	//
	m_OpenGL->MatrixTranslation(TraslacionBill, billMontaña7->x, -15, billMontaña7->z);
	m_BillMontaña7Shader->SetShader(m_OpenGL);
	m_OpenGL->MatrixRotationY(RotacionBill, 45 * PI / 180);
	m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
	m_BillMontaña7Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_BillMontaña7Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_BillMontaña7Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_BillMontaña7Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Col", 24);
	m_BillMontaña7Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Norm", 25);
	m_BillMontaña7Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_BillMontaña7Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_BillMontaña7Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	billMontaña7->Render(m_OpenGL);


	//// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	//
	m_OpenGL->MatrixTranslation(TraslacionBill, billMontaña8->x, -15, billMontaña8->z);
	m_BillMontaña8Shader->SetShader(m_OpenGL);
	m_OpenGL->MatrixRotationY(RotacionBill, -45 * PI / 180);
	m_OpenGL->MatrixMultiply(worldMatrixBill, RotacionBill, TraslacionBill);
	m_BillMontaña8Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_BillMontaña8Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_BillMontaña8Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_BillMontaña8Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Col", 24);
	m_BillMontaña8Shader->Pon1Entero(m_OpenGL, (char*)"BillMontana3Norm", 25);
	m_BillMontaña8Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_BillMontaña8Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_BillMontaña8Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	billMontaña8->Render(m_OpenGL);

	
	// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	m_ModeloShader->SetShader(m_OpenGL);
	m_OpenGL->GetWorldMatrix(modmatrix);
	m_OpenGL->MatrixTranslation(TraslacionModelos, Casa1->x, terreno->Superficie(Casa1->x, Casa1->z) - .3, Casa1->z);
	m_OpenGL->MatrixRotationY(RotacionModelos, 0);
	m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"Casa1Text", 10);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"Casa1Norm", 11);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"Casa1Spec", 12);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	Casa1->Render(m_OpenGL);

	// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	m_Casa2Shader->SetShader(m_OpenGL);
	m_OpenGL->GetWorldMatrix(modmatrix);
	m_OpenGL->MatrixTranslation(TraslacionModelos, Casa2->x, terreno->Superficie(Casa2->x, Casa2->z) - .5, Casa2->z);
	m_OpenGL->MatrixRotationY(RotacionModelos, -0);
	m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
	m_Casa2Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
	m_Casa2Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_Casa2Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_Casa2Shader->Pon1Entero(m_OpenGL, (char*)"Casa2Text", 14);
	m_Casa2Shader->Pon1Entero(m_OpenGL, (char*)"Casa2Norm", 15);
	m_Casa2Shader->Pon1Entero(m_OpenGL, (char*)"Casa2Spec", 16);
	m_Casa2Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_Casa2Shader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	m_Casa2Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_Casa2Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	Casa2->Render(m_OpenGL);

	// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	m_Casa3Shader->SetShader(m_OpenGL);
	m_OpenGL->GetWorldMatrix(modmatrix);
	m_OpenGL->MatrixTranslation(TraslacionModelos, Casa3->x, terreno->Superficie(Casa3->x, Casa3->z) - .25, Casa3->z);
	m_OpenGL->MatrixRotationY(RotacionModelos, 0);
	m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
	m_Casa3Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
	m_Casa3Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_Casa3Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_Casa3Shader->Pon1Entero(m_OpenGL, (char*)"Casa3Text", 17);
	m_Casa3Shader->Pon1Entero(m_OpenGL, (char*)"Casa3Norm", 18);
	m_Casa3Shader->Pon1Entero(m_OpenGL, (char*)"Casa3Spec", 19);
	m_Casa3Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_Casa3Shader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	m_Casa3Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_Casa3Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	Casa3->Render(m_OpenGL);

	// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	m_Casa4Shader->SetShader(m_OpenGL);
	m_OpenGL->GetWorldMatrix(modmatrix);
	m_OpenGL->MatrixTranslation(TraslacionModelos, Casa4->x, terreno->Superficie(Casa4->x, Casa4->z) + .1, Casa4->z);
	m_OpenGL->MatrixRotationY(RotacionModelos, -85 * PI / 180);
	m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
	m_Casa4Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
	m_Casa4Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_Casa4Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_Casa4Shader->Pon1Entero(m_OpenGL, (char*)"Casa3Text", 17);
	m_Casa4Shader->Pon1Entero(m_OpenGL, (char*)"Casa3Norm", 18);
	m_Casa4Shader->Pon1Entero(m_OpenGL, (char*)"Casa3Spec", 19);
	m_Casa4Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_Casa4Shader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	m_Casa4Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_Casa4Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	Casa4->Render(m_OpenGL);

	// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	m_Casa5Shader->SetShader(m_OpenGL);
	m_OpenGL->GetWorldMatrix(modmatrix);
	m_OpenGL->MatrixTranslation(TraslacionModelos, Casa5->x, terreno->Superficie(Casa5->x, Casa5->z) + .4, Casa5->z);
	m_OpenGL->MatrixRotationY(RotacionModelos, -135 * PI / 180);
	m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
	m_Casa5Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
	m_Casa5Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_Casa5Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_Casa5Shader->Pon1Entero(m_OpenGL, (char*)"Casa1Text", 10);
	m_Casa5Shader->Pon1Entero(m_OpenGL, (char*)"Casa1Norm", 11);
	m_Casa5Shader->Pon1Entero(m_OpenGL, (char*)"Casa1Spec", 12);
	m_Casa5Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_Casa5Shader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	m_Casa5Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_Casa5Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	Casa5->Render(m_OpenGL);

	// Set the light shader as the current shader program and set the matrices that it will use for rendering.
	m_Casa6Shader->SetShader(m_OpenGL);
	m_OpenGL->GetWorldMatrix(modmatrix);
	m_OpenGL->MatrixTranslation(TraslacionModelos, Casa6->x, terreno->Superficie(Casa6->x, Casa6->z) - .5, Casa6->z);
	m_OpenGL->MatrixRotationY(RotacionModelos, 90 * PI / 180);
	m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
	m_Casa6Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
	m_Casa6Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_Casa6Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_Casa6Shader->Pon1Entero(m_OpenGL, (char*)"Casa2Text", 14);
	m_Casa6Shader->Pon1Entero(m_OpenGL, (char*)"Casa2Norm", 15);
	m_Casa6Shader->Pon1Entero(m_OpenGL, (char*)"Casa2Spec", 16);
	m_Casa6Shader->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
	m_Casa6Shader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	m_Casa6Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_Casa6Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	Casa6->Render(m_OpenGL);


	for (int i = 0; i <= 7; i++) {
		m_RocasShader[i]->SetShader(m_OpenGL);
		m_OpenGL->GetWorldMatrix(modmatrix);
		m_OpenGL->MatrixTranslation(TraslacionModelos, Rocas[i]->x, terreno->Superficie(Rocas[i]->x, Rocas[i]->z) - .5, Rocas[i]->z);
		m_OpenGL->MatrixRotationY(RotacionModelos, 0);
		m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
		m_RocasShader[i]->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
		m_RocasShader[i]->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_RocasShader[i]->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_RocasShader[i]->Pon1Entero(m_OpenGL, (char*)"RocaText", 34);
		m_RocasShader[i]->Pon1Entero(m_OpenGL, (char*)"RocaNorm", 35);
		m_RocasShader[i]->Pon1Entero(m_OpenGL, (char*)"RocaSpec", 36);
		m_RocasShader[i]->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
		m_RocasShader[i]->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
		m_RocasShader[i]->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_RocasShader[i]->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		Rocas[i]->Render(m_OpenGL);
	}

	for (int i = 0; i <= 2; i++) {
		m_BarrilShader[i]->SetShader(m_OpenGL);
		m_OpenGL->GetWorldMatrix(modmatrix);
		m_OpenGL->MatrixTranslation(TraslacionModelos, Barril[i]->x, terreno->Superficie(Barril[i]->x, Barril[i]->z) - .3, Barril[i]->z);
		m_OpenGL->MatrixRotationY(RotacionModelos, 0);
		m_OpenGL->MatrixMultiply(modmatrix, RotacionModelos, TraslacionModelos);
		m_BarrilShader[i]->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
		m_BarrilShader[i]->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BarrilShader[i]->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BarrilShader[i]->Pon1Entero(m_OpenGL, (char*)"BarrilText", 37);
		m_BarrilShader[i]->Pon1Entero(m_OpenGL, (char*)"BarrilNorm", 38);
		m_BarrilShader[i]->Pon1Entero(m_OpenGL, (char*)"BarrilSpec", 39);
		m_BarrilShader[i]->Pon1Entero(m_OpenGL, (char*)"FactorAmbiental", AportacionAmbiental);
		m_BarrilShader[i]->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
		m_BarrilShader[i]->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BarrilShader[i]->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		Barril[i]->Render(m_OpenGL);
	}


	//Calcular colisiones
	if (sqrt(pow(Casa1->x - m_Camera->GetXPos(), 2) + pow(Casa1->z - m_Camera->GetZPos(), 2)) < Casa1->RadioColisión) {
		Chocando = true;
		Radio = Casa1->RadioColisión;
		ChoqueX = Casa1->x;
		ChoqueZ = Casa1->z;
	}
	else if (sqrt(pow(Casa2->x - m_Camera->GetXPos(), 2) + pow(Casa2->z - m_Camera->GetZPos(), 2)) < Casa2->RadioColisión) {
		Chocando = true;
		Radio = Casa2->RadioColisión;
		ChoqueX = Casa2->x;
		ChoqueZ = Casa2->z;
	}
	else if (sqrt(pow(Casa3->x - m_Camera->GetXPos(), 2) + pow(Casa3->z - m_Camera->GetZPos(), 2)) < Casa3->RadioColisión) {
		Chocando = true;
		Radio = Casa3->RadioColisión;
		ChoqueX = Casa3->x;
		ChoqueZ = Casa3->z;
	}
	else if (sqrt(pow(Casa4->x - m_Camera->GetXPos(), 2) + pow(Casa4->z - m_Camera->GetZPos(), 2)) < Casa4->RadioColisión) {
		Chocando = true;
		Radio = Casa4->RadioColisión;
		ChoqueX = Casa4->x;
		ChoqueZ = Casa4->z;
	}
	else if (sqrt(pow(Casa5->x - m_Camera->GetXPos(), 2) + pow(Casa5->z - m_Camera->GetZPos(), 2)) < Casa5->RadioColisión) {
		Chocando = true;
		Radio = Casa5->RadioColisión;
		ChoqueX = Casa5->x;
		ChoqueZ = Casa5->z;
	}
	else if (sqrt(pow(Casa6->x - m_Camera->GetXPos(), 2) + pow(Casa6->z - m_Camera->GetZPos(), 2)) < Casa6->RadioColisión) {
		Chocando = true;
		Radio = Casa6->RadioColisión;
		ChoqueX = Casa6->x;
		ChoqueZ = Casa6->z;
	}
	if (!Chocando) {
		for (int i = 0; i <= 7; i++) {
			if (sqrt(pow(Rocas[i]->x - m_Camera->GetXPos(), 2) + pow(Rocas[i]->z - m_Camera->GetZPos(), 2)) < Rocas[i]->RadioColisión) {
				Chocando = true;
				Radio = Rocas[i]->RadioColisión;
				ChoqueX = Rocas[i]->x;
				ChoqueZ = Rocas[i]->z;
				i = 8;
			}
		}
	}

	if (!Chocando) {
		for (int i = 0; i <= 2; i++) {
			if (sqrt(pow(Barril[i]->x - m_Camera->GetXPos(), 2) + pow(Barril[i]->z - m_Camera->GetZPos(), 2)) < Barril[i]->RadioColisión) {
				Chocando = true;
				Radio = Barril[i]->RadioColisión;
				ChoqueX = Barril[i]->x;
				ChoqueZ = Barril[i]->z;
				i = 8;
			}
		}
	}

	// Present the rendered scene to the screen.
	m_OpenGL->EndScene();

	return true;
}