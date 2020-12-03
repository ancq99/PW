import os
import unittest
import core.FirstSolver as core
import core.HandleFile as handler


class FirstSolverTests(unittest.TestCase):
    pharmacy = supplier = connectionsMatrix = []

    @classmethod
    def setUpClass(cls):
        path = os.getcwd() + "\\unittests\\test_data\\correctFile.txt"
        readFile = handler.handleFileWithoutValidation(path)
        FirstSolverTests.supplier = readFile[0]
        FirstSolverTests.pharmacy = readFile[1]
        FirstSolverTests.connectionsMatrix = core.createConnectionsMatrix(readFile[2])

    def test_updateConnection_shouldUpdateMaxDeliveryValueOfConnection(self):
        # given
        pharmacy = FirstSolverTests.pharmacy[0]
        supplier = FirstSolverTests.supplier[0]
        connectionsMatrix = FirstSolverTests.connectionsMatrix

        # when
        core.updateConnections(pharmacy, supplier, connectionsMatrix, 12)
        value = connectionsMatrix[supplier.getID()][pharmacy.getID()].getMaxDelivery()

        self.assertEqual(2000, value)

    def test_checkIfDeliveryIsPossible_shouldReturnTrueIfDeliveryAmountIsSmallerThanMaxDelivery(self):
        # given
        pharmacy = FirstSolverTests.pharmacy[0]
        supplier = FirstSolverTests.supplier[1]
        connectionsMatrix = FirstSolverTests.connectionsMatrix

        # when
        value1 = core.checkIfDeliveryIsPossible(pharmacy, supplier, connectionsMatrix, 100)
        value2 = core.checkIfDeliveryIsPossible(pharmacy, supplier, connectionsMatrix, 1000)

        # then
        self.assertEqual(True, value1)
        self.assertEqual(False, value2)

    def test_remainingMaxDelivery_shouldReturnMaxDeliveryAccordingToPharmacyAndSupplierID(self):
        # given
        pharmacy = FirstSolverTests.pharmacy[0]
        supplier = FirstSolverTests.supplier[1]
        connectionsMatrix = FirstSolverTests.connectionsMatrix

        # when
        value = core.remainingMaxDelivery(pharmacy, supplier, connectionsMatrix)

        # then
        self.assertEqual(200, value)

    def test_getConnectionCost_shouldReturnCostAccordingToPharmacyAndSupplierID(self):
        # given
        pharmacy = FirstSolverTests.pharmacy[0]
        supplier = FirstSolverTests.supplier[0]
        connectionsMatrix = FirstSolverTests.connectionsMatrix

        # when
        value = core.getConnectionCost(pharmacy, supplier, connectionsMatrix)

        # then
        self.assertEqual(70.5, value)


if __name__ == '__main__':
    FirstSolverTests.setUp()
    unittest.main()
