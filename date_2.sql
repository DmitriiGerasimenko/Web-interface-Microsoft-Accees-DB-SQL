SELECT 
t01.����, 
t01.�����, 
t01.�������� AS [*1],
t02.�������� AS [*2]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02

WHERE 
(t01.���� BETWEEN #<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># and #<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR>#)


AND (t01.���� = t02.����)

ORDER BY t01.���� ASC
;
