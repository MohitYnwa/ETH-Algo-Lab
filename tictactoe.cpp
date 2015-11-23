#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Index {
	int x,y;
	Index() {}
	
	Index(int x1,int y1)
	{
		x=x1;
		y=y1;
	}
};

struct Move {
	int playerId;
	int value;	
	Index moveIndex;
	Index gameIndex;
	Move(int pid, int val,Index moveIndex1, Index gameIndex1)
	{
		playerId = pid;
		value =val;
		moveIndex = moveIndex1;
		gameIndex = gameIndex1;
	}
	Move() {
	}
};

class Player {
	int id;
	public:
		Player(int id) : id(id)
		{}
		Player() {
		}
};

class HumanPlayer : public Player {
	public:
	HumanPlayer(int id)	 : Player(id) {
	}
};

class ComputerPlayer : public Player {
	public:
	ComputerPlayer(int id) : Player(id) {
	}
};

class Board {
	protected:
		int dimension;
	public:
		Board(int dimension)
		{
			this->dimension = dimension;
		}
		
		Board()
		{
			dimension = 0;
		}
		virtual void set(int playerid, Index index, int value) { }
		virtual int getBoardValue(Index index) {}
		virtual int getPlayerValue(Index index) {}
		virtual int getDimension()
		{
			return dimension;
		}
};

class TicTacToeBoard: public Board {
	vector < vector< int> > _board;
	vector < vector< int> > _player;
	public: 
		TicTacToeBoard(int dim) : Board(dim)
		{

			_board = vector<vector< int > > (dimension, vector<int> (dimension,0));
			_player = vector<vector< int > > (dimension, vector<int> (dimension,0));
		}
		
		void set(int playerid, Index index, int value)
		{
			_player[index.x][index.y] = playerid;
			_board[index.x][index.y] = value;
		}
		
		int getBoardValue(Index index) 
		{
			return _board[index.x][index.y];
		}
		
		int getPlayerValue(Index index) 
		{
			return _player[index.x][index.y];
		}
};


class RuleEngine {
	protected: 
		int winner;
		Board *board;
	public:
		RuleEngine(Board* board)
		{
			this->board = board;
		}
		
		RuleEngine() {
		}
		
		virtual bool isValidMove(int player, Index index, int value)  { cout<<"base"<<endl; return false;};
		
		virtual bool evaluateGame() { return true;}
		
		int getWinner() { 
			return winner;
		}
};

class TicTacToeRuleEngine : public RuleEngine {
		
	public:
		TicTacToeRuleEngine(Board* board) : RuleEngine(board)
		{
			
		}
		
		bool isValidMove(int player, Index index, int value)
		{
			
			int boardval = this->board->getBoardValue(index);
			int playerval = this->board->getPlayerValue(index);
			
			if (playerval == 0 && boardval ==0) return true;
			
			return false;
		}
		
		bool evaluateGame()
		{			
			//Check rows
			int dim = this->board->getDimension();
			for (int i=0;i<dim;i++)
			{
				int player =  this->board->getPlayerValue(Index(i,0)) ;
				if (player ==0) return false;
				bool success = true;
				for (int j=1;j<dim;j++)
				{
					
					if(this->board->getPlayerValue(Index(i,j)) !=  player) {
						success = false;
						break;
					}
				}
				if (success == true) { 
					winner=player;
					return true;
				}
			}
			
			//Check columns
			for (int j=0;j<dim;j++)
			{
				int player =  this->board->getPlayerValue(Index(0,j));
				if (player==0) return false;
				bool success = true;
				for (int i=1;i<dim;i++)
				{
					if(this->board->getPlayerValue(Index(i,j)) !=  player) {
						success = false;
						break;
					}
				}
				if (success == true) { 
					winner=player;
					return true;
				}
			}
			
			return false;
		}
};

class Game {
	Board *board;	
	RuleEngine *ruleEngine;
	public:
		Game(Board *board,RuleEngine *ruleEngine) 
		{
			this->board = board;	
			this->ruleEngine = ruleEngine;
		}
		
		bool move(int player, Index index, int value)
		{
			//cout<<player<<value<<endl;
			
			if (ruleEngine->isValidMove(player, index, value))
			 {
			 	board->set(player, index, value);
			 	return true;
			 }
			return false;
		}	
		
