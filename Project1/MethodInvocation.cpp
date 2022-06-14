#include "MethodInvocation.h"
#include <iostream>

LightOnCommand::LightOnCommand(Light* light)
{
	Name = "Light on";
	this->light = light;
}

void LightOnCommand::execute()
{
	light->On();
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



}

Light::Light(std::string installplace)
{
	Installplace = installplace;
}

void Light::On()
{
	std::cout << "%s Light is On.\n",Installplace;
}

void Light::Off()
{
	std::cout << "%s Light is Off.\n",Installplace;
}

RemoteControl::RemoteControl()
{
	Command* tempOnCom = new Command[NUM_COMMANDS];
	Command* tempOffCom = new Command[NUM_COMMANDS];

	onCommands.insert(onCommands.end(), tempOnCom, tempOnCom + NUM_COMMANDS);
	offCommands.insert(offCommands.end(), tempOffCom, tempOffCom + NUM_COMMANDS);

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

std::string RemoteControl::toString()
{
	std::string* stringBuff = new std::string();
	stringBuff->append("\n----- Remote Control -----\n");
	for (int i = 0; i < onCommands.size(); i++)
	{
		stringBuff->append(("[slot %d] %s     %s\n",i, onCommands[i]->getName(), offCommands[i]->getName()).c_str());
	}
	return stringBuff->data();
}

void NoCommand::execute()
{

}

LightOffCommand::LightOffCommand(Light* light)
{
	this->light = light;
}

void LightOffCommand::execute()
{
	light->Off();
}

Stereo::Stereo(std::string installplace)
{
	Installplace = installplace;
}

void Stereo::On()
{
	std::cout << "%s Stereo is On.\n",Installplace;
}

void Stereo::setCD()
{
	std::cout << "%s Stereo set CD.\n",Installplace;
}

void Stereo::setVolume(int val)
{
	std::cout << "%s Stereo set Volume: %d.\n", val;
}

CeilingFan::CeilingFan(std::string installplace)
{
	Installplace = installplace;
}

void CeilingFan::On()
{
	std::cout << "%s CeilingFan is On.\n",Installplace;
}

void CeilingFan::Off()
{
	std::cout << "%s CeilingFan off.\n",Installplace;
}

GarageDoor::GarageDoor(std::string installplace)
{
	Installplace = installplace;
}

void GarageDoor::Up()
{
	std::cout << "%s GarageDoor is on.\n",Installplace;
}

void GarageDoor::Down()
{
	std::cout << "%s GarageDoor is off.\n",Installplace;
}

CeilingFanOnCommand::CeilingFanOnCommand(CeilingFan* ceilingFan)
{
	this->ceilingFan = ceilingFan;
}

void CeilingFanOnCommand::execute()
{
	ceilingFan->On();
}

CeilingFanOffCommand::CeilingFanOffCommand(CeilingFan* ceilingFan)
{
	this->ceilingFan = ceilingFan;
}

void CeilingFanOffCommand::execute()
{
	ceilingFan->Off();
}
