// CP2020CharGen.cpp
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

int stats[9];
int role_skills[10];
int pup_skills[5];
int sum;
std::string stat_names[9] = { "int", "ref", "tech", "cool", "attr", "luck", "ma", "body", "emp" };
//role skill name
std::string r_s_n[10];
//pickup skill name
std::vector<std::string> p_s_n = { " ", " ", " ", " ", " "};
//cyberwear loadout
std::vector<std::string> cyware;
//gear loadout
std::string loadout;

//loadouts
std::string r_skills[10] = {"charismatic ability", "awareness", "perform", "wardrobe", "composition", "brawling", "instrument", "streetwise", "persuasion", "seduction"};
std::string s_skills[10] = { "combat sense", "awareness", "handgun", "brawling", "melee", "weapons tech", "rifle", "athletics", "submachinegun", "stealth" };
std::string n_skills[10] = { "interface", "awareness", "basic tech", "education", "system knowledge", "cybertech", "cyberdeck design", "composition", "electronics", "programming" };
std::string t_skills[10] = { "jury rig", "awareness", "basic tech", "cybertech", "teaching", "education", "electronics", "pilot", "tech", "weaponsmith"};
std::string mt_skills[10] = { "medical tech", "awareness", "basic tech", "diagnose", "education", "cryotank operation", "library search", "pharmaceuticals", "zoology", "human perception" };
std::string m_skills[10] = { "credibility", "awareness", "composition", "education", "persuasion", "human perception", "social", "streetwise", "photo", "interview" };
std::string p_skills[10] = { "autority", "awareness", "handgun", "human perception", "athletics", "education", "brawling", "melee", "interrogation", "streetwise" };
std::string c_skills[10] = { "resources", "human perception", "education", "library search", "social", "persuasion", "stock market", "wardrobe", "personal grooming" };
std::string f_skills[10] = { "streetdeal", "awareness", "forgery", "handgun", "brawling", "melee", "picklock", "pickpocket", "intimidate", "persuasion" };
std::string o_skills[10] = { "family", "awareness", "endurance", "melee", "rifle", "drive", "basic tech", "survival", "brawling", "athletics" };

//master skill list
std::vector<std::string> mas_skills = {"personal grooming", "wardrobe", "endurance", "strength", "swimming", "interrogation", "intimidate", "oratory", "resist", "streetwise", "human perceptipn", 
"interview", "leadership", "seduction", "social", "social", "persuasion", "perform", "accounting", "anthropology", "awareness", "biology", "botany", "chemistry", "composition", "diagnose",
"education", "expert", "gamble", "geology", "hide", "history", "know language", "library search", "mathematics", "physics", "programming", "shadow", "stock market", "system knowledge",
"teaching", "survival", "zoology", "archery", "athletics", "brawling", "dance", "dodge", "driving", "fencing", "handgun", "heavy weapons", "melee", "motorcycle", 
"operate hvy. machinery", "pilot", "rifle", "stealth", "submachinegun", "aereotech", "AV tech", "basic tech", "cryotank operation", "cyberdeck design", "cybertech", "demolitions", "disguise",
"electronics", "elect. security", "first aid", "forgery", "paint", "photo", "pharmaceuticals", "picklock", "pickpocket", "instrument", "weaponsmith"};

//cyberwear type array
std::vector<std::string> cyware_list = { "cyberoptics", "cyberarm", "cyberaudio", "big knucks", "rippers", "vampires", "slice'n'dice", "kerenzikov", "sandevistan", " "};
std::vector<std::string> cyware_used;
//cyberwear object array
std::string cyware_op[6] = { "infrared", "lowlight", "camera", "dargun", "antidazzle", "targeting scope" };
std::string cyware_arm[6] = {"med. pistol", "light pistol", "med. pistol", "light smg", "very heavy pistol", "heavy pistol"};
std::string cyware_audio[6] = {"wearman", "radio splice", "phone link", "amplified hearing", "sound editing", "digital recording link"};
//equipment array list
std::string equipment[10] = { "armor: heavy leather | weapon: knife", "armor: armor vest | weapon: light pistol", "armor: light armor jacket | weapon: med. pistol",
"armor: light armor jacket | weapon: heavy pistol", "armor: med. armor jacket | weapon: heavy pistol", "armor: med armor jacket | weapon: light smg",
"armor: med armor jacket | weapon: lt. assault rifle", "armor: hvy armor jacket | weapon: med. assault rifle", "armor: hvy armor jacket | weapon: hvy assault rifle",
"armor: metal gear | weapon: hvy assault rifle" };

