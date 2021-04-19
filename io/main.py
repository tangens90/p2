import csv

def readCSVfile(obj, name):
	with open(name) as csv_file:
		csv_reader = csv.reader(csv_file, delimiter=',')
		first = True
		for row in csv_reader:
			if first is True:
				first = False
				continue
			if name == "worldcities.csv":
				obj.worldcities.append((row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10]))
			elif name == "country.csv":
				obj.country.append((row[0], row[1], row[2], row[3], row[4], row[5]))


class DAO:
	__instance = None
	worldcities = []
	country = []

	def __new__(self):
		if self.__instance is None:
			self.__instance = object.__new__(self)
			readCSVfile(self, "worldcities.csv")
			readCSVfile(self, "country.csv")
		return self.__instance


class CityPresenter:
	def __new__(self, cityName):
		city = [x for x in DAO().worldcities if x[0] == cityName]
		print(city[0])

def nonNegStr(val):
	return int(val) if val.isdigit() else 0

def populationSortKey(e):
	return nonNegStr(e[9])
	#return int(e[9]) if e[9].isdigit() else 0

class CityStatistic:
	def __new__(self):
		DAO().worldcities.sort(key=populationSortKey, reverse=True)
		print("Top 10 miast:")
		for i in range(10):
			print (DAO().worldcities[i])
		sumOfPopulation = 0
		for x in DAO().worldcities:
			tmp = int(x[9]) if x[9].isdigit() else 0
			sumOfPopulation += tmp
		print(f"\n\nŚrednia wielkość miasta to {sumOfPopulation / len(DAO().worldcities)}")

		# średnia wielkość na kontynencie
		continentSum = {}
		continentCount = {}
		biggestCityOnContinentNum = {}
		biggestCityOnContinentName = {}

		

		for row in DAO().country:
			if row[0] not in continentSum:
				continentSum[row[0]] = 0
				continentCount[row[0]] = 0
				biggestCityOnContinentName[row[0]] = ''
				biggestCityOnContinentNum[row[0]] = 0

			sumList = []
			for city in DAO().worldcities:
				if row[3] == city[5]:
					sumList.append(nonNegStr(city[9]))
					if biggestCityOnContinentNum[row[0]] < nonNegStr(city[9]):
						biggestCityOnContinentNum[row[0]] = nonNegStr(city[9])
						biggestCityOnContinentName[row[0]] = city[0]

			continentSum[row[0]] += sum(sumList)
			continentCount[row[0]] += len(sumList)


		biggestCityName = {}
		biggestCityNum = {}
		for city in DAO().worldcities:
			if city[4] not in biggestCityName:
				biggestCityName[city[4]] = ''
				biggestCityNum[city[4]] = 0
			if biggestCityNum[city[4]] < nonNegStr(city[9]):
				biggestCityNum[city[4]] = nonNegStr(city[9])
				biggestCityName[city[4]] = city[0]


		print("\n\nŚrednia wielkość miasta na kontynencie")
		for key, value in sorted(continentSum.items()):
			print(key, value / continentCount[key])

		print("\n\nNajwiększe miasto na kontynencie")
		for key, value in sorted(biggestCityOnContinentName.items()):
			print(key, "->", value)

		print("\n\nNajwiększe miasto danego kraju")
		for key, value in sorted(biggestCityName.items(), key=lambda item: item[1]):
			print(key, "->", value)

	

CityPresenter('Shanghai')
CityStatistic()
