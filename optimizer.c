/* GitHub Devs: Algorthim designed by @qwainaina, python by @henchhing-limbu, cpp & c by @ajazayeri72 */
#include <stdio.h>
#include <time.h>


//Define Time Zones
#define EARLIEST_AFRICAN_TIMEZONE -1
#define LATEST_AFRICAN_TIMEZONE 4
#define EARLIEST_ASIAN_TIMEZONE 5
#define EARLIEST_EUROPEAN_TIMEZONE 0

//Define Regional Rewards
#define CARRIBEAN_REGION_REWARD 20
#define SOUTH_AMERICAN_REGION_REWARD 15
#define AFRICAN_REGION_REWARD 45
#define ASIAN_REGION_REWARD 15
#define OTHER_REGION_REWARD 5

//Define TOTAL_YESPOWER_REWARD 103.125 - NOT NEEDED ANY MORE

//Define Machine Processor
#define OS_ARM 1
#define OS_WINDOWS 0

struct coordinate
{
    int top_left_x;
	int top_left_y;
	int bottom_right_x;
	int bottom_right_y;
};

struct coordinate RegionCoordiantes(int x1, int x2, int x3, int x4) {
	struct coordinate result;
	result.top_left_x = x1;
	result.top_left_y = x2;
	result.bottom_right_x = x3;
	result.bottom_right_y = x4;
	return result;
}

struct coordinate CARRIBEAN_REGION;
struct coordinate SOUTH_AMERICAN_REGION;
struct coordinate AFRICAN_REGION;
struct coordinate ASIAN_REGION;


#ifdef __arm__
#define OS_ARM 1
#elif defined(_WIN32) || defined (WIN32) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS 1
#endif


//Get Processor Reward %
int get_processor_reward() {
	if (OS_WINDOWS) {
		return 20;
	}
	else if (OS_ARM) {
		return 50;
	}
	else {
		return 30;
	}
}


//Get Machine Timezone
int get_timezone() {
	time_t now = time(NULL);
    time_t tmp = time(&tmp);
    struct tm *utc = gmtime(&tmp);
    int diff = (now - mktime(utc)) / 3600;
	return diff;
}

//Set timezone score
int get_time_zone_reward() {
	int timezone = get_timezone();
	if ((EARLIEST_AFRICAN_TIMEZONE < timezone) && (timezone <= EARLIEST_EUROPEAN_TIMEZONE)) {
		return 40;
	}
	else
	{
		if ((EARLIEST_EUROPEAN_TIMEZONE < timezone) && (timezone <= LATEST_AFRICAN_TIMEZONE)) {
			return 30;
		}
		else
		{
			if ((LATEST_AFRICAN_TIMEZONE < timezone) && (timezone <= EARLIEST_ASIAN_TIMEZONE)) {
				return 20;
			}
			else
			{
				return 10;
			}
		}
	}
}


//Get timezone score
int get_machine_coordinates_reward(double latitude, double longitude)
{
	if ((CARRIBEAN_REGION.top_left_x <= longitude) && (longitude < CARRIBEAN_REGION.bottom_right_x) && (CARRIBEAN_REGION.bottom_right_y <= latitude) && (latitude < CARRIBEAN_REGION.top_left_y)) {
		return CARRIBEAN_REGION_REWARD;
	}
	else if ((SOUTH_AMERICAN_REGION.top_left_x <= longitude) && (longitude < SOUTH_AMERICAN_REGION.bottom_right_x) && (SOUTH_AMERICAN_REGION.bottom_right_y <= latitude) && (latitude < SOUTH_AMERICAN_REGION.top_left_y)) {
		return SOUTH_AMERICAN_REGION_REWARD;
	}
	else if ((AFRICAN_REGION.top_left_x <= longitude) && (longitude < AFRICAN_REGION.bottom_right_x) && (AFRICAN_REGION.bottom_right_y <= latitude) && (latitude < AFRICAN_REGION.top_left_y)) {
		return AFRICAN_REGION_REWARD;
	}
	else if ((ASIAN_REGION.top_left_x <= longitude) && (longitude < ASIAN_REGION.bottom_right_x) && (ASIAN_REGION.bottom_right_y <= latitude) && (latitude < ASIAN_REGION.top_left_y)) {
		return ASIAN_REGION_REWARD;
	}
	else {
		return OTHER_REGION_REWARD;
	}
}


//Main function
int main() {
    CARRIBEAN_REGION = RegionCoordiantes(-90, 30, -45, 15);
    SOUTH_AMERICAN_REGION = RegionCoordiantes(-90, 15, -30, -60);
    AFRICAN_REGION = RegionCoordiantes(-20, 30, 50, -45);
    ASIAN_REGION = RegionCoordiantes(50, 30, 90, -30);

    int timezone_reward = get_time_zone_reward();

    int location_reward = 0; //forcing location reward 40% Africa, 20% Carribean, 20% SouthEastAsia, 10% Middle-east, 10% South America, 0% Europe, 0% Asia, 0% America

	int process_reward = get_processor_reward();

	//Float total_percentage_reward = ((location_reward * (0.6)) + (process_reward * (0.4)));
	//Float total_percentage_reward = ((location_reward * 3 / 6) + (timezone_reward * 1 / 6) + (process_reward * 2 / 6)); //Add when Coordinates data is available
	float total_percentage_reward = ((timezone_reward * 3 / 6) + (process_reward * 3 / 6));

    int o = (int)total_percentage_reward; //Generating optimization score o as an integer
	printf("Total Percentage Reward: %d \n", o);

    if (o  > 14)
    {
    //Use rand function to generate random number between (0 and total_percentage_reward);
    int randomNumber;
    srand((unsigned) time(NULL)); //Make number random each time
    randomNumber = (rand() % 45) + 1; //Made the max 45 instead of 100 % more forgiving
    printf("Randomizer: %d \n", randomNumber);
    if (randomNumber <= o)
        {
        printf("Create YP Hash: Success\n");

        }
    else
        {
        printf("Create YP Hash: Failure\n");

        }
    }
}
