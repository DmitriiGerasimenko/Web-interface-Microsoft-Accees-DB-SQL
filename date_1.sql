SELECT 
t01.����, 
t01.�����, 
t01.�������� AS [*1]

FROM <#TABLE_NAME1> t01

WHERE 
(t01.���� BETWEEN #<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># and #<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR>#)

ORDER BY t01.���� ASC
;
