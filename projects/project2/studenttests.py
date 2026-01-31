import sys
import unittest
from framework import AssemblyTest, print_coverage, _venus_default_args
from tools.check_hashes import check_hashes

"""
Coverage tests for project 2 is meant to make sure you understand
how to test RISC-V code based on function descriptions.
Before you attempt to write these tests, it might be helpful to read
unittests.py and framework.py.
Like project 1, you can see your coverage score by submitting to gradescope.
The coverage will be determined by how many lines of code your tests run,
so remember to test for the exceptions!
"""

"""
abs_loss
# =======================================================
# FUNCTION: Get the absolute difference of 2 int arrays,
#   store in the result array and compute the sum
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the length of the arrays
#   a3 (int*) is the pointer to the start of the result array

# Returns:
#   a0 (int)  is the sum of the absolute loss
# Exceptions:
# - If the length of the array is less than 1,
#   this function terminates the program with error code 36.
# =======================================================
"""


class TestAbsLoss(unittest.TestCase):
    def test_abs_standard(self):
        # load the test for abs_loss.s
        t = AssemblyTest(self, "../coverage-src/abs_loss.s")

        # create an array in the data section
        array0 = t.array([1, -2, 3, 0, 8, -6, 7, -8, -9])
        # load address of `array0` into register a0
        t.input_array("a0", array0)
        # create an array in the data section
        array1 = t.array([2, -2, 3, 0, 5, -6, 7, -8, 10])
        # load address of `array0` into register a0
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        array2 = t.array([-1, -1, -1, -1, -1, -1, -1, -1, -1])
        # load address of `array0` into register a0
        t.input_array("a3", array2)
        # call the `relu` function
        t.call("abs_loss")
        # check that the array0 was changed appropriately
        t.check_scalar("a0", 23)
        t.check_array(array2, [1, 0, 0, 0, 3, 0, 0, 0, 19])
        # generate the `assembly/TestRelu_test_simple.s` file and run it through venus
        t.execute()

    def test_abs_length_1(self):
        # load the test for abs_loss.s
        t = AssemblyTest(self, "../coverage-src/abs_loss.s")

        # create an array in the data section
        array0 = t.array([-1])
        # load address of `array0` into register a0
        t.input_array("a0", array0)
        # create an array in the data section
        array1 = t.array([1])
        # load address of `array0` into register a0
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        array2 = t.array([-1])
        # load address of `array0` into register a0
        t.input_array("a3", array2)
        # call the `relu` function
        t.call("abs_loss")
        # check that the array0 was changed appropriately
        t.check_scalar("a0", 2)
        t.check_array(array2, [2])
        # generate the `assembly/TestRelu_test_simple.s` file and run it through venus
        t.execute()

    # Add other test cases if necessary
    def test_abs_invalid_n(self):
        t = AssemblyTest(self, "../coverage-src/abs_loss.s")
        # set a2 to an invalid length of array
        t.input_scalar("a2", -1)
        t.call("abs_loss")
        t.execute(code=36)

    @classmethod
    def tearDownClass(cls):
        print_coverage("abs_loss.s", verbose=False)


"""
squared_loss
# =======================================================
# FUNCTION: Get the squared difference of 2 int arrays,
#   store in the result array and compute the sum
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the length of the arrays
#   a3 (int*) is the pointer to the start of the result array

# Returns:
#   a0 (int)  is the sum of the squared loss
# Exceptions:
# - If the length of the array is less than 1,
#   this function terminates the program with error code 36.
# =======================================================
"""


class TestSquaredLoss(unittest.TestCase):
    def test_squared_standard(self):
        # load the test for squared_loss.s
        t = AssemblyTest(self, "../coverage-src/squared_loss.s")

        # create an array in the data section
        array0 = t.array([1, -2, 3, 0, 8, -6, 7, -8, -9])
        # load address of `array0` into register a0
        t.input_array("a0", array0)
        # create an array in the data section
        array1 = t.array([2, -2, 3, 0, 5, -6, 7, -8, 10])
        # load address of `array0` into register a0
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        array2 = t.array([-1, -1, -1, -1, -1, -1, -1, -1, -1])
        # load address of `array0` into register a0
        t.input_array("a3", array2)
        # call the `relu` function
        t.call("squared_loss")
        # check that the array0 was changed appropriately
        t.check_scalar("a0", 371)
        t.check_array(array2, [1, 0, 0, 0, 9, 0, 0, 0, 361])
        # generate the `assembly/TestRelu_test_simple.s` file and run it through venus
        t.execute()

    def test_squared_length_1(self):
        # load the test for squared_loss.s
        t = AssemblyTest(self, "../coverage-src/squared_loss.s")

        # create an array in the data section
        array0 = t.array([-1])
        # load address of `array0` into register a0
        t.input_array("a0", array0)
        # create an array in the data section
        array1 = t.array([1])
        # load address of `array0` into register a0
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        array2 = t.array([-1])
        # load address of `array0` into register a0
        t.input_array("a3", array2)
        # call the `relu` function
        t.call("squared_loss")
        # check that the array0 was changed appropriately
        t.check_scalar("a0", 4)
        t.check_array(array2, [4])
        # generate the `assembly/TestRelu_test_simple.s` file and run it through venus
        t.execute()

    # Add other test cases if necessary
    def test_squared_invalid_n(self):
        t = AssemblyTest(self, "../coverage-src/squared_loss.s")
        # set a2 to an invalid length of array
        t.input_scalar("a2", 0)
        t.call("squared_loss")
        t.execute(code=36)

    @classmethod
    def tearDownClass(cls):
        print_coverage("squared_loss.s", verbose=False)


