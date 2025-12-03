#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets)
{
    if (fuel <= 0)
    {
        printf("\nFuel exhausted! Mission failed.\n");
        return 0;
    }

    if (planet > totalPlanets)
    {
        return 1;
    }

    fuel = fuel - consumption;

    fuel = fuel + recharge;

    if (planet % 4 == 0)
    {
        fuel = fuel + solarBonus;
    }

    printf("Planet %d : Fuel Remaining = %d\n", planet, fuel);

    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main()
{
    int fuel, consumption, recharge, solarBonus, totalPlanets;

    printf("Enter initial fuel: ");
    scanf("%d", &fuel);

    printf("Enter fuel consumption per planet: ");
    scanf("%d", &consumption);

    printf("Enter gravitational recharge amount: ");
    scanf("%d", &recharge);

    printf("Enter solar bonus (after every 4 planets): ");
    scanf("%d", &solarBonus);

    printf("Enter total number of planets: ");
    scanf("%d", &totalPlanets);

    printf("\n--- Space Journey Fuel Simulation ---\n");

    int result = calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets);

    if (result == 1)
    {
        printf("\nMission Status: SUCCESS — Spacecraft completed the journey.\n");
    }
    else
    {
        printf("\nMission Status: FAILED — Spacecraft could not reach all planets.\n");
    }

    return 0;
}