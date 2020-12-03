import core.DataClasses as dataClasses
import core.TextHighlighter as txt


def SolutionFinder(readFile: list):
    print("Starting first solver!\n")
    outputArr = []
    suppliers = readFile[0]
    pharmacies = readFile[1]
    connections = readFile[2]
    deliverCosts = {}
    finalCost = 0
    deliveredProducts = 0

    connectionsMatrix = createConnectionsMatrix(connections)
    sortedPharmacies = sorted(pharmacies, key=lambda x: x.getDailyNeed(), reverse=True)
    sortedSuppliers = sorted(suppliers, key=lambda x: x.getID())

    for pharmacy in sortedPharmacies:
        deliverCosts.clear()
        for connection in connections:
            if connection.getPharmacyID() == pharmacy.getID():
                deliverCosts[connection.getSupplierID()] = connection.getCost()

        sortedDeliveryCosts = sorted(deliverCosts.items(), key=lambda x: x[1])

        lowestCostIdArr = []
        for lowestCostId in sortedDeliveryCosts:
            lowestCostIdArr.append(lowestCostId[0])

        moduloValue = len(sortedDeliveryCosts)
        index = 0

        while pharmacy.stillNeed():
            dailyNeed = pharmacy.getDailyNeed()
            supplier = getCheapestSupplier(sortedSuppliers, lowestCostIdArr[index % moduloValue])
            dailyProduction = supplier.getDailyProduction()
            cost = getConnectionCost(pharmacy, supplier, connectionsMatrix)
            index += 1

            if dailyNeed <= dailyProduction and checkIfDeliveryIsPossible(pharmacy, supplier, connectionsMatrix, dailyNeed):
                pharmacy.updateDailyNeed(dailyNeed)
                supplier.updateDailyProduction(dailyNeed)
                updateConnections(pharmacy, supplier, connectionsMatrix, dailyNeed)

                writeToArr(outputArr, supplier.getName(), pharmacy.getName(), dailyNeed, cost)
                finalCost += dailyNeed * cost
                deliveredProducts += dailyNeed
                break

            else:
                if checkIfDeliveryIsPossible(pharmacy, supplier, connectionsMatrix, dailyProduction):
                    pharmacy.updateDailyNeed(dailyProduction)
                    supplier.updateDailyProduction(dailyProduction)
                    updateConnections(pharmacy, supplier, connectionsMatrix, dailyProduction)

                    writeToArr(outputArr, supplier.getName(), pharmacy.getName(), dailyProduction, cost)
                    finalCost += dailyProduction * cost
                    deliveredProducts += dailyProduction

                else:
                    maxPossibleDelivery = remainingMaxDelivery(pharmacy, supplier, connectionsMatrix)
                    if maxPossibleDelivery == 0:
                        break

                    if pharmacy.getDailyNeed() < maxPossibleDelivery:
                        maxPossibleDelivery = pharmacy.getDailyNeed()

                    pharmacy.updateDailyNeed(maxPossibleDelivery)
                    supplier.updateDailyProduction(maxPossibleDelivery)
                    updateConnections(pharmacy, supplier, connectionsMatrix, maxPossibleDelivery)

                    writeToArr(outputArr, supplier.getName(), pharmacy.getName(), maxPossibleDelivery, cost)
                    finalCost += maxPossibleDelivery * cost
                    deliveredProducts += maxPossibleDelivery

    finalCost = round(finalCost, 2)

    if deliveredProducts != dataClasses.Pharmacy.sumOfNeeds:
        txt.coloredPrint("Warning! Couldn't deliver products to all pharmacies!", txt.styleOfHighlight.WARNING, True)

    else:
        txt.coloredPrint("Delivery successful! Final cost of delivery = {}".format(finalCost), txt.styleOfHighlight.SUCCESS, True)

    print("First solver finished!\n")

    outputArr.append("\n\nSum of costs: {}".format(finalCost))

    return finalCost, deliveredProducts, outputArr


def createConnectionsMatrix(connections: list):
    numberOfPharmacies = dataClasses.Pharmacy.pharmacyCounter
    numberOfSuppliers = dataClasses.Supplier.supplierCounter

    connectionMatrix = [[0] * numberOfPharmacies for i in range(numberOfSuppliers)]

    for connection in connections:
        supplierID = connection.getSupplierID()
        pharmacyID = connection.getPharmacyID()
        connectionMatrix[supplierID][pharmacyID] = connection

    return connectionMatrix


def updateConnections(pharmacy: dataClasses.Pharmacy, supplier: dataClasses.Supplier, connectionsMatrix: list, updateValue: int):
    pharmacyID = pharmacy.getID()
    supplierID = supplier.getID()

    connectionsMatrix[supplierID][pharmacyID].updateMaxDelivery(updateValue)


def checkIfDeliveryIsPossible(pharmacy: dataClasses.Pharmacy, supplier: dataClasses.Supplier, connectionsMatrix: list, updateValue: int):
    pharmacyID = pharmacy.getID()
    supplierID = supplier.getID()
    maxDelivery = connectionsMatrix[supplierID][pharmacyID].getMaxDelivery()

    if updateValue <= maxDelivery:
        return True

    else:
        return False


def remainingMaxDelivery(pharmacy: dataClasses.Pharmacy, supplier: dataClasses.Supplier, connectionsMatrix: list):
    pharmacyID = pharmacy.getID()
    supplierID = supplier.getID()

    return connectionsMatrix[supplierID][pharmacyID].getMaxDelivery()


def getConnectionCost(pharmacy: dataClasses.Pharmacy, supplier: dataClasses.Supplier, connectionsMatrix: list):
    pharmacyID = pharmacy.getID()
    supplierID = supplier.getID()

    return connectionsMatrix[supplierID][pharmacyID].getCost()


def getCheapestSupplier(suppliers: list, cheapestId: int):
    return suppliers[cheapestId]


def writeToArr(outputArr: list, supplierName: str, pharmacyName: str, howMany: int, cost: float):
    if howMany > 0:
        outputArr.append("{} --> {} [Koszt = {} * {} = {} zł]\n".format(supplierName, pharmacyName, howMany, cost, round(howMany * cost, 2)))
