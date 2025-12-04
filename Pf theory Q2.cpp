#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge,
                   int solarBonus, int planet, int totalPlanets)
{
    
    if (fuel <= 0) {
        printf("Mission failed: Fuel exhausted at Planet %d.\n", planet - 1);
        return;
    }

    
    if (planet > totalPlanets) {
        printf("Mission successful: Spacecraft reached all %d planets with %d fuel remaining.\n",
                totalPlanets, fuel);
        return;
    }

    
    fuel -= consumption;

    
    fuel += recharge;

    
    if (planet % 4 == 0) {
        fuel += solarBonus;
    }

    
    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    
    calculateFuel(fuel, consumption, recharge, solarBonus,
                  planet + 1, totalPlanets);
}

int main()
{
    int initialFuel   = 500;  
    int consumption   = 70;   
    int recharge      = 20;   
    int solarBonus    = 100;  
    int totalPlanets  = 10;   

    printf("\n====Starting Space Mission Fuel Simulation:\n\n");

    calculateFuel(initialFuel, consumption, recharge,
                  solarBonus, 1, totalPlanets);

    return 0;
}

