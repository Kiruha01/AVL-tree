import os
import subprocess

import pytest

PATH_TO_BUILD = os.environ.get("BUILD_PATH") or "../build/"


@pytest.fixture(params=[("input1.txt", "output1.txt"),
                        ("input2.txt", "output2.txt"),
                        ("input3.txt", "output3.txt")])
def fileout(request):
    with open(request.param[0], 'r') as file:
        with open("input.txt", "w") as infile:
            infile.write(file.read())
    return request.param[1]


def test_tree(fileout):
    code = subprocess.run("sudo " + os.path.join(PATH_TO_BUILD, "AVL_tree"))
    assert code.returncode == 0
    with open(fileout, 'r') as correct_file:
        with open("output.txt", 'r') as testing_file:
            for l1, l2 in zip(correct_file.readlines(), testing_file.readlines()):
                assert l1 == l2
