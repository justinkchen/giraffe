#ifndef SENSORMANAGER_H_
#define SENSORMANAGER_H_
#include <FUixSensor.h>

 using namespace Tizen::Uix::Sensor;

class SensorParser : public ISensorEventListener
{
	public:
		SensorParser(void);
			virtual ~SensorParser(void);
			bool CreateSensor(void);

			virtual void OnDataReceived(SensorType sensorType, SensorData& sensorData, result r);

	public:
			float xAcc;
			float yAcc;
			float zAcc;
			float azimuth;
			float pitch;
			float roll;
			float xMag;
			float yMag;
			float zMag;


	private:
			SensorManager __sensorManager;
};



#endif /* SENSORMANAGER_H_ */
