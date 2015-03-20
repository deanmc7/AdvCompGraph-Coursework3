#ifndef __Lighting_h_
#define __Lighting_h_

#include "Utility.h"
#include "Shaders.h"

class Lighting
{
private:
	Shaders	lightingShader;

	GLfloat lightPos0[4];
	GLfloat lightPos1[4];
	GLfloat lightPos2[4];

	GLfloat lightRotation;
	/* ambient RGBA reflectance of the material */
	float materialAmbience[4];
	/* ambient RGBA intensity of entire scene */
	float sceneAmbience[4];

	float lightDirection[4];
public:
	Lighting();

	void InitShaders(void);
	void Display(void);
	void UseShader(void);

	void SetUpLighting(void);
	void TurnLightsOff(void);
	void TurnLightsOn(void);
	void SetSmoothShadeModel(void);
	void SetFlatShadeModel(void);
	void ActivateLight(void);
	void SetupLightDirection(void);
};

#endif //#ifndef __Lighting_h_