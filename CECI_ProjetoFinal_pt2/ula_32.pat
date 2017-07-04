
-- description generated by Pat driver

--			date     : Thu Jun  9 01:57:51 2016
--			revision : v109

--			sequence : ula_32

-- input / output list :
in       op (2 downto 0) B;;;
in       srca (31 downto 0) X;;;
in       srcb (31 downto 0) X;;;
out      aluresult (31 downto 0) X;;;
out      ovfl B;;;
out      zero B;;;
in       vdd B;;;
in       vss B;;;

begin

-- Pattern description :

--                                o    s         s          a          o   z  v  v   
--                                p    r         r          l          v   e  d  s   
--                                     c         c          u          f   r  d  s   
--                                     a         b          r          l   o         
--                                                          e                        
--                                                          s                        
--                                                          u                        
--                                                          l                        
--                                                          t                        


-- Beware : unprocessed patterns

<          0 ps>ADD_0           : 010  00000000  00000000  ?00000000  ?0  ?1  1  0  ;
<          1 ps>                : 010  00000000  7fffffff  ?7fffffff  ?0  ?0  1  0  ;
<          2 ps>                : 010  7fffffff  00000000  ?7fffffff  ?0  ?0  1  0  ;
<          3 ps>                : 010  7ffffffe  00000001  ?7fffffff  ?0  ?0  1  0  ;
<          4 ps>                : 010  7fffffff  7fffffff  ?fffffffe  ?1  ?0  1  0  ;
<          5 ps>                : 010  8fffffff  00000001  ?90000000  ?0  ?0  1  0  ;
<          6 ps>                : 010  8fffffff  8fffffff  ?1ffffffe  ?1  ?0  1  0  ;
<          7 ps>                : 010  ffffffff  7fffffff  ?7ffffffe  ?0  ?0  1  0  ;
<          8 ps>SUB_8           : 110  00000000  00000000  ?00000000  ?0  ?1  1  0  ;
<          9 ps>                : 110  00000000  7fffffff  ?80000001  ?0  ?0  1  0  ;
<         10 ps>                : 110  7fffffff  00000000  ?7fffffff  ?0  ?0  1  0  ;
<         11 ps>                : 110  7ffffffe  00000001  ?7ffffffd  ?0  ?0  1  0  ;
<         12 ps>                : 110  7fffffff  7fffffff  ?00000000  ?0  ?1  1  0  ;
<         13 ps>                : 110  8fffffff  00000001  ?8ffffffe  ?0  ?0  1  0  ;
<         14 ps>                : 110  8fffffff  8fffffff  ?00000000  ?0  ?1  1  0  ;
<         15 ps>                : 110  ffffffff  7fffffff  ?80000000  ?0  ?0  1  0  ;
<         16 ps>SLT_16          : 111  00000000  00000000  ?00000000  ?0  ?1  1  0  ;
<         17 ps>                : 111  00000000  7fffffff  ?00000001  ?0  ?0  1  0  ;
<         18 ps>                : 111  7fffffff  00000000  ?00000000  ?0  ?1  1  0  ;
<         19 ps>                : 111  7ffffffe  00000001  ?00000000  ?0  ?1  1  0  ;
<         20 ps>                : 111  7fffffff  7fffffff  ?00000000  ?0  ?1  1  0  ;
<         21 ps>                : 111  8fffffff  00000001  ?00000001  ?1  ?0  1  0  ;
<         22 ps>                : 111  8fffffff  8fffffff  ?00000000  ?0  ?1  1  0  ;
<         23 ps>                : 111  ffffffff  7fffffff  ?00000001  ?1  ?0  1  0  ;
<         24 ps>AND_24          : 000  00000000  00000000  ?00000000  ?0  ?1  1  0  ;
<         25 ps>                : 000  00000000  ffffffff  ?00000000  ?0  ?1  1  0  ;
<         26 ps>                : 000  ffffffff  00000000  ?00000000  ?0  ?1  1  0  ;
<         27 ps>                : 000  ffffffff  ffffffff  ?ffffffff  ?0  ?0  1  0  ;
<         28 ps>OR_28           : 001  00000000  00000000  ?00000000  ?0  ?1  1  0  ;
<         29 ps>                : 001  00000000  ffffffff  ?ffffffff  ?0  ?0  1  0  ;
<         30 ps>                : 001  ffffffff  00000000  ?ffffffff  ?0  ?0  1  0  ;
<         31 ps>                : 001  ffffffff  ffffffff  ?ffffffff  ?0  ?0  1  0  ;
<         32 ps>SrcANandSrcB_32 : 100  00000000  00000000  ?00000000  ?0  ?1  1  0  ;
<         33 ps>                : 100  00000000  ffffffff  ?00000000  ?0  ?1  1  0  ;
<         34 ps>                : 100  ffffffff  00000000  ?ffffffff  ?0  ?0  1  0  ;
<         35 ps>                : 100  ffffffff  ffffffff  ?00000000  ?1  ?1  1  0  ;
<         36 ps>SrcANorSrcB_36  : 101  00000000  00000000  ?ffffffff  ?1  ?0  1  0  ;
<         37 ps>                : 101  00000000  ffffffff  ?00000000  ?0  ?1  1  0  ;
<         38 ps>                : 101  ffffffff  00000000  ?ffffffff  ?0  ?0  1  0  ;
<         39 ps>                : 101  ffffffff  ffffffff  ?ffffffff  ?0  ?0  1  0  ;

end;
