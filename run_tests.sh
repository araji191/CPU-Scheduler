#!/bin/bash

# Clear previous output
> testcase_results.txt

# Run all test cases
for i in {1..30}
do
  echo "===== Running input$i.txt =====" >> testcase_results.txt
  ./cpu_scheduler input$i.txt >> testcase_results.txt
  echo -e "\n" >> testcase_results.txt
done