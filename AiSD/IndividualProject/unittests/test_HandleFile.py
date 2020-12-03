import os
import unittest
import core.HandleFile as handler


class HandleFileTests(unittest.TestCase):
    def test_shouldRiseExceptionIfDataFormatIsNotCorrect(self):
        # given
        pathToFile = os.getcwd() + "unittests\\test_data\\wrongFileFormat.txt"

        # when

        # then
        self.assertRaises(Exception, handler.handleFile, pathToFile)

    def test_shouldRiseExceptionIfDataInFileIsNotCorrect(self):
        # given
        pathToFile = os.getcwd() + "unittests\\test_data\\wrongFileData.txt"

        # when

        # then
        self.assertRaises(Exception, handler.handleFile, pathToFile)

    def test_shouldRiseExceptionIfDataContentIsNotCorrect(self):
        # given
        pathToFile = os.getcwd() + "unittests\\test_data\\wrongDataContent.txt"

        # when

        # then
        self.assertRaises(Exception, handler.handleFile, pathToFile)


if __name__ == '__main__':
    unittest.main()
