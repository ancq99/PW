import sys
from pathlib import Path
from core import HandleFile as fileHandler
from core import TextHighlighter as txt
import core.VAM as VAM
import core.FirstSolver as firstSolver
import core.DataClasses as dataClass


def run(filePath: str):
    validateFilePath = Path(filePath)
    if validateFilePath.is_file():
        readFile = fileHandler.handleFile(filePath)

    else:
        txt.coloredPrint("Error! File don't exists!", txt.styleOfHighlight.ERROR, True)
        raise Exception("Program stopped!")

    print("Starting connection finder! It may take a while\n")

    finalCost, deliveredProducts, outputArr = firstSolver.SolutionFinder(readFile)

    dataClass.reset()
    readFile = fileHandler.handleFileWithoutValidation(filePath)

    finalCostVAM, deliveredProductsVAM, outputArrVAM, balanceValue = VAM.VAM(readFile)

    txt.coloredPrint("Comparing results!", txt.styleOfHighlight.WARNING, True, True)

    sumOfNeeds = dataClass.Pharmacy.sumOfNeeds
    deliveredProductsVAM -= abs(balanceValue)

    if deliveredProducts == deliveredProductsVAM:
        if finalCost > finalCostVAM:
            print("VAM got better results! Saving to file...\n")
            fileHandler.save2file(outputArrVAM)

        else:
            print("First solver got better results! Saving to file...\n")
            fileHandler.save2file(outputArr)

    elif deliveredProducts == sumOfNeeds and deliveredProductsVAM != sumOfNeeds:
        print("Only first solver delivered all vaccines! Saving to file...\n")
        fileHandler.save2file(outputArr)

    elif deliveredProducts != sumOfNeeds and deliveredProductsVAM == sumOfNeeds:
        print("Only VAM delivered all vaccines! Saving to file...\n")
        fileHandler.save2file(outputArrVAM)

    else:
        txt.coloredPrint("Warning both of solvers could't deliver all vaccines! Saving both to results files!", txt.styleOfHighlight.WARNING, True)
        fileHandler.save2file(outputArrVAM, "outputVAM.txt")
        fileHandler.save2file(outputArr, "outputFirst.txt")

    print("Program finished!\n")


if __name__ == "__main__":
    if len(sys.argv) > 1:
        inputFilePath = sys.argv[1]
        print("\nStarting program!\n")
        run(inputFilePath)

    else:
        txt.coloredPrint("Error! Too few arguments!", txt.styleOfHighlight.ERROR, True)
        raise Exception("Program stopped!")
