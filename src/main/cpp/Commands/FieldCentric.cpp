#include "Commands/FieldCentric.h"
#include "Modules/Logger.h"
#include "Robot.h"

// ==========================================================================

FieldCentric::FieldCentric()
: frc::Command("FieldCentric") {
	LOG(GetName() + "::ctor");

	Requires(Robot::driveTrain);
}

// ==========================================================================

void FieldCentric::Initialize() {
	Robot::driveTrain->CrabInit();
	SmartDashboard::PutString("Driving Mode","Field Centric");
}

// ==========================================================================

void FieldCentric::Execute() {
	auto x = Robot::oi->GetJoystickX();
	auto y = Robot::oi->GetJoystickY();
	auto z = Robot::oi->GetJoystickZ();
	if(x > 0) x = x* x + 0.1;
	else if(x < 0) x = -(x* x + 0.1);

	if(y > 0) y = y* y + 0.1;
	else if(y < 0) y = -(y* y + 0.1);

	if(z > 0) z = z* z + 0.1;
	else if(z < 0) z = -(z* z + 0.1);

	Robot::driveTrain->FieldCentricCrab(z, -y, x, true);

}

// ==========================================================================

bool FieldCentric::IsFinished() {
	return false;
}

// ==========================================================================

void FieldCentric::End() {
	SmartDashboard::PutString("Driving Mode","Unknown");
}

// ==========================================================================

void FieldCentric::Interrupted() {
	End();
}

// ==========================================================================
