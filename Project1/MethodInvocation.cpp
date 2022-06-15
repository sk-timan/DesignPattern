#include "MethodInvocation.h"
#include <iostream>
#include <windows.h>

LightOnCommand::LightOnCommand(Light* light)
{
	Name = "Light on";
	this->light = light;
}

void LightOnCommand::execute()
{
	light->On();
}
void LightOnCommand::undo()
{
	light->Off();
}

void SimpleRemoteControl::setCommand(Command* command)
{
	this->slot = command;
}

void SimpleRemoteControl::buttonWasPressed()
{
	slot->execute();
}

void MethodInvocation::RemoteControlTestFunc()
{
	SimpleRemoteControl* remote = new SimpleRemoteControl();
	Light* light = new Light("livingRoom");
	LightOnCommand* lightOn = new LightOnCommand(light);

	remote->setCommand(lightOn);
	remote->buttonWasPressed();

	delete remote;
	delete lightOn;
	delete light;

	lightOn = nullptr;
	light = nullptr;
	remote = nullptr;
}

void MethodInvocation::RemoteLoaderTestFunc()
{
	RemoteControl* remotecontrol = new RemoteControl();

	Light* livingRoomLight = new Light("Living Room");
	Light* kitchenLight = new Light("Kitchen");
	CeilingFan* ceilingFan = new CeilingFan("Living Room");
	GarageDoor* garageDoor = new GarageDoor("");
	Stereo* stereo = new Stereo("Living Room");

	LightOnCommand* livingRoomLightOn = new LightOnCommand(livingRoomLight);
	LightOffCommand* livingRoomLightOff = new LightOffCommand(livingRoomLight);
	LightOnCommand* kitchenLightOn = new LightOnCommand(kitchenLight);
	LightOffCommand* kitchenLightOff = new LightOffCommand(kitchenLight);

	CeilingFanOnCommand* ceilingFanOn = new CeilingFanOnCommand(ceilingFan);
	CeilingFanOffCommand* ceilingFanOff = new CeilingFanOffCommand(ceilingFan);

	StereoOnWithCDCommand* stereoOnWithCD = new StereoOnWithCDCommand(stereo);
	StereoOffCommand* stereoOff = new StereoOffCommand(stereo);

	remotecontrol->setCommand(0, livingRoomLightOn, livingRoomLightOff);
	remotecontrol->setCommand(1, kitchenLightOn, kitchenLightOff);
	remotecontrol->setCommand(2, ceilingFanOn, ceilingFanOff);
	remotecontrol->setCommand(3, stereoOnWithCD, stereoOff);

	std::cout << remotecontrol->ToString();

	remotecontrol->OnButtonWasPushed(0);
	remotecontrol->OffButtonWasPushed(0);
	remotecontrol->OnButtonWasPushed(1);
	remotecontrol->OffButtonWasPushed(1);
	remotecontrol->OnButtonWasPushed(2);
	remotecontrol->OffButtonWasPushed(2);
	remotecontrol->OnButtonWasPushed(3);
	remotecontrol->OffButtonWasPushed(3);

	RemoteControlWithUndo* remoteControl = new RemoteControlWithUndo();
	remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);

	remoteControl->OnButtonWasPushed(0);
	remoteControl->OffButtonWasPushed(0);
	std::cout << remoteControl->ToString();
	remoteControl->undoButtonWasPushed();
	remoteControl->OffButtonWasPushed(0);
	remoteControl->OnButtonWasPushed(0);
	std::cout << remoteControl->ToString();
	remoteControl->undoButtonWasPushed();

}

Light::Light(std::string installplace)
{
	Installplace = installplace;
}

void Light::On()
{
	std::cout << Installplace + " Light is On.\n";
}

void Light::Off()
{
	std::cout << Installplace + " Light is Off.\n";
}

RemoteControl::RemoteControl()
{
	//Command* tempOnCom = new Command[NUM_COMMANDS];
	//Command* tempOffCom = new Command[NUM_COMMANDS];
	//onCommands.insert(onCommands.begin(), tempOnCom, tempOnCom+ NUM_COMMANDS);
	//offCommands.insert(offCommands.end(), tempOffCom, tempOffCom + NUM_COMMANDS);

	onCommands.resize(NUM_COMMANDS);
	offCommands.resize(NUM_COMMANDS);

	Command* noCommand = new NoCommand();
	for (int i = 0; i < NUM_COMMANDS; i++)
	{
		onCommands[i] = noCommand;
		offCommands[i] = noCommand;
	}
}

void RemoteControl::setCommand(int slot, Command* onCommand, Command* offCommand)
{
	onCommands[slot] = onCommand;
	offCommands[slot] = offCommand;
}

