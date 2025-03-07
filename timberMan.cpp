#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
	VideoMode vm(1920,1080);
	
	RenderWindow window(vm,"Timber Man");
	
	View view(FloatRect(0,0,1920,1080));
	window.setView(view);
	
	Texture textureBackground;                                          //texture stores pixel value 
	
	textureBackground.loadFromFile("graphics/background.png");		   //sprite is basically a sticker attaching pic on gaming window	
	
	Sprite spriteBackground;									   // Used for BG Img
	
	spriteBackground.setTexture(textureBackground);                     //
	
	spriteBackground.setPosition(0,0);
	
	Texture textureTree;                                          //
	
	textureTree.loadFromFile("graphics/tree.png");		       //	
	
	Sprite spriteTree;									   // Used for Tree
	
	spriteTree.setTexture(textureTree);                           //
	
	spriteTree.setPosition(800,0);                                //
	
	Texture textureBee;                                          //
	
	textureBee.loadFromFile("graphics/bee.png");		   //	
	
	Sprite spriteBee;							   // Used for Bee Img
	
	spriteBee.setTexture(textureBee);                     //
	
	spriteBee.setPosition(0,700);						//
	
	bool BeeActive = false;
	float BeeSpeed = 0;
	
	Texture textureCloud;                                    //
	
	textureCloud.loadFromFile("graphics/cloud.png");		   //	
	
	Sprite spriteCloud1;							   // Used for cloud Img
	
	spriteCloud1.setTexture(textureCloud);                  //
	
	spriteCloud1.setPosition(0,50);
	
	spriteCloud1.setScale(0.75,0.75);
	
	Sprite spriteCloud2;						    	   // Used for cloud Img
	
	spriteCloud2.setTexture(textureCloud);                   //
	
	spriteCloud2.setPosition(0,150);
	
	spriteCloud1.setScale(0.89,0.89);

	Sprite spriteCloud3;							      // Used for cloud Img
	
	spriteCloud3.setTexture(textureCloud);                     //
	
	spriteCloud3.setPosition(0,250);
	
	bool CloudActive1 = false;
	bool CloudActive2 = false;
	bool CloudActive3 = false;
	float CloudSpeed1 = 0;
	float CloudSpeed2 = 0;
	float CloudSpeed3 = 0;
	
	
	Clock clock;
	
	RectangleShape timeBar;
	
	float timeBarStartWidth = 400;
	float timeBarHeight = 40;
	
	timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
	timeBar.setFillColor(Color::Yellow);
	timeBar.setPosition(750,960);
	
	Time gameTimeTotal;
	float timeRemaining = 6.0;//game starts with 6sec in hand of the player
	float timeBarWidthPerSecond = timeBarStartWidth/timeRemaining; // 400/6=66.6 pixels reduced per second
	
	bool paused = true; //
	int score=0;        // initially game is paused until start is pressed by user with initial score 0
	
	//for text of game
	Text messageText;
	Text messageText0;
	Text scoreText;
	Text scoreText0;
	
	Font font;
	font.loadFromFile("font/KOMIKAP_.ttf");
	messageText.setFont(font);
	messageText0.setFont(font);
	scoreText.setFont(font);
	scoreText0.setFont(font);
	
	messageText.setString("Press ENTER to start!!!");
	messageText0.setString("Press ENTER to start!!!");
	scoreText.setString("Score = 0");
	scoreText0.setString("Score = 0");
	
	messageText.setCharacterSize(75);
	messageText0.setCharacterSize(75);
	scoreText.setCharacterSize(50);
	scoreText0.setCharacterSize(50);
	
	messageText.setFillColor(Color::White);
	messageText0.setFillColor(Color::Black);
	scoreText.setFillColor(Color::White);
	scoreText0.setFillColor(Color::Black);
	
	FloatRect textRect1 = messageText.getLocalBounds(); //retrieves the local values of left,top,right,bottom of gaming window
	messageText.setOrigin(textRect1.left + textRect1.width/2, textRect1.top + textRect1.height/2); 
	messageText.setPosition(960,540);
	FloatRect textRect2 = messageText0.getLocalBounds(); //retrieves the local values of left,top,right,bottom of gaming window
	messageText0.setOrigin(textRect2.left + textRect2.width/2, textRect2.top + textRect2.height/2); 
	messageText0.setPosition(955,535);
	scoreText.setPosition(50,50);
	scoreText0.setPosition(46,46);
	
	//gaming loop	
		
	while(window.isOpen())                                              //
	{                                                                   //   
		Event event;                                                   //
		while(window.pollEvent(event))                                 // 
		{                                                              // used to ensure that the window doesnt close before pressing close
			if(event.type == Event::Closed)                           //
			{                                                         //
				window.close();                                      // 
			}                                                         //
		}                                                              //
		if(Keyboard::isKeyPressed(Keyboard::Escape))                 
		{
			window.close();
		}
		
		if(Keyboard::isKeyPressed(Keyboard::Return)) 
		//when enter is pressed by user game isn't paused anymore and starts with a score of 0             
		{
			paused=false;
			score=0;
		}
		
		Time dt = clock.restart(); //reinitialize the time
		
		if(!paused)
		{
			timeRemaining -= dt.asSeconds();  //makes time bar reduction frame rate independent : 6-(1/60)
			timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining,timeBarHeight));//decreases time bar 
				
			if(timeRemaining<=0)
			{
				paused=true; //stops the time bar after its exhausted
			}	
			
		}
		
		
		if(!BeeActive)
		{
			srand((int)time(0));
			BeeSpeed=(rand() % 200)+200; //random speed between 200 - 400
			float height=(rand() % 500)+500; //random height between 500 - 1000
			spriteBee.setPosition(2000,height); //initializes bee position
			BeeActive = true; //triggers else condition to run
		}
		
		else
		{
			spriteBee.setPosition(spriteBee.getPosition().x - (BeeSpeed * dt.asSeconds()),spriteBee.getPosition().y); 
			//dt.asSeconds() makes it fps independent/ frame rate independence
			//decreases X values for right to left movement with 60fps for example
			if(spriteBee.getPosition().x < 0)
			{
				BeeActive=false;	
			}
		}
		
		if(!CloudActive1)
		{
			srand((int)time(0)*10);
			CloudSpeed1=(rand() % 100)+100; //random speed between 200 - 400
			spriteCloud1.setPosition(-800,50); //initializes bee position
			float height=(rand() % 50)+400; //random height between 500 - 1000
			CloudActive1 = true; //triggers else condition to run
		}
		
		else
		{
			spriteCloud1.setPosition(spriteCloud1.getPosition().x + (CloudSpeed1 * dt.asSeconds()),spriteCloud1.getPosition().y); 
			//decreases X values for left to right movement with 60fps for example
			if(spriteCloud1.getPosition().x > 1920 )
			{
				CloudActive1=false;	
			}
		}
		
		if(!CloudActive2)
		{
			srand((int)time(0)*10);
			CloudSpeed2=(rand() % 200)+100; //random speed between 200 - 400
			spriteCloud2.setPosition(-1000,250); //initializes bee position
			float height=(rand() % 50)+400; //random height between 500 - 1000
			CloudActive2 = true; //triggers else condition to run
		}
		
		else
		{
			spriteCloud2.setPosition(spriteCloud2.getPosition().x + (CloudSpeed2 * dt.asSeconds()),spriteCloud2.getPosition().y); 
			//decreases X values for left to right movement with 60fps for example
			if(spriteCloud2.getPosition().x > 1920 )
			{
				CloudActive2=false;	
			}
		}
		
		if(!CloudActive3)
		{
			srand((int)time(0)*10);//
			CloudSpeed3=(rand() % 150)+100; //random speed between 200 - 400
			spriteCloud3.setPosition(-500,150); //initializes bee position
			float height=(rand() % 50)+400; //random height between 500 - 1000
			CloudActive3 = true; //triggers else condition to run
		}
		
		else
		{
			spriteCloud3.setPosition(spriteCloud3.getPosition().x + (CloudSpeed3 * dt.asSeconds()),spriteCloud3.getPosition().y); 
			//decreases X values for left to right movement with 60fps for example
			if(spriteCloud3.getPosition().x > 1920 )
			{
				CloudActive3=false;	
			}
		}
	
	window.clear();
	window.draw(spriteBackground);
	window.draw(spriteCloud1);
	window.draw(spriteCloud2);
	window.draw(spriteCloud3);
	window.draw(spriteTree);
	window.draw(spriteBee);
	window.draw(timeBar);
	window.draw(messageText0);
	window.draw(messageText);
	window.draw(scoreText0);
	window.draw(scoreText);
	window.display();
	}
	
	return 0;
}
