//How easy is it to draw Exodia?
//A stupid program by Tyler Clark

#include<iostream>
#include<time.h>

char hand[40];
int handSize = 0;
char deck[40];
int deckSize = 40;
int testMode = 1; //Set this to 1 to see an in depth view of how the game is actually played. Set to 0 to calculate percentage
int exodiaCount = 0;
double epsilon = 26;
double delta = 14;

//Formula for delta and epsilon: Both started at 50
//On failure, subtract the number of card draws we would've lost.
//On success, add the cards we drew divided by the cards we would've drawn playing card destruction immediately.
//Epsilon, after 100000000 tries: 26
//Delta, after 100000000 tries: 14
//This supports the hypothesis that it's worth gambling on pot of greed 


int cardDestruction(int index);
void potOfGreed(int index);
int gracefulCharity(int index);
void upstartGoblin(int index);
void discard(int choice);
void discardAll();
int draw(int drawValue);
void pop(std::string queue);
std::string topOfQueue(std::string newChar, std::string queue);
std::string bottomOfQueue(std::string newChar, std::string queue);
int viewHand();
void shuffle();
void swap(int a, int b);
int firstHand();
void showDeck();


int exodiaProbability(int draws)
{
	double probability = 1;
	if(deckSize >= draws)
	{
		for(int i = 0; i < draws; i++)
		{
			probability = probability * ((double)(deckSize - i + exodiaCount - 5)/(deckSize - i));
		}
		
		probability = (1 - probability) * 100; //Multiply by 100 for percent.
		//std::cout << probability << std::endl;
		return (int)probability;
	}
	return 0;
}

int cardDestruction(int index)
{
	int temp = 0;
	int cardsDrawn = 0;
	if(exodiaCount > 0)
	{
		hand[index] = 'X';
		return 0;
	}
		
	for(int i = 0; i < handSize; i++)
	{
 		if(hand[i] == 'P')
		{
			if(exodiaProbability(2) < epsilon) 
			{
				//temp = handSize - 1;
				potOfGreed(i);
/* 				if( hand[handSize - 2] == 'E' || hand[handSize - 1] == 'E') //If we get the bad result and get punished for our risk
				{
					if(testMode == 1)
						std::cout << "Lowering epsilon!\n New epsilon value: ";
					epsilon = epsilon - (double)(temp - 2)*e; //We lose the draw value of whatever our handsize - 1 was, plus 2 cards we drew with pot. 
					if(testMode == 1)
						std::cout << epsilon << std::endl;
					
				}
				else
				{
					if(testMode == 1)
						std::cout << "Raising epsilon!\n New epsilon value: ";
					epsilon = epsilon + (double)(3.0/temp)*e; //We gained 3 draws from playing pot of greed first if it doesn't fail
					if(testMode == 1)
						std::cout << epsilon << std::endl;
					
				}
				e = e*e; //Keep minorly decreasing E without it ever hitting 0 */
				return 0;
			}
		}
		if(hand[i] == 'U')
		{
			if(exodiaProbability(1) < delta)
			{
				//temp = handSize - 1;
				upstartGoblin(i);
				/* if(hand[handSize - 1] == 'E') //If we get the bad result and get punished for our risk
				{
					if(testMode == 1)
						std::cout << "Lowering delta!\n New delta value: ";
					delta = delta - (double)(temp - 1)*z;
					if(testMode == 1)
						std::cout << delta << std::endl;
					z = z*z; //Keep minorly decreasing E without it ever hitting 0
					
				}
				else
				{
					if(testMode == 1)
						std::cout << "Raising delta!\n New delta value: ";
					delta = delta + (double)(1.0/temp)*z;
					if(testMode == 1)
						std::cout << epsilon << std::endl;
					z = z*z; //Keep minorly decreasing Z without it ever hitting 0
					
				} */
				return 0;
			}
			
		}
		if(hand[i] == 'G')
		{
			if(exodiaProbability(3) < 30)
			{
				gracefulCharity(i);
				return 0;
			}
		}
				
	}
	if(deckSize >= (handSize - 1))
	{
		if(testMode == 1)
			std::cout << "Activated Card Destruction!" << std::endl;
		temp = handSize;
		discardAll();
		draw(temp - 1);
		return 1;
		
	}
	else
	{
		hand[index] = 'X';
	}
	
	return 0;
}

