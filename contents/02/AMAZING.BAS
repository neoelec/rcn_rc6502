SCR
LOMEM=768
HIMEM=16384
10 TAB (28): PRINT "AMAZING PROGRAM"
20 TAB (15): PRINT "CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY"
25 REM PORTED TO REPLICA/1 BY CARL CLAUNCH
30 PRINT : PRINT : PRINT : PRINT
100 INPUT "WHAT ARE YOUR WIDTH AND LENGTH",H,V
102 IF H#1 AND V#1 THEN 110
104 PRINT "MEANINGLESS DIMENSIONS. TRY AGAIN.": GOTO 100
110 DIM W(H*V),U(H*V)
115 FOR I=1 TO H*V:W(I)=0:U(I)=0: NEXT I
120 PRINT
130 PRINT
140 PRINT
150 PRINT
160 Q=0:Z=0:X= RND (H)+1
165 FOR I=1 TO H
170 IF I=X THEN 173
171 PRINT ".--";: GOTO 180
173 PRINT ".  ";
180 NEXT I
190 PRINT "."
195 C=1:W((X-1)*V+1)=C:C=C+1
200 R=X:S=1: GOTO 260
210 IF R#H THEN 240
215 IF S#V THEN 230
220 R=1:S=1: GOTO 250
230 R=1:S=S+1: GOTO 250
240 R=R+1
250 IF W((R-1)*V+S)=0 THEN 210
260 IF R-1=0 THEN 530
265 IF W((R-2)*V+S)#0 THEN 530
270 IF S-1=0 THEN 390
280 IF W((R-1)*V+S-1)#0 THEN 390
290 IF R=H THEN 330
300 IF W(R*V+S)#0 THEN 330
310 X= RND (3)+1
320 GOTO 320+X
321 GOTO 790
322 GOTO 820
323 GOTO 860
330 IF S#V THEN 340
334 IF Z=1 THEN 370
338 Q=1: GOTO 350
340 IF W((R-1)*V+S+1)#0 THEN 370
350 X= RND (3)+1
360 GOTO 360+X
361 GOTO 790
362 GOTO 820
363 GOTO 910
370 X= RND (2)+1
380 GOTO 380+X
381 GOTO 790
382 GOTO 820
390 IF R=H THEN 470
400 IF W(R*V+S)#0 THEN 470
405 IF S#V THEN 420
410 IF Z=1 THEN 450
415 Q=1: GOTO 430
420 IF W((R-1)*V+S+1)#0 THEN 450
430 X= RND (3)+1
440 GOTO 440+X
441 GOTO 790
442 GOTO 860
443 GOTO 910
450 X= RND (2)+1
460 GOTO 460+X
461 GOTO 790
462 GOTO 860
470 IF S#V THEN 490
480 IF Z=1 THEN 520
485 Q=1: GOTO 500
490 IF W((R-1)*V+S+1)#0 THEN 520
500 X= RND (2)+1
510 GOTO 510+X
511 GOTO 790
512 GOTO 910
520 GOTO 790
530 IF S-1=0 THEN 670
540 IF W((R-1)*V+S-1)#0 THEN 670
545 IF R=H THEN 610
547 IF W(R*V+S)#0 THEN 610
550 IF S#V THEN 560
552 IF Z=1 THEN 590
554 Q=1: GOTO 570
560 IF W((R-1)*V+S+1)#0 THEN 590
570 X= RND (3)+1
580 GOTO 580+X
581 GOTO 820
582 GOTO 860
583 GOTO 910
590 X= RND (2)+1
600 GOTO 600+X
601 GOTO 820
602 GOTO 860
610 IF S#V THEN 630
620 IF Z=1 THEN 660
625 Q=1: GOTO 640
630 IF W((R-1)*V+S+1)#0 THEN 660
640 X= RND (2)+1
650 GOTO 650+X
651 GOTO 820
652 GOTO 910
660 GOTO 820
670 IF R=H THEN 740
680 IF W(R*V+S)#0 THEN 740
685 IF S#V THEN 700
690 IF Z=1 THEN 730
695 Q=1: GOTO 830
700 IF W((R-1)*V+S+1)#0 THEN 730
710 X= RND (2)+1
720 GOTO 720+X
721 GOTO 860
722 GOTO 910
730 GOTO 860
740 IF S#V THEN 760
750 IF Z=1 THEN 780
755 Q=1: GOTO 770
760 IF W((R-1)*V+S+1)#0 THEN 780
770 GOTO 910
780 GOTO 1000
790 W((R-2)*V+S)=C
800 C=C+1:U((R-2)*V+S)=2:R=R-1
810 IF C=H*V+1 THEN 1010
815 Q=0: GOTO 260
820 W((R-1)*V+S-1)=C
830 C=C+1
840 U((R-1)*V+S-1)=1:S=S-1: IF C=H*V+1 THEN 1010
850 Q=0: GOTO 260
860 W(R*V+S)=C
870 C=C+1: IF U((R-1)*V+S)=0 THEN 880
875 U((R-1)*V+S)=3: GOTO 890
880 U((R-1)*V+S)=2
890 R=R+1
900 IF C=H*V+1 THEN 1010
905 GOTO 530
910 IF Q=1 THEN 960
920 W((R-1)*V+S+1)=C:C=C+1: IF U((R-1)*V+S)=0 THEN 940
930 U((R-1)*V+S)=3: GOTO 950
940 U((R-1)*V+S)=1
950 S=S+1: IF C=H*V+1 THEN 1010
955 GOTO 260
960 Z=1
970 IF U((R-1)*V+S)=0 THEN 980
975 U((R-1)*V+S)=3:Q=0: GOTO 1000
980 U((R-1)*V+S)=1:Q=0:S=1:R=1: GOTO 250
1000 GOTO 210
1010 FOR J=1 TO V
1011 PRINT "I";
1012 FOR I=1 TO H
1013 IF U((I-1)*V+J)<2 THEN 1030
1020 PRINT "   ";
1021 GOTO 1040
1030 PRINT "  I";
1040 NEXT I
1041 PRINT
1043 FOR I=1 TO H
1045 IF U((I-1)*V+J)=0 THEN 1060
1050 IF U((I-1)*V+J)=2 THEN 1060
1051 PRINT ":  ";
1052 GOTO 1070
1060 PRINT ":--";
1070 NEXT I
1071 PRINT "."
1072 NEXT J
1073 END
