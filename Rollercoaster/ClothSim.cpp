#include "ClothSim.h"

ClothSim unitParticle[20][40];
ClothSim parallelSpring[20][40];
ClothSim perpendicularSpring[20][40];

/*
=================
Cloth
-Default Constructor setups spring factors and constants
=================
*/
ClothSim::ClothSim()
{
	total_polygons = 1;
	gravity = -3.174;
	spring_tension_constant = 1800.0;
	spring_shear_constant = 1100.0;
	spring_damping_constant = 8.0;
	drag_coefficient = 0.01;
	wind_factor = 0.1;

	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 1; cloth_column++)
		{
			parallelSpring[cloth_row][cloth_column].spring_rest_length = (0.2);
			perpendicularSpring[cloth_row][cloth_column].spring_rest_length = (0.2);

			parallelSpring[cloth_row][cloth_column].tensile_spring_constant = spring_tension_constant;
			perpendicularSpring[cloth_row][cloth_column].tensile_spring_constant = spring_tension_constant;

			parallelSpring[cloth_row][cloth_column].damping_factor = spring_damping_constant;
			perpendicularSpring[cloth_row][cloth_column].damping_factor = spring_damping_constant;

			parallelSpring[cloth_row][cloth_column].firstpass_row_index = cloth_row;
			perpendicularSpring[cloth_row][cloth_column].firstpass_row_index = cloth_row;

			parallelSpring[cloth_row][cloth_column].secondpass_row_index = cloth_row;
			perpendicularSpring[cloth_row][cloth_column].secondpass_column_index = cloth_column;

			parallelSpring[cloth_row][cloth_column].firstpass_column_index = cloth_column;
			perpendicularSpring[cloth_row][cloth_column].firstpass_column_index = cloth_column;

			perpendicularSpring[cloth_row][cloth_column].secondpass_row_index = cloth_row + 1;
			parallelSpring[cloth_row][cloth_column].secondpass_column_index = cloth_column + 1;
		}
	}
}

/*
=================
setMoveableParticles
-flag moveable particles
=================
*/
void ClothSim::setMoveableParticles(int row, int column, bool flag)
{
	unitParticle[row + 2][column + 2].particle_movable_flag = flag;
}

/*
=================
setStaticParticles
-flag static particles
=================
*/
void ClothSim::setStaticParticles(int row, int column, bool flag)
{
	unitParticle[row][column].particle_movable_flag = flag;
}

/*
=================
getTotalFaces
-calculate number of facing polygons
=================
*/
float ClothSim::getTotalFaces(int row, int column)
{
	return unitParticle[row][column].number_of_polygons;
}

/*
=================
particleMass
-calculate particle mass
=================
*/
void ClothSim::particleMass(int row, int column, float total_mass, float total_polygons)
{
	unitParticle[row][column].particle_mass = (unitParticle[row][column].number_of_polygons * total_mass / total_polygons);
}

/*
=================
setParticlePosX
-set particle's x position
=================
*/
void ClothSim::setParticlePosX(int row, int column)
{
	unitParticle[row][column].paricle_position_x = column * (0.2);
}

/*
=================
setParticlePosY
-set particle's y position
=================
*/
void ClothSim::setParticlePosY(int row, int column)
{
	unitParticle[row][column].paricle_position_y = (-1 * row) * (0.2);
}

/*
=================
setSharedPolygons
-set number of adjacent polygons
=================
*/
void ClothSim::setSharedPolygons(int row, int column, int number)
{
	unitParticle[row][column].number_of_polygons = number;
}

/*
=================
setForceTopUnitParticle
-set resultant force for first grouping of particles
=================
*/
void ClothSim::setForceTopUnitParticle(int row, int column)
{
	unitParticle[parallelSpring[row][column].firstpass_row_index][parallelSpring[row][column].firstpass_column_index].resultant_force_x += parallelSpring[row][column].resultant_force_x;
	unitParticle[parallelSpring[row][column].firstpass_row_index][parallelSpring[row][column].firstpass_column_index].resultant_force_y += parallelSpring[row][column].resultant_force_y;
	unitParticle[parallelSpring[row][column].firstpass_row_index][parallelSpring[row][column].firstpass_column_index].resultant_force_z += parallelSpring[row][column].resultant_force_z;
	unitParticle[perpendicularSpring[row][column].firstpass_row_index][perpendicularSpring[row][column].firstpass_column_index].resultant_force_x += perpendicularSpring[row][column].resultant_force_x;
	unitParticle[perpendicularSpring[row][column].firstpass_row_index][perpendicularSpring[row][column].firstpass_column_index].resultant_force_y += perpendicularSpring[row][column].resultant_force_y;
	unitParticle[perpendicularSpring[row][column].firstpass_row_index][perpendicularSpring[row][column].firstpass_column_index].resultant_force_z += perpendicularSpring[row][column].resultant_force_z;
}

