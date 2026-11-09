#include <vector>
#include <cstring>
#include <random>
#include <iostream>
using namespace std;

class Bad_Egg
{};

class Egg
{
private:
	int size;
	string flavor;
public:
	
	Egg(int s, string f)
	{
		size = s;
		flavor = f;
	}
	
	virtual void eat_egg() = 0;

	int get_size()
	{
		return size;
	}

	string get_flavor()
	{
		return flavor;
	}

	virtual ~Egg() = default;
};

class Goose_Egg : public Egg
{
private:

public:

	Goose_Egg() : Egg(2, "Thick")
	{}

	void eat_egg()
	{
		cout << "Ate the Goose Egg. It has a Thicker texture." << endl;
	}
};

class Chicken_Egg : public Egg
{
private:

public:

	Chicken_Egg() : Egg(1, "Savory")
	{}

	void eat_egg()
	{
		cout << "Ate the Chicken Egg. It has a Savory taste!" << endl;
	}
};

class Rotten_Egg : public Egg
{
private:

public:

	Rotten_Egg() : Egg(0, "Sickening")
	{}

	void eat_egg()
	{
		throw Bad_Egg();
	}
};

class Carton
{
private:

public:
	vector<Egg*> eggs;

	Carton()
	{
		for (int i = 0; i < 12; i++)
		{
			int randomizer = rand() % 7;
			if(randomizer <= 3)
				eggs.push_back(new Chicken_Egg());
			else if (randomizer <= 5)
				eggs.push_back(new Goose_Egg());
			else if (randomizer == 6)
				eggs.push_back(new Rotten_Egg());
		}
	}

	void Consume_EGG()
	{
		if (eggs.empty())
		{
			cout << "Cannot consume an Egg - the Carton is Empty." << endl;
			return;
		}

		int random = rand() % eggs.size();
		Egg* currentEgg = eggs[random];
		eggs.erase(eggs.begin() + random);

		try
		{
			currentEgg->eat_egg();
		}
		catch (Bad_Egg)
		{
			cout << "HEY! No eating Bad Eggs on my watch!" << endl;
			cout << "(Caught a Bad Egg and reduced it to atoms)" << endl;
		}

		delete currentEgg;
	}
};

int main()
{
	srand(time(0));
	bool check;
	string input;
	cout << "Would you like to begin testing? (Y/N)" << endl;
	cin >> input;
	if (input == "Y")
	{
		cout << "Great, let's get started!" << endl;
		check = true;
	}
	else if (input == "N")
	{
		cout << "Oh, nevermind. Understandable have a great day :)" << endl;
		check = false;
	}
	else if ((input != "Y") && (input != "N"))
		check = false;
	//skips program on test deny or improper entry. Why? Idk. Genuinely dunno why I implemented this, but I did for some reason.
	
	if (check == true)
	{
		check = false; //resets the bool condition for "recursive" testing. A 'While Loop', because we have Recursion at home.
		Carton carton = Carton();
		cout << "Initial Carton Created." << endl;

		while (check == false)
		{
			cout << "What would you like to do? ('reset' Carton, 'eat' Egg or 'eatAll' to devour the Carton, 'end' Testing, 'clear' window)  [case sensitive]" << endl;
			cin >> input;
			if (input == "reset")
			{
				cout << "Resetting Carton..." << endl;
				carton = Carton();
				cout << "Carton has been Reset." << endl;
			}
			else if (input == "eat")
			{
				cout << "Proceeding..." << endl;
				carton.Consume_EGG();
			}
			else if (input == "eatAll")
			{
				cout << "Proceeding..." << endl;
				if (carton.eggs.size() == 0)
					carton.Consume_EGG();
				else
					for (int c = 0; c < carton.eggs.size(); c++)
					{
						carton.Consume_EGG();
						if(carton.eggs.size() != 0)
							c--;
					}
			}
			else if (input == "end")
			{
				cout << "Understood, ending Testing." << endl;
				check = true;
			}
			else if (input == "clear")
			{
				cout << "\033[2J\033[1;1H"; //resets output window to prevent clutter.
				// Yes, I copied this from the Portfolio. And yes, I copied the syntax from the internet as I could not decipher how it works, and no I still can't. I plan to figure that out... eventually...
				cout << "Cleared the output window to remove the excess clutter for your convenience." << endl;
			}
			else
				cout << "Improper command format, Trying again." << endl;
		}

		cout << "Testing Concluded." << endl;
	}
}



// By the way, a fun nod down here. The name is a reference to a Sonic Heroes 2 fandub by Snapcube.
// Specifically, Alfred who voices Eggman from their group, and says "E, G.G." when Eggman tries entering a password into a computer.
// There's a 16min video of all his moments from the fandub, lowkey funny. If you're into meme culture, he's how the "Eggman's Announcement" meme came to be so funny.