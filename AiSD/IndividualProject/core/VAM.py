import core.DataClasses as dataClasses
import core.TextHighlighter as txt
import numpy as np


def VAM(readFile: list):
    print("Starting VAM algorithm!\n")
    outputArr = []
    suppliers = readFile[0]
    pharmacies = readFile[1]
    connections = readFile[2]
    dataClasses.sortedLists(pharmacies, suppliers)

    connectionsMatrix = createConnectionsMatrix(connections)
    needArr, prodArr, costArr = createDataArray(pharmacies, suppliers, connections)

    balancedData = balanceData(prodArr, needArr, costArr)

    needArr = balancedData[1]
    prodArr = balancedData[0]
    diff = balancedData[3]

    balancedMatrix = createBalancedMatrix(balancedData, connectionsMatrix)
    limitMatrix = createLimitMatrix(balancedData, balancedMatrix, connectionsMatrix, diff)
    TOCmatrix = createTOCmatrix(balancedData, connectionsMatrix)

    finalCost, deliveredProducts = solver(TOCmatrix, balancedMatrix, limitMatrix, needArr, prodArr, outputArr)
    finalCost = round(finalCost, 2)

    sumOfNeedsAfterBalance = dataClasses.Pharmacy.sumOfNeeds + abs(diff)
    if deliveredProducts != sumOfNeedsAfterBalance:
        txt.coloredPrint("Warning! Couldn't deliver products to all pharmacies!", txt.styleOfHighlight.WARNING, True)

    else:
        txt.coloredPrint("Delivery successful! Final cost of delivery = {}".format(finalCost), txt.styleOfHighlight.SUCCESS, True)

    outputArr.append("\n\nSum of costs: {}".format(finalCost))

    print("VAM algorithm finished!\n")

    return finalCost, deliveredProducts, outputArr, diff


def solver(workMatrix: list, balancedMatrix: list, limitMatrix: list, needArr: list, prodArr: list, outputArr: list):
    finalCost = 0
    deliveredProducts = 0

    while True:
        workMatrix2 = np.array(workMatrix)
        typ, idx, value = getBiggestPenalty(workMatrix)

        if value == 0:
            break

        if typ == "r":
            minCost = min(workMatrix[idx])
            supplierID = idx
            pharmacyID = np.where(workMatrix[idx] == minCost)[0][0]

            production = prodArr[supplierID]
            delivery = needArr[pharmacyID]

            if production >= delivery:
                connectionCost = balancedMatrix[supplierID][pharmacyID]
                data = deliverProductsInCol(pharmacyID, supplierID, delivery, limitMatrix, workMatrix, prodArr, needArr, connectionCost, outputArr)
                finalCost += data[0]
                deliveredProducts += data[1]
                workMatrix = data[2]

            else:
                delivery = prodArr[supplierID]
                connectionCost = balancedMatrix[supplierID][pharmacyID]
                data = deliverProductsInRow(pharmacyID, supplierID, delivery, limitMatrix, workMatrix, prodArr, needArr, connectionCost, outputArr)
                finalCost += data[0]
                deliveredProducts += data[1]
                workMatrix = data[2]

        elif typ == 'c':
            transposedMatrix = workMatrix2.T
            minCost = min(transposedMatrix[idx])

            pharmacyID = idx
            supplierID = np.where(transposedMatrix[idx] == minCost)[0][0]

            production = prodArr[supplierID]
            delivery = needArr[pharmacyID]

            if production >= delivery:
                connectionCost = balancedMatrix[supplierID][pharmacyID]
                data = deliverProductsInCol(pharmacyID, supplierID, delivery, limitMatrix, workMatrix, prodArr, needArr, connectionCost, outputArr)
                finalCost += data[0]
                deliveredProducts += data[1]
                workMatrix = data[2]

            else:
                delivery = prodArr[supplierID]
                connectionCost = balancedMatrix[supplierID][pharmacyID]
                data = deliverProductsInRow(pharmacyID, supplierID, delivery, limitMatrix, workMatrix, prodArr, needArr, connectionCost, outputArr)
                finalCost += data[0]
                deliveredProducts += data[1]
                workMatrix = data[2]
        else:
            break

    return finalCost, deliveredProducts