		bool evaluateGame()
		{
			this->ruleEngine->evaluateGame();
		}
		
		int declareWinner()
		{
			return ruleEngine->getWinner();
		}
};



class GameBoard {
	private:
		vector<vector<Game> > games;
		vector<Player> players;
	public:
		
		GameBoard(vector<vector<Game> > games1, vector<Player> players)	
		{
			this->games = games1;
			this->players = players;
		}
		
		bool playGame(Move move)
		{
			Game game = games[move.gameIndex.x][move.gameIndex.y];
			
			return game.move(move.playerId, move.moveIndex, move.value);
		}
		
		bool evaluateBoard()
		{
			bool complete = true;
			for (int i=0;i<games.size();i++)	
			{
				for (int j=0;j<games[i].size();j++)
				{
					complete &= games[i][j].evaluateGame();
				}
			}
			
			return complete;
		}
		
		void declareWinner()
		{
			
			for (int i=0;i<games.size();i++)	
			{
				for (int j=0;j<games[i].size();j++)
				{
					cout<<"Winner of board ["<<i<<","<<j<<"] is "<<games[i][j].declareWinner()<<endl;
				}
			}
		}
};

enum GameType { TIC_TAC_TOE, CHESS, MONOPOLY };
class GameBoardFactory {
	
	private:
		static Game getGame(GameType gameType,int dimension)
		{
			if (gameType == TIC_TAC_TOE)
			{		
				Board* board = new TicTacToeBoard(dimension);
				return Game(board, new TicTacToeRuleEngine(board) );
				
			}
		}
	public:
		static GameBoard getGameBoard(vector<vector<GameType> > gameTypes, vector<Player> players,int dimension)
		{
			int size =gameTypes.size();
			vector<vector<Game> > games(size);
			for (int i=0;i<gameTypes.size();i++)		
				for (int j=0;j<gameTypes[i].size();j++)
					games[i].push_back(getGame(gameTypes[i][j],dimension));
					
			return GameBoard(games,players);
		}
};

enum PlayerType { HUMAN, COMPUTER };
	
class PlayerFactory {
	public:
		static Player getPlayer(PlayerType playerType, int id)
		{
			if (playerType ==  HUMAN)	return  HumanPlayer(id);
			if (playerType ==  COMPUTER) return ComputerPlayer(id);
		}
};

//Human Player/Computer
int main()
{		
	
	PlayerFactory playerFactory;
	
	Player humanPlayer = playerFactory.getPlayer(HUMAN, 1);
	Player computerPlayer = playerFactory.getPlayer(COMPUTER,2);
	vector<Player> players(2);
	players[0] = humanPlayer; players[1] = computerPlayer;
	
	vector <vector <GameType> > gameTypes(1,vector<GameType>(1));
	gameTypes[0][0]=TIC_TAC_TOE;
	
	GameBoardFactory gameBoardFactory;
	GameBoard gameBoard = gameBoardFactory.getGameBoard(gameTypes, players, 3); //Game Board initializes the board and the individual games
	cout<<1<<endl;
	vector<vector<Move> > playerMoves(3, vector<Move> (2)); //2 players - 3 moves each
	//Move 1
	playerMoves[0][0] = Move(1, 1, Index(0,0), Index(0,0));
	playerMoves[0][1] = Move(2, 2, Index(1,0), Index(0,0));
	//Move2
	playerMoves[1][0] = Move(1, 1, Index(0,1), Index(0,0));
	playerMoves[1][1] = Move(2, 2, Index(2,0), Index(0,0));
	//Move3
	playerMoves[2][0] = Move(1, 1, Index(0,2), Index(0,0));
	playerMoves[2][1] = Move(2, 2, Index(1,1), Index(0,0));
	
	int noPlayers = playerMoves[0].size();
	int noMoves = playerMoves.size();
	
	for (int i=0;i<noMoves;i++) 
	{
		for (int j=0;j<noPlayers; j++)
		{
			cout<<"Move :"<<i<<" Player:"<<j<<endl;
			bool success = gameBoard.playGame(playerMoves[i][j]);

			if (!success) cout<<"Invalid Move player no:"<<j<<endl;	
			bool gameResult = gameBoard.evaluateBoard();
			if (gameResult)
			{
				gameBoard.declareWinner();
				return 0;
			}
		}
	}
	
	return 0;
}

