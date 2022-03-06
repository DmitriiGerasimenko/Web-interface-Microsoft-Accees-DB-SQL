SELECT 
t01.����, 
t01.�����, 
t01.�������� AS [*1]

FROM <#TABLE_NAME1> t01

WHERE 

(t01.���� + t01.�����) BETWEEN 
(#<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># + #<#FROM_HOUR>.<#FROM_MINUTE>#) 
AND 
(#<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR># + #<#TO_HOUR>.<#TO_MINUTE>#)


ORDER BY t01.���� ASC, t01.����� ASC
;


