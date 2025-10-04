from src.domain.CityManagement import CityManagement
import random


class CityService:
    def __init__(self):
        self.__city_management = CityManagement()

    def get_city_management(self):
        return self.__city_management

    def is_lose(self):
        if self.__city_management.starving_people > self.__city_management.population / 2:
            return True
        return False

    def is_win(self):
        if self.__city_management.population > 100 and self.__city_management.acres_of_land > 1000:
            return True
        return False

    def set_land_price(self, number):
        self.__city_management.set_land_price(number)

    def set_harvest_units(self, number):
        self.__city_management.set_harvest(number)

    def test_acres_to_sell_or_buy(self, number: int):
        if number <= 0:
            if self.__city_management.acres_of_land + number < 0:
                return False
        elif self.__city_management.stocks < number * self.__city_management.land_price:
            return False
        return True

    def sell_or_buy_acres(self, number: int):
        if number <= 0:
            self.__city_management.set_acres(number)
            self.__city_management.set_stocks(self.__city_management.stocks - number * self.__city_management.land_price)
        else:
            self.__city_management.set_acres(number)
            self.__city_management.set_stocks(self.__city_management.stocks - number * self.__city_management.land_price)

    def test_units_to_feed(self, number: int, acres_to_sell_or_buy: int):
        if number > self.__city_management.stocks - acres_to_sell_or_buy * self.__city_management.land_price:
            return False
        return True

    def feed_population(self, number: int):
        self.__city_management.feed_population(number)

    def test_acres_to_plant(self, number: int, units_to_feed: int, acres_to_sell_or_buy: int):
        if number > self.__city_management.acres_of_land:
            return False
        if self.__city_management.stocks - units_to_feed - acres_to_sell_or_buy * self.__city_management.land_price < number:
            return False
        return True

    def plant_acres(self, number: int):
        number = min(number, self.__city_management.population * 10)
        self.__city_management.plant_acres(number)

    def rat_infest(self):
        number = random.randint(1, 10)
        if number <= 2:
            units = random.randint(0, int(self.__city_management.stocks * 20 / 100))
            self.__city_management.set_rat_units(units)
            self.__city_management.set_stocks(self.__city_management.stocks - units)
        else:
            self.__city_management.set_rat_units(0)
