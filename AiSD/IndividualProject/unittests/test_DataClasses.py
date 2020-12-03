import unittest
import core.DataClasses as dataClass


class PharmaciesTests(unittest.TestCase):
    # given
    pharmacy1 = dataClass.Pharmacy(1, "test1", 10000)
    pharmacy2 = dataClass.Pharmacy(2, "test2", 20000)
    pharmacy3 = dataClass.Pharmacy(3, "test3", 30000)

    def test_pharmacyCounter_shouldReturnNumberOfAddedPharmacies(self):
        # when
        pharmacyCounter = dataClass.Pharmacy.pharmacyCounter

        # then
        self.assertEqual(3, pharmacyCounter)

    def test_sumOfDailyNeeds_shouldReturnSumOfDailyNeedsOfAllPharmacies(self):
        # when
        sumOfNeeds = dataClass.Pharmacy.sumOfNeeds

        # then
        self.assertEqual(60000, sumOfNeeds)

    def test_getID_shouldReturnIDOfSelectedPharmacy(self):
        # given
        pharmacy1 = PharmaciesTests.pharmacy1

        # when
        returnedID = pharmacy1.getID()

        # then
        self.assertEqual(1, returnedID)

    def test_getName_shouldReturnNameOfSelectedPharmacy(self):
        # given
        pharmacy = PharmaciesTests.pharmacy1

        # when
        returnedName = pharmacy.getName()

        # then
        self.assertEqual("test1", returnedName)

    def test_getDailyNeed_shouldReturnDailyNeedOfSelectedPharmacy(self):
        # given
        pharmacy = PharmaciesTests.pharmacy1

        # when
        returnedDailyNeed = pharmacy.getDailyNeed()

        # then
        self.assertEqual(10000, returnedDailyNeed)

    def test_updateDailyNeed_shouldUpdateDailyNeedOfSelectedPharmacy(self):
        # given
        pharmacy = PharmaciesTests.pharmacy1

        # when
        pharmacy.updateDailyNeed(5000)
        updatedValue = pharmacy.getDailyNeed()

        # then
        self.assertEqual(5000, updatedValue)

    def test_stillNeed_shouldReturnFalseIfDailyNeedOfPharmacyIsZero(self):
        # given
        pharmacy = PharmaciesTests.pharmacy2

        # when
        pharmacy.updateDailyNeed(20000)
        returnedValue = pharmacy.stillNeed()

        # then
        self.assertEqual(False, returnedValue)


class SuppliersTests(unittest.TestCase):
    # given
    supplier1 = dataClass.Supplier(1, "test1", 10000)
    supplier2 = dataClass.Supplier(2, "test2", 20000)
    supplier3 = dataClass.Supplier(3, "test3", 30000)

    def test_supplierCounter_shouldReturnNumberOfAddedSuppliers(self):
        # when
        supplierCounter = dataClass.Supplier.supplierCounter

        # then
        self.assertEqual(3, supplierCounter)

    def test_sumOfProduction_shouldReturnSumOfProductionsOfAllSuppliers(self):
        # when
        sumOfProduction = dataClass.Supplier.sumOfProduction

        # then
        self.assertEqual(60000, sumOfProduction)

    def test_getID_shouldReturnIDOfSelectedSupplier(self):
        # given
        supplier = SuppliersTests.supplier1

        # when
        returnedID = supplier.getID()

        # then
        self.assertEqual(1, returnedID)

    def test_getName_shouldReturnNameOfSelectedSupplier(self):
        # given
        supplier = SuppliersTests.supplier2

        # when
        returnedName = supplier.getName()

        # then
        self.assertEqual("test2", returnedName)

    def test_getDailyProduction_shouldReturnDailyProductionOfSelectedSupplier(self):
        # given
        supplier = SuppliersTests.supplier3

        # when
        returnedValue = supplier.getDailyProduction()

        # then
        self.assertEqual(30000, returnedValue)

    def test_updateDailyProduction_shouldUpdateDailyProductionOfSupplier(self):
        # given
        supplier = SuppliersTests.supplier3

        # when
        supplier.updateDailyProduction(15000)
        returnedValue = supplier.getDailyProduction()

        # then
        self.assertEqual(15000, returnedValue)


class ConnectionsTests(unittest.TestCase):
    # given
    connection1 = dataClass.Connections(1, 1, 600, 79.99)
    connection2 = dataClass.Connections(2, 2, 1200, 85.99)
    connection3 = dataClass.Connections(3, 3, 1600, 179.99)

    def test_connectionCounter_shouldReturnNumberOfAddedConnections(self):
        # when
        connectionCounter = dataClass.Connections.connectionCounter

        # then
        self.assertEqual(3, connectionCounter)

    def test_getSupplierID_shouldReturnIDOfSupplierInSelectedConnection(self):
        # given
        connection = ConnectionsTests.connection1

        # when
        returnedID = connection.getSupplierID()

        # then
        self.assertEqual(1, returnedID)

    def test_getPharmacyID_shouldReturnIDOfPharmacyInSelectedConnection(self):
        # given
        connection = ConnectionsTests.connection2

        # when
        returnedID = connection.getSupplierID()

        # then
        self.assertEqual(2, returnedID)

    def test_getMaxDelivery_shouldReturnMaxDeliveryInSelectedConnection(self):
        # given
        connection = ConnectionsTests.connection1

        # when
        returnedValue = connection.getMaxDelivery()

        # then
        self.assertEqual(600, returnedValue)

    def test_getCost_shouldReturnCostInSelectedConnection(self):
        # given
        connection = ConnectionsTests.connection2

        # when
        returnedValue = connection.getCost()

        # then
        self.assertEqual(85.99, returnedValue)

    def test_updateMaxDelivery_shouldUpdateMaxDeliveryInSelectedConnection(self):
        # given
        connection = ConnectionsTests.connection3

        # when
        connection.updateMaxDelivery(500)
        returnedValue = connection.getMaxDelivery()

        # then
        self.assertEqual(1100, returnedValue)


class SortedListsTests(unittest.TestCase):
    def test_shouldReturnSortedLists(self):
        # given
        suppliers = [dataClass.Supplier(3, "name1", 40), dataClass.Supplier(1, "name2", 14), dataClass.Supplier(2, "name3", 24)]
        pharmacies = [dataClass.Pharmacy(4, "name1", 23), dataClass.Pharmacy(1, "name1", 23), dataClass.Pharmacy(2, "name1", 23)]

        # when
        dataClass.sortedLists(pharmacies, suppliers)
        sortedSuppliers = dataClass.sortedLists.sortedSuppliers
        sortedPharmacies = dataClass.sortedLists.sortedPharmacies
        pharmaciesID = []
        suppliersID = []

        for x in range(3):
            pharmaciesID.append(sortedPharmacies[x].getID())
            suppliersID.append(sortedSuppliers[x].getID())

        # then
        self.assertEqual([1, 2, 3], suppliersID)
        self.assertEqual([1, 2, 4], pharmaciesID)


if __name__ == '__main__':
    unittest.main()