def deliverProductsInCol(pharmacyID, supplierID, delivery, limitMatrix, workMatrix, prodArr, needArr, minCost, outputArr):
    finalCost = 0
    deliveredProducts = 0

    if checkIfDeliveryIsPossible(pharmacyID, supplierID, limitMatrix, delivery):
        prodArr[supplierID] -= delivery
        updateConnections(pharmacyID, supplierID, limitMatrix, workMatrix, delivery)
        workMatrix = ignore("col", workMatrix, pharmacyID)

        writeToArray(outputArr, supplierID, pharmacyID, delivery, minCost)
        finalCost += minCost * delivery
        deliveredProducts += delivery

        needArr[pharmacyID] = 0

    else:
        delivery = remainingMaxDelivery(pharmacyID, supplierID, limitMatrix)
        prodArr[supplierID] -= delivery
        updateConnections(pharmacyID, supplierID, limitMatrix, workMatrix, delivery)

        writeToArray(outputArr, supplierID, pharmacyID, delivery, minCost)
        finalCost += minCost * delivery
        deliveredProducts += delivery

        needArr[pharmacyID] -= delivery

    return finalCost, deliveredProducts, workMatrix


def deliverProductsInRow(pharmacyID, supplierID, delivery, limitMatrix, workMatrix, prodArr, needArr, minCost, outputArr):
    finalCost = 0
    deliveredProducts = 0

    if checkIfDeliveryIsPossible(pharmacyID, supplierID, limitMatrix, delivery):
        needArr[pharmacyID] -= delivery
        updateConnections(pharmacyID, supplierID, limitMatrix, workMatrix, delivery)
        workMatrix = ignore("row", workMatrix, supplierID)

        writeToArray(outputArr, supplierID, pharmacyID, delivery, minCost)
        finalCost += minCost * delivery
        deliveredProducts += delivery

        prodArr[supplierID] = 0

    else:
        delivery = remainingMaxDelivery(pharmacyID, supplierID, limitMatrix)
        needArr[pharmacyID] -= delivery
        updateConnections(pharmacyID, supplierID, limitMatrix, workMatrix, delivery)

        writeToArray(outputArr, supplierID, pharmacyID, delivery, minCost)
        finalCost += minCost * delivery
        deliveredProducts += delivery

        prodArr[supplierID] -= delivery

    return finalCost, deliveredProducts, workMatrix


def ignore(what: str, matrix: list, idx: int):
    if what == 'col':
        matrix = np.array(matrix).T
        matrix[idx] = [np.inf] * len(matrix[idx])
        return matrix.T

    elif what == 'row':
        matrix[idx] = [np.inf] * len(matrix[idx])
        return matrix


def getBiggestPenalty(balancedMatrix: list):
    penaltiesInRow = []
    penaltiesInCol = []

    for x in range(len(balancedMatrix)):
        diff = absoluteDifferenceOfTwoSmallestInRow(balancedMatrix[x])
        penaltiesInRow.append(diff)

    transposed = np.array(balancedMatrix).T

    for x in range(len(transposed)):
        diff = absoluteDifferenceOfTwoSmallestInRow(transposed[x])
        penaltiesInCol.append(diff)

    max_r = max(penaltiesInRow)
    max_c = max(penaltiesInCol)

    if max_c >= max_r:
        index = np.where(penaltiesInCol == max_c)[0]
        if len(index) != 0:
            return "c", index[0], max_c

    else:
        index = np.where(penaltiesInRow == max_r)[0]
        if len(index) != 0:
            return "r", index[0], max_r

    return "stop", 0, 0


def absoluteDifferenceOfTwoSmallestInRow(row: list):
    row = np.array(row)
    if len(set(row)) == 1 and np.isinf(row[0]):
        return 0

    nonInfMax = np.nanmax(row[row != np.inf])
    row[row == np.inf] = nonInfMax

    if len(set(row)) == 1 and not np.isinf(row[0]):
        return row[0]

    else:
        value1, value2 = np.partition(row, 1)[0:2]
        return abs(value1 - value2)


def balanceData(supply: list, demand: list, costs: list):
    totalSupply = sum(supply)
    totalDemand = sum(demand)
    diff = totalDemand - totalSupply

    if totalSupply < totalDemand:
        newSupply = supply + [totalDemand - totalSupply]
        newCosts = costs + [[0 for x in supply]]

        return newSupply, demand, newCosts, diff

    if totalSupply > totalDemand:
        newDemand = demand + [totalSupply - totalDemand]
        newCosts = costs + [[0 for x in demand]]

        return supply, newDemand, newCosts, diff

    return supply, demand, costs, diff


