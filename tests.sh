#!/bin/bash
for i in {1..6}; do
./main1 < tests/test$i.txt > tests/my$i.txt
echo diff $i:
diff tests/my$i.txt tests/result$i.txt
done

