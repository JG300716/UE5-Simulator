// Fill out your copyright notice in the Description page of Project Settings.


#include "YawDevice.h"

YawDevice::YawDevice(FIPv4Address* ipAddress, int tcpPort, int udpPort, FString id, FString name, DeviceStatus status) :
    ipAddress(ipAddress), tcpPort(tcpPort), udpPort(udpPort), id(id), name(name), status(status)
{

}

void YawDevice::SetStatus(DeviceStatus statusDS)
{
	this->status = statusDS;
}
