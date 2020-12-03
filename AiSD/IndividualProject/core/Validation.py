import core.TextHighlighter as txt
import core.DataClasses as dataClasses


def validateFileFormat(inputFileLines: list):
    commentLineNumber = -2
    paragraphNumber = 0
    charCounter = 0
    errorCounter = 0

    for line in inputFileLines:
        charCounter += line.count('#')

    if charCounter != 3:
        txt.coloredPrint("Error! Too few comments!", txt.styleOfHighlight.ERROR, True, True)
        return False

    for i in range(0, len(inputFileLines)):
        if not inputFileLines[i].strip():
            txt.coloredPrint("Error at line: {}. Empty line occurred!".format(i + 1), txt.styleOfHighlight.ERROR)
            errorCounter += 1

        if inputFileLines[i][0] == '#':
            if i - commentLineNumber <= 1:
                txt.coloredPrint("Error at line: {}! No data between comments!".format(i + 1), txt.styleOfHighlight.ERROR)
                errorCounter += 1
            commentLineNumber = i
            paragraphNumber += 1

        else:
            if inputFileLines[i].count('|') != 2 and paragraphNumber != 3:
                txt.coloredPrint("Error at line: {}! Too few separator chars!".format(i + 1), txt.styleOfHighlight.ERROR)
                errorCounter += 1

            if inputFileLines[i].count('|') != 3 and paragraphNumber == 3:
                txt.coloredPrint("Error at line: {}! Too few separator chars!".format(i + 1), txt.styleOfHighlight.ERROR)
                errorCounter += 1

    if errorCounter == 0:
        return True

    else:
        txt.coloredPrint("Number of errors: {}!".format(errorCounter), txt.styleOfHighlight.ERROR, True, True)
        return False


def validateFileData(inputFileLines: list):
    lineCounter = 1
    paragraphCounter = 0
    errorCounter = 0
    for line in inputFileLines:
        line = line.replace(" ", "")
        if line[0] != '#':
            splittedLine = line.split('|')

            if paragraphCounter != 3:
                if not isPositiveInt(splittedLine[0]):
                    txt.coloredPrint("Error at line: {}! ID must be positive int!".format(lineCounter), txt.styleOfHighlight.ERROR)
                    errorCounter += 1

                if len(splittedLine[1]) == 0:
                    txt.coloredPrint("Error at line: {}! Name cannot be empty!".format(lineCounter), txt.styleOfHighlight.ERROR)
                    errorCounter += 1

                if not isPositiveInt(splittedLine[2]):
                    txt.coloredPrint("Error at line: {}! Daily production/demand must be int!".format(lineCounter), txt.styleOfHighlight.ERROR)
                    errorCounter += 1

            else:
                if not isPositiveInt(splittedLine[0]) or not isPositiveInt(splittedLine[1]):
                    txt.coloredPrint("Error at line: {}! ID must be positive int!".format(lineCounter), txt.styleOfHighlight.ERROR)
                    errorCounter += 1

                if not isPositiveInt(splittedLine[2]):
                    txt.coloredPrint("Error at line: {}! Max daily delivery must be int!".format(lineCounter), txt.styleOfHighlight.ERROR)
                    errorCounter += 1

                if not costCheck(splittedLine[3]):
                    txt.coloredPrint("Error at line: {}! Cost must be non-negative float!".format(lineCounter), txt.styleOfHighlight.ERROR)
                    errorCounter += 1

        else:
            paragraphCounter += 1
        lineCounter += 1

    if errorCounter == 0:
        return True

    else:
        txt.coloredPrint("Number of errors: {}!".format(errorCounter), txt.styleOfHighlight.ERROR, True, True)
        return False