//reset cyware loadout. void->void
void resetCyware()
{
    cyware.erase(cyware.begin(), cyware.end());
}

//RNG selects cyberwear per class number. void->void
void getCyware(std::string role)
{
    int it = 0;
    if (role == "solo")
    {
        for (int i = 0; i < 6; i++)
        {
            it = rand() % cyware_list.size();
            cyware.push_back(cyware_list[it]);
            cyware_used.push_back(cyware_list[it]);
            cyware_list.erase(cyware_list.begin() + it);
        }
    }
    else 
    {
        for (int i = 0; i < 3; i++)
        {
            it = rand() % cyware_list.size();
            cyware.push_back(cyware_list[it]);
            cyware_used.push_back(cyware_list[it]);
            cyware_list.erase(cyware_list.begin() + it);
        }
    }
    for (int i = 0; i < cyware_used.size(); i++) //replaces all of the used bits to the masterlist
    {
        cyware_list.push_back(cyware_used[i]); 
    }
    cyware_used.clear(); //clears the used bin to get stacked once more!!!
}

//RNG selectively formats cyberwear. void->void
void formatCyware()
{
    int it = 0;
    for (int i = 0; i < cyware.size(); i++)
    {
        it = rand() % 6;
        if (cyware[i] == "cyberoptics")
        {
            cyware[i] += ": (" + cyware_op[it] + ")";
        }
        else if (cyware[i] == "cyberarm")
        {
            cyware[i] += ": (" + cyware_arm[it] + ")";
        }
        else if (cyware[i] == "cyberaudio")
        {
            cyware[i] += ": (" + cyware_audio[it] + ")";
        }
        else
        {
            cyware[i] += "";
        }
    }
}

//print cyware loadout
void printCyware()
{
    std::system("CLS");
    cout << "Your cyberwear loadout is: " << endl;
    for (int i = 0; i < cyware.size(); i++)
    {
        cout << cyware[i] << endl;
    }
}

//rolls equipment loadout. string->void
void getEquip(std::string role)
{
    int it = rand() % 10;
    int mod = 0;
    if (role == "solo")
    {
        mod = 3;
    }
    else if (role == "nomad" || role == "cop")
    {
        mod = 2;
    }
    else
    {
        mod = 0;
    }
    it += mod;
    if (it > 9)
    {
        it = 9;
    }
    loadout = equipment[it]; //se esta pasando we have to limite
}

//print equipment loadout. void->void
void printEquip()
{
    system("CLS");
    cout << "Your equipment loadout is: " << endl;
    cout << loadout << endl;
}

//retrieves RNG 3-10 statistics for each of the 9 attributes. void->array
int* getStats()
{
    for (int i = 0; i < 9; i++)
    {
        do{
            stats[i] = rand() % 10 + 1;
        } while (stats[i] == 1 || stats[i] == 2);
    }
    return stats;
}// RNG stat generation. Figure a way to do pass by reference.

//prints statistics alongside the names of each. array, string->void
void printStats(int param[9], std::string names[9])
{
    std::system("CLS");
    cout << "Your stats are: " << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << names[i] << ": ";
        cout << param[i] << endl;
    }
}

//verifies a valid role name has been entered. string->bool
bool roleCheck(string role_name) //
{
    if (role_name == "rockerboy")
    {
        return true;
    } 
    else if (role_name == "solo")
    {
        return true;
    }
    else if (role_name == "netrunner")
    {
        return true;
    }
    else if (role_name == "techie")
    {
        return true;
    }
    else if (role_name == "media")
    {
        return true;
    }
    else if (role_name == "cop")
    {
        return true;
    }
    else if (role_name == "corporate")
    {
        return true;
    }
    else if (role_name == "fixer")
    {
        return true;
    }
    else if (role_name == "nomad")
    {
        return true;
    }  
    else if (role_name == "medtech")
    {
        return true;
    }
    else {
        cout << "Please input a valid role: " << endl;
        return false;
    }
        
}