"""
zero_one_loss
# =======================================================
# FUNCTION: Generates a 0-1 classifer array inplace in the result array,
#  where result[i] = (arr0[i] == arr1[i])
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the length of the arrays
#   a3 (int*) is the pointer to the start of the result array

# Returns:
#   NONE
# Exceptions:
# - If the length of the array is less than 1,
#   this function terminates the program with error code 36.
# =======================================================
"""


class TestZeroOneLoss(unittest.TestCase):
    def test_zero_one_standard(self):
        # load the test for zero_one_loss.s
        t = AssemblyTest(self, "../coverage-src/zero_one_loss.s")

        # create an array in the data section
        array0 = t.array([1, -2, 3, 0, 8, -6, 7, -8, -9])
        # load address of `array0` into register a0
        t.input_array("a0", array0)
        # create an array in the data section
        array1 = t.array([2, -2, 3, 0, 5, -6, 7, -8, 10])
        # load address of `array0` into register a0
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        array2 = t.array([-1, -1, -1, -1, -1, -1, -1, -1, -1])
        # load address of `array0` into register a0
        t.input_array("a3", array2)
        # call the `relu` function
        t.call("zero_one_loss")
        # check that the array0 was changed appropriately
        t.check_array(array2, [0, 1, 1, 1, 0, 1, 1, 1, 0])
        # generate the `assembly/TestRelu_test_simple.s` file and run it through venus
        t.execute()

    def test_zero_one_length_1(self):
        # load the test for zero_one_loss.s
        t = AssemblyTest(self, "../coverage-src/zero_one_loss.s")

        # create an array in the data section
        array0 = t.array([-1])
        # load address of `array0` into register a0
        t.input_array("a0", array0)
        # create an array in the data section
        array1 = t.array([1])
        # load address of `array0` into register a0
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        array2 = t.array([-1])
        # load address of `array0` into register a0
        t.input_array("a3", array2)
        # call the `relu` function
        t.call("zero_one_loss")
        # check that the array0 was changed appropriately
        t.check_array(array2, [0])
        # generate the `assembly/TestRelu_test_simple.s` file and run it through venus
        t.execute()

    # Add other test cases if necessary
    def test_zero_one_invalid_n(self):
        t = AssemblyTest(self, "../coverage-src/zero_one_loss.s")
        # set a2 to an invalid length of array
        t.input_scalar("a2", 0)
        t.call("zero_one_loss")
        t.execute(code=36)

    @classmethod
    def tearDownClass(cls):
        print_coverage("zero_one_loss.s", verbose=False)


"""
initialize_zero
# =======================================================
# FUNCTION: Initialize a zero array with the given length
# Arguments:
#   a0 (int) size of the array

# Returns:
#   a0 (int*)  is the pointer to the zero array
# Exceptions:
# - If the length of the array is less than 1,
#   this function terminates the program with error code 36.
# - If malloc fails, this function terminates the program with exit code 26.
# =======================================================
"""


class TestInitializeZero(unittest.TestCase):
    def test_initilize_zero(self):
        t = AssemblyTest(self, "../coverage-src/initialize_zero.s")
        # input the length of the desired array
        # TODO
        t.input_scalar("a0", 3)
        # call the `initialize_zero` function
        # TODO
        t.call("initialize_zero")
        # check that the register a0 contains the correct array (hint: look at the check_array_pointer function in framework.py)
        t.check_array_pointer("a0", [0, 0, 0])
        # TODO
        t.execute()

    # Add other test cases if neccesary
    def test_initialize_zero_invalid_n(self):
        t = AssemblyTest(self, "../coverage-src/initialize_zero.s")
        # set a2 to an invalid length of array
        t.input_scalar("a0", 0)
        t.call("initialize_zero")
        t.execute(code=36)

    def test_initialize_zero_malloc_n(self):
        t = AssemblyTest(self, "../coverage-src/initialize_zero.s")
        # set a2 to an invalid length of array
        t.input_scalar("a0", 1)
        t.call("initialize_zero")
        t.execute(code=26, fail="malloc")

    @classmethod
    def tearDownClass(cls):
        print_coverage("initialize_zero.s", verbose=False)


if __name__ == "__main__":
    split_idx = sys.argv.index("--")
    for arg in sys.argv[split_idx + 1 :]:
        _venus_default_args.append(arg)

    check_hashes()

    unittest.main(argv=sys.argv[:split_idx])
