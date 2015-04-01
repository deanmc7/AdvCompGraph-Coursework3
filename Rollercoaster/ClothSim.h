#ifndef __ClothSim_h_
#define __ClothSim_h_

#include "Utility.h"

class ClothSim
{
public:
	ClothSim();

	void particleSetup();
	void initUnitForce();
	void clothPhysics();
	void drawCloth();

	void setMoveableParticles(int row, int column, bool flag);
	void particleMass(int row, int column, float total_mass, float total_polygons);
	void setParticlePosX(int row, int column);
	void setParticlePosY(int row, int column);
	void setStaticParticles(int row, int column, bool flag);
	void setSharedPolygons(int row, int column, int number);
	void setForceTopUnitParticle(int row, int column);
	void setForceBottomUnitParticle(int row, int column);
	void setUnitForce();
	void setParticleAcc(int cloth_row, int cloth_column);
	void setParticleVel(int cloth_row, int cloth_column);
	void setParticlePos(int cloth_row, int cloth_column);
	void setParSpringForce(int cloth_row, int cloth_column);
	void setParSpringDirection(int cloth_row, int cloth_column);
	void setPerSpringForce(int cloth_row, int cloth_column);
	void setPerSpringDirection(int cloth_row, int cloth_column, float delta_x, float delta_y, float delta_z);

	float getTotalFaces(int row, int column);
public:
	const static int total_cloth_rows = 20;
	const static int total_cloth_collumns = 40;
	const static int total_cloth_mass = 1000;

	GLfloat *vertices;

	float paricle_position_x;
	float paricle_position_y;
	float paricle_position_z;

	float paricle_velocity_x;
	float paricle_velocity_y;
	float paricle_velocity_z;

	float paricle_acceleration_x;
	float paricle_acceleration_y;
	float paricle_acceleration_z;

	float resultant_force_x;
	float resultant_force_y;
	float resultant_force_z;

	int number_of_polygons;
	float particle_mass;
	bool particle_movable_flag;

	int firstpass_row_index;
	int firstpass_column_index;
	int secondpass_row_index;
	int secondpass_column_index;

	float particle_direction_x;
	float particle_direction_y;
	float particle_direction_z;

	float tensile_spring_constant;
	float damping_factor;
	float spring_rest_length;
	float computed_new_length;

	float total_polygons;

	float gravity;
	float spring_tension_constant;
	float spring_shear_constant;

	float spring_damping_constant;
	float drag_coefficient;
	float wind_factor;

	float delta_x; //change in x
	float delta_y; //change in y
	float delta_z; //change in z

	float wind;

	GLfloat *normals;
};

#endif //#ifndef __ClothSim_h_