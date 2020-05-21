#!/bin/sh
# Validate input sample
LEX_OUT=$(./lex <test/fixture/input_sample.txt)
EXPECTED='P(0)V(0)N(20)V(1)P(1)P(6)V(0):V(0):=V(0)+N(1):P(5)
V(2)N(2)P(0)(V(0)>N(10))P(1)P(4)V(1):=N(20)
N(2)#V(0)#N(4)N(28)V(0)V(3)

V(0)@N(1):=V(1)+V(0):P(2)$N(34)
V(4):=V(5)
V(4):=V(6)&V(7)#P(6)
V(0)$N(1)#P(0)&V(8)@V(9)
V(0)V(10)V(11)V(10)V(0)'

[ "$LEX_OUT" = "$EXPECTED" ] && exit 0
exit 1
