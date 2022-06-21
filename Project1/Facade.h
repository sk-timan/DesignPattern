#pragma once
#include <string>

class Tuner;
class DVDPlayer;
class CDPlayer;

class Amplifier
{
public:
	void on();
	void off();
	void setCD();
	void setDVD();
	void setStereoSound();
	void setSurroundSound();
	void setTuner();
	void setVolume(int vol);
	void toString();

private:
	Tuner* tuner;
	DVDPlayer* dvdPlayer;
	CDPlayer* cdPlayer;

};

class Tuner
{
public:
	void on();
	void off();
	void setAm();
	void setFm();
	void setFrequency();
	void toString();
private:
	Amplifier* amplifier;
};

class DVDPlayer
{
public:
	void on();
	void off();
	void eject();
	void pause();
	void play();
	void setSurroundAudio();
	void setTwoChannelAudio();
	void stop();

private:
	Amplifier* amplifier;
};

class CDPlayer
{
public:
	void on();
	void off();
	void eject();
	void pause();
	void play();
	void stop();
	void toString();

private:
	Amplifier* amplifier;
};
class Screen
{
public:
	void up();
	void down();
	void toString();
};

class PopcornPopper
{
public:
	void on();
	void off();
	void pop();
	void toString();

};

class TheaterLights
{
public:
	void on();
	void off();
	void dim(int val);
	void toString();

};

class Projector
{
public:
	void on();
	void off();
	void tvMode();
	void wideScreenMode();
	void toString();

private:
	DVDPlayer* dvdPlayer;

};
class HomeTheaterFacade
{
public:
	HomeTheaterFacade(
		Amplifier* amp,
		Tuner* tuner,
		DVDPlayer* dvd,
		CDPlayer* cd,
		Projector* projector,
		TheaterLights* lights,
		Screen* screen,
		PopcornPopper* popper);

public:
	void watchMovie(std::string movie);

	void endMovie();

private:
	Amplifier* amp;
	Tuner* tuner;
	DVDPlayer* dvd;
	CDPlayer* cd;
	Projector* projector;
	TheaterLights* lights;
	Screen* screen;
	PopcornPopper* popper;

};

class Facade
{
public:
	static void HomeTheaterTestDrive();
};

