#pragma once
#include <vector>

#define NUM_COMMANDS 7
class Light
{
public:
	Light(std::string installplace);

public:
	void On();
	void Off();
private:
	std::string Installplace;
};

class Stereo
{
public:
	Stereo(std::string installplace);

public:
	void On();
	void setCD();
	void setVolume(int val);
private:
	std::string Installplace;
};

class CeilingFan
{
public:
	CeilingFan(std::string installplace);

public:
	void On();
	void Off();
private:
	std::string Installplace;
};

class GarageDoor
{
public:
	GarageDoor(std::string installplace);

public:
	void Up();
	void Down();
private:
	std::string Installplace;
};


class Command
{
public:
	virtual void execute(){};

	std::string getName() { return Name; };

protected:
	std::string Name;
};

class NoCommand : public Command
{
public:
	virtual void execute()override;
};

class LightOnCommand : public Command
{
public:
	LightOnCommand(Light* light);

	virtual void execute() override;

private:
	Light* light;
};

class LightOffCommand : public Command
{
public:
	LightOffCommand(Light* light);

public:
	virtual void execute()override;

private:
	Light* light;
};

class CeilingFanOnCommand : public Command
{
public:
	CeilingFanOnCommand(CeilingFan* ceilingFan);

	virtual void execute() override;

private:
	CeilingFan* ceilingFan;
};

class CeilingFanOffCommand : public Command
{
public:
	CeilingFanOffCommand(CeilingFan* ceilingFan);

	virtual void execute() override;

private:
	CeilingFan* ceilingFan;
};

class SimpleRemoteControl
{
public:
	SimpleRemoteControl() {};

	void setCommand(Command* command);

	void buttonWasPressed();

private:
	Command* slot = nullptr;
};

class RemoteControl
{
public:
	RemoteControl();

	void setCommand(int slot, Command* onCommand, Command* offCommand);

	void OnButtonWasPushed(int slot);

	void OffButtonWasPushed(int slot);

	std::string toString();

private:
	std::vector<Command*> onCommands;
	std::vector<Command*> offCommands;
};

class MethodInvocation
{
public:
	static void RemoteControlTestFunc();
	static void RemoteLoaderTestFunc();
};

