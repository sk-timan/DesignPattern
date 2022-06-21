#include "Facade.h"
#include <iostream>

void Amplifier::on()
{
	std::cout << "Amplifier on.\n";
}

void Amplifier::off()
{
	std::cout << "Amplifier off.\n";
}

void Amplifier::setCD()
{
}

void Amplifier::setDVD()
{
	std::cout << "Amplifier setting DVD player.\n";
}

void Amplifier::setStereoSound()
{
}

void Amplifier::setSurroundSound()
{
	std::cout << "Amplifier set surround sound on.\n";
}

void Amplifier::setTuner()
{
}

void Amplifier::setVolume(int vol)
{
	std::cout << "Amplifier setting volume to " << vol << "\n";
}

void Amplifier::toString()
{
}

void Tuner::on()
{
}

void Tuner::off()
{
}

void Tuner::setAm()
{
}

void Tuner::setFm()
{
}

void Tuner::setFrequency()
{
}

void Tuner::toString()
{
}

void DVDPlayer::on()
{
	std::cout << "DVD Player on.\n";
}

void DVDPlayer::off()
{
	std::cout << "DVD Player off.\n";
}

void DVDPlayer::eject()
{

}

void DVDPlayer::pause()
{
	std::cout << "DVD Playing eject.\n";
}

void DVDPlayer::play()
{
	std::cout << "DVD Playing \"Raiders of the Lost Ark\".\n";
}

void DVDPlayer::setSurroundAudio()
{
}

void DVDPlayer::setTwoChannelAudio()
{
}

void DVDPlayer::stop()
{
	std::cout << "DVD player stopped \"Raiders of the Lost Ark\".";
}

void Screen::up()
{
	std::cout << "Theater screen going up.\n";
}

void Screen::down()
{
	std::cout << "Theater screen going down.\n";
}

void Screen::toString()
{
}

void PopcornPopper::on()
{
	std::cout << "Popcorn popper is on.\n";
}

void PopcornPopper::off()
{
	std::cout << "Popcorn popper off.\n";
}

void PopcornPopper::pop()
{
	std::cout << "Popcorn popper is popping.\n";
}

void PopcornPopper::toString()
{
}

void TheaterLights::on()
{
	std::cout << "Theater lights on\.";
}

void TheaterLights::off()
{
}

void TheaterLights::dim(int val)
{
	std::cout << "Theater lights dimming to " << val << "%.\n";
}

void TheaterLights::toString()
{
}

void Projector::on()
{
	std::cout << "Projector on.\n";
}

void Projector::off()
{
	std::cout << "Projector off.\n";
}

void Projector::tvMode()
{
}

void Projector::wideScreenMode()
{
	std::cout << "Projector in widescreen mode (16x9 aspect ratio).\n";
}

void Projector::toString()
{
}

void CDPlayer::on()
{
}

void CDPlayer::off()
{
}

void CDPlayer::eject()
{
}

void CDPlayer::pause()
{
}

void CDPlayer::play()
{
}

void CDPlayer::stop()
{
}

void CDPlayer::toString()
{
}

HomeTheaterFacade::HomeTheaterFacade(Amplifier* amp, Tuner* tuner, DVDPlayer* dvd, CDPlayer* cd, Projector* projector, TheaterLights* lights, Screen* screen, PopcornPopper* popper)
{
	this->amp = amp;
	this->cd = cd;
	this->dvd = dvd;
	this->lights = lights;
	this->popper = popper;
	this->projector = projector;
	this->screen = screen;
	this->tuner = tuner;
}

void HomeTheaterFacade::watchMovie(std::string movie)
{
	std::cout << "Get ready to watch a movie...\n";
	popper->on();
	popper->pop();
	lights->dim(10);
	screen->down();
	projector->on();
	projector->wideScreenMode();
	amp->on();
	amp->setDVD();
	amp->setSurroundSound();
	amp->setVolume(5);
	dvd->on();
	dvd->play();

}

void HomeTheaterFacade::endMovie()
{
	std::cout << "Shutting movie theater down...\n";
	popper->off();
	lights->on();
	screen->up();
	projector->off();
	amp->off();
	dvd->stop();
	dvd->eject();
	dvd->off();

}

void Facade::HomeTheaterTestDrive()
{
	Amplifier* amp = new Amplifier();
	Tuner* tuner = new Tuner();
	DVDPlayer* dvdPlayer = new DVDPlayer();
	CDPlayer* cdPlayer = new CDPlayer();
	Projector* projector = new Projector();
	TheaterLights* lights = new TheaterLights();
	Screen* screen = new Screen();
	PopcornPopper* popper = new PopcornPopper();

	HomeTheaterFacade* homeTheater = new HomeTheaterFacade(amp, tuner, dvdPlayer, cdPlayer, projector, lights, screen, popper);
	homeTheater->watchMovie("Raiders of the Lost Ark");
	homeTheater->endMovie();

}