def validateDataContent(readValue: tuple):
    errorCounter = 0
    suppliers = readValue[0]
    pharmacies = readValue[1]
    connections = readValue[2]

    numberOfPharmacies = dataClasses.Pharmacy.pharmacyCounter
    numberOfSuppliers = dataClasses.Supplier.supplierCounter
    numberOfConnections = dataClasses.Connections.connectionCounter

    if numberOfPharmacies > 1000:
        txt.coloredPrint("Error! Too many pharmacies! Max number of pharmacies: 1000, got: {}".format(numberOfPharmacies), txt.styleOfHighlight.ERROR)
        errorCounter += 1

    if numberOfSuppliers > 1000:
        txt.coloredPrint("Error! Too many suppliers! Max number of pharmacies: 1000, got: {}".format(numberOfSuppliers), txt.styleOfHighlight.ERROR)
        errorCounter += 1

    if numberOfConnections != numberOfSuppliers * numberOfPharmacies:
        txt.coloredPrint("Error! Number of connections have to be equal to number of pharmacies multiplied by number of suppliers", txt.styleOfHighlight.ERROR)
        errorCounter += 1

    if dataClasses.Pharmacy.sumOfNeeds > dataClasses.Supplier.sumOfProduction:
        txt.coloredPrint("Error! Sum of needs is bigger than sum of productions!", txt.styleOfHighlight.ERROR)
        errorCounter += 1

    pharmacyNames = []
    pharmacyIDs = [0] * numberOfPharmacies

    for pharmacy in pharmacies:
        pharmacyNames.append(pharmacy.getName())
        pharmacyID = pharmacy.getID()

        if pharmacyID >= numberOfPharmacies:
            txt.coloredPrint("Error! Pharmacy ID index out of range!", txt.styleOfHighlight.ERROR)
            return False

        pharmacyIDs[pharmacyID] += 1

    for index, count in enumerate(pharmacyIDs):
        if count > 1:
            txt.coloredPrint("Error! Pharmacy with ID = {} is duplicated!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

        if count < 1:
            txt.coloredPrint("Error! Pharmacy with ID = {} doesnt exisits!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

    if len(pharmacyNames) != len(set(pharmacyNames)):
        txt.coloredPrint("Error! Pharmacies names have to be unique!", txt.styleOfHighlight.ERROR)
        errorCounter += 1

    supplierNames = []
    supplierIDs = [0] * numberOfSuppliers

    for supplier in suppliers:
        supplierNames.append(supplier.getName())
        supplierID = supplier.getID()

        if supplierID >= numberOfSuppliers:
            txt.coloredPrint("Error! Supplier ID index out of range!", txt.styleOfHighlight.ERROR)
            return False

        supplierIDs[supplierID] += 1

    for index, count in enumerate(supplierIDs):
        if count > 1:
            txt.coloredPrint("Error! Supplier with ID = {} is duplicated!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

        if count < 1:
            txt.coloredPrint("Error! Supplier with ID = {} doesnt exisits!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

    if len(supplierNames) != len(set(supplierNames)):
        txt.coloredPrint("Error! Suppliers names have to be unique!", txt.styleOfHighlight.ERROR)
        errorCounter += 1

    maxDeliveryForPharmacy = [0] * numberOfPharmacies
    pharmacyIDsCounter = [0] * numberOfPharmacies
    supplierIDsCounter = [0] * numberOfSuppliers

    for connection in connections:
        supplierID = connection.getSupplierID()
        pharmacyID = connection.getPharmacyID()

        if supplierID >= numberOfSuppliers or pharmacyID >= numberOfPharmacies:
            txt.coloredPrint("Error! Either supplier or pharmacy index out of range (connections paragraph)!", txt.styleOfHighlight.ERROR)
            return False

        maxDeliveryForPharmacy[pharmacyID] += connection.getMaxDelivery()
        supplierIDsCounter[supplierID] += 1
        pharmacyIDsCounter[pharmacyID] += 1

    for index, pharmacy in enumerate(pharmacies):
        if pharmacy.getDailyNeed() > maxDeliveryForPharmacy[index]:
            txt.coloredPrint("Error! Daily need of pharmacy ID = {} is bigger than max possible delivery!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

    for index, count in enumerate(supplierIDsCounter):
        if count > numberOfPharmacies:
            txt.coloredPrint("Error! Supplier with ID= {} has duplicated connection with some of pharmacies!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

        if count < numberOfPharmacies:
            txt.coloredPrint("Error! Supplier with ID= {} dont have connection with some of pharmacies!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

    for index, count in enumerate(pharmacyIDsCounter):
        if count > numberOfSuppliers:
            txt.coloredPrint("Error! Pharmacy with ID= {} has duplicated connection with some of suppliers!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

        if count < numberOfSuppliers:
            txt.coloredPrint("Error! Pharmacy with ID= {} dont have connection with some of suppliers!".format(index), txt.styleOfHighlight.ERROR)
            errorCounter += 1

    if errorCounter == 0:
        return True

    else:
        txt.coloredPrint("Number of errors: {}!".format(errorCounter), txt.styleOfHighlight.ERROR, True, True)
        return False


def isPositiveInt(value: str):
    try:
        if int(value) < 0:
            return False

        int(value)
        return True

    except ValueError:
        return False


def costCheck(value: str):
    try:
        if float(value) <= 0.0:
            return False

        float(value)
        return True

    except ValueError:
        return False
