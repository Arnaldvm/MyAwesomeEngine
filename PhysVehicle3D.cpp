#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet\include\btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Black;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);	
	chassis.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();
	
	//TESTING ----
	Cube frontchassis(info.chassis_size.x + 0.1f, info.chassis_size.y + 0.1f, info.chassis_size.z - 1.5f);
	frontchassis.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&frontchassis.transform);
	btQuaternion q2 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset2(info.chassis_offset.x, info.chassis_offset.y - 0.2f, info.chassis_offset.z + 2.2f);
	offset2 = offset2.rotate(q2.getAxis(), q2.getAngle());

	frontchassis.transform.M[12] += offset2.getX();
	frontchassis.transform.M[13] += offset2.getY();
	frontchassis.transform.M[14] += offset2.getZ();

	
	Cube backchassis(info.chassis_size.x + 0.1f, info.chassis_size.y + 0.1f, info.chassis_size.z - 1.5f);
	backchassis.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&backchassis.transform);
	btQuaternion q3 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset3(info.chassis_offset.x, info.chassis_offset.y - 0.2f, info.chassis_offset.z - 2.2f);
	offset3 = offset3.rotate(q3.getAxis(), q3.getAngle());

	backchassis.transform.M[12] += offset3.getX();
	backchassis.transform.M[13] += offset3.getY();
	backchassis.transform.M[14] += offset3.getZ();


	Cube rightchassis(info.chassis_size.x - 1.80f, info.chassis_size.y + 0.1f, info.chassis_size.z + 0.9f);
	rightchassis.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&rightchassis.transform);
	btQuaternion q4 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset4(info.chassis_offset.x - 1.7f, info.chassis_offset.y - 0.2f, info.chassis_offset.z);
	offset4 = offset4.rotate(q4.getAxis(), q4.getAngle());

	rightchassis.transform.M[12] += offset4.getX();
	rightchassis.transform.M[13] += offset4.getY();
	rightchassis.transform.M[14] += offset4.getZ();


	Cube leftchassis(info.chassis_size.x - 1.80f, info.chassis_size.y + 0.1f, info.chassis_size.z + 0.9f);
	leftchassis.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&leftchassis.transform);
	btQuaternion q5 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset5(info.chassis_offset.x + 1.7f, info.chassis_offset.y - 0.2f, info.chassis_offset.z);
	offset5 = offset5.rotate(q5.getAxis(), q5.getAngle());

	leftchassis.transform.M[12] += offset5.getX();
	leftchassis.transform.M[13] += offset5.getY();
	leftchassis.transform.M[14] += offset5.getZ();


	Cube basechassis(info.chassis_size.x - 0.20f, info.chassis_size.y + 0.1f, info.chassis_size.z - 1.0f);
	basechassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&basechassis.transform);
	btQuaternion q6 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset6(info.chassis_offset.x, info.chassis_offset.y + 0.1f, info.chassis_offset.z - 0.6f);
	offset6 = offset6.rotate(q6.getAxis(), q6.getAngle());

	basechassis.transform.M[12] += offset6.getX();
	basechassis.transform.M[13] += offset6.getY();
	basechassis.transform.M[14] += offset6.getZ();


	Cube sitchassis(info.chassis_size.x - 0.20f, info.chassis_size.y + 1.6f, info.chassis_size.z - 1.9f);
	sitchassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&sitchassis.transform);
	btQuaternion q7 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset7(info.chassis_offset.x, info.chassis_offset.y + 0.9f, info.chassis_offset.z - 1.1f);
	offset7 = offset7.rotate(q7.getAxis(), q7.getAngle());

	sitchassis.transform.M[12] += offset7.getX();
	sitchassis.transform.M[13] += offset7.getY();
	sitchassis.transform.M[14] += offset7.getZ();


	Cube leftbasechassis(info.chassis_size.x - 1.80f, info.chassis_size.y - 0.1f, info.chassis_size.z + 0.9f);
	leftbasechassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&leftbasechassis.transform);
	btQuaternion q8 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset8(info.chassis_offset.x + 1.5f, info.chassis_offset.y - 0.3f, info.chassis_offset.z);
	offset8 = offset8.rotate(q8.getAxis(), q8.getAngle());

	leftbasechassis.transform.M[12] += offset8.getX();
	leftbasechassis.transform.M[13] += offset8.getY();
	leftbasechassis.transform.M[14] += offset8.getZ();


	Cube rightbasechassis(info.chassis_size.x - 1.80f, info.chassis_size.y - 0.1f, info.chassis_size.z + 0.9f);
	rightbasechassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&rightbasechassis.transform);
	btQuaternion q9 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset9(info.chassis_offset.x - 1.5f, info.chassis_offset.y - 0.3f, info.chassis_offset.z);
	offset9 = offset9.rotate(q9.getAxis(), q9.getAngle());

	rightbasechassis.transform.M[12] += offset9.getX();
	rightbasechassis.transform.M[13] += offset9.getY();
	rightbasechassis.transform.M[14] += offset9.getZ();


	Cube wheelbasechassis(info.chassis_size.x - 1.00f, info.chassis_size.y + 0.8f, info.chassis_size.z - 1.0f);
	wheelbasechassis.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&wheelbasechassis.transform);
	btQuaternion q10 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset10(info.chassis_offset.x, info.chassis_offset.y + 0.3f, info.chassis_offset.z + 1.8f);
	offset10 = offset10.rotate(q10.getAxis(), q10.getAngle());

	wheelbasechassis.transform.M[12] += offset10.getX();
	wheelbasechassis.transform.M[13] += offset10.getY();
	wheelbasechassis.transform.M[14] += offset10.getZ();


	Cube wheelchassis(info.chassis_size.x - 1.0f, info.chassis_size.y -0.1f, info.chassis_size.z - 1.0f);
	wheelchassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&wheelchassis.transform);
	btQuaternion q11 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset11(info.chassis_offset.x, info.chassis_offset.y + 0.9f, info.chassis_offset.z + 1.3f);
	offset11 = offset11.rotate(q11.getAxis(), q11.getAngle());

	wheelchassis.transform.M[12] += offset11.getX();
	wheelchassis.transform.M[13] += offset11.getY();
	wheelchassis.transform.M[14] += offset11.getZ();
	

	Cube bar1chassis(info.chassis_size.x - 1.9f, info.chassis_size.y - 0.2f, info.chassis_size.z + 2.2f);
	bar1chassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&bar1chassis.transform);
	btQuaternion q12 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset12(info.chassis_offset.x + 0.5, info.chassis_offset.y - 0.3f, info.chassis_offset.z);
	offset12 = offset12.rotate(q12.getAxis(), q12.getAngle());

	bar1chassis.transform.M[12] += offset12.getX();
	bar1chassis.transform.M[13] += offset12.getY();
	bar1chassis.transform.M[14] += offset12.getZ();


	Cube bar2chassis(info.chassis_size.x - 1.9f, info.chassis_size.y - 0.2f, info.chassis_size.z + 2.2f);
	bar2chassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&bar2chassis.transform);
	btQuaternion q13 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset13(info.chassis_offset.x - 0.5, info.chassis_offset.y - 0.3f, info.chassis_offset.z);
	offset13 = offset13.rotate(q13.getAxis(), q13.getAngle());

	bar2chassis.transform.M[12] += offset13.getX();
	bar2chassis.transform.M[13] += offset13.getY();
	bar2chassis.transform.M[14] += offset13.getZ();


	Cube bar3chassis(info.chassis_size.x + 1.6f, info.chassis_size.y - 0.2f, info.chassis_size.z - 1.9f);
	bar3chassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&bar3chassis.transform);
	btQuaternion q14 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset14(info.chassis_offset.x, info.chassis_offset.y - 0.3f, info.chassis_offset.z - 0.5f);
	offset14 = offset14.rotate(q14.getAxis(), q14.getAngle());

	bar3chassis.transform.M[12] += offset14.getX();
	bar3chassis.transform.M[13] += offset14.getY();
	bar3chassis.transform.M[14] += offset14.getZ();


	Cube bar4chassis(info.chassis_size.x + 1.6f, info.chassis_size.y - 0.2f, info.chassis_size.z - 1.9f);
	bar4chassis.color = Black;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&bar4chassis.transform);
	btQuaternion q15 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset15(info.chassis_offset.x, info.chassis_offset.y - 0.3f, info.chassis_offset.z + 0.5f);
	offset15 = offset15.rotate(q15.getAxis(), q15.getAngle());

	bar4chassis.transform.M[12] += offset15.getX();
	bar4chassis.transform.M[13] += offset15.getY();
	bar4chassis.transform.M[14] += offset15.getZ();
	/*
	Cube cube_back(3.0f, 0.5f, 0.5f);
	cube_back.SetPos(info.chassis_offset.x, info.chassis_offset.y + 0.2f, info.chassis_offset.z + 7.7f);
	
	Cube cube_front(3.0f, 0.5f, 0.5f);
	cube_front.SetPos(info.chassis_offset.x, info.chassis_offset.y + 0.2f, info.chassis_offset.z + 12.4f);
	*/

	chassis.Render();
	frontchassis.Render();
	backchassis.Render();
	rightchassis.Render();
	leftchassis.Render();
	basechassis.Render();
	sitchassis.Render();
	wheelbasechassis.Render();
	leftbasechassis.Render();
	rightbasechassis.Render();
	wheelchassis.Render();
	bar1chassis.Render();
	bar2chassis.Render();
	bar3chassis.Render();
	bar4chassis.Render();
	//cube_back.Render();
	//cube_front.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}

vec3 PhysVehicle3D::getPos(){
	btTransform t = vehicle->getRigidBody()->getWorldTransform();
	btVector3 v = t.getOrigin();
	vec3 ret; 
	ret.Set(v.getX(), v.getY(), v.getZ());
	return ret; 
}