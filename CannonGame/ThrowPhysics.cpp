#include "ThrowPhysics.h"


ThrowPhysics::ThrowPhysics() :
	m_currentPosition(sf::Vector2f(0.0f, 0.0f)),
	m_currentVelocity(sf::Vector2f(0.0f, 0.0f)),
	m_currentAccel(sf::Vector2f(0.0f, 0.0f))
{
	init();
}

ThrowPhysics::ThrowPhysics(double initialHeight, double launchAngleDeg, double initialSpeed, double steadySpeed, double windSpeed, double gravAccel, double timeStep) :
	m_initialPos(Vector2d(0, initialHeight)),
	m_launchAngle(launchAngleDeg),
	m_initialSpeed(initialSpeed),
	m_steadySpeed(steadySpeed)
{
	init();
}

ThrowPhysics::~ThrowPhysics()
{
}


void ThrowPhysics::init()
{
	// TODO надо где-то задать m_maxPointsNumber 
	m_heightVsDistanceData.reserve(m_maxPointsNumber);
	m_speedVsTimeData.reserve(m_maxPointsNumber);
	m_accelVsTimeData.reserve(m_maxPointsNumber);

	m_currentTime = 0;
	m_currentAccel = Vector2d(0, 0); // ???
	const double angleRad = m_launchAngle * M_PI / 180.0;

	switch (m_method)
	{
	case CalcMethod::Euler:
	case CalcMethod::Verlet:
		m_currentPosition = m_initialPos;
		m_currentVelocity.x = m_initialSpeed * cos(angleRad);
		m_currentVelocity.y = m_initialSpeed * sin(angleRad);
		break;
	case CalcMethod::VerificationFormula:
		m_currentPosition.x = 0.0;
		m_currentPosition.y = m_initialPos.y;
		m_currentVelocity = Vector2d(0, 0);

		break;
	default:
		break;
	}
}

/*
 * 
 */
Vector2d ThrowPhysics::calcAccel(Vector2d gravityAccel, Vector2d velocity, double vmax, Vector2d wind, double height)
{
	return gravityAccel - exp(-height / 10000.0) * sf::length(gravityAccel) * (velocity - wind) * sf::length(velocity - wind) / (vmax * vmax);
}


void ThrowPhysics::stepEulerMethod()
{
	m_currentAccel = calcAccel(m_gravAccel, m_currentVelocity, m_steadySpeed, m_windSpeed, m_currentPosition.y);

	m_currentVelocity += m_currentAccel * m_timeStep;
	m_currentPosition += m_currentVelocity * m_timeStep;
}

void ThrowPhysics::stepVerletPredKorrMethod()
{
	Vector2d accel = calcAccel(m_gravAccel, m_currentVelocity, m_steadySpeed, m_windSpeed, m_currentPosition.y);

	m_currentPosition += m_currentVelocity * m_timeStep  +  0.5 * accel * (m_timeStep * m_timeStep);
	
	Vector2d vPred = m_currentVelocity + accel * m_timeStep;
	m_currentVelocity += 0.5 * accel * m_timeStep;

	accel = calcAccel(m_gravAccel, vPred, m_steadySpeed, m_windSpeed, m_currentPosition.y);
	
	m_currentVelocity += 0.5 * accel * m_timeStep;

	m_currentAccel = accel;
}

void ThrowPhysics::stepVerificationFormula()
{
	m_currentVelocity.y = m_steadySpeed * tanh(-m_gravAccel.y * m_currentTime / m_steadySpeed);

	m_currentPosition.y -= m_currentVelocity.y * m_timeStep;
}

void ThrowPhysics::fullUpdate()
{
	init();
	m_heightVsDistanceData.clear();
	m_speedVsTimeData.clear();
	m_accelVsTimeData.clear();

	while (m_currentTime < c_maxTime) // for (size_t i = 0; i < m_maxPointsNumber; i++)
	{
		step();
		if (m_currentPosition.y <= 0)
			return;
	}
}

void ThrowPhysics::clear()
{
	m_heightVsDistanceData.clear();
	m_speedVsTimeData.clear();
	m_accelVsTimeData.clear();
}