/*
=================
setForceBottomUnitParticle
-set resultant force for second grouping of particles
=================
*/
void ClothSim::setForceBottomUnitParticle(int row, int column)
{
	unitParticle[parallelSpring[row][column].secondpass_row_index][parallelSpring[row][column].secondpass_column_index].resultant_force_x += (-1)*parallelSpring[row][column].resultant_force_x;
	unitParticle[parallelSpring[row][column].secondpass_row_index][parallelSpring[row][column].secondpass_column_index].resultant_force_y += (-1)*parallelSpring[row][column].resultant_force_y;
	unitParticle[parallelSpring[row][column].secondpass_row_index][parallelSpring[row][column].secondpass_column_index].resultant_force_z += (-1)*parallelSpring[row][column].resultant_force_z;
	unitParticle[perpendicularSpring[row][column].secondpass_row_index][perpendicularSpring[row][column].secondpass_column_index].resultant_force_x += (-1)*perpendicularSpring[row][column].resultant_force_x;
	unitParticle[perpendicularSpring[row][column].secondpass_row_index][perpendicularSpring[row][column].secondpass_column_index].resultant_force_y += (-1)*perpendicularSpring[row][column].resultant_force_y;
	unitParticle[perpendicularSpring[row][column].secondpass_row_index][perpendicularSpring[row][column].secondpass_column_index].resultant_force_z += (-1)*perpendicularSpring[row][column].resultant_force_z;
}

/*
=================
setUnitForce
-set unit force for particles
=================
*/
void ClothSim::setUnitForce()
{
	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 1; cloth_column++)
		{
			unitParticle[cloth_row][cloth_column].resultant_force_x = 0.0;
			unitParticle[cloth_row][cloth_column].resultant_force_y = 0.0;
			unitParticle[cloth_row][cloth_column].resultant_force_z = 0.0;
			unitParticle[cloth_row][cloth_column].resultant_force_z += wind;
			unitParticle[cloth_row][cloth_column].resultant_force_y += (gravity * unitParticle[cloth_row][cloth_column].particle_mass);
		}
	}
}

/*
=================
setParticleAcc
-set particle acceleration
=================
*/
void ClothSim::setParticleAcc(int cloth_row, int cloth_column)
{
	unitParticle[cloth_row][cloth_column].paricle_acceleration_x = unitParticle[cloth_row][cloth_column].resultant_force_x / unitParticle[cloth_row][cloth_column].particle_mass;
	unitParticle[cloth_row][cloth_column].paricle_acceleration_y = unitParticle[cloth_row][cloth_column].resultant_force_y / unitParticle[cloth_row][cloth_column].particle_mass;
	unitParticle[cloth_row][cloth_column].paricle_acceleration_z = unitParticle[cloth_row][cloth_column].resultant_force_z / unitParticle[cloth_row][cloth_column].particle_mass;
}

/*
=================
setParticleVel
-set particle velocity
=================
*/
void ClothSim::setParticleVel(int cloth_row, int cloth_column)
{
	unitParticle[cloth_row][cloth_column].paricle_velocity_x += unitParticle[cloth_row][cloth_column].paricle_acceleration_x*(0.02);
	unitParticle[cloth_row][cloth_column].paricle_velocity_y += unitParticle[cloth_row][cloth_column].paricle_acceleration_y*(0.02);
	unitParticle[cloth_row][cloth_column].paricle_velocity_z += unitParticle[cloth_row][cloth_column].paricle_acceleration_z*(0.02);
}

