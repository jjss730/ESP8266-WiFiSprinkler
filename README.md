# ESP8266-WiFiSprinkler
WiFi Sprinkler files 

1. Introduction

This project consists of creating a Sprinkler controlled via Wi-Fi.


2. Main building blocks

The WiFiSprinkler is part of a larger project which is a smart home control network. At the moment,
the main building blocks are:
	- MQTT broker (based on a Raspberry Pi 3)
	- WiFiSprinkler - This project - To control a 8 channel sprinkler system
	- RTC Server - provides a Real Time Clock syncronization by publishing a time stamp
	  tag in the MQTT network.

3. Revisions
	Rev01 : Basic controls and communication functions of WiFiSprinkler
		Successfull communication to MQTT broker
		Manual control of WiFiSprinkler channels via MQTT client in Smart Phone (IoT Controller app) 
