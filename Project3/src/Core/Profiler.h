#ifndef PROFILER_H
#define PROFILER_H

#include <map>
#include <string>

class Profiler
{
private:
	float baseTime;
public:
	Profiler() {baseTime = 1.0/60;}
	~Profiler() {}

	std::map<std::string, float> profiles;
	
	void resetProfiles();
	void startMeasure(std::string profile);
	void stopMeasure(std::string profile);

	double getMeasurement(std::string profile);
	double getPercentage(std::string profile);
};

#endif