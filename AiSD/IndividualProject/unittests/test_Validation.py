import unittest
import core.Validation as validate


class auxiliaryFunctionsTests(unittest.TestCase):
    def test_costCheck_shouldReturnFalseIfValueIsNaNOrIsSmallerThanZero(self):
        # given
        value1 = "str"
        value2 = "99.99"
        value3 = "-85.55"

        # when
        test1 = validate.costCheck(value1)
        test2 = validate.costCheck(value2)
        test3 = validate.costCheck(value3)

        # then
        self.assertEqual(False, test1)
        self.assertEqual(True, test2)
        self.assertEqual(False, test3)

    def test_isPositiveInt_shouldReturnFalseIfValueIsNotAnIntOrIsNotPositive(self):
        # given
        value1 = "str"
        value2 = "99"
        value3 = "-7"
        value4 = "89.5"

        # when
        test1 = validate.isPositiveInt(value1)
        test2 = validate.isPositiveInt(value2)
        test3 = validate.isPositiveInt(value3)
        test4 = validate.isPositiveInt(value4)

        # then
        self.assertEqual(False, test1)
        self.assertEqual(True, test2)
        self.assertEqual(False, test3)
        self.assertEqual(False, test4)


class validateFileFormatTests(unittest.TestCase):
    def test_shouldReturnFalseIfLessOrMoreThanThreeComments(self):
        # given
        givenValue = ["# comment1", "# comment2"]

        # when
        returnedValue = validate.validateFileFormat(givenValue)

        # then
        self.assertEqual(False, returnedValue)

    def test_shouldReturnFalseIfNoDataBetweenComments(self):
        # given
        givenValue = ["# comment1", "# comment2", "# comment3"]

        # when
        returnedValue = validate.validateFileFormat(givenValue)

        # then
        self.assertEqual(False, returnedValue)

    def test_shouldReturnFalseIfEmptyLineAppears(self):
        # given
        givenValue = [" ", "# comment1", "# comment2", "# comment3"]

        # when
        returnedValue = validate.validateFileFormat(givenValue)

        # then
        self.assertEqual(False, returnedValue)

    def test_shouldReturnFalseIfTooFewSeparators(self):
        # given
        givenValue = ["# comment1", "1 | 234", "# comment2", "1 | Name | 234", "# comment3", "1|1|634|83.25"]

        # when
        returnedValue = validate.validateFileFormat(givenValue)

        # then
        self.assertEqual(False, returnedValue)


class validateFileDataTests(unittest.TestCase):
    def test_shouldReturnFalseIfAnyIDIsNotPositiveInt(self):
        # given
        givenValue = ["# comment1", "A | Name |234", "# comment2", "1 | Name | 234", "# comment3", "1 | 1 | 634 | 83.25"]

        # when
        returnedValue = validate.validateFileData(givenValue)

        # then
        self.assertEqual(False, returnedValue)

    def test_shouldReturnFalseIfAnyNameIsEmpty(self):
        # given
        givenValue = ["# comment1", "1 | |234", "# comment2", "1 | Name | 234", "# comment3", "1 | 1 | 634 | 83.25"]

        # when
        returnedValue = validate.validateFileData(givenValue)

        # then
        self.assertEqual(False, returnedValue)

    def test_shouldReturnFalseIfProductionDemandIsNotPositiveInt(self):
        # given
        givenValue = ["# comment1", "1 | Name | 23A4", "# comment2", "1 | Name | 23A4", "# comment3", "1 | 1 | 634 | 83.25"]

        # when
        returnedValue = validate.validateFileData(givenValue)

        # then
        self.assertEqual(False, returnedValue)


if __name__ == '__main__':
    unittest.main()
