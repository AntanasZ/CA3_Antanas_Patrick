class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient(ClientProxyPtr inClientProxy);
	void HandleLostClient(ClientProxyPtr inClientProxy);

	PlayerPtr	GetSharkForPlayer(int inPlayerId);
	void	SpawnSharkForPlayer(int inPlayerId);


private:
	Server();

	bool	InitNetworkManager();
	void	SetupWorld();
	sf::Time tick_rate;
	sf::Time tick_time;
	sf::Clock tick_clock;
	sf::Time m_pickup_spawn_countdown;
	sf::Time m_enemy_spawn_countdown;
	sf::Time m_rock_spawn_countdown;
};