/*
=================
setParticlePos
-set particle position
=================
*/
void ClothSim::setParticlePos(int cloth_row, int cloth_column)
{
	unitParticle[cloth_row][cloth_column].paricle_position_x += unitParticle[cloth_row][cloth_column].paricle_velocity_x*(0.02);
	unitParticle[cloth_row][cloth_column].paricle_position_y += unitParticle[cloth_row][cloth_column].paricle_velocity_y*(0.02);
	unitParticle[cloth_row][cloth_column].paricle_position_z += unitParticle[cloth_row][cloth_column].paricle_velocity_z*(0.02);
}

/*
=================
particleSetup
-assign properties to particles
=================
*/
void ClothSim::particleSetup()
{
	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 1; cloth_column++)
		{
			ClothSim::setParticlePosX(cloth_row, cloth_column);
			ClothSim::setParticlePosY(cloth_row, cloth_column);
		}
	}

	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 1; cloth_column++)
		{
			ClothSim::setSharedPolygons(cloth_row, cloth_column, 10);
		}
	}

	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 1; cloth_column++)
		{
			if (cloth_row == 0)
			{
				ClothSim::setMoveableParticles(cloth_row, cloth_column, false);
			}
			else
			{
				ClothSim::setStaticParticles(cloth_row, cloth_column, true);
			}

			total_polygons += getTotalFaces(cloth_row, cloth_column);
		}
	}

	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 1; cloth_column++)
		{
			particleMass(cloth_row, cloth_column, total_cloth_mass, total_polygons);
		}
	}
}

/*
=================
setParSpringForce
-set the parallel spring force (horizontal)
=================
*/
void ClothSim::setParSpringForce(int cloth_row, int cloth_column)
{
	parallelSpring[cloth_row][cloth_column].resultant_force_x = (-1)*(parallelSpring[cloth_row][cloth_column].particle_direction_x / parallelSpring[cloth_row][cloth_column].computed_new_length);
	parallelSpring[cloth_row][cloth_column].resultant_force_x *= (parallelSpring[cloth_row][cloth_column].tensile_spring_constant*(parallelSpring[cloth_row][cloth_column].computed_new_length - parallelSpring[cloth_row][cloth_column].spring_rest_length) + parallelSpring[cloth_row][cloth_column].damping_factor*(parallelSpring[cloth_row][cloth_column].paricle_velocity_x*parallelSpring[cloth_row][cloth_column].particle_direction_x + parallelSpring[cloth_row][cloth_column].paricle_velocity_y*parallelSpring[cloth_row][cloth_column].particle_direction_y + parallelSpring[cloth_row][cloth_column].paricle_velocity_z*parallelSpring[cloth_row][cloth_column].particle_direction_z) / 0.31);
	parallelSpring[cloth_row][cloth_column].resultant_force_y = (-1)*(parallelSpring[cloth_row][cloth_column].particle_direction_y / parallelSpring[cloth_row][cloth_column].computed_new_length);
	parallelSpring[cloth_row][cloth_column].resultant_force_y *= (parallelSpring[cloth_row][cloth_column].tensile_spring_constant*(parallelSpring[cloth_row][cloth_column].computed_new_length - parallelSpring[cloth_row][cloth_column].spring_rest_length) + parallelSpring[cloth_row][cloth_column].damping_factor*(parallelSpring[cloth_row][cloth_column].paricle_velocity_x*parallelSpring[cloth_row][cloth_column].particle_direction_x + parallelSpring[cloth_row][cloth_column].paricle_velocity_y*parallelSpring[cloth_row][cloth_column].particle_direction_y + parallelSpring[cloth_row][cloth_column].paricle_velocity_z*parallelSpring[cloth_row][cloth_column].particle_direction_z) / 0.31);
	parallelSpring[cloth_row][cloth_column].resultant_force_z = (-1)*(parallelSpring[cloth_row][cloth_column].particle_direction_z / parallelSpring[cloth_row][cloth_column].computed_new_length);
	parallelSpring[cloth_row][cloth_column].resultant_force_z *= (parallelSpring[cloth_row][cloth_column].tensile_spring_constant*(parallelSpring[cloth_row][cloth_column].computed_new_length - parallelSpring[cloth_row][cloth_column].spring_rest_length) + parallelSpring[cloth_row][cloth_column].damping_factor*(parallelSpring[cloth_row][cloth_column].paricle_velocity_x*parallelSpring[cloth_row][cloth_column].particle_direction_x + parallelSpring[cloth_row][cloth_column].paricle_velocity_y*parallelSpring[cloth_row][cloth_column].particle_direction_y + parallelSpring[cloth_row][cloth_column].paricle_velocity_z*parallelSpring[cloth_row][cloth_column].particle_direction_z) / 0.31);
}

