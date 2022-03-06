SELECT 
t01.����, 
t01.�����, 
t01.�������� AS [*1],
t02.�������� AS [*2],
t03.�������� AS [*3],
t04.�������� AS [*4],
t05.�������� AS [*5]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02, <#TABLE_NAME3> t03, <#TABLE_NAME4> t04, <#TABLE_NAME5> t05

WHERE 

(t01.���� + t01.�����) BETWEEN 
(#<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># + #<#FROM_HOUR>.<#FROM_MINUTE>#) 
AND 
(#<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR># + #<#TO_HOUR>.<#TO_MINUTE>#)



AND ((t01.���� = t02.����) and (t01.����� = t02.�����))
AND ((t01.���� = t03.����) and (t01.����� = t03.�����))
AND ((t01.���� = t04.����) and (t01.����� = t04.�����))
AND ((t01.���� = t05.����) and (t01.����� = t05.�����))

ORDER BY t01.���� ASC, t01.����� ASC
;