void potOfGreed(int index)
{
	if(draw(2))
	{
		if(testMode == 1)
			std::cout << "Activated Pot of Greed!" << std::endl;
		discard(index);
	}
	else //If you would deck out if you played this card
	{
		hand[index] = 'X';
	}
	return;
}

int gracefulCharity(int index)
{
	int requirement[2];
	int discards = 0;
	if(draw(3))
	{
		if(testMode == 1)
		{
			std::cout << "Activated Graceful Charity!" << std::endl;
		}
		discard(index);
		for(int i = 0; i < handSize; i++)
		{
			if(hand[i] == 'X' || (hand[i] == 'C' && exodiaCount > 0) )
			{
				requirement[discards] = i;
				discards++;
			}
			if(discards == 2)
			{
				if(testMode == 1)
				{
					std::cout << "Discarded two X's" << std::endl;
				}
				discard(requirement[0]);
				discard(requirement[1]);
				return 1;
			}
				
		}
		for(int i = 0; i < handSize; i++)
		{
			if(hand[i] == 'U')
			{
				requirement[discards] = i;
				discards++;
			}
			if(discards == 2)
			{
				if(testMode == 1)
				{
					std::cout << "Discarded two X's and U's" << std::endl;
				}
				discard(requirement[0]);
				discard(requirement[1]);
				return 1;
			}
			
		}
		for(int i = 0; i < handSize; i++)
		{
			if(hand[i] == 'P' || hand[i] == 'C' || hand[i] == 'G')
			{
				requirement[discards] = i;
				discards++;
			}
			if(discards == 2)
			{
				if(testMode == 1)
				{
					std::cout << "Discarded two non exodias" << std::endl;
				}
				discard(requirement[0]);
				discard(requirement[1]);
				return 1;
			}
		}
		for(int i = 0; i < 2 - discards; i++) //This means exodia pieces get destroyed, that's sad
		{
			requirement[discards] = i;
			discards++;
			if(discards == 2)
			{
				if(testMode == 1)
				{
					std::cout << "Discarded at least one exodia" << std::endl;
				}
				discard(requirement[0]);
				discard(requirement[1]);
				return 1;
			}
			
		}
		
		
	}
	hand[index] = 'X';
	return 0;
}

void upstartGoblin(int index)
{
	if(draw(1))
	{
		if(testMode == 1)
			std::cout << "Activated Upstart Goblin!" << std::endl;
		discard(index);
	}
	else //If you would deck out if you played this card
	{
		hand[index] = 'X';
	}
	return;
}

void discard(int choice)
{
	//If there are eight cards and I want to discard the fifth card, I'd need to move over all 3 other cards ahead of it down one spot
	for(int i = choice; i < handSize; i++)
	{
		hand[i] = hand[i + 1];
	}
	handSize--;
	
}

void discardAll()
{
	for(int i = 0; i < handSize; i++)
	{
		hand[i] = '0';
	}
	handSize = 0;
}

int draw(int drawValue)
{	
	if((deckSize - drawValue) < 0) //You can only draw 40 cards before you lose the game
	{
		//std::cout << "Decked out!";
		return 0;
	}
	for(int i = 0; i < drawValue; i++)
	{
		hand[handSize] = deck[40 - deckSize];
		deckSize--;
		handSize++;
	}
	return 1;
	
}

void pop(std::string queue, int queueIndexes[])
{
	int length = queue.length(); 
	if(queue[0] == 'C')
	{
		cardDestruction(queueIndexes[0]);
	}
	if(queue[0] == 'P')
		potOfGreed(queueIndexes[0]);
	if(queue[0] == 'G')
	{
		if(gracefulCharity(queueIndexes[0]))
			return; //If Graceful Charity discarded a draw card, just run through another hand to be safe.
	}
	if(queue[0] == 'U')
		upstartGoblin(queueIndexes[0]);
		
		
	
	return;
}

std::string topOfQueue(std::string newChar, std::string queue)
{
	newChar.append(queue);
	return newChar;
	
}

