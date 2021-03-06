/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
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

	//float GetGameTimer() { return m_game_timer; }

private:
	Server();

	bool	InitNetworkManager();
	void	SetupWorld();
	/*sf::Time tick_rate;
	sf::Time tick_time;
	sf::Clock tick_clock;
	sf::Time m_pickup_spawn_countdown;
	sf::Time m_enemy_spawn_countdown;
	sf::Time m_boat_spawn_countdown;
	sf::Time m_rock_spawn_countdown;*/
	float m_pickup_spawn_countdown;
	float m_enemy_spawn_countdown;
	float m_rock_spawn_countdown;
	float m_boat_spawn_countdown;
	float m_game_timer;
};