/*
=================
setPerSpringForce
-set the perpendicular spring force (vertical)
=================
*/
void ClothSim::setPerSpringForce(int cloth_row, int cloth_column)
{
	perpendicularSpring[cloth_row][cloth_column].resultant_force_x = -1.0*(perpendicularSpring[cloth_row][cloth_column].particle_direction_x / perpendicularSpring[cloth_row][cloth_column].computed_new_length)*(perpendicularSpring[cloth_row][cloth_column].tensile_spring_constant*(perpendicularSpring[cloth_row][cloth_column].computed_new_length - perpendicularSpring[cloth_row][cloth_column].spring_rest_length));
	perpendicularSpring[cloth_row][cloth_column].resultant_force_y = -1.0*(perpendicularSpring[cloth_row][cloth_column].particle_direction_y / perpendicularSpring[cloth_row][cloth_column].computed_new_length)*(perpendicularSpring[cloth_row][cloth_column].tensile_spring_constant*(perpendicularSpring[cloth_row][cloth_column].computed_new_length - perpendicularSpring[cloth_row][cloth_column].spring_rest_length));
	perpendicularSpring[cloth_row][cloth_column].resultant_force_z = -1.0*(perpendicularSpring[cloth_row][cloth_column].particle_direction_z / perpendicularSpring[cloth_row][cloth_column].computed_new_length)*(perpendicularSpring[cloth_row][cloth_column].tensile_spring_constant*(perpendicularSpring[cloth_row][cloth_column].computed_new_length - perpendicularSpring[cloth_row][cloth_column].spring_rest_length));
}

/*
=================
setPerSpringDirection
-set the perpendicular spring direction (vertical)
=================
*/
void ClothSim::setPerSpringDirection(int cloth_row, int cloth_column, float delta_x, float delta_y, float delta_z)
{
	perpendicularSpring[cloth_row][cloth_column].computed_new_length = sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
	perpendicularSpring[cloth_row][cloth_column].particle_direction_x = delta_x;
	perpendicularSpring[cloth_row][cloth_column].particle_direction_y = delta_y;
	perpendicularSpring[cloth_row][cloth_column].particle_direction_z = delta_z;
}

/*
=================
setParSpringDirection
-set the parallel spring direction (horizontal)
=================
*/
void ClothSim::setParSpringDirection(int cloth_row, int cloth_column)
{
	parallelSpring[cloth_row][cloth_column].particle_direction_x = unitParticle[parallelSpring[cloth_row][cloth_column].firstpass_row_index][parallelSpring[cloth_row][cloth_column].firstpass_column_index].paricle_position_x - unitParticle[parallelSpring[cloth_row][cloth_column].secondpass_row_index][parallelSpring[cloth_row][cloth_column].secondpass_column_index].paricle_position_x;
	parallelSpring[cloth_row][cloth_column].particle_direction_y = unitParticle[parallelSpring[cloth_row][cloth_column].firstpass_row_index][parallelSpring[cloth_row][cloth_column].firstpass_column_index].paricle_position_y - unitParticle[parallelSpring[cloth_row][cloth_column].secondpass_row_index][parallelSpring[cloth_row][cloth_column].secondpass_column_index].paricle_position_y;
	parallelSpring[cloth_row][cloth_column].particle_direction_z = unitParticle[parallelSpring[cloth_row][cloth_column].firstpass_row_index][parallelSpring[cloth_row][cloth_column].firstpass_column_index].paricle_position_z - unitParticle[parallelSpring[cloth_row][cloth_column].secondpass_row_index][parallelSpring[cloth_row][cloth_column].secondpass_column_index].paricle_position_z;
}

