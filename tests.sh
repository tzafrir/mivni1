#!/bin/bash
for i in {1..5}; do
./main1 < test$i.txt > my$i.txt
echo diff $i:
diff my$i.txt result$i.txt
done

