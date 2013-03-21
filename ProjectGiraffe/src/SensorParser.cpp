#include "SensorParser.h"

SensorParser::SensorParser(void)
	: xAcc(0.0F)
	, yAcc(0.0F)
	, zAcc(0.0F)
	, azimuth(0.0F)
	, pitch(0.0F)
	, roll(0.0F)
	, xMag(0.0F)
	, yMag(0.0F)
	, zMag(0.0F)
{
 // Initializes the sensor manager
	__sensorManager.Construct();
}

SensorParser::~SensorParser(void)
{
 // Finalizes the sensor manager
}

void SensorParser::OnDataReceived(SensorType sensorType, SensorData& sensorData, result r)
{

	//Read sensor values.
	if (sensorType == SENSOR_TYPE_ACCELERATION) {
		sensorData.GetValue(static_cast<SensorDataKey>(ACCELERATION_DATA_KEY_X), xAcc);
		sensorData.GetValue(static_cast<SensorDataKey>(ACCELERATION_DATA_KEY_Y), yAcc);
		sensorData.GetValue(static_cast<SensorDataKey>(ACCELERATION_DATA_KEY_Z), zAcc);
		AppLog("Acceleration in X-coord: %f", xAcc);
	}

	if (sensorType == SENSOR_TYPE_TILT) {
		sensorData.GetValue(static_cast<SensorDataKey>(TILT_DATA_KEY_AZIMUTH), azimuth);
		sensorData.GetValue(static_cast<SensorDataKey>(TILT_DATA_KEY_PITCH), pitch);
		sensorData.GetValue(static_cast<SensorDataKey>(TILT_DATA_KEY_ROLL), roll);
	}
	if (sensorType == SENSOR_TYPE_MAGNETIC) {
		sensorData.GetValue(static_cast<SensorDataKey>(MAGNETIC_DATA_KEY_X ), xMag);
		sensorData.GetValue(static_cast<SensorDataKey>(MAGNETIC_DATA_KEY_Y ), yMag);
		sensorData.GetValue(static_cast<SensorDataKey>(MAGNETIC_DATA_KEY_Z ), zMag);
	}
}

bool SensorParser::CreateSensor(void)
{
	result r = E_SUCCESS;
	bool success = true;

	if (__sensorManager.IsAvailable(SENSOR_TYPE_ACCELERATION))
	{
		r = __sensorManager.AddSensorListener(*this, SENSOR_TYPE_ACCELERATION, 50, true);
		if (IsFailed(r))
		{
			success = false;
		}
	}
	else
	{
		AppLogException("Acceleration sensor is not available.");
		success = false;
	}


	//Currently not enabled on phone.
	if (__sensorManager.IsAvailable(SENSOR_TYPE_TILT))
	{
		r = __sensorManager.AddSensorListener(*this, SENSOR_TYPE_TILT, 50, true);
		if (IsFailed(r))
		{
			return false;
		}
	}
	else
	{
		AppLogException("Tilt sensor is not available.");
		return false;
	}

	//Currently not enabled on phone.
	if (__sensorManager.IsAvailable(SENSOR_TYPE_MAGNETIC))
	{
		r = __sensorManager.AddSensorListener(*this, SENSOR_TYPE_MAGNETIC, 50, true);
		if (IsFailed(r))
		{
			success = false;
		}
	}
	else
	{
		AppLogException("Magnetic sensor is not available.");
		success = false;
	}

	return success;
}

void SensorParser::StopParsing(void)
{
	__sensorManager.RemoveSensorListener(*this);
}
