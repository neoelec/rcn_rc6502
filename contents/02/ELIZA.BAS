SCR
LOMEM=768
HIMEM=16384
5 PRINT "**************************"
10 TAB (6): PRINT "ELIZA"
20 PRINT "CREATIVE COMPUTING"
30 PRINT "MORRISTOWN, NEW JERSEY": PRINT
40 REM PORTED AND REWRITTEN FOR REPLICA 1
45 REM BY VINCE BRIEL AND CARL CLAUNCH
55 PRINT "*************************"
60 PRINT : PRINT : PRINT
100 DIM S(36),R(36),N(36)
105 DIM K$(36),W$(37),O$(27),R$(112),I$(90),X$(155)
106 DIM P$(100)
107 DIM J(14),J$(112)
108 DIM D$(255),D(36),E(36)
109 DIM B$(200)
110 N1=36:V1=14:P$=""
120 GOSUB 5000
160 PRINT "HI! I'M ELIZA. WHAT'S YOUR PROBLEM?"
200 INPUT X$
201 I$=" "
202 I$(2)=X$
203 F= LEN(I$)
204 I$(F+1)="  "
205 F=F+2
210 IF X$="QUIT" THEN 9999
215 X$(F-2)="    "
220 IF X$(1,4)#"SHUT" THEN 255
230 PRINT "IF YOU FEEL THAT WAY, THEN I WILL SHUT UP.": GOTO 9999
255 IF I$#P$ THEN 260
256 PRINT "PLEASE DON'T REPEAT YOURSELF!": GOTO 200
260 M=0:B$="":Q=0:K=36
267 H=0
270 FOR L=1 TO F
275 Y$=I$(L,L)
280 IF Y$#" " THEN 285
281 H=1
282 GOTO 300
285 IF Y$="!" THEN 800
297 GOTO 500
300 IF Q=0 THEN 500
315 A=0
320 FOR X=1 TO V1-1
330 W$=J$(X*8-7,X*8+J(X)-8)
335 O$=J$(X*8+1,X*8+J(X+1))
350 T=J(X)
353 B=T+L-1
355 U=J(X+1)
356 C=U+L-1
357 IF B>F THEN 400
360 IF I$(L,B)#W$ THEN 400
365 B$(M+1)=O$
370 M=M+U
375 L=B
380 X=V1
385 A=1
390 GOTO 470
400 IF C>F THEN 470
410 IF I$(L,C)#O$ THEN 470
420 B$(M+1)=W$
430 M=M+T
440 L=C
450 X=V1
460 A=1
470 X=X+1
475 NEXT X
480 IF A#1 THEN 500
485 A=0
490 GOTO 800
500 IF Y$=" " THEN 790
505 IF H=0 THEN 790
507 H=0
510 IF Q#0 THEN 790
515 GOSUB 4000
520 FOR S=P TO O
530 K$=D$(D(S),E(S))
540 G= LEN(K$)+1
550 K$(G)=" "
560 V=L+G-1
570 IF V+1>F THEN 650
600 IF I$(L,V)#K$ THEN 650
610 L=V-1
615 Y$=" "
620 Q=1
630 K=S
640 S=N1
650 NEXT S
790 IF Q=0 THEN 800
794 M=M+1
795 B$(M)=Y$
800 NEXT L
900 GOSUB 1310+(R(K)*10)
940 R(K)=R(K)+1: IF R(K)>N(K) THEN R(K)=S(K)
950 I= LEN(R$)
960 IF R$(I,I)#"*" THEN 990
965 IF LEN(B$)>=3 THEN 975
970 PRINT "YOU WILL HAVE TO ELABORATE MORE FOR ME TO HELP YOU": GOTO 995
975 IF B$(2,3)="  " THEN 970
980 R$(I)=B$(2)
990 PRINT R$
995 P$=I$: GOTO 200
1320 R$="DON'T YOU BELIEVE THAT I CAN*": RETURN
1330 R$="PERHAPS YOU WOULD LIKE TO BE LIKE ME*": RETURN
1340 R$="YOU WANT ME TO BE ABLE TO*": RETURN
1350 R$="PERHAPS YOU DON'T WANT TO*": RETURN
1360 R$="DO YOU WANT TO BE ABLE TO*": RETURN
1365 R$="DO YOU WANT TO BE ABLE TO*": RETURN
1370 R$="WHAT MAKES YOU THINK I AM*": RETURN
1380 R$="DOES IT PLEASE YOU TO BELIEVE I AM*": RETURN
1390 R$="PERHAPS YOU WOULD LIKE TO BE*": RETURN
1400 R$="DO YOU SOMETIMES WISH YOU WERE*": RETURN
1410 R$="DON'T YOU REALLY*": RETURN
1420 R$="WHY DON'T YOU*": RETURN
1430 R$="DO YOU WISH TO BE ABLE TO*": RETURN
1440 R$="DOES THAT TROUBLE YOU*": RETURN
1450 R$="DO YOU OFTEN FEEL*": RETURN
1460 R$="DO YOU OFTEN FEEL*": RETURN
1470 R$="DO YOU ENJOY FEELING*": RETURN
1480 R$="DO YOU REALLY BELIEVE I DON'T*": RETURN
1490 R$="PERHAPS IN GOOD TIME I WILL*": RETURN
1500 R$="DO YOU WANT ME TO*": RETURN
1510 R$="DO YOU THINK YOU SHOULD BE ABLE TO*": RETURN
1520 R$="WHY CAN'T YOU*": RETURN
1530 R$="WHY ARE YOU INTERESTED IN WHETHER OR NOT I AM*": RETURN
1540 R$="WOULD YOU PREFER IF I WERE NOT*": RETURN
1550 R$="PERHAPS IN YOUR FANTASIES I AM*": RETURN
1560 R$="HOW DO YOU KNOW YOU CAN'T*": RETURN
1570 R$="HAVE YOU TRIED?": RETURN
1580 R$="PERHAPS YOU CAN NOW*": RETURN
1590 R$="DID YOU COME TO ME BECAUSE YOU ARE*": RETURN
1600 R$="HOW LONG HAVE YOU BEEN*": RETURN
1610 R$="DO YOU BELIEVE IT IS NORMAL TO BE*": RETURN
1620 R$="DO YOU ENJOY BEING*": RETURN
1630 R$="WE WERE DISCUSSING YOU--NOT ME.": RETURN
1640 R$="OH, I*": RETURN
1650 R$="YOU'RE NOT REALLY TALKING ABOUT ME, ARE YOU?": RETURN
1660 R$="WHAT WOULD IT MEAN TO YOU IF YOU GOT*": RETURN
1670 R$="WHY DO YOU WANT*": RETURN
1680 R$="SUPPOSE YOU SOON GOT*": RETURN
1690 R$="WHAT IF YOU NEVER GOT*": RETURN
1700 R$="I SOMETIMES ALSO WANT*": RETURN
1710 R$="WHY DO YOU ASK?": RETURN
1720 R$="DOES THAT QUESTION INTEREST YOU?": RETURN
1730 R$="WHAT ANSWER WOULD PLEASE YOU THE MOST?": RETURN
1740 R$="WHAT DO YOU THINK?": RETURN
1750 R$="ARE SUCH QUESTIONS ON YOUR MIND OFTEN?": RETURN
1760 R$="WHAT IS IT THAT YOU REALLY WANT TO KNOW?": RETURN
1770 R$="HAVE YOU ASKED ANYONE ELSE?": RETURN
1780 R$="HAVE YOU ASKED SUCH QUESTIONS BEFORE?": RETURN
1790 R$="WHAT ELSE COMES TO MIND WHEN YOU ASK THAT?": RETURN
1800 R$="NAMES DON'T INTEREST ME.": RETURN
1810 R$="I DON'T CARE ABOUT NAMES --PLEASE GO ON.": RETURN
1820 R$="IS THAT THE REAL REASON?": RETURN
1830 R$="DON'T ANY OTHER REASONS COME TO MIND?": RETURN
1840 R$="DOES THAT REASON EXPLAIN ANYTHING ELSE?": RETURN
1850 R$="WHAT OTHER REASONS MIGHT THERE BE?": RETURN
1860 R$="PLEASE DON'T APOLOGIZE!": RETURN
1870 R$="APOLOGIES ARE NOT NECESSARY.": RETURN
1880 R$="WHAT FEELINGS DO YOU HAVE WHEN YOU APOLOGIZE?": RETURN
1890 R$="DON'T BE SO DEFENSIVE!": RETURN
1900 R$="WHAT DOES THAT DREAM SUGGEST TO YOU?": RETURN
1910 R$="DO YOU DREAM OFTEN?": RETURN
1920 R$="WHAT PERSONS APPEAR IN YOUR DREAMS?": RETURN
1930 R$="ARE YOU DISTURBED BY YOUR DREAMS?": RETURN
1940 R$="HOW DO YOU DO ...PLEASE STATE YOUR PROBLEM.": RETURN
1950 R$="YOU DON'T SEEM QUITE CERTAIN.": RETURN
1960 R$="WHY THE UNCERTAIN TONE?": RETURN
1970 R$="CAN'T YOU BE MORE POSITIVE?": RETURN
1980 R$="YOU AREN'T SURE?": RETURN
1990 R$="DON'T YOU KNOW?": RETURN
2000 R$="ARE YOU SAYING NO JUST TO BE NEGATIVE?": RETURN
2010 R$="YOU ARE BEING A BIT NEGATIVE.": RETURN
2020 R$="WHY NOT?": RETURN
2030 R$="ARE YOU SURE?": RETURN
2040 R$="WHY NO?": RETURN
2050 R$="WHY ARE YOU CONCERNED ABOUT MY*": RETURN
2060 R$="WHAT ABOUT YOUR OWN*": RETURN
2070 R$="CAN YOU THINK OF A SPECIFIC EXAMPLE?": RETURN
2080 R$="WHEN?": RETURN
2090 R$="WHAT ARE YOU THINKING OF?": RETURN
2100 R$="REALLY, ALWAYS?": RETURN
2110 R$="DO YOU REALLY THINK SO?": RETURN
2120 R$="BUT YOU ARE NOT SURE YOU*": RETURN
2130 R$="DO YOU DOUBT YOU*": RETURN
2140 R$="IN WHAT WAY?": RETURN
2150 R$="WHAT RESEMBLANCE DO YOU SEE?": RETURN
2160 R$="WHAT DOES THE SIMILARITY SUGGEST TO YOU?": RETURN
2170 R$="WHAT OTHER CONNECTIONS DO YOU SEE?": RETURN
2180 R$="COULD THERE REALLY BE SOME CONNECTION?": RETURN
2190 R$="HOW?": RETURN
2200 R$="YOU SEEM QUITE POSITIVE.": RETURN
2210 R$="ARE YOU SURE?": RETURN
2220 R$="I SEE.": RETURN
2230 R$="I UNDERSTAND.": RETURN
2240 R$="WHY DO YOU BRING UP THE TOPIC OF FRIENDS?": RETURN
2250 R$="DO YOUR FRIENDS WORRY YOU?": RETURN
2260 R$="DO YOUR FRIENDS PICK ON YOU?": RETURN
2270 R$="ARE YOU SURE YOU HAVE ANY FRIENDS?": RETURN
2280 R$="DO YOU IMPOSE ON YOUR FRIENDS?": RETURN
2290 R$="PERHAPS YOUR LOVE FOR FRIENDS WORRIES YOU.": RETURN
2300 R$="DO COMPUTERS WORRY YOU?": RETURN
2310 R$="ARE YOU TALKING ABOUT ME IN PARTICULAR?": RETURN
2320 R$="ARE YOU FRIGHTENED BY MACHINES?": RETURN
2330 R$="WHY DO YOU MENTION COMPUTERS?": RETURN
2340 R$="WHAT DO YOU THINK MACHINES HAVE TO DO WITH YOUR PROBLEM?": RETURN
2350 R$="DON'T YOU THINK COMPUTERS CAN HELP PEOPLE?": RETURN
2360 R$="WHAT IS IT ABOUT MACHINES THAT WORRIES YOU?": RETURN
2370 R$="SAY, DO YOU HAVE ANY PSYCHOLOGICAL PROBLEMS?": RETURN
2380 R$="WHAT DOES THAT SUGGEST TO YOU?": RETURN
2390 R$="I SEE.": RETURN
2400 R$="I'M NOT SURE I UNDERSTAND YOU FULLY.": RETURN
2410 R$="COME COME ELUCIDATE YOUR THOUGHTS.": RETURN
2420 R$="CAN YOU ELABORATE ON THAT?": RETURN
2430 R$="THAT IS QUITE INTERESTING.": RETURN
4000 IF Y$#"A" THEN 4030
4010 P=1
4020 O=3
4025 RETURN
4030 IF Y$#"C" THEN 4060
4040 P=4
4050 O=7
4055 RETURN
4060 IF Y$#"D" THEN 4090
4070 P=8
4080 O=8
4085 RETURN
4090 IF Y$#"F" THEN 4120
4100 P=9
4110 O=9
4115 RETURN
4120 IF Y$#"H" THEN 4150
4130 P=10
4140 O=12
4145 RETURN
4150 IF Y$#"I" THEN 4180
4160 P=13
4170 O=18
4175 RETURN
4180 IF Y$#"M" THEN 4210
4190 P=19
4200 O=19
4205 RETURN
4210 IF Y$#"N" THEN 4240
4220 P=20
4230 O=21
4235 RETURN
4240 IF Y$#"S" THEN 4270
4250 P=22
4260 O=22
4265 RETURN
4270 IF Y$#"T" THEN 4300
4280 P=23
4290 O=23
4295 RETURN
4300 IF Y$#"Y" THEN 4330
4310 P=24
4320 O=28
4325 RETURN
4330 P=29
4350 O=35
4355 RETURN
5000 S(1)=76:N(1)=S(1)+3
5001 S(2)=83:N(2)=S(2)+6
5002 S(3)=22:N(3)=S(3)+2
5003 S(4)=1:N(4)=S(4)+2
5004 S(5)=4:N(5)=S(5)+1
5005 S(6)=51:N(6)=S(6)+3
5006 S(7)=99:N(7)=S(7)+1
5007 S(8)=59:N(8)=S(8)+3
5008 S(9)=93:N(9)=S(9)+5
5009 S(10)=63:N(10)=S(10)
5010 S(11)=63:N(12)=S(11)
5011 S(12)=40:N(12)=S(12)+8
5012 S(13)=10:N(13)=S(13)+3
5013 S(14)=14:N(14)=S(14)+2
5014 S(15)=25:N(15)=S(15)+2
5015 S(16)=28:N(16)=S(16)+3
5016 S(17)=28:N(17)=S(17)+3
5017 S(18)=35:N(18)=S(18)+4
5018 S(19)=64:N(19)=S(19)+4
5019 S(20)=49:N(20)=S(20)+1
5020 S(21)=69:N(21)=S(21)+4
5021 S(22)=55:N(22)=S(22)+3
5022 S(23)=80:N(23)=S(23)+2
5023 S(24)=74:N(24)=S(24)+1
5024 S(25)=6:N(25)=S(25)+3
5025 S(26)=90:N(26)=S(26)+2
5026 S(27)=6:N(27)=S(27)+3
5027 S(28)=32:N(28)=S(28)+2
5028 S(29)=40:N(29)=S(29)+8
5029 S(30)=40:N(30)=S(30)+8
5030 S(31)=40:N(31)=S(31)+8
5031 S(32)=40:N(32)=S(32)+8
5032 S(33)=20:N(33)=S(33)+1
5033 S(34)=17:N(34)=S(34)+2
5034 S(35)=40:N(35)=S(35)+8
5035 S(36)=106:N(36)=S(36)+6
5045 FOR X=1 TO 36
5050 R(X)=S(X)
5055 NEXT X
6000 REM LOADS THE CONJUGATE PAIRS INTO A SINGLE STRING
6001 J$=" ARE    ":J(1)=5
6002 J$(9)=" AM     ":J(2)=4
6003 J$(17)=" WERE   ":J(3)=6
6004 J$(25)=" WAS    ":J(4)=5
6005 J$(33)=" YOU    ":J(5)=5
6006 J$(41)=" I      ":J(6)=3
6007 J$(49)=" YOUR   ":J(7)=6
6008 J$(57)=" MY     ":J(8)=4
6009 J$(65)=" I'VE   ":J(9)=6
6010 J$(73)=" YOU'VE ":J(10)=8
6011 J$(81)=" I'M    ":J(11)=5
6012 J$(89)=" YOU'RE ":J(12)=8
6013 J$(97)=" ME     ":J(13)=4
6014 J$(105)=" YOU    ":J(14)=5
7000 D$="": REM PACKS KEYWORDS INTO A STRING
7001 K$="ALWAYS":D(1)= LEN(D$)+1:E(1)=D(1)+ LEN(K$)-1:D$=K$
7002 K$="ALIKE":D(2)= LEN(D$)+1:E(2)=D(2)+ LEN(K$)-1:D$(D(2))=K$
7003 K$="ARE YOU":D(3)= LEN(D$)+1:E(3)=D(3)+ LEN(K$)-1:D$(D(3))=K$
7004 K$="CAN YOU":D(4)= LEN(D$)+1:E(4)=D(4)+ LEN(K$)-1:D$(D(4))=K$
7005 K$="CAN I":D(5)= LEN(D$)+1:E(5)=D(5)+ LEN(K$)-1:D$(D(5))=K$
7006 K$="CAUSE":D(6)= LEN(D$)+1:E(6)=D(6)+ LEN(K$)-1:D$(D(6))=K$
7007 K$="COMPUTER":D(7)= LEN(D$)+1:E(7)=D(7)+ LEN(K$)-1:D$(D(7))=K$
7008 K$="DREAM":D(8)= LEN(D$)+1:E(8)=D(8)+ LEN(K$)-1:D$(D(8))=K$
7009 K$="FRIEND":D(9)= LEN(D$)+1:E(9)=D(9)+ LEN(K$)-1:D$(D(9))=K$
7010 K$="HELLO":D(10)= LEN(D$)+1:E(10)=D(10)+ LEN(K$)-1:D$(D(10))=K$
7011 K$="HI":D(11)= LEN(D$)+1:E(11)=D(11)+ LEN(K$)-1:D$(D(11))=K$
7012 K$="HOW":D(12)= LEN(D$)+1:E(12)=D(12)+ LEN(K$)-1:D$(D(12))=K$
7013 K$="I DON'T":D(13)= LEN(D$)+1:E(13)=D(13)+ LEN(K$)-1:D$(D(13))=K$
7014 K$="I FEEL":D(14)= LEN(D$)+1:E(14)=D(14)+ LEN(K$)-1:D$(D(14))=K$
7015 K$="I CAN'T":D(15)= LEN(D$)+1:E(15)=D(15)+ LEN(K$)-1:D$(D(15))=K$
7016 K$="I AM":D(16)= LEN(D$)+1:E(16)=D(16)+ LEN(K$)-1:D$(D(16))=K$
7017 K$="I'M":D(17)= LEN(D$)+1:E(17)=D(17)+ LEN(K$)-1:D$(D(17))=K$
7018 K$="I WANT":D(18)= LEN(D$)+1:E(18)=D(18)+ LEN(K$)-1:D$(D(18))=K$
7019 K$="MAYBE":D(19)= LEN(D$)+1:E(19)=D(19)+ LEN(K$)-1:D$(D(19))=K$
7020 K$="NAME":D(20)= LEN(D$)+1:E(20)=D(20)+ LEN(K$)-1:D$(D(20))=K$
7021 K$="NO":D(21)= LEN(D$)+1:E(21)=D(21)+ LEN(K$)-1:D$(D(21))=K$
7022 K$="SORRY":D(22)= LEN(D$)+1:E(22)=D(22)+ LEN(K$)-1:D$(D(22))=K$
7023 K$="THINK":D(23)= LEN(D$)+1:E(23)=D(23)+ LEN(K$)-1:D$(D(23))=K$
7024 K$="YOUR":D(24)= LEN(D$)+1:E(24)=D(24)+ LEN(K$)-1:D$(D(24))=K$
7025 K$="YOU ARE":D(25)= LEN(D$)+1:E(25)=D(25)+ LEN(K$)-1:D$(D(25))=K$
7026 K$="YES":D(26)= LEN(D$)+1:E(26)=D(26)+ LEN(K$)-1:D$(D(26))=K$
7027 K$="YOU'RE":D(27)= LEN(D$)+1:E(27)=D(27)+ LEN(K$)-1:D$(D(27))=K$
7028 K$="YOU":D(28)= LEN(D$)+1:E(28)=D(28)+ LEN(K$)-1:D$(D(28))=K$
7029 K$="WHAT":D(29)= LEN(D$)+1:E(29)=D(29)+ LEN(K$)-1:D$(D(29))=K$
7030 K$="WHO":D(30)= LEN(D$)+1:E(30)=D(30)+ LEN(K$)-1:D$(D(30))=K$
7031 K$="WHERE":D(31)= LEN(D$)+1:E(31)=D(31)+ LEN(K$)-1:D$(D(31))=K$
7032 K$="WHEN":D(32)= LEN(D$)+1:E(32)=D(32)+ LEN(K$)-1:D$(D(32))=K$
7033 K$="WHY CAN'T I":D(33)= LEN(D$)+1:E(33)=D(33)+ LEN(K$)-1:D$(D(33))=K$
7034 K$="WHY DON'T YOU":D(34)= LEN(D$)+1:E(34)=D(34)+ LEN(K$)-1:D$(D(34))=K$
7035 K$="WHY":D(35)= LEN(D$)+1:E(35)=D(35)+ LEN(K$)-1:D$(D(35))=K$
7036 K$="NOKEYFOUND":D(36)= LEN(D$)+1:E(36)=D(36)+ LEN(K$)-1:D$(D(36))=K$
7100 RETURN
9999 END
