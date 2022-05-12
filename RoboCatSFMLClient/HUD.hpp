//I take care of rendering things!

class HUD
{
public:

	static void StaticInit();
	static std::unique_ptr< HUD >	sInstance;

	void Render();

	void SetPlayerHealth(int inHealth) { mHealth = inHealth; }
	
	void UpdateRemainingTime(float remaining_time);
	void SetGameOver(bool value) { m_is_game_over = value; }

private:

	HUD();
	void RenderGameTimer();
	void RenderGameOver();
	void	RenderBandWidth();
	void	RenderRoundTripTime();
	void	RenderScoreBoard();
	void	RenderHealth();
	void	RenderText(const string& inStr, const Vector3& origin, const Vector3& inColor);

	Vector3										mBandwidthOrigin;
	Vector3										mRoundTripTimeOrigin;
	Vector3										mScoreBoardOrigin;
	Vector3										mScoreOffset;
	Vector3										mHealthOffset;
	Vector3 m_game_timer_offset;
	Vector3 m_game_over_offset;
	int											mHealth;
	int m_minutes;
	int m_seconds;
	bool m_is_game_over;
	string m_winner;
};



