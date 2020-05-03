#pragma once

class Game
{
	public:
		void start();

	private:
		void startSingleplayer();
		void startMultiplayerAsHost();
		void startMultiplayerAsPeer();
};