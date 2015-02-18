#include "Profiler.h"
#include "glfw.h"

void Profiler::resetProfiles()
{
	profiles.clear();
}

void Profiler::startMeasure(std::string profile)
{
	profiles[profile] = glfwGetTime();
}

void Profiler::stopMeasure(std::string profile)
{
	profiles[profile] = glfwGetTime()-profiles[profile];
}

double Profiler::getMeasurement(std::string profile)
{
	return profiles[profile];
}

double Profiler::getPercentage(std::string profile)
{
	return getMeasurement(profile)*100 / baseTime;
}