def createDataArray(pharmacies: list, suppliers: list, connections: list):
    needArr = []
    prodArr = []
    costArr = []

    for pharmacy in pharmacies:
        needArr.append(pharmacy.getDailyNeed())

    for supplier in suppliers:
        prodArr.append(supplier.getDailyProduction())

    for connection in connections:
        costArr.append(connection.getCost())

    return needArr, prodArr, costArr


def updateConnections(pharmacyID: int, supplierID: int, limitMatrix: list, workMatrix: list, value: int):
    limitMatrix[supplierID][pharmacyID] -= value

    if limitMatrix[supplierID][pharmacyID] == 0:
        workMatrix[supplierID][pharmacyID] = np.inf


def checkIfDeliveryIsPossible(pharmacyID: int, supplierID: int, limitMatrix: list, value: int):
    if limitMatrix[supplierID][pharmacyID] >= value:
        return True

    return False


def createTOCmatrix(balancedData: tuple, connectionsMatrix: list):
    TOCmatrixRows = createBalancedMatrix(balancedData, connectionsMatrix)
    TOCmatrixCols = createBalancedMatrix(balancedData, connectionsMatrix)

    for i in range(len(TOCmatrixRows)):
        minValue = min(TOCmatrixRows[i])
        for j in range(len(TOCmatrixRows[i])):
            TOCmatrixRows[i][j] -= minValue

    TOCmatrixCols = np.array(TOCmatrixCols).T
    for i in range(len(TOCmatrixCols)):
        minValue = min(TOCmatrixCols[i])
        for j in range(len(TOCmatrixCols[i])):
            TOCmatrixCols[i][j] -= minValue

    TOCmatrixCols = np.array(TOCmatrixCols).T

    return TOCmatrixRows + TOCmatrixCols


def createLimitMatrix(data: tuple, balancedMatrix: list, connectionsMatrix: list, diff: int):
    numberOfPharmacies = dataClasses.Pharmacy.pharmacyCounter
    numberOfSuppliers = dataClasses.Supplier.supplierCounter

    supply = data[0]
    need = data[1]
    matrix = [[0] * len(need) for i in range(len(supply))]

    for y in range(len(balancedMatrix)):
        for x in range(len(balancedMatrix[y])):
            if x < numberOfPharmacies and y < numberOfSuppliers:
                matrix[y][x] = connectionsMatrix[y][x].getMaxDelivery()

            else:
                matrix[y][x] = abs(diff)

    return matrix


def createBalancedMatrix(data: tuple, connectionMatrix: list):
    supply = data[0]
    need = data[1]
    matrix = [[0] * len(need) for i in range(len(supply))]

    if len(supply) != dataClasses.Supplier.supplierCounter:
        rangeY = len(supply) - 1
        rangeX = len(need)

    elif len(need) != dataClasses.Pharmacy.pharmacyCounter:
        rangeY = len(supply)
        rangeX = len(need) - 1

    else:
        rangeY = len(supply)
        rangeX = len(need)

    for y in range(rangeY):
        for x in range(rangeX):
            matrix[y][x] = getConnectionCost(x, y, connectionMatrix)

    return matrix


def createConnectionsMatrix(connections: list):
    numberOfPharmacies = dataClasses.Pharmacy.pharmacyCounter
    numberOfSuppliers = dataClasses.Supplier.supplierCounter

    connectionMatrix = [[0] * numberOfPharmacies for i in range(numberOfSuppliers)]

    for connection in connections:
        supplierID = connection.getSupplierID()
        pharmacyID = connection.getPharmacyID()
        connectionMatrix[supplierID][pharmacyID] = connection

    return connectionMatrix


def remainingMaxDelivery(pharmacyID: int, supplierID: int, limitMatrix: list):
    return limitMatrix[supplierID][pharmacyID]


def getConnectionCost(pharmacyID: int, supplierID: int, connectionsMatrix: list):
    return connectionsMatrix[supplierID][pharmacyID].getCost()


def writeToArray(outputArr: list, supplierID: int, pharmacyID: int, howMany: int, cost: float):
    if howMany > 0 and cost > 0:
        pharmacyName = dataClasses.sortedLists.sortedPharmacies[pharmacyID].getName()
        supplierName = dataClasses.sortedLists.sortedSuppliers[supplierID].getName()

        outputArr.append("{} --> {} [Koszt = {} * {} = {} zł]\n".format(supplierName, pharmacyName, howMany, cost, round(howMany * cost, 2)))