//assigns adequate career skill list as per role. string->void
void getPackage(std::string role_name)
{
    if (role_name == "rockerboy")
    {
        r_s_n[0] = r_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = r_skills[i];
        }
    }
    else if (role_name == "solo")
    {
        r_s_n[0] = s_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = s_skills[i];
        }
    }
    else if (role_name == "netrunner")
    {
        r_s_n[0] = n_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = n_skills[i];
        }
    }
    else if (role_name == "techie")
    {
        r_s_n[0] = t_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = t_skills[i];
        }
    }
    else if (role_name == "media")
    {
        r_s_n[0] = t_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = t_skills[i];
        }

    }
    else if (role_name == "cop")
    {
        r_s_n[0] = p_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = p_skills[i];
        }
    }
    else if (role_name == "corporate")
    {
        r_s_n[0] = c_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = c_skills[i];
        }
    }
    else if (role_name == "fixer")
    {
        r_s_n[0] = f_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = f_skills[i];
        }
    }
    else if (role_name == "nomad")
    {
        r_s_n[0] = o_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = o_skills[i];
        }
    } 
    else if (role_name == "medtech")
    {
        r_s_n[0] = mt_skills[0];
        for (int i = 1; i < 10; i++)
        {
            r_s_n[i] = mt_skills[i];
        }
    }
}

//RNG for dividing 40 points among the career skills. void->void
void getRoleSkills()
{
    srand(time(NULL));
    int points = 39;
    int temp = 0;
    int i = 0;
    role_skills[0] = 1;

    //RNG skill bank loop

    while (points>0)
    {
        temp = rand() % 11;
        role_skills[i] += temp;
        points -= temp;
        if (role_skills[i] >= 10)
        {
            points += role_skills[i] - 10;
            role_skills[i] = 10;
        }
        i++;

        if (i > 9)
        {
            i = 0;
        }
    }
} // find a way to reset the seed immediately after runtime

//resets role skill values to 0 void->void
void resetRoleSkills()
{
    for (int i = 0; i < 10; i++)
    {
        role_skills[i] = 0;
    }
}

//prints role skills void->void
void printRoleSkills()
{
    int sum = 0;
    system("CLS");
    cout << "Your career skill loadout is: " << endl;
    for (int i = 0; i < 10; i++)
    {
        sum += role_skills[i];
        cout << r_s_n[i] << ": ";
        cout << role_skills[i] << endl;
    }
}

//Removes career skills from master skill list. void->void
void scalpPupNames()
{
    for (int i = 0; i<mas_skills.size(); i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (r_s_n[j].compare(mas_skills[i])==0)
            {
                mas_skills.erase(mas_skills.begin() + i);
            }
        }
    }
}

//RNG skill choice for pickup skills list void->void
void getPupNames()
{
    std::string temp = "null";
    for (int i = 0; i < 5; i++)
    {
        p_s_n[i] = mas_skills[rand() % (mas_skills.size())]; 
        if (p_s_n[i].compare(temp) == 0) //this is so that we don't get repeat skills
        {
            p_s_n[i] = p_s_n[i + 1];
        }
        temp = p_s_n[i];
    }
}

//prints names for pickup skills
void printPupNames()
{
    std::system("CLS");
    cout << "Your pickup skills are: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << p_s_n[i] << endl;
    }
}

//RNG for dividing points based off of INT + REF. int[i], int[j] -> void
void getPupSkills(int intl, int ref)
{
    int points = intl + ref;
    int temp = 0;
    int i = 0;

    while (points > 0)
    {
        temp = rand() % 11;
        pup_skills[i] += temp;
        points -= temp;
        if (pup_skills[i] >= 10)
        {
            points += pup_skills[i] - 10;
            pup_skills[i] = 10;
        }
        i++;

        if (i > 5)
        {
            i = 0;
        }
    }
}

//resets pickup skill assignment void->void
void resetPupSkills()
{
    for (int i = 0; i < 5; i++)
    {
        pup_skills[i] = 0;
    }
}

//prints pickup skills void->void
void printPupSkills()
{
    std::system("CLS");
    cout << "These are your pickup skill assignments: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << p_s_n[i] << ": ";
        cout << pup_skills[i] << endl;
    }
}

