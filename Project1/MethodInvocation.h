#pragma once
#include <vector>
#include <string>

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
	void Off();

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

	virtual void execute() {};
	virtual void undo() {};

	std::string getName() { return Name; };

protected:
	std::string Name;
};

class NoCommand : public Command
{
public:
	NoCommand();

	virtual void execute()override;
};

class LightOnCommand : public Command
{
public:
	LightOnCommand(Light* light);

	virtual void execute() override;
	virtual void undo() override;

private:
	Light* light;
};

class LightOffCommand : public Command
{
public:
	LightOffCommand(Light* light);

public:
	virtual void execute()override;
	virtual void undo() override;

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

class GarageDoorUpCommand : public Command
{
public:
	GarageDoorUpCommand(GarageDoor* garageDoor);

	virtual void execute() override;

private:
	GarageDoor* garageDoor;
};

class GarageDoorDownCommand : public Command
{
public:
	GarageDoorDownCommand(GarageDoor* garageDoor);

	virtual void execute() override;

private:
	GarageDoor* garageDoor;
};

class StereoOnWithCDCommand : public Command
{
public:
	StereoOnWithCDCommand(Stereo* stereo);

	virtual void execute() override;

private:
	Stereo* stereo;
};

class StereoOffCommand : public Command
{
public:
	StereoOffCommand(Stereo* stereo);

	virtual void execute() override;

private:
	Stereo* stereo;
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

	std::string ToString();

protected:
	std::vector<Command*> onCommands;
	std::vector<Command*> offCommands;
};

class RemoteControlWithUndo : public RemoteControl
{
public:
	RemoteControlWithUndo();

	void OnButtonWasPushed(int slot);

	void OffButtonWasPushed(int slot);

	void undoButtonWasPushed();

	std::string ToString();

private:
	Command* undoCommand;
};

class MethodInvocation
{
public:
	static void RemoteControlTestFunc();
	static void RemoteLoaderTestFunc();
};

