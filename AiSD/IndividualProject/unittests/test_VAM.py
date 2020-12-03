import os
import unittest
import core.VAM as core
import core.HandleFile as handler
import numpy as np


class VAMTests(unittest.TestCase):
    pharmacies = suppliers = connections = connectionsMatrix = []

    @classmethod
    def setUpClass(cls):
        path = os.getcwd() + "\\test_data\\correctFile.txt"
        readFile = handler.handleFileWithoutValidation(path)
        VAMTests.suppliers = readFile[0]
        VAMTests.pharmacies = readFile[1]
        VAMTests.connections = readFile[2]
        VAMTests.connectionsMatrix = core.createConnectionsMatrix(readFile[2])

    def test_getConnectionCost_shouldReturnCostOfSpecificConnection(self):
        # given
        pharmacyID = 0
        supplierID = 0
        connectionsMatrix = VAMTests.connectionsMatrix

        # when
        returnedValue = core.getConnectionCost(pharmacyID, supplierID, connectionsMatrix)

        # then
        self.assertEqual(70.5, returnedValue)

    def test_balanceData_shouldBalancedTotalDemandAndTotalProduction(self):
        # given
        pharmacies = VAMTests.pharmacies
        suppliers = VAMTests.suppliers
        connections = VAMTests.connections

        needArr, prodArr, costsArr = core.createDataArray(pharmacies, suppliers, connections)

        # when
        returnedData = core.balanceData(needArr, prodArr, costsArr)
        balanceDiff = abs(returnedData[3])

        # then
        self.assertEqual(12784, balanceDiff)

    def test_remainingMaxDelivery_shouldReturnRemainingMaxDeliveryForSpecificConenction(self):
        # given
        pharmacyID = 0
        supplierID = 0
        connectionsMatrix = VAMTests.connectionsMatrix

        needArr, prodArr, costsArr = core.createDataArray(VAMTests.pharmacies, VAMTests.suppliers, VAMTests.connections)
        balancedData = core.balanceData(needArr, prodArr, costsArr)
        balancedMatrix = core.createBalancedMatrix(balancedData, connectionsMatrix)

        limitMatrix = core.createLimitMatrix(balancedData, balancedMatrix, connectionsMatrix, balancedData[3])

        # when
        returnedValue = core.remainingMaxDelivery(pharmacyID, supplierID, limitMatrix)

        # then
        self.assertEqual(2012, returnedValue)

    def test_absoluteDifferenceOfTwoSmallestInRow_shouldReturnDifferenceOfTwoSmallestValuesInArray(self):
        # given
        array = [2, 2015, 354, 574, 214]

        # when
        returnedValue = core.absoluteDifferenceOfTwoSmallestInRow(array)

        # then
        self.assertEqual(212, returnedValue)

    def test_checkIfDeliveryIsPossible_shouldReturnTrueIfValueIsNotBiggerThanMaxDeliveryOfSpecificIDs(self):
        # given
        pharmacyID = 0
        supplierID = 0
        connectionsMatrix = VAMTests.connectionsMatrix

        needArr, prodArr, costsArr = core.createDataArray(VAMTests.pharmacies, VAMTests.suppliers, VAMTests.connections)
        balancedData = core.balanceData(needArr, prodArr, costsArr)
        balancedMatrix = core.createBalancedMatrix(balancedData, connectionsMatrix)

        limitMatrix = core.createLimitMatrix(balancedData, balancedMatrix, connectionsMatrix, balancedData[3])

        # when
        returnedValue1 = core.checkIfDeliveryIsPossible(pharmacyID, supplierID, limitMatrix, 2500)
        returnedValue2 = core.checkIfDeliveryIsPossible(pharmacyID, supplierID, limitMatrix, 250)
        returnedValue3 = core.checkIfDeliveryIsPossible(pharmacyID, supplierID, limitMatrix, 2012)

        # then
        self.assertEqual(False, returnedValue1)
        self.assertEqual(True, returnedValue2)
        self.assertEqual(True, returnedValue3)

    def test_updateConnection_shouldUpdateSpecificCellOfLimitOrWorkMatirx(self):
        # given
        pharmacyID = 0
        supplierID = 1
        connectionsMatrix = VAMTests.connectionsMatrix

        needArr, prodArr, costsArr = core.createDataArray(VAMTests.pharmacies, VAMTests.suppliers, VAMTests.connections)
        balancedData = core.balanceData(needArr, prodArr, costsArr)
        workMatrix = core.createBalancedMatrix(balancedData, connectionsMatrix)

        limitMatrix = core.createLimitMatrix(balancedData, workMatrix, connectionsMatrix, balancedData[3])

        # when
        core.updateConnections(pharmacyID, supplierID, limitMatrix, workMatrix, 150)

        # then
        self.assertEqual(50, limitMatrix[supplierID][pharmacyID])

    def test_ignore_shouldChangeWholeRowOrColumnToINF(self):
        # given
        connectionsMatrix = VAMTests.connectionsMatrix

        needArr, prodArr, costsArr = core.createDataArray(VAMTests.pharmacies, VAMTests.suppliers, VAMTests.connections)
        balancedData = core.balanceData(needArr, prodArr, costsArr)
        matrix = core.createBalancedMatrix(balancedData, connectionsMatrix)

        # when
        core.ignore("row", matrix, 0)

        # then
        for x in range(len(matrix[0])):
            self.assertEqual(np.inf, matrix[0][x])

    def test_getBiggestPenalty_shouldReturnTypeIndexAndValueOfBiggestABSDifferenceInMatrix(self):
        # given
        connectionsMatrix = VAMTests.connectionsMatrix
        needArr, prodArr, costsArr = core.createDataArray(VAMTests.pharmacies, VAMTests.suppliers, VAMTests.connections)
        balancedData = core.balanceData(needArr, prodArr, costsArr)
        matrix = core.createBalancedMatrix(balancedData, connectionsMatrix)

        # when
        returnedValue = core.getBiggestPenalty(matrix)

        # then
        expectedValue = "r", 1, 152.99
        self.assertEqual(expectedValue, returnedValue)


if __name__ == '__main__':
    VAMTests.setUp()
    unittest.main()
