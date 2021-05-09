@test "Test 1" {
  ./run_avl.sh input1.txt
  run cmp output1.txt output.txt -s
  [ "$status" -eq 0 ]
}

@test "Test 2" {
  ./run_avl.sh input2.txt
  run cmp output2.txt output.txt -s
  [ "$status" -eq 0 ]
}

@test "Test 3" {
  ./run_avl.sh input3.txt
  run cmp output3.txt output.txt -s
  [ "$status" -eq 0 ]
}