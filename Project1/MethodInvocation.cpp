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

	CeilingFanMediumCommand* ceilingFanMedium = new CeilingFanMediumCommand(ceilingFan);
	CeilingFanHighCommand* ceilingFanHigh = new CeilingFanHighCommand(ceilingFan);

	remoteControl->setCommand(0, ceilingFanMedium, ceilingFanOff);
	remoteControl->setCommand(1, ceilingFanHigh, ceilingFanOff);

	remoteControl->OnButtonWasPushed(0);
	remoteControl->OffButtonWasPushed(0);
	std::cout << remoteControl->ToString();
	remoteControl->undoButtonWasPushed();

	remoteControl->OnButtonWasPushed(1);
	std::cout << remoteControl->ToString();
	remoteControl->undoButtonWasPushed();

	std::cout << "-----------------------------------\n";
	TV* tv = new TV("Living Room");
	Hottub* hottub = new Hottub();
	TVOnCommand* tvOn = new TVOnCommand(tv);
	HottubOnCommand* hottubOn = new HottubOnCommand(hottub);
	TVOffCommand* tvOff = new TVOffCommand(tv);
	HottubOffCommand* hottubOff = new HottubOffCommand(hottub);

	Command* partyOn[] = { livingRoomLightOn,stereoOnWithCD,tvOn,hottubOn };
	Command* partyOff[] = { livingRoomLightOff,stereoOff,tvOff,hottubOff };
	MacroCommand* partyOnMacro = new MacroCommand(partyOn, sizeof(partyOn) / sizeof(Command*));
	MacroCommand* partyOffMacro = new MacroCommand(partyOff, sizeof(partyOff) / sizeof(Command*));

	remoteControl->setCommand(0, partyOnMacro, partyOffMacro);
	std::cout << remoteControl->ToString() << "--- Pushing Macro On ---\n";
	remoteControl->OnButtonWasPushed(0);

	std::cout << "--- Pushing Undo ---\n";
	remoteControl->undoButtonWasPushed();

	std::cout << "--- Pushing Macro Off ---\n";
	remoteControl->OffButtonWasPushed(0);

	std::cout << "--- Pushing Undo ---\n";
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

int CeilingFan::HIGH = 3;
int CeilingFan::MEDIUM = 2;
int CeilingFan::LOW = 1;
int CeilingFan::OFF = 0;

CeilingFan::CeilingFan(std::string installplace)
{
	Installplace = installplace;
	speed = OFF;
}

void CeilingFan::On()
{
	std::cout << Installplace + " CeilingFan is On.\n";
}

void CeilingFan::Off()
{
	speed = OFF;
	std::cout << Installplace + " CeilingFan off.\n";
}

void CeilingFan::high()
{
	speed = HIGH;
	std::cout << Installplace + " CeilingFan is on High.\n";
}

void CeilingFan::medium()
{
	speed = MEDIUM;
	std::cout << Installplace + " CeilingFan is on Medium.\n";
}

void CeilingFan::low()
{
	speed = LOW;
	std::cout << Installplace + " CeilingFan is on Low.\n";
}

int CeilingFan::getSpeed()
{
	return speed;
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
	prevSpeed = ceilingFan->getSpeed();
	ceilingFan->Off();
}

void CeilingFanOffCommand::undo()
{
	if (prevSpeed == CeilingFan::HIGH)
		ceilingFan->high();
	else if (prevSpeed == CeilingFan::MEDIUM)
		ceilingFan->medium();
	else if (prevSpeed == CeilingFan::LOW)
		ceilingFan->low();
	else if (prevSpeed == CeilingFan::OFF)
		ceilingFan->Off();

}

CeilingFanHighCommand::CeilingFanHighCommand(CeilingFan* ceilingFan)
{
	Name = "CeilingFan High";
	this->ceilingFan = ceilingFan;
}

void CeilingFanHighCommand::execute()
{
	prevSpeed = ceilingFan->getSpeed();
	ceilingFan->high();
}

void CeilingFanHighCommand::undo()
{
	if (prevSpeed == CeilingFan::HIGH)
		ceilingFan->high();
	else if (prevSpeed == CeilingFan::MEDIUM)
		ceilingFan->medium();
	else if (prevSpeed == CeilingFan::LOW)
		ceilingFan->low();
	else if (prevSpeed == CeilingFan::OFF)
		ceilingFan->Off();

}

CeilingFanMediumCommand::CeilingFanMediumCommand(CeilingFan* ceilingFan)
{
	Name = "CeilingFan Medium";
	this->ceilingFan = ceilingFan;
}

void CeilingFanMediumCommand::execute()
{
	prevSpeed = ceilingFan->getSpeed();
	ceilingFan->medium();
}

void CeilingFanMediumCommand::undo()
{
	if (prevSpeed == CeilingFan::HIGH)
		ceilingFan->high();
	else if (prevSpeed == CeilingFan::MEDIUM)
		ceilingFan->medium();
	else if (prevSpeed == CeilingFan::LOW)
		ceilingFan->low();
	else if (prevSpeed == CeilingFan::OFF)
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

void StereoOnWithCDCommand::undo()
{
	stereo->Off();
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

void StereoOffCommand::undo()
{
	stereo->On();
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

void MacroCommand::execute()
{
	for (int i = 0; i < commands.size(); i++)
		commands[i]->execute();
}

void MacroCommand::undo()
{
	for (int i = 0; i < commands.size(); i++)
		commands[i]->undo();

}

MacroCommand::MacroCommand(Command** commands, size_t num)
{
	Name = "MacroCommand";
	this->commands.resize(num);
	this->commands.assign(commands, commands + num);
}

TV::TV(std::string Installplace)
{
	this->Installplace = Installplace;
}

void TV::On()
{
	std::cout << Installplace + " TV is On.\n";
}

void TV::Off()
{
	std::cout << Installplace + " TV is Off.\n";
}

void TV::setInputChannel(int Cha)
{
}

void TV::setVolume(int val)
{
	std::cout << Installplace + " TV set Volume : " + std::to_string(val) + "\n";
}

Hottub::Hottub()
{
}

void Hottub::On()
{
	std::cout << "Hottub is On.\n";
}

void Hottub::Off()
{
	std::cout << "Hottub is Off.\n";
}

void Hottub::Circulate()
{
}

void Hottub::jetsOn()
{
}

void Hottub::jetsOff()
{
}

void Hottub::setTemperature(int temp)
{
}

TVOnCommand::TVOnCommand(TV* tv)
{
	this->tv = tv;
}

void TVOnCommand::execute()
{
	tv->On();
}

void TVOnCommand::undo()
{
	tv->Off();
}

TVOffCommand::TVOffCommand(TV* tv)
{
	this->tv = tv;
}

void TVOffCommand::execute()
{
	tv->Off();
}

void TVOffCommand::undo()
{
	tv->On();
}

HottubOnCommand::HottubOnCommand(Hottub* hottub)
{
	this->hottub = hottub;
}

void HottubOnCommand::execute()
{
	hottub->On();
}

void HottubOnCommand::undo()
{
	hottub->Off();
}

HottubOffCommand::HottubOffCommand(Hottub* hottub)
{
	this->hottub = hottub;
}

void HottubOffCommand::execute()
{
	hottub->Off();
}

void HottubOffCommand::undo()
{
	hottub->On();
}