void RemoteControl::OnButtonWasPushed(int slot)
{
	onCommands[slot]->execute();
}

void RemoteControl::OffButtonWasPushed(int slot)
{
	offCommands[slot]->execute();
}

std::string RemoteControl::ToString()
{
	std::string* stringBuff = new std::string();
	stringBuff->append("\n----- Remote Control -----\n");
	for (int i = 0; i < onCommands.size(); i++)
		stringBuff->append("[slot " + std::to_string(i) + "] " + onCommands[i]->getName() + "    " + offCommands[i]->getName() + "\n");

	return stringBuff->data();
}

void NoCommand::execute()
{
}

NoCommand::NoCommand()
{
	Name = "No Command";
}

LightOffCommand::LightOffCommand(Light* light)
{
	Name = "Light off";
	this->light = light;
}

void LightOffCommand::execute()
{
	light->Off();
}

void LightOffCommand::undo()
{
	light->On();
}

Stereo::Stereo(std::string installplace)
{
	Installplace = installplace;
}

void Stereo::On()
{
	std::cout << Installplace + " Stereo is On.\n";
}

void Stereo::setCD()
{
	std::cout << Installplace + " Stereo is Set for CD input\n";
}

void Stereo::setVolume(int val)
{
	std::cout << Installplace + " Stereo set Volume : " + std::to_string(val) + "\n";
}

void Stereo::Off()
{
	std::cout << Installplace + " Stereo is Off.\n";
}

CeilingFan::CeilingFan(std::string installplace)
{
	Installplace = installplace;
}

void CeilingFan::On()
{
	std::cout << Installplace + " CeilingFan is On.\n";
}

void CeilingFan::Off()
{
	std::cout << Installplace + " CeilingFan off.\n";
}

GarageDoor::GarageDoor(std::string installplace)
{
	Installplace = installplace;
}

void GarageDoor::Up()
{
	std::cout << Installplace + " GarageDoor is on.\n";
}

void GarageDoor::Down()
{
	std::cout << Installplace + " GarageDoor is off.\n";
}

CeilingFanOnCommand::CeilingFanOnCommand(CeilingFan* ceilingFan)
{
	Name = "CeilingFan On";
	this->ceilingFan = ceilingFan;
}

void CeilingFanOnCommand::execute()
{
	ceilingFan->On();
}

CeilingFanOffCommand::CeilingFanOffCommand(CeilingFan* ceilingFan)
{
	Name = "CeilingFan Off";
	this->ceilingFan = ceilingFan;
}

void CeilingFanOffCommand::execute()
{
	ceilingFan->Off();
}

GarageDoorUpCommand::GarageDoorUpCommand(GarageDoor* garageDoor)
{
	Name = "GarageDoor Up";
	this->garageDoor = garageDoor;
}

void GarageDoorUpCommand::execute()
{
	garageDoor->Up();
}

GarageDoorDownCommand::GarageDoorDownCommand(GarageDoor* garageDoor)
{
	Name = "GarageDoor Down";
	this->garageDoor = garageDoor;
}

void GarageDoorDownCommand::execute()
{
	garageDoor->Down();
}

StereoOnWithCDCommand::StereoOnWithCDCommand(Stereo* stereo)
{
	Name = "Stereo On";
	this->stereo = stereo;
}

void StereoOnWithCDCommand::execute()
{
	stereo->On();
	stereo->setCD();
	stereo->setVolume(11);

}

StereoOffCommand::StereoOffCommand(Stereo* stereo)
{
	Name = "Stereo Off";
	this->stereo = stereo;
}

void StereoOffCommand::execute()
{
	stereo->Off();
}

RemoteControlWithUndo::RemoteControlWithUndo()
{
	undoCommand = new NoCommand();
}

void RemoteControlWithUndo::OnButtonWasPushed(int slot)
{
	onCommands[slot]->execute();
	undoCommand = onCommands[slot];
}

void RemoteControlWithUndo::OffButtonWasPushed(int slot)
{
	offCommands[slot]->execute();
	undoCommand = offCommands[slot];
}

void RemoteControlWithUndo::undoButtonWasPushed()
{
	undoCommand->undo();
}

std::string RemoteControlWithUndo::ToString()
{
	std::string* stringBuff = new std::string();
	stringBuff->append("\n----- Remote Control -----\n");
	for (int i = 0; i < onCommands.size(); i++)
		stringBuff->append("[slot " + std::to_string(i) + "] " + onCommands[i]->getName() + "    " + offCommands[i]->getName() + "\n");
	if (undoCommand != nullptr)
		stringBuff->append("[undo] " + undoCommand->getName() + "\n");

	return stringBuff->data();
}
