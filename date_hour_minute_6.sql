SELECT 
t01.����, 
t01.�����, 
t01.�������� AS [*1],
t02.�������� AS [*2],
t03.�������� AS [*3],
t04.�������� AS [*4],
t05.�������� AS [*5],
t06.�������� AS [*6]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02, <#TABLE_NAME3> t03, <#TABLE_NAME4> t04, <#TABLE_NAME5> t05, <#TABLE_NAME6> t06

WHERE 

(t01.���� + t01.�����) BETWEEN 
(#<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># + #<#FROM_HOUR>.<#FROM_MINUTE>#) 
AND 
(#<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR># + #<#TO_HOUR>.<#TO_MINUTE>#)


AND ((t01.���� = t02.����) and hour(t01.�����) = hour(t02.�����) and minute(t01.�����) = minute(t02.�����))
AND ((t01.���� = t03.����) and hour(t01.�����) = hour(t03.�����) and minute(t01.�����) = minute(t03.�����))
AND ((t01.���� = t04.����) and hour(t01.�����) = hour(t04.�����) and minute(t01.�����) = minute(t04.�����))
AND ((t01.���� = t05.����) and hour(t01.�����) = hour(t05.�����) and minute(t01.�����) = minute(t05.�����))
AND ((t01.���� = t06.����) and hour(t01.�����) = hour(t06.�����) and minute(t01.�����) = minute(t06.�����))

ORDER BY t01.���� ASC, t01.����� ASC
;