void ThrowPhysics::step()
{
	switch (m_method)
	{
	case CalcMethod::Euler:
		stepEulerMethod();
		break;
	case CalcMethod::Verlet:
		stepVerletPredKorrMethod();
		break;
	case CalcMethod::VerificationFormula:
		stepVerificationFormula();
		break;
	default:
		std::cout << "In ThrowPhysics::step() something went wrong!" << std::endl;
		break;
	}
	
	m_heightVsDistanceData.push_back(m_currentPosition);
	m_speedVsTimeData.push_back(Vector2d(m_currentTime, sf::length(m_currentVelocity)));
	m_accelVsTimeData.push_back(Vector2d(m_currentTime, sf::length(m_currentAccel)));

	m_currentTime += m_timeStep;
	//if (m_currentPosition.y <= 0)
	//	return;
	
	// Для теста
	//m_heightVsDistanceData.push_back(Vector2d(m_currentTime, m_currentTime* m_currentTime));
	//m_currentTime++;
}

const std::vector<Vector2d>& ThrowPhysics::getHeightVsDistanceData() const
{
	return m_heightVsDistanceData;
}

const std::vector<Vector2d>& ThrowPhysics::getSpeedVsTimeData() const
{
	return m_speedVsTimeData;
}

const std::vector<Vector2d>& ThrowPhysics::getAccelVsTimeData() const
{
	return m_accelVsTimeData;
}

void ThrowPhysics::debugDump()
{
	std::cout << "Parameters:\n";
	std::cout << "Initial Height: " << m_initialPos.y << '\n';
	std::cout << "Launch Angle: " << m_launchAngle << '\n';
	std::cout << "Initial Speed: " << m_initialSpeed << '\n';
	std::cout << "Steady Speed: " << m_steadySpeed << '\n';
	std::cout << "Wind Speed: " << m_windSpeed.x << '\n';
	std::cout << "Grav Accel: " << m_gravAccel.y << '\n';
	std::cout << "Time Step: " << m_timeStep << '\n';
	std::cout << "" << '\n';
	std::cout << "" << '\n';
	std::cout << "HeightVsDistanceData-----------------------------------------\n";

	for (int i = 0; i < 100; i++)
	{
		std::cout << m_heightVsDistanceData[i].x << ", " << m_heightVsDistanceData[i].y << "\n";
	}
	std::cout << "\n\n\n\n\n\n\n\n\n";
}

bool ThrowPhysics::isEqual(ThrowPhysics other)
{
	// FIXME: может как-то можно сделать лучше??
	if (getLaunchAngle() == other.getLaunchAngle()     &&
		getInitialHeight() == other.getInitialHeight() &&
		getInitialSpeed() == other.getInitialSpeed()   &&
		getSteadySpeed() == other.getSteadySpeed()     &&
		getWindSpeed() == other.getWindSpeed()         &&
		getGravAccel() == other.getGravAccel()         &&
		getTimeStep() == other.getTimeStep()           &&
		getCalcMethod() == other.getCalcMethod())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// --- Interface --------------------------------------

void ThrowPhysics::setCalcMethod(CalcMethod method)
{
	if (m_isCalcFinished) return;
	m_method = method;
}

CalcMethod ThrowPhysics::getCalcMethod()
{
	return m_method;
}

void ThrowPhysics::setInitialHeight(double height)
{
	if (m_isCalcFinished) return;
	m_initialPos.y = height;
}

double ThrowPhysics::getInitialHeight()
{
	return m_initialPos.y;
}

void ThrowPhysics::setInitialPosition(Vector2d pos)
{
	m_initialPos = pos;
}

void ThrowPhysics::setLaunchAngle(double angleDeg)
{
	if (m_isCalcFinished) return;
	m_launchAngle = angleDeg;
}

double ThrowPhysics::getLaunchAngle()
{
	return m_launchAngle;
}

void ThrowPhysics::setInitialSpeed(double speed)
{
	if (m_isCalcFinished) return;
	m_initialSpeed = speed;
}

double ThrowPhysics::getInitialSpeed()
{
	return m_initialSpeed;
}

void ThrowPhysics::setSteadySpeed(double speed)
{
	if (m_isCalcFinished) return;
	m_steadySpeed = speed;
}

double ThrowPhysics::getSteadySpeed()
{
	return m_steadySpeed;
}

void ThrowPhysics::setWindSpeed(double wind)
{
	if (m_isCalcFinished) return;
	m_windSpeed.x = wind;
}

double ThrowPhysics::getWindSpeed()
{
	return m_windSpeed.x;
}

void ThrowPhysics::setGravAccel(double accel)
{
	if (m_isCalcFinished) return;
	m_gravAccel.y = -accel;
}

double ThrowPhysics::getGravAccel()
{
	return m_gravAccel.y;
}

void ThrowPhysics::setTimeStep(double step)
{
	if (m_isCalcFinished) return;
	m_timeStep = step;
}

double ThrowPhysics::getTimeStep()
{
	return m_timeStep;
}
