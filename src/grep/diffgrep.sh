filename1=s21_grep.c;
filename2=s21_grep.h;
filename3=pattern.txt;
echo ----------------------------------------------*GREP 1
diff <(grep int "$filename1" "$filename2") <(./s21_grep int "$filename1" "$filename2") -s -q
echo ----------------------------------------------*GREP 1
diff <(grep -e int "$filename1" "$filename2") <(./s21_grep -e int "$filename1" "$filename2") -s -q
echo ----------------------------------------------*GREP 2
diff <(grep -i int "$filename1") <(./s21_grep -i int "$filename1") -s -q
echo ----------------------------------------------*GREP 3
diff <(grep -v int "$filename1") <(./s21_grep -v int "$filename1") -s -q
echo ----------------------------------------------*GREP 4
diff <(grep -c int "$filename1") <(./s21_grep -c int "$filename1") -s -q
echo ----------------------------------------------*GREP 5
diff <(grep -l int "$filename1" "$filename2") <(./s21_grep -l int "$filename1" "$filename2") -s -q
echo ----------------------------------------------*GREP 6
diff <(grep -n int "$filename1") <(./s21_grep -n int "$filename1") -s -q
echo ----------------------------------------------*GREP 7 BONUS TASK
diff <(grep -h int "$filename1") <(./s21_grep -h int "$filename1") -s -q
echo ----------------------------------------------*GREP 8 BONUS TASK
diff <(grep -o int "$filename1") <(./s21_grep -o int "$filename1") -s -q
echo ----------------------------------------------*GREP 9 BONUS TASK
diff <(grep -h int "$filename2" "$filename1") <(./s21_grep -h int "$filename2" "$filename1") -s -q
echo ----------------------------------------------*GREP 10 BONUS TASK
diff <(grep -s int qwert) <(./s21_grep -s int qwert) -s -q
echo ----------------------------------------------*GREP 11 BONUS TASK
diff <(grep -f "$filename3" "$filename2") <(./s21_grep -f "$filename3" "$filename2") -s -q
echo ----------------------------------------------*GREP 12 BONUS TASK
diff <(grep -in int "$filename1") <(./s21_grep -in int "$filename1") -s -q
echo ----------------------------------------------*GREP 13 BONUS TASK
diff <(grep -cv int "$filename1") <(./s21_grep -cv int "$filename1") -s -q
echo ----------------------------------------------*GREP 14 BONUS TASK
diff <(grep -iv int "$filename1") <(./s21_grep -iv int "$filename1") -s -q
echo ----------------------------------------------*GREP 15 BONUS TASK
diff <(grep -lv int "$filename1" "$filename2" "$filename3") <(./s21_grep -lv int "$filename1" "$filename2" "$filename3") -s -q
echo ----------------------------------------------*GREP 16 BONUS TASK
diff <(grep -ho int "$filename1" "$filename2") <(./s21_grep -ho int "$filename1" "$filename2") -s -q
echo ----------------------------------------------*GREP 17 BONUS TASK
diff <(grep -nf "$filename3" "$filename1") <(./s21_grep -nf "$filename3" "$filename1") -s -q
echo ----------------------------------------------*GREP 18 BONUS TASK
diff <(grep -hv int "$filename1" "$filename2") <(./s21_grep -hv int "$filename1" "$filename2") -s -q
echo ----------------------------------------------*GREP 19 BONUS TASK
diff <(grep -e int -e for -c "$filename1" "$filename2") <(./s21_grep -e int -e for -c "$filename1" "$filename2") -s -q
echo ----------------------------------------------*GREP 20 BONUS TASK
diff <(grep -e for -e while "$filename1" "$filename2" -vnc) <(./s21_grep -e for -e while "$filename1" "$filename2" -vnc) -s -q
echo ----------------------------------------------*Tests ended*
