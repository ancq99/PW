def reset():
    Pharmacy.pharmacyCounter = 0
    Pharmacy.sumOfNeeds = 0
    Supplier.supplierCounter = 0
    Supplier.sumOfProduction = 0
    Connections.connectionCounter = 0


class Pharmacy:
    pharmacyCounter = 0
    sumOfNeeds = 0

    def __init__(self, ID: int, name: str, dailyNeed: int):
        self.ID = ID
        self.name = name
        self.dailyNeed = dailyNeed
        Pharmacy.pharmacyCounter += 1
        Pharmacy.sumOfNeeds += dailyNeed

    def getName(self):
        return self.name

    def getID(self):
        return self.ID

    def getDailyNeed(self):
        return self.dailyNeed

    def updateDailyNeed(self, updateValue):
        self.dailyNeed -= updateValue

    def stillNeed(self):
        return True if self.dailyNeed > 0 else False


class Supplier:
    supplierCounter = 0
    sumOfProduction = 0

    def __init__(self, ID: int, name: str, dailyProduction: int):
        self.ID = ID
        self.name = name
        self.dailyProduction = dailyProduction
        Supplier.sumOfProduction += dailyProduction
        Supplier.supplierCounter += 1

    def getName(self):
        return self.name

    def getID(self):
        return self.ID

    def getDailyProduction(self):
        return self.dailyProduction

    def updateDailyProduction(self, updateValue: int):
        self.dailyProduction -= updateValue


class Connections:
    connectionCounter = 0

    def __init__(self, supplierID: int, pharmacyID: int, maxDelivery: int, cost: float):
        self.supplierID = supplierID
        self.pharmacyID = pharmacyID
        self.maxDelivery = maxDelivery
        self.cost = cost
        Connections.connectionCounter += 1

    def getSupplierID(self):
        return self.supplierID

    def getPharmacyID(self):
        return self.pharmacyID

    def getMaxDelivery(self):
        return self.maxDelivery

    def getCost(self):
        return self.cost

    def updateMaxDelivery(self, updateValue):
        self.maxDelivery -= updateValue


class sortedLists:
    sortedSuppliers = []
    sortedPharmacies = []

    def __init__(self, pharmacies, suppliers):
        sortedLists.sortedSuppliers = sorted(suppliers, key=lambda x: x.getID())
        sortedLists.sortedPharmacies = sorted(pharmacies, key=lambda x: x.getID())
