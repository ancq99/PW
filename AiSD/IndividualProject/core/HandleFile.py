import codecs
import os
import core.TextHighlighter as txt
import core.Validation as validation
import core.DataClasses as dataClasses


def handleFile(inputFilePath: str):
    inputFile = codecs.open(inputFilePath, "r", "UTF-8")
    inputFileLines = []

    for line in inputFile:
        inputFileLines.append(line)

    print("Starting file format validation!\n")

    if validation.validateFileFormat(inputFileLines):
        if validation.validateFileData(inputFileLines):
            txt.coloredPrint("File format validation finished!", txt.styleOfHighlight.SUCCESS, True)
            print("Starting reading file!\n")

            readValue = readFile(inputFileLines)

            txt.coloredPrint("File read successfully!", txt.styleOfHighlight.SUCCESS, True)
            print("Starting data content validation!\n")

            if validation.validateDataContent(readValue):
                txt.coloredPrint("Data content validation finished!", txt.styleOfHighlight.SUCCESS, True)
                return readValue

            else:
                txt.coloredPrint("Error! File content is not correct!", txt.styleOfHighlight.ERROR, True)
                raise Exception("Program stopped!")

        else:
            txt.coloredPrint("Error! File data is not correct!", txt.styleOfHighlight.ERROR, True)
            raise Exception("Program stopped!")

    else:
        txt.coloredPrint("Error! File format is not correct!", txt.styleOfHighlight.ERROR, True)
        raise Exception("Program stopped!")


def handleFileWithoutValidation(inputFilePath: str):
    inputFile = codecs.open(inputFilePath, "r", "UTF-8")
    inputFileLines = []

    for line in inputFile:
        inputFileLines.append(line)

    readValue = readFile(inputFileLines)

    return readValue


def readFile(inputFile: list):
    pharmacyArray = []
    supplierArray = []
    connectionsArray = []
    paragraphCounter = 0

    for line in inputFile:
        line = line.replace(" ", "")

        if line[0] != '#':
            splittedLines = line.split('|')

            if paragraphCounter == 1:
                supplierArray.append(dataClasses.Supplier(int(splittedLines[0]), splittedLines[1], int(splittedLines[2])))

            elif paragraphCounter == 2:
                pharmacyArray.append(dataClasses.Pharmacy(int(splittedLines[0]), splittedLines[1], int(splittedLines[2])))

            elif paragraphCounter == 3:
                connectionsArray.append(dataClasses.Connections(int(splittedLines[0]), int(splittedLines[1]), int(splittedLines[2]), float(splittedLines[3])))

        else:
            paragraphCounter += 1

    return supplierArray, pharmacyArray, connectionsArray


def save2file(outputArr, name="output.txt"):
    outputFile = codecs.open(name, "w", "UTF-8")

    for line in outputArr:
        outputFile.write(line)

    outputFile.close()

    txt.coloredPrint("Better results saved in: {}".format(os.getcwd()), txt.styleOfHighlight.SUCCESS, True)
