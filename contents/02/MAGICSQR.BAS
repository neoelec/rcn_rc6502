SCR
10 REM MAGIC SQUARES, WORKS ON PRIME NUMBERS LARGER THAN 3, THE SIZE OF THE SQUARE THAT IS
20 PRINT
30 PRINT "MAGIC SQUARES BY BAMSE."
40 PRINT "THE REPLICA 1 WILL NOW GENERATE A 7X7 SQUARE."
50 PRINT "THE SUM OF ROWS/COLS/DIAGONAL WILL BE 175."
60 PRINT "DRUMROLL PLEASE..."
70 DIM S(49): REM THE MAGIC SQUARE
80 DIM R(7): REM THE WORKING ROW
90 DIM T(7): REM TEMPORARY ROW
100 FOR I=1 TO 7: REM CLEAR THE WORKING ROW BY SETTING ALL VALUES TO 0
110 R(I)=0
120 NEXT I
130 R(1)= RND (7)+1: REM GENERATE 1 TO 7 IN THE WORKING ROW IN A RANDOM ORDER
140 FOR I=2 TO 7
150 N= RND (7)+1
160 J=1
170 IF R(J)=N THEN 150
180 J=J+1
190 IF J<I THEN 170
200 R(I)=N
210 NEXT I: REM DONE, WE NOW HAVE 1-7 IN A RANDOM ORDER IN THE WORK ROW
220 FOR J=1 TO 7
230 FOR I=1 TO 7
240 S(I+(J-1)*7)=(R(I)-1)+(R(8-I)-1)*7+1: REM CALUCALTE MAGIC NUMBER WITH A SECRET FORMULA
250 NEXT I
260 GOSUB 1000: REM ROTATE WORKING ROW
270 NEXT J
280 PRINT : REM MAGIC SQUARE DONE, LET'S PRINT IT
290 FOR J=1 TO 7
300 PRINT "************************************"
310 PRINT "*";
320 FOR I=1 TO 7
330 PRINT " ";
340 IF S(I+(J-1)*7)<10 THEN PRINT " ";: REM PRINT EXTRA SPACE IF NUMBER IS 1-9.
350 PRINT S(I+(J-1)*7);" *";: REM PRINT MAGIC NUMBER
360 NEXT I
370 PRINT
380 NEXT J
390 PRINT "************************************"
400 PRINT
410 PRINT "DONE, BRING ON THE CALCULATORS."
420 END
1000 Q=3: REM ROTATE THE WORKING ROW TWO STEPS, 1234567 WOULD BE 3456712
1010 FOR I=1 TO 7
1020 T(I)=R(Q): REM FIRST ROTATE THE TEMPORARY ROW
1030 Q=Q+1
1040 IF Q>7 THEN Q=1
1050 NEXT I
1060 FOR I=1 TO 7: REM COPY TEMPORARY ROW TO WORK ROW
1070 R(I)=T(I)
1080 NEXT I
1090 RETURN
