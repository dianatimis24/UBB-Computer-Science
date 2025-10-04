from src.service.CityService import CityService
import random


class UI:
    def __init__(self):
        self.__city_service = CityService()

    def test_input(self, acres_to_sell_or_buy, units_to_feed, acres_to_plant):
        if not self.__city_service.test_acres_to_sell_or_buy(acres_to_sell_or_buy):
            raise ValueError("Not enough money!")

        add_stock = acres_to_sell_or_buy

        if not self.__city_service.test_units_to_feed(units_to_feed, add_stock):
            raise ValueError("Not enough food!")

        if not self.__city_service.test_acres_to_plant(acres_to_plant, units_to_feed, add_stock):
            raise ValueError("Invalid input for acres!")

    def decide(self):
        acres_to_sell_or_buy = int(input("Acres to buy/sell(+/-)-> "))
        units_to_feed = int(input("Units to feed the population -> "))
        acres_to_plant = int(input("Acres to plant -> "))
        try:
            self.test_input(acres_to_sell_or_buy, units_to_feed, acres_to_plant)

            land_price = random.randint(15, 25)
            harvest_units = random.randint(1, 6)

            self.__city_service.sell_or_buy_acres(acres_to_sell_or_buy)
            self.__city_service.feed_population(units_to_feed)
            self.__city_service.set_harvest_units(harvest_units)
            self.__city_service.plant_acres(acres_to_plant)
            self.__city_service.set_land_price(land_price)
            self.__city_service.rat_infest()
        except ValueError as ve:
            raise ValueError(ve)

    def run_ui(self):
        win = 0
        years_passed = 0

        while True:
            if years_passed == 5:
                break
            try:
                print(self.__city_service.get_city_management())

                self.decide()

                if self.__city_service.is_win():
                    win = 1
                    print(self.__city_service.get_city_management())
                    print("CONGRATULATIONS! YOU WON!")
                    break
                if self.__city_service.is_lose():
                    win = 0
                    print(self.__city_service.get_city_management())
                    print("YOU LOST!")
                    break

                years_passed += 1

            except ValueError as ve:
                print(ve)

        if not win:
            print("YOU LOST!")