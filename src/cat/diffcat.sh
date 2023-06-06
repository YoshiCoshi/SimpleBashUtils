filename=test.txt;
echo ----------------------------------------------*CAT 1
diff <(cat -b "$filename") <(./s21_cat -b "$filename") -s -q
echo ----------------------------------------------*CAT 2
diff <(cat -e "$filename") <(./s21_cat -e "$filename") -s -q
echo ----------------------------------------------*CAT 3
diff <(cat -n "$filename") <(./s21_cat -n "$filename") -s -q
echo ----------------------------------------------*CAT 5
diff <(cat -s "$filename") <(./s21_cat -s "$filename") -s -q
echo ----------------------------------------------*CAT 6
diff <(cat -t "$filename") <(./s21_cat -t "$filename") -s -q
echo ----------------------------------------------*CAT 7
diff <(cat "$filename") <(./s21_cat "$filename") -s
echo ----------------------------------------------*CAT 8
diff <(cat -tv "$filename") <(./s21_cat -tv "$filename") -s -q
echo ----------------------------------------------*CAT 9
diff <(cat -ev "$filename") <(./s21_cat -ev "$filename") -s -q
echo ----------------------------------------------*CAT 10
diff <(cat -b -e -n -s -t -v "$filename") <(./s21_cat -b -e -n -s -t -v "$filename") -s -q