void printCharSheet(std::string name, std::string role)
{
    system("CLS");
    cout << "name: " << name << endl << "role: " << role << endl;
    cout << "_______________________________________________________________________" << endl;
    cout << "stats: " << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << "     " << stat_names[i] << ": ";
        cout << stats[i] << endl;
    }
    cout << "_______________________________________________________________________" << endl;
    cout << "skills: " << endl;
    for (int i = 0; i < 10; i++)
    {
        sum += role_skills[i];
        cout << "     " << r_s_n[i] << ": ";
        cout << role_skills[i] << endl;
    }
    for (int i = 0; i < 5; i++)
    {
        cout << "     " << p_s_n[i] << ": ";
        cout << pup_skills[i] << endl;
    }
    cout << "_______________________________________________________________________" << endl;
    cout << "cybernetics: " << endl;
    for (int i = 0; i < cyware.size(); i++)
    {
        cout << "     " << cyware[i] << endl;
    }
    cout << "_______________________________________________________________________" << endl;
    cout << "equipment: " << endl;
    cout << "     " << loadout << endl;
}

//RNG cyberwear power
void charSheetToFile(std::string name, std::string role)
{
    ofstream myfile;
    std::string filename = name + " the " + role + " (CP2020)" + ".txt";
    myfile.open(filename);
    system("CLS");
    myfile << "name: " << name << endl << "role: " << role << endl;
    myfile << "_______________________________________________________________________" << endl;
    myfile << "stats: " << endl;
    for (int i = 0; i < 9; i++)
    {
        myfile << "     " << stat_names[i] << ": ";
        myfile << stats[i] << endl;
    }
    myfile << "_______________________________________________________________________" << endl;
    myfile << "skills: " << endl;
    for (int i = 0; i < 10; i++)
    {
        sum += role_skills[i];
        myfile << "     " << r_s_n[i] << ": ";
        myfile << role_skills[i] << endl;
    }
    for (int i = 0; i < 5; i++)
    {
        myfile << "     " << p_s_n[i] << ": ";
        myfile << pup_skills[i] << endl;
    }
    myfile << "_______________________________________________________________________" << endl;
    myfile << "cybernetics: " << endl;
    for (int i = 0; i < cyware.size(); i++)
    {
        myfile << "     " << cyware[i] << endl;
    }
    myfile << "_______________________________________________________________________" << endl;
    myfile << "equipment: " << endl;
    myfile << "     " << loadout << endl;
    myfile.close();
}


int main()
{
    srand(time(NULL)); // resets seeds for RNG
    static std::string char_name;
    static std::string char_role;
    char choice = 'y';

    //name choice

    cout << "What is your name? (lowercase only)" << endl;
    cin >> char_name;

    //choosing a role

    cout << "What is your role? (lowercase only)" << endl;
    do { //role check
        cin >> char_role;
    } while (roleCheck(char_role) == false);
    std::system("CLS");

    //stat generation
    while (choice == 'y' || choice == 'Y')
    {
        getStats();
        printStats(getStats(), stat_names);
        cout << "Would you like to roll again? (y/n)" << endl;
        cin >> choice;
    }
    std::system("CLS");

    //career skill assignment

    getPackage(char_role);

    do {
        resetRoleSkills();
        getRoleSkills();
        printRoleSkills();
        cout << "Would you like to roll again? (y/n)" << endl;
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    std::system("CLS");

    //debug for making sure the number of points used is ok : cout << sum << endl;

    //pickup skill assignment;

    do {
        scalpPupNames();
        getPupNames();
        printPupNames();
        cout << "Would you like a different loadout? (y/n)" << endl;
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    std::system("CLS");

    do {
        resetPupSkills();
        getPupSkills(stats[0], stats[2]);
        printPupSkills();
        cout << "Would you like to roll again? (y/n)" << endl;
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    std::system("CLS");

    //roll for cyberwear
    do 
    {
        resetCyware();
        getCyware(char_role);
        formatCyware();
        printCyware();
        cout << "Would you like a different loadout? (y/n)" << endl;
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    std::system("CLS");
    //roll for gear
    do 
    {
        getEquip(char_role);
        printEquip();
        cout << "Would you like a different loadout? (y/n)" << endl;
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    //master print

    cout << "Here's your final character sheet: " << endl;
    printCharSheet(char_name, char_role);
    cout << "_______________________________________________________________________" << endl;
    cout << "Would you like to save your character sheet as a text file?" << endl;
    cin >> choice;
    if (choice == 'y')
    {
        cout << "Your character sheet has been saved as a text file." << endl;
        charSheetToFile(char_name, char_role);
        cout << "Press any key to exit." << endl;
        cin >> choice;
        return 0;
    }
    else
        cout << "Press any key to exit." << endl;
        cin >> choice;
    return 0;
}