std::string bottomOfQueue(std::string newChar, std::string queue)
{
	queue.append(newChar);
	return queue;
	
}
int viewHand()
{
	int result = 0;
	int moreCards = 0;
	std::string queue = "";
	int queueIndexes[35];
	int specialCards = 0;
	exodiaCount = 0;
	
	if(testMode == 1)
	{
		std::cout << "Current Hand: ";

		for(int i = 0; i < handSize; i++)
		{
			std::cout << hand[i];
		}
		std::cout << "\n";
	}		
	for(int i = 0; i < handSize; i++)
	{
		if(hand[i] != 'X') //If the card is important
		{
			std::string cardAbility(1, hand[i]);
			if(hand[i] == 'E') //If the card is an Exodia piece
			{
				exodiaCount++;
				if(exodiaCount == 5)
				{
					if(testMode == 1)
						std::cout << "Exodia Obliterate!" << std::endl;
					result = 1;
					return result; //Win the game
				}
			}
			else if(hand[i] == 'C') //If the card is Card Destruction
			{
				if(exodiaCount == 0)
				{
					queueIndexes[specialCards] = i;
					specialCards++;
					queue = topOfQueue(cardAbility, queue);
					moreCards = 1;
				}
				else
					hand[i] = 'X'; //If there's an exodia piece in hand, never discard. Don't even bother.
			}
			else if(hand[i] == 'P') //If the card is Pot of Greed
			{
				queueIndexes[specialCards] = i;
				specialCards++;
				queue = bottomOfQueue(cardAbility, queue);
				moreCards = 1;
			}
			else if(hand[i] == 'G') //If the card is Graceful Charity
			{
				queueIndexes[specialCards] = i;
				specialCards++;
				queue = bottomOfQueue(cardAbility, queue);
				moreCards = 1;
			}
			else if(hand[i] == 'U') //If the card is Upstart Goblin
			{
				queueIndexes[specialCards] = i;
				specialCards++;
				queue = bottomOfQueue(cardAbility, queue);
				moreCards = 1;
			}

		}			
		
	}
	
	
	if(moreCards)
	{
		pop(queue, queueIndexes);
		return viewHand();
	}
	return result;
}

void shuffle()
{
	srand(time(0));
	for(int i = (40 - deckSize); i < 40; i++)
	{
		int r = (rand() % 40) + (40 - deckSize);
		swap(i,r);
	}
	
}

void swap(int a, int b)
{
	char temp = deck[a];
	deck[a] = deck[b];
	deck[b] = temp;
}

int firstHand()
{
	draw(6);
	exodiaCount = 0;
	return viewHand();
}

void showDeck()
{
	std::cout << "\n";
	for(int i = (40 - deckSize); i < 40; i++)
	{
		std::cout << deck[i];
	}
	std::cout << "\n";
}


int main()
{
	char specialCards[] = {'P','U','G','C','E'};
	int copies[5];
	int cards = 0;
	int success = 0;
	int tries = 1000000;
	double percent = 0;
	std::cout << "How many pot of greeds?\n";
	std::cin >> copies[0];
	std::cout << "How many Upstart Goblins?\n";
	std::cin >> copies[1];
	std::cout << "How many Graceful Charities?\n";
	std::cin >> copies[2];	
	std::cout << "How many Card Destructions?\n";
	std::cin >> copies[3];
	copies[4] = 5;
	for(int i = 0; i < 40; i++)
	{
		deck[i] = 'X';
	}
	
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < copies[i]; j++)
		{
			if(cards >= 40)
			{
				break;
			}
			deck[cards] = specialCards[i];
			cards++;
			
		}
		
	}
	if(cards >= 40) //Make sure there are always 5 cards of exodia
	{
		for(int i = 35; i < 40; i++)
		{
			deck[i] = 'E';
		}
	}
	if(testMode == 1)
		tries = 5;
	for(int i = 0; i < tries; i++)
	{
		deckSize = 40;
		exodiaCount = 0;
		handSize = 0;
		shuffle();
		//std::cout << "\n";
		if(testMode == 1)
		{
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 10; j++)
				{
					std::cout << deck[j + (10*i)];
				}
				std::cout << "\n";
				
			}
		}
		if(firstHand() == 1)
			success++;
		if(testMode == 1)
			showDeck();
	}
	percent = (((double)success)/tries)*100;
	std::cout << "\n There were ";
	std::cout << success;
	std::cout << " successes out of ";
	std::cout << tries;
	std::cout << " tries.\n";
	std::cout << percent;
	std::cout << "%" << std::endl;
	std::cout << "delta: ";
	std::cout << delta;
	std::cout << "\nepsilon: ";
	std::cout << epsilon;
	return 0;
	
}