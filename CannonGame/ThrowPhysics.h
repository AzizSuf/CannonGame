#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>
#include <iostream>

using Vector2d = sf::Vector2<double>;

namespace sf {

	// Returns the length (module) of the sf::Vector2
	template<typename T>
	double length(sf::Vector2<T> vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}
}


#if 0
class MyVector2d : public sf::Vector2<double>
{
public:

	// For constructor
	//using sf::Vector2<double>::Vector2;


	operator sf::Vector2<double>() const
	{
		return sf::Vector2<double>(*this);
	}

	double modul()
	{
		return sqrt(x * x + y * y);
	}
};
#endif


enum class CalcMethod
{
	Euler,
	Verlet,
	VerificationFormula
};

// Модель броска тела брошенного под углом к горизонту с 
// учетом сопротивления воздуха
class ThrowPhysics
{
public:
	

public:
	ThrowPhysics();
	// TODO: Может нужно задавать не просто высоту, а начальные координаты x,y тела?
	ThrowPhysics(double initialHeight, double launchAngleDeg, double initialSpeed,
		double steadySpeed, double windSpeed = 0.0, double gravAccel = 9.80, double timeStep = 0.001);
	virtual ~ThrowPhysics();
	/*
	void fullCalculate();
	void stepCalculate();

	*/

	void init();

	void updateCurrentAccel();
	Vector2d calcAccel(Vector2d gravityAccel, Vector2d velocity, double vmax, Vector2d wind, double height);
	//sf::Vector2f calcAccelWithoutAirResistance(Vector2d gravityAccel, Vector2d velocity, double vmax, Vector2d wind, double height);
	
	void stepEulerMethod();
	void stepVerletPredKorrMethod();

	void stepVerificationFormula();

	void fullUpdate();
	
	// Calc next point
	void step();

	// Clear all stored calculation data
	void clear();

	const std::vector<Vector2d>& getHeightVsDistanceData() const;
	const std::vector<Vector2d>& getSpeedVsTimeData() const;
	const std::vector<Vector2d>& getAccelVsTimeData() const;

	// --
	//double maxHeight();
	//double maxDistance();
	//double flightTime();

	// -------
	// TODO: Может нужно переместить дебаг в другое место?
	void debugDump();
	// TODO: придумать более точное название
	// проверяет на равенство только физические параметры для рачетаы
	bool isEqual(ThrowPhysics other);

	// --- Interface
	void setCalcMethod(CalcMethod method);
	CalcMethod getCalcMethod();

	void setInitialHeight(double height);
	double getInitialHeight();

	void setInitialPosition(Vector2d pos);

	void setLaunchAngle(double angleDeg);
	double getLaunchAngle();

	void setInitialSpeed(double speed);
	double getInitialSpeed();

	void setSteadySpeed(double speed);
	double getSteadySpeed();

	void setWindSpeed(double wind);
	double getWindSpeed();

	void setGravAccel(double accel);
	double getGravAccel();

	void setTimeStep(double step);
	double getTimeStep();

private:
	CalcMethod m_method = CalcMethod::Verlet;
	
	double m_launchAngle;    // in degrees
	Vector2d m_initialPos;   // in meters
	double m_initialSpeed;   // in m/s
	double m_steadySpeed;    // in m/s
	Vector2d m_windSpeed;    // in m/s
	Vector2d m_gravAccel;    // in m/s^2
	double m_timeStep;       // in seconds

	// The current state of the object being thrown
	Vector2d m_currentPosition;
	Vector2d m_currentAccel;
	Vector2d m_currentVelocity;
	double m_currentTime = 0.0;

	std::vector<Vector2d> m_heightVsDistanceData; // y(x)
	std::vector<Vector2d> m_speedVsTimeData;      // v(t) (modul)

	std::vector<Vector2d> m_accelVsTimeData;          // a(t) (modul)

	size_t m_maxPointsNumber = 100000;

	// const запрещает move и copy конструктор по умолчанию!!!!
	/*const*/ size_t c_maxTime = 300;		       // in seconds
	
	bool m_isCalcFinished = false;
	/*
	HeightVsDistance,
	SpeedVsTime,
	DistanceVsTime */


	// ---------
};


/* 
	Usage example:

	ThrowPhysics physics;
	physics.setLaunchAngle(45)
		...
		...
	//physics.step()
	physics.fullUpdate()
    
	...

*/