/*
=================
initUnitForce
-initialises the unit force for the particles
=================
*/
void ClothSim::initUnitForce()
{
	bool flag = false;

	ClothSim::setUnitForce();

	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 2; cloth_column++)
		{
			ClothSim::setForceTopUnitParticle(cloth_row, cloth_column);
			ClothSim::setForceBottomUnitParticle(cloth_row, cloth_column);
		}
	}

	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 1; cloth_column++)
		{
			if (unitParticle[cloth_row][cloth_column].particle_movable_flag == true)
			{
				ClothSim::setParticleAcc(cloth_row, cloth_column);
				ClothSim::setParticleVel(cloth_row, cloth_column);
				ClothSim::setParticlePos(cloth_row, cloth_column);
			}
		}
	}
}

/*
=================
clothPhysics
-setups the physics for a cloth
=================
*/
void ClothSim::clothPhysics()
{
	for (int cloth_row = 0; cloth_row <= total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column <= total_cloth_collumns - 1; cloth_column++)
		{
			parallelSpring[cloth_row][cloth_column].computed_new_length = 0.21;

			ClothSim::setParSpringDirection(cloth_row, cloth_column);

			ClothSim::setParSpringForce(cloth_row, cloth_column);
		}
	}

	for (int cloth_row = 0; cloth_row < total_cloth_rows - 1; cloth_row++)
	{
		for (int cloth_column = 0; cloth_column < total_cloth_collumns; cloth_column++)
		{
			delta_x = unitParticle[(perpendicularSpring[cloth_row][cloth_column].firstpass_row_index)][(perpendicularSpring[cloth_row][cloth_column].firstpass_column_index)].paricle_position_x - unitParticle[(perpendicularSpring[cloth_row][cloth_column].secondpass_row_index)][(perpendicularSpring[cloth_row][cloth_column].secondpass_column_index)].paricle_position_x;
			delta_y = unitParticle[(perpendicularSpring[cloth_row][cloth_column].firstpass_row_index)][(perpendicularSpring[cloth_row][cloth_column].firstpass_column_index)].paricle_position_y - unitParticle[(perpendicularSpring[cloth_row][cloth_column].secondpass_row_index)][(perpendicularSpring[cloth_row][cloth_column].secondpass_column_index)].paricle_position_y;
			delta_z = unitParticle[(perpendicularSpring[cloth_row][cloth_column].firstpass_row_index)][(perpendicularSpring[cloth_row][cloth_column].firstpass_column_index)].paricle_position_z - unitParticle[(perpendicularSpring[cloth_row][cloth_column].secondpass_row_index)][(perpendicularSpring[cloth_row][cloth_column].secondpass_column_index)].paricle_position_z;

			ClothSim::setPerSpringDirection(cloth_row, cloth_column, delta_x, delta_y, delta_z);

			ClothSim::setPerSpringForce(cloth_row, cloth_column);
		}
	}
}

