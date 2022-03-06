SELECT 
t01.����, 
t01.�����, 
t01.�������� AS [*1],
t02.�������� AS [*2]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02

WHERE 

(t01.���� + t01.�����) BETWEEN 
(#<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># + #<#FROM_HOUR>.<#FROM_MINUTE>#) 
AND 
(#<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR># + #<#TO_HOUR>.<#TO_MINUTE>#)


AND ((t01.���� = t02.����) and hour(t01.�����) = hour(t02.�����) and minute(t01.�����) = minute(t02.�����))

ORDER BY t01.���� ASC, t01.����� ASC
;