/*
=================
drawCloth
-for the rendering of a cloth instance (4 cloths)
=================
*/
void ClothSim::drawCloth()
{
	int midp = ClothSim::total_cloth_collumns / 2;

	glPushMatrix();
	glTranslatef(0.0, 7.0, 0.0);
	for (int cloth_column = 0; cloth_column <= ClothSim::total_cloth_collumns - 2; cloth_column++)
	{
		for (int cloth_row = 0; cloth_row <= total_cloth_rows - 2; cloth_row++)
		{
			//bind the last texture specified in the Geometry.h class - the Persian carpet texture
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);
			glBegin(GL_TRIANGLES);//MODE);
			glNormal3f(1, 0, 1);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column].paricle_position_x, unitParticle[cloth_row][cloth_column].paricle_position_y, unitParticle[cloth_row][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column].paricle_position_x, unitParticle[cloth_row + 1][cloth_column].paricle_position_y, unitParticle[cloth_row + 1][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column + 1].paricle_position_x, unitParticle[cloth_row][cloth_column + 1].paricle_position_y, unitParticle[cloth_row][cloth_column + 1].paricle_position_z);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column].paricle_position_x, unitParticle[cloth_row + 1][cloth_column].paricle_position_y, unitParticle[cloth_row + 1][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column + 1].paricle_position_x, unitParticle[cloth_row][cloth_column + 1].paricle_position_y, unitParticle[cloth_row][cloth_column + 1].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_x, unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_y, unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_z);
			glEnd();
			glDisable(GL_BLEND);
		}
	}
	glPopMatrix();



	glPushMatrix();
	glTranslatef(8.0, 7.0, 0.0);
	for (int cloth_column = 0; cloth_column <= ClothSim::total_cloth_collumns - 2; cloth_column++)
	{
		for (int cloth_row = 0; cloth_row <= total_cloth_rows - 2; cloth_row++)
		{
			//bind the last texture specified in the Geometry.h class
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);
			glBegin(GL_TRIANGLES);
			glNormal3f(1, 0, 1);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column].paricle_position_x, unitParticle[cloth_row][cloth_column].paricle_position_y, unitParticle[cloth_row][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column].paricle_position_x, unitParticle[cloth_row + 1][cloth_column].paricle_position_y, unitParticle[cloth_row + 1][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column + 1].paricle_position_x, unitParticle[cloth_row][cloth_column + 1].paricle_position_y, unitParticle[cloth_row][cloth_column + 1].paricle_position_z);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column].paricle_position_x, unitParticle[cloth_row + 1][cloth_column].paricle_position_y, unitParticle[cloth_row + 1][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column + 1].paricle_position_x, unitParticle[cloth_row][cloth_column + 1].paricle_position_y, unitParticle[cloth_row][cloth_column + 1].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_x, unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_y, unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_z);
			glEnd();
			glDisable(GL_BLEND);
		}
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16.0, 7.0, 0.0);
	for (int cloth_column = 0; cloth_column <= ClothSim::total_cloth_collumns - 2; cloth_column++)
	{
		for (int cloth_row = 0; cloth_row <= total_cloth_rows - 2; cloth_row++)
		{
			//bind the last texture specified in the Geometry.h class
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);
			glBegin(GL_TRIANGLES);
			glNormal3f(1, 0, 1);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column].paricle_position_x, unitParticle[cloth_row][cloth_column].paricle_position_y, unitParticle[cloth_row][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column].paricle_position_x, unitParticle[cloth_row + 1][cloth_column].paricle_position_y, unitParticle[cloth_row + 1][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column + 1].paricle_position_x, unitParticle[cloth_row][cloth_column + 1].paricle_position_y, unitParticle[cloth_row][cloth_column + 1].paricle_position_z);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column].paricle_position_x, unitParticle[cloth_row + 1][cloth_column].paricle_position_y, unitParticle[cloth_row + 1][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column + 1].paricle_position_x, unitParticle[cloth_row][cloth_column + 1].paricle_position_y, unitParticle[cloth_row][cloth_column + 1].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_x, unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_y, unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_z);
			glEnd();
			glDisable(GL_BLEND);
		}
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.0, 7.0, 0.0);
	for (int cloth_column = 0; cloth_column <= ClothSim::total_cloth_collumns - 2; cloth_column++)
	{
		for (int cloth_row = 0; cloth_row <= total_cloth_rows - 2; cloth_row++)
		{
			//bind the last texture specified in the Geometry.h class
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);
			glBegin(GL_TRIANGLES);
			glNormal3f(1, 0, 1);

			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column].paricle_position_x, unitParticle[cloth_row][cloth_column].paricle_position_y, unitParticle[cloth_row][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column].paricle_position_x, unitParticle[cloth_row + 1][cloth_column].paricle_position_y, unitParticle[cloth_row + 1][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column + 1].paricle_position_x, unitParticle[cloth_row][cloth_column + 1].paricle_position_y, unitParticle[cloth_row][cloth_column + 1].paricle_position_z);
			glTexCoord2f((cloth_column + 0.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column].paricle_position_x, unitParticle[cloth_row + 1][cloth_column].paricle_position_y, unitParticle[cloth_row + 1][cloth_column].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 0.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row][cloth_column + 1].paricle_position_x, unitParticle[cloth_row][cloth_column + 1].paricle_position_y, unitParticle[cloth_row][cloth_column + 1].paricle_position_z);
			glTexCoord2f((cloth_column + 1.0) / total_cloth_collumns, (cloth_row + 1.0) / total_cloth_rows);
			glVertex3f(unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_x, unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_y, unitParticle[cloth_row + 1][cloth_column + 1].paricle_position_z);
			glEnd();
			glDisable(GL_BLEND);
		}
	}
	glPopMatrix();
